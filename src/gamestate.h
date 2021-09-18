#pragma once
#include "basestate.h"
#include "map.h"

class CGameState : public IBaseState
{
public:
	CGameState() : IBaseState("CGameState")
	{

	}

	virtual void setup();

	virtual void update();

	virtual void draw();

	virtual void release();

	virtual void keyPressed(int key);

	virtual void keyReleased(int key);

	virtual void keyChanged(int key);

	//call CMap::LoadMap and set up the map
	void LoadMap(std::string sMapName);
	//delete the current map
	void UnloadMap();

	friend class CMap;

	CMap* m_pMap;

	int m_iStartNoteY = 0;
	int	m_iHitNoteY = ofGetWindowHeight() - 100;
	int m_iEndNoteY = ofGetWindowHeight();

	float m_flHealth;

	int m_iKeysPressed;
	//current tick of the song
	uint64_t m_iCurrTick;
};

