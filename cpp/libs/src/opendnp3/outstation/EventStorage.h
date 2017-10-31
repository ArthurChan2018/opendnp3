/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef OPENDNP3_EVENTSTORAGE_H
#define OPENDNP3_EVENTSTORAGE_H

#include "opendnp3/outstation/Event.h"
#include "opendnp3/outstation/IEventWriteHandler.h"
#include "opendnp3/outstation/EventLists.h"

#include <limits>

namespace opendnp3
{

/*
	Data-stucture for holding events.

	* Only performs dynamic allocation at initialization
	* Maintains distinct lists for each type of event to optimize memory usage
*/

class EventStorage
{

public:

	explicit EventStorage(const EventBufferConfig& config);

	// write selected events to some handler

	uint32_t Write(IEventWriteHandler& handler);

	// ---- these functions return true if an overflow occurs ----

	bool Update(const Event<BinarySpec>& evt);
	bool Update(const Event<DoubleBitBinarySpec>& evt);
	bool Update(const Event<AnalogSpec>& evt);
	bool Update(const Event<CounterSpec>& evt);
	bool Update(const Event<FrozenCounterSpec>& evt);
	bool Update(const Event<BinaryOutputStatusSpec>& evt);
	bool Update(const Event<AnalogOutputStatusSpec>& evt);

	// ---- function used to select distinct types ----

	uint32_t SelectByType(EventBinaryVariation variation, uint32_t max);
	uint32_t SelectByType(EventDoubleBinaryVariation variation, uint32_t max);
	uint32_t SelectByType(EventAnalogVariation variation, uint32_t max);
	uint32_t SelectByType(EventCounterVariation variation, uint32_t max);
	uint32_t SelectByType(EventFrozenCounterVariation variation, uint32_t max);
	uint32_t SelectByType(EventBinaryOutputStatusVariation variation, uint32_t max);
	uint32_t SelectByType(EventAnalogOutputStatusVariation variation, uint32_t max);

	// ---- function used to select by event class ----

	uint32_t SelectByClass(EventClass clazz, uint32_t max);

	inline uint32_t SelectByClass(EventClass clazz)
	{
		return SelectByClass(clazz, std::numeric_limits<uint32_t>::max());
	}

private:

	EventLists state;

	typedef openpal::LinkedListIterator<EventRecord> event_iterator_t;

};

}

#endif

