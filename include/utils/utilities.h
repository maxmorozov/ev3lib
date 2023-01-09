#pragma once

#include <cstdlib>

namespace ev3lib::utils {

	struct destructible
	{
		virtual ~destructible() = default;
	};

	/**
	 * This class makes descendants not copyable but moveable
	 */
	class noncopyable
	{
	protected:
		noncopyable() = default;
		~noncopyable() = default;

	public:
		//Don't allow to create copies
		noncopyable(const noncopyable &) = delete;
		const noncopyable &operator =(const noncopyable &) = delete;

		noncopyable(noncopyable &&) = default;
		noncopyable &operator =(noncopyable &&) = default;
	};


	template<typename T,size_t size>
	constexpr size_t count_of(T (&)[size]) noexcept { return size; }

}
