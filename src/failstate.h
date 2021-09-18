#include "basestate.h"

class CFailState : public IBaseState
{
public:
	CFailState() : IBaseState("CFailState")
	{

	}

	virtual void setup();

	virtual void update();

	virtual void draw();

	virtual void release();

	ofSoundPlayer m_FailSound;

	ofImage m_FailImage;

	int m_iEndTime;

};