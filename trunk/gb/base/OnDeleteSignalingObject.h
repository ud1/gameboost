#pragma once

#include <boost/function.hpp>
#include <vector>

namespace gb
{
	namespace base
	{

		class OnDeleteSignalingObject
		{
		public:
			typedef boost::function<void ()> Signal;
			typedef size_t SignalId;
			
			~OnDeleteSignalingObject()
			{
				for (Signals::iterator it = signals.begin(); it != signals.end(); ++it)
				{
					if (*it)
					{
						(*it)();
					}
				}
			}
			
			SignalId addSignal(Signal signal)
			{
				SignalId result = signals.size();
				signals.push_back(signal);
				return result;
			}
			
			void removeSignal(SignalId id)
			{
				signals[id] = Signal();
			}
			
		private:
			typedef std::vector<Signal> Signals;
			Signals signals;
		};
		
	}
}
