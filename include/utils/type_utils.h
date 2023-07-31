//
// type_utils.h
//

#pragma once

#include <type_traits>

namespace ev3lib::utils {
    /**
     * Checks if the class is derived from another:
     *  class T: public U.
     *
     * @tparam T type to test
     * @tparam U base type to test
     */
    template<class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    /**
     * Checks if the type T is derived from U and does not have deleted move constructor.
     *
     * @tparam T type to test
     * @tparam U base type to test
     */
    template<class T, class U>
    concept DerivedMovable = Derived<T, U> && std::is_move_constructible<T>::value;

    /**
     * Converts a strong typed enum value to its underlying type
     *
     * @tparam E enum type
     * @param e enum value
     * @return integer constant associated with the enum value
     */
    template <typename E>
    constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
        return static_cast<typename std::underlying_type<E>::type>(e);
    }
}