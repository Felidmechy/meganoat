#include "basestate.h"

IBaseState::IBaseState(const char* sStateName)
{
	m_sStateName = sStateName;
}

void IBaseState::setup()
{

}
void IBaseState::update()
{

}
void IBaseState::draw()
{

}
void IBaseState::release()
{
	delete this;
}

void IBaseState::keyPressed(int key)
{

}
void IBaseState::keyReleased(int key)
{

}
void IBaseState::mouseMoved(int x, int y)
{

}
void IBaseState::mouseDragged(int x, int y, int button)
{

}
void IBaseState::mousePressed(int x, int y, int button)
{

}
void IBaseState::mouseReleased(int x, int y, int button)
{

}
void IBaseState::mouseEntered(int x, int y)
{

}
void IBaseState::mouseExited(int x, int y)
{

}
void IBaseState::windowResized(int w, int h)
{

}
void IBaseState::dragEvent(ofDragInfo dragInfo)
{

}
void IBaseState::gotMessage(ofMessage msg)
{

}