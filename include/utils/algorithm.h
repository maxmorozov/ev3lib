//
// algorithm.h
//

#pragma once

#include <span>
#include <algorithm>

namespace ev3lib::utils {

    template<typename SrcElementType, std::size_t SrcExtent, typename DestElementType, std::size_t DestExtent>
    void copy(std::span<SrcElementType, SrcExtent> src, std::span<DestElementType, DestExtent> dest) {
        static_assert(std::is_assignable<decltype(*dest.data()), decltype(*src.data())>::value,
                      "Elements of source span can not be assigned to elements of destination span");
        static_assert(SrcExtent == std::dynamic_extent || DestExtent == std::dynamic_extent ||
                      (SrcExtent <= DestExtent),
                      "Source range is longer than target range");

        if (dest.size() < src.size()) {
            std::terminate();
        }

        std::copy_n(src.data(), src.size(), dest.data());
    }

}