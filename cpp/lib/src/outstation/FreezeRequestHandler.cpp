/*
 * Copyright 2013-2019 Automatak, LLC
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
 * LLC (www.automatak.com) under one or more contributor license agreements.
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership. Green Energy Corp and Automatak LLC license
 * this file to you under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "outstation/FreezeRequestHandler.h"

#include "gen/objects/Group12.h"
#include "gen/objects/Group41.h"

#include <ser4cpp/serialization/LittleEndian.h>

namespace opendnp3
{

FreezeRequestHandler::FreezeRequestHandler(bool clear, Database& database)
    : clear(clear),
      database(database)
{

}

bool FreezeRequestHandler::IsAllowed(uint32_t headerCount, GroupVariation gv, QualifierCode qc)
{
    if(gv == GroupVariation::Group20Var0 && qc == QualifierCode::ALL_OBJECTS)
        return true;
    
    return false;
}

IINField FreezeRequestHandler::ProcessHeader(const AllObjectsHeader& record)
{
    this->database.SelectAll(GroupVariation::Group20Var0);
    this->database.FreezeSelectedCounters(clear);
    return IINField::Empty();
}

} // namespace opendnp3
