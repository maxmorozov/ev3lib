/*
 * Button.h
 */

#ifndef EV3LIB_BUTTON_H_
#define EV3LIB_BUTTON_H_

#include <hardware/detail/UIManager.h>

namespace ev3lib {
namespace hardware {

class Button {
private:
	detail::UIManager* m_manager;
	size_t m_buttonNo;
public:
	Button(detail::UIManager* manager, size_t buttonNo);

	bool isPressed() const;
};

} /* namespace hardware */
} /* namespace ev3lib */

#endif /* EV3LIB_BUTTON_H_ */
