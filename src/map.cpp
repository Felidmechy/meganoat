#include "map.h"
#include "meganoat.h"
#include "failstate.h"

void IMapEvent::OnReached()
{
	m_pMap->m_iEventsLeft--;
	delete this;
}

void CKeyEvent::OnReached()
{
	CKey key;
	key.m_iCreationTime = m_iTime;
	key.m_iHitTime = m_iHitTime;
	key.m_iChannel = m_iChannel;
	key.m_iDeletionTime = key.m_iCreationTime + m_pMap->m_iTimeToEnd;

	key.m_flSpeed = (float)(m_pMap->m_pGameState->m_iHitNoteY) / (m_pMap->m_iTimeToHit);

	m_pMap->m_Keys.emplace_back(key);
	IMapEvent::OnReached();
}

void CSpeedChange::OnReached()
{
	m_pMap->m_flSpeed = m_flSpeed;
	IMapEvent::OnReached();
}


CMap::CMap()
{

}

/*
CMap::CMap(std::string name, float bpm, int timesig, int channels)
{
	m_cName = name;
	m_flBPM = bpm;
	m_iTimeSig = timesig;
	m_iChannels = channels;
}
*/

CMap::~CMap()
{
	for (auto event : m_Events)
	{
		delete event;
	}
}

void CMap::update()
{
	m_flKeySpeed = (float)(m_pGameState->m_iHitNoteY) / ( m_iTimeToHit );
	m_iTimeToEnd = ((m_pGameState->m_iEndNoteY) / m_flKeySpeed);

	while (!m_Keys.empty())
	{
		if (m_Keys.front().m_iDeletionTime > m_pGameState->m_iCurrTick)
		{
			break;
		}
		m_Keys.pop_front();
		m_pGameState->m_flHealth = ofClamp(m_pGameState->m_flHealth - 10, 0, 100);
		if (m_pGameState->m_flHealth - 10 <= 0)
		{
			meganoat::ChangeState(new CFailState);
			break;
		}
	}
}

/*
CMap* CMap::LoadMap(std::string sMapName)
{
	int iLength;

	char* pData = ReadFile(("maps/" + sMapName).c_str(), iLength);
	CMap* pMap = new CMap();

	bool bSuccess = pMap->ParseMap(pData, iLength);

	if (!bSuccess)
	{
		ofLog(OF_LOG_ERROR, "Failed to parse map " + sMapName);
		delete pMap;
		return nullptr;
	}
}
*/

//prepare for some unholy parsing (extreme cruft ahead)
bool CMap::ParseMap(std::string sMapName)
{
	std::ifstream map("maps/" + sMapName, std::ifstream::in);

	map.seekg(0, std::ios::end);

	int length = map.tellg();

	char* filecontents = new char[length + 1];

	filecontents[length] = '\x00';

	map.seekg(0, std::ios::beg);

	map.read(filecontents, length);

	map.close();

	std::string text = filecontents;

	size_t start = text.find("Name = ");
	start += sizeof("Name = ")-1;
	size_t end = text.find('\n', start);

	char* buf = new char[end - start + 1];
	text.copy(buf, end - start, start);

	buf[end - start] = '\x00';
	m_cName = buf;

	delete[] buf;


	start = text.find("[SyncTrack]\n{\n");
	start += sizeof("[SyncTrack]\n{\n") - 1;
	end = text.find("}", start);

	buf = new char[end - start + 1];
	text.copy(buf, end - start, start);

	buf[end - start] = '\x00';


	auto iterator = m_Events.before_begin();

	{
		std::stringstream time;
		std::stringstream speed;
		bool parsingtime = true;
		bool parsingspeed = false;
		bool parsingjunk = false;
		bool skip = false;
		bool skipline = false;
		for (int i = 0; buf[i] != 0; i++)
		{
			if (buf[i] == '\n')
			{
				if (skipline)
				{
					skipline = false;
					parsingtime = true;
					parsingspeed = false;
					parsingjunk = false;
					skip = false;
					time.seekp(std::ios::beg);
					speed.seekp(std::ios::beg);
					continue;
				}
				int finaltime = std::stoi(time.str());
				int finalspeed = std::stof(speed.str());

				time.seekp(std::ios::beg);
				speed.seekp(std::ios::beg);

				CSpeedChange* speedchange = new CSpeedChange();

				speedchange->m_iTime = finaltime;
				speedchange->m_flSpeed = finalspeed;
				speedchange->m_pMap = this;

				iterator = m_Events.insert_after(iterator, speedchange);

				parsingtime = true;
				parsingspeed = false;
				parsingjunk = false;
				skip = false;
				skipline = false;

				m_iEventsLeft++;

				continue;
			}
			if (buf[i] == 'B')
			{
				skipline = true;
				parsingjunk = true;
				parsingtime = false;
				parsingspeed = false;
			}
			if (skip)
			{
				skip = false;
				continue;
			}
			if (parsingjunk)
			{
				continue;
			}
			if (buf[i] == ' ' || buf[i] == '\t')
			{
				if (parsingspeed)
				{
					parsingjunk = true;
					parsingspeed = false;
					parsingtime = false;
				}
				continue;
			}
			if (buf[i] == '=')
			{
				parsingtime = false;
				skip = true;
				continue;
			}
			if (buf[i] == 'T' || buf[i+1] == 'S')
			{
				parsingspeed = true;
				i++;
				skip = true;
				continue;
			}
			if (parsingtime)
			{
				time.put(buf[i]);
				continue;
			}
			if (parsingspeed)
			{
				speed.put(buf[i]);
				continue;
			}

		}
	}

	delete[] buf;


	start = text.find("[ExpertSingle]\n{\n");
	start += sizeof("[ExpertSingle]\n{\n")-1;
	end = text.find('}', start);

	buf = new char[end - start + 1];
	text.copy(buf, end - start, start);

	buf[end - start] = '\x00';


	std::stringstream time;
	std::stringstream channel;
	bool parsingtime = true;
	bool parsingchannel = false;
	bool parsingjunk = false;
	bool skip = false;
	for (int i = 0; buf[i] != 0; i++)
	{
		if (buf[i] == '\n')
		{
			int finaltime = std::stoi(time.str());
			int finalchannel = std::stoi(channel.str());

			time.seekp(std::ios::beg);
			channel.seekp(std::ios::beg);

			if (finalchannel > 3)
			{
				parsingtime = true;
				parsingchannel = false;
				parsingjunk = false;
				skip = false;
				continue;
			}

			CKeyEvent* key = new CKeyEvent();

			key->m_iTime = finaltime - m_iTimeToHit;
			key->m_iHitTime = finaltime;
			key->m_iChannel = finalchannel;
			key->m_pMap = this;

			iterator = m_Events.insert_after(iterator, key);

			parsingtime = true;
			parsingchannel = false;
			parsingjunk = false;
			skip = false;

			m_iEventsLeft++;

			continue;
		}
		if (skip)
		{
			skip = false;
			continue;
		}
		if (parsingjunk)
		{
			continue;
		}
		if (buf[i] == ' ' || buf[i] == '\t')
		{
			if (parsingchannel)
			{
				parsingjunk = true;
				parsingchannel = false;
				parsingtime = false;
			}
			continue;
		}
		if (buf[i] == '=')
		{
			parsingtime = false;
			skip = true;
			continue;
		}
		if (buf[i] == 'N')
		{
			parsingchannel = true;
			skip = true;
			continue;
		}
		if (parsingtime)
		{
			time.put(buf[i]);
			continue;
		}
		if (parsingchannel)
		{
			channel.put(buf[i]);
			continue;
		}
	}
	

	delete[] buf;


	
	/*
	auto iterator = m_Events.before_begin();

	for (int i = 0; i < 22; i++)
	{
		CKey key;
		std::string keydata = kv["[ExpertSingle]"][i].value.string;

		std::stringstream time;
		std::stringstream channel;
		
		bool parsingtime = true;
		bool parsingchannel = false;
		bool skip = false;
		for (auto character : keydata)
		{
			if (skip)
			{
				skip = false;
				continue;
			}
			if (character == ' ' || character == '\t')
			{
				if (parsingchannel)
				{
					break;
				}
				continue;
			}
			if (character == '=')
			{
				parsingtime = false;
				skip = true;
				continue;
			}
			if (character == 'N')
			{
				parsingchannel = true;
				continue;
			}
			if (parsingtime)
			{
				time.putback(character);
				continue;
			}
			if (parsingchannel)
			{
				channel.putback(character);
				continue;
			}
		}

		int finaltime = std::stoi(time.str());
		int finalchannel = std::stoi(channel.str());

		key.m_iTime = finaltime;
		key.m_iChannel = finalchannel;

		iterator = m_Events.insert_after(iterator, key);
	}
	*/

	delete[] filecontents;

	return true;
}