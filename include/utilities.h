#if !defined(__EV3LIB_UTILITIES_H__)
#define __EV3LIB_UTILITIES_H__

#include <stdlib.h>

namespace ev3lib {

	struct destructible
	{
		virtual ~destructible()	{}
	};

	class noncopyable
	{
	protected:
		noncopyable()
		{	}

		//Don't allow to create copies
		noncopyable(const noncopyable &) = delete;
		const noncopyable &operator =(const noncopyable &) = delete;
	};


	template<typename T,size_t size>
	size_t count_of(T (&)[size]) { return size; }
}

#endif // !defined(__EV3LIB_UTILITIES_H__)
