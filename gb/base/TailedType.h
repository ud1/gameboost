#pragma once

namespace gb
{
	namespace base
	{
		
		template <typename Head, typename Tail>
		class TailedType
		{
		public:
			TailedType() {}
			TailedType(const TailedType<Head, Tail> &o) : head(o.head), tail(o.tail) {}
			TailedType(const Head &head, const Tail &tail) : head(head), tail(tail) {}
			
			bool operator < (const TailedType<Head, Tail> &o) const
			{
				return head < o.head;
			}
			
			TailedType<Head, Tail> &operator = (const TailedType<Head, Tail> &o)
			{
				head = o.head;
				tail = o.tail;
				return *this;
			}
			
			Head head;
			Tail tail;
		};
	}
}