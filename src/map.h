#pragma once
#include "ofMain.h"
#include "gamestate.h"

class CMap;


//an event that can occur in a map
class IMapEvent
{
public:
	//when this event is reached (m_iTime < currenttime)
	virtual void OnReached();
	//the time (in ms) in which the event occurs in the map
	int m_iTime;

	CMap* m_pMap;
};

//an actual key on screen
class CKey
{
public:
	int m_iCreationTime;
	int m_iHitTime;
	int m_iDeletionTime;
	int m_iChannel;

	//speed at which this key should move
	float m_flSpeed;
};

//an event that creates a key
class CKeyEvent : public IMapEvent
{
public:
	virtual void OnReached();

	//the channel this note belongs to
	int m_iChannel;
	//when this note should be hit
	int m_iHitTime;
};

class CSpeedChange : public IMapEvent
{
public:
	virtual void OnReached();

	int m_flSpeed;
};

//helps parse and create keys reading a map
//class CKeyHelper
//{
//public:
//	CKeyHelper(const char* line);
//};

//a map (or level) with notes and events and such
class CMap
{
public:
	CMap();

	//CMap(std::string name, float bpm, int timesig, int channels);

	~CMap();

	//name of the map
	std::string m_cName; 
	//beats per minute, (60 would be a beat every second)
	float m_flBPM;
	//how many beats there are in a measure (usually 4)
	int m_iTimeSig = 4;
	//speed modifier
	float m_flSpeed = 10;
	//current number of channels that notes can appear on
	int m_iChannels = 5;
	//the sound player for the music
	ofSoundPlayer m_Music;
	//a forward list of events (bpm changes, new notes, etc)
	std::forward_list<IMapEvent*> m_Events;
	//number of events in the map left
	int m_iEventsLeft = 0;

	std::list<CKey> m_Keys;

	//a constant for how fast keys move on the screen
	float m_flKeySpeed;
	//the amount of ms the keys should be visually spawned before the hit time
	int m_iCreationOffset = std::max(m_iTimeToHit, 300);
	//the time in ms between creation and hit for notes
	int m_iTimeToHit = 200;
	//the time in ms bwteen creation and end for notes
	int m_iTimeToEnd;


	//TEMP: how long map took to parse
	int m_iParseTime;

	friend class CGameState;

	CGameState* m_pGameState;

	void update();

	//load a map by filename
	//static CMap* LoadMap(std::string sMapName);
	//parse the map
	bool ParseMap(std::string sMapName);
	
};

