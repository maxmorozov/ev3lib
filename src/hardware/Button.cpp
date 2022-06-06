/*
 * Button.cpp
 */

#include <hardware/Button.h>

namespace ev3lib::hardware {

Button::Button(detail::UIManager* manager, size_t buttonNo)
	: m_manager(manager), m_buttonNo(buttonNo)
{

}


bool Button::isPressed() const {
	return m_manager->checkButton(m_buttonNo);
}



} /* namespace ev3lib::hardware */
