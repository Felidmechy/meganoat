#include "failstate.h"
#include "meganoat.h"



void CFailState::setup()
{
	m_FailSound.load("sounds/fail.ogg", true);
	m_FailSound.play();

	m_FailImage.load("sprites/fail.png");

	//buzzer sound is about 1.15 seconds long or 1150 ms
	m_iEndTime = ofGetSystemTimeMillis() + 1150;
}


void CFailState::update()
{
	if (ofGetSystemTimeMillis() > m_iEndTime)
	{
		//lol
		exit(1);
	}
}


void CFailState::draw()
{
	ofBackground(ofColor::black);

	m_FailImage.draw(glm::vec2(ofGetWidth() / 2 - 60, ofGetHeight() / 2));
}


void CFailState::release()
{

	IBaseState::release();
}