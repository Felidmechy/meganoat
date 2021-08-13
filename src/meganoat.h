#pragma once

#include "ofMain.h"
#include "basestate.h"


class meganoat : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//the current state of the game
		IBaseState* m_pState = nullptr;

		//change the state, automatically handles deleting old state
		static void ChangeState(IBaseState* pNewState);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

extern meganoat* g_pmeganoat;