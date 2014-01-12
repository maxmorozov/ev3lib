#if !defined(__EV3LIB_UTILITIES_H__)
#define __EV3LIB_UTILITIES_H__

namespace ev3lib {
namespace hardware {
namespace detail {

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

}}}

#endif // !defined(__EV3LIB_UTILITIES_H__)
