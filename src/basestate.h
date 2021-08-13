#include "ofMain.h"
#pragma once

//base state (like a screen such as main menu, game screen, options, etc) 
class IBaseState
{
public:

	IBaseState(const char* sStateName);

	const char* m_sStateName;

	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void release();

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mouseDragged(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);
	virtual void mouseEntered(int x, int y);
	virtual void mouseExited(int x, int y);
	virtual void windowResized(int w, int h);
	virtual void dragEvent(ofDragInfo dragInfo);
	virtual void gotMessage(ofMessage msg);
};

