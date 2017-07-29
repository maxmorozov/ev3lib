#pragma once

#include <cstdio>
#include <stdexcept>

namespace ev3lib {
    class str_const {
    private:
        const char *const m_value;
        const std::size_t m_size;
    public:
        template<std::size_t N>
        constexpr explicit str_const(const char (&a)[N]) : m_value(a), m_size(N - 1) {}

        constexpr char operator[] (std::size_t n) const {
            return n < m_size ? m_value[n] :
                   throw std::out_of_range("");
        }

        constexpr std::size_t size() const { return m_size; }
        constexpr const char* value() const { return m_value; }
    };

}