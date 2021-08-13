#include "gamestate.h"
#include "meganoat.h"

void CGameState::setup()
{
	ofResetElapsedTimeCounter();

	m_pMap = new CMap();
	m_pMap->m_pGameState = this;

	uint64_t beforeparse = ofGetSystemTimeMillis();
	m_pMap->ParseMap("notes(1).chart");
	uint64_t afterparse = ofGetSystemTimeMillis();

	m_pMap->m_iParseTime = afterparse - beforeparse;


	m_pMap->m_Music.load("../maps/song(1).ogg", true);
	m_pMap->m_Music.play();
}

void CGameState::update()
{
	m_iCurrTick = ofGetElapsedTimeMillis() * (m_pMap->m_flSpeed / 10);
	m_pMap->update();
	while (!m_pMap->m_Events.empty())
	{
		if (m_pMap->m_Events.front()->m_iTime > m_iCurrTick)
		{
			break;
		}
		m_pMap->m_Events.front()->OnReached();
		m_pMap->m_Events.pop_front();
	}
}

void CGameState::draw()
{
	ofBackground(ofColor::black);

	ofSetColor(ofColor::white);
	float flCurrentHeight = 0;
	ofDrawBitmapString(ofToString(m_iCurrTick) + " MS", glm::vec2(10, flCurrentHeight += 20));
	ofDrawBitmapString(ofToString(ofGetFrameRate()) + " FPS", glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString(m_sStateName, glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString(m_pMap->m_cName, glm::vec2(10, flCurrentHeight += 30));
	ofDrawBitmapString("Events Remaining: " + ofToString(m_pMap->m_iEventsLeft), glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("Next Event: " + ofToString(m_pMap->m_Events.front()->m_iTime) + " MS", glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("Keys Active: " + ofToString(m_pMap->m_Keys.size()), glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("Speed: " + ofToString(m_pMap->m_flSpeed) + "/10", glm::vec2(10, flCurrentHeight += 15));
	//ofDrawBitmapString("KeySpeed: " + ofToString(m_pMap->m_flKeySpeed), glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("Parse Time: " + ofToString(m_pMap->m_iParseTime) + " MS", glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("CreationOffset: " + ofToString(m_pMap->m_iCreationOffset), glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("TimeToHit: " + ofToString(m_pMap->m_iTimeToHit), glm::vec2(10, flCurrentHeight += 15));
	ofDrawBitmapString("TimeToEnd: " + ofToString(m_pMap->m_iTimeToEnd), glm::vec2(10, flCurrentHeight += 15));



	for (auto key : m_pMap->m_Keys)
	{
		//float flFrac = (m_iCurrTick - key.m_iCreationTime) / ((key.m_iHitTime - key.m_iCreationTime));
		//float flSpeed = (float)((ofGetWindowHeight() - 100) ) / (key.m_iHitTime - key.m_iCreationTime);
		//float t = (float)(((ofGetWindowHeight() - 100) - 0) / flSpeed);

		int y = ofMap(m_iCurrTick, key.m_iCreationTime, key.m_iDeletionTime, m_iStartNoteY, m_iEndNoteY, true);
		//int offset = y - key.m_flSpeed * m_pMap->m_iTimeToEnd;

		int ycoord = y;
		int xcoord = key.m_iChannel * 50 + 200;

		ofSetColor(ofColor::white);
		ofDrawCircle(glm::vec2(xcoord, ycoord), 25.0f);
		ofSetColor(ofColor::black);
		ofDrawCircle(glm::vec2(xcoord, ycoord), 2.0f);
		ofDrawBitmapString(ofToString(key.m_iChannel), glm::vec2(xcoord, ycoord));
	}

	ofSetColor(ofColor::white);
	ofDrawRectangle(0, ofGetWindowHeight() - 98, ofGetWindowWidth(), 3);

}

void CGameState::release()
{
	delete m_pMap;
}

void CGameState::LoadMap(std::string sMapName)
{

}

void CGameState::UnloadMap()
{

}