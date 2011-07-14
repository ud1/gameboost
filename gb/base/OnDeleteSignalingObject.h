#pragma once

#include <boost/function.hpp>
#include <vector>
#include <cassert>

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
				if (!unused_signal_ids.empty())
				{
					SignalId result = unused_signal_ids.back();
					signals[result] = signal;
					unused_signal_ids.pop_back();
					return result;
				}
				
				SignalId result = signals.size();
				signals.push_back(signal);
				return result;
			}
			
			void removeSignal(SignalId id)
			{
				assert(signals.size() > id);
				
				if (signals[id])
				{
					signals[id] = Signal();
					unused_signal_ids.push_back(id);
				}
			}
			
		private:
			typedef std::vector<Signal> Signals;
			Signals signals;
			typedef std::vector<SignalId> UnusedSignalIds;
			UnusedSignalIds unused_signal_ids;
		};
		
	}
}
