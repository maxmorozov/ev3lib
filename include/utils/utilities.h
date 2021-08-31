#if !defined(__EV3LIB_UTILITIES_H__)
#define __EV3LIB_UTILITIES_H__

#include <cstdlib>
#include <gsl/span>

namespace ev3lib {

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
	constexpr size_t count_of(T (&)[size]) { return size; }

	//Helper function to convert span::size to size_t type
	template <typename T, size_t Extent>
	constexpr size_t size(const gsl::span<T, Extent>& span) {
		return static_cast<size_t>(span.size());
	};
}

#endif // !defined(__EV3LIB_UTILITIES_H__)
