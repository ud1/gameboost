#pragma once

#include <cassert>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>

namespace gb
{
	namespace t
	{
		
		namespace detail
		{
			template <bool is_pointer>
			struct debug_cast_impl;

			template <>
			struct debug_cast_impl<true>
			{
				template <typename Result, typename Source>
				static Result cast (Source *in_source)
				{
					assert (static_cast <Result> (in_source) == dynamic_cast <Result> (in_source));
					return static_cast <Result> (in_source);
				}
			};
			
			template <>
			struct debug_cast_impl<false>
			{
				template <typename Result, typename Source>
				static Result cast (Source &in_source)
				{
					#ifdef DEBUG
					try
					{
						assert (&static_cast<Result>(in_source) == &dynamic_cast<Result>(in_source));
					}
					catch (...)
					{
						assert(0 && "Cast error");
					}
					#endif
					return static_cast<Result>(in_source);
				}
			};
		}

		template <typename Result, typename Source>
		inline Result debug_cast (Source &in_source)
		{
			return detail::debug_cast_impl <
				boost::is_pointer<Source>::value
			>::template cast<Result, typename boost::remove_pointer<Source>::type>(in_source);
		}
		
	}
}

