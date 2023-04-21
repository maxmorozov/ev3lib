/*
 * Button.h
 */

#pragma once

#include <hardware/detail/UIManager.h>

namespace ev3lib::hardware {

class Button {
private:
	detail::UIManager* m_manager;
	size_t m_buttonNo;
public:
	Button(detail::UIManager* manager, size_t buttonNo);

	bool isPressed() const;
};

} /* namespace ev3lib */
