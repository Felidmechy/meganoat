#include "meganoat.h"
#include "gamestate.h"

//--------------------------------------------------------------
void meganoat::setup()
{
	meganoat::ChangeState(new CGameState);
}

//--------------------------------------------------------------
void meganoat::update()
{
	m_pState->update();
}

//--------------------------------------------------------------
void meganoat::draw()
{
	m_pState->draw();
}

void meganoat::ChangeState(IBaseState* pNewState)
{
	if (g_pmeganoat->m_pState)
	{
		g_pmeganoat->m_pState->release();
		ofLog(OF_LOG_NOTICE, "Changing State from %s to %s", g_pmeganoat->m_pState->m_sStateName, pNewState->m_sStateName);
	}
	else
	{
		ofLog(OF_LOG_NOTICE, "Changing Initial State to %s", pNewState->m_sStateName);
	}

	g_pmeganoat->m_pState = pNewState;
	g_pmeganoat->m_pState->setup();
}

//--------------------------------------------------------------
void meganoat::keyPressed(int key)
{
	m_pState->keyPressed(key);
}

//--------------------------------------------------------------
void meganoat::keyReleased(int key)
{
	m_pState->keyReleased(key);
}

//--------------------------------------------------------------
void meganoat::mouseMoved(int x, int y )
{
	m_pState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void meganoat::mouseDragged(int x, int y, int button)
{
	m_pState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void meganoat::mousePressed(int x, int y, int button)
{
	m_pState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void meganoat::mouseReleased(int x, int y, int button)
{
	m_pState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void meganoat::mouseEntered(int x, int y)
{
	m_pState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void meganoat::mouseExited(int x, int y)
{
	m_pState->mouseExited(x, y);
}

//--------------------------------------------------------------
void meganoat::windowResized(int w, int h)
{
	m_pState->windowResized(w, h);
}

//--------------------------------------------------------------
void meganoat::gotMessage(ofMessage msg)
{
	m_pState->gotMessage(msg);
}

//--------------------------------------------------------------
void meganoat::dragEvent(ofDragInfo dragInfo)
{
	m_pState->dragEvent(dragInfo);
}
