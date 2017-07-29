#if !defined(__EV3LIB_UTILITIES_H__)
#define __EV3LIB_UTILITIES_H__

#include <cstdlib>

namespace ev3lib {

	struct destructible
	{
		virtual ~destructible() = default;
	};

	class noncopyable
	{
	protected:
		noncopyable() = default;

	public:
		//Don't allow to create copies
		noncopyable(const noncopyable &) = delete;
		const noncopyable &operator =(const noncopyable &) = delete;
	};


	template<typename T,size_t size>
	constexpr size_t count_of(T (&)[size]) { return size; }
}

#endif // !defined(__EV3LIB_UTILITIES_H__)
