/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan & Ong Wei Xiang & Hassan Ali Askari
 *  File:   EventList.h
 *
 *
 * Copyright (c) 2012, AY11/12 Special Term 1 CS2103 Group C1. All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither our names nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef EVENTLIST_H
#define	EVENTLIST_H

#include <string>
#include <vector>
#include <sstream>
#include "EventData.h"
#include "CentralStorage.h"
#include "EventType.h"

using namespace std;

class EventList
{
    private:
        vector<string> _formattedScheduledEvents, _formattedUrgentScheduledEvents;
        vector<string> _formattedDueEvents, _formattedUrgentDueEvents;
        vector<string> _formattedMissedDueEvents, _formattedMissedScheduledEvents;
        vector<string> _dynamicWindowString;

    public:
        EventList();
        virtual ~EventList();

        void formatString(vector<EventData> &_incoming, int _stId, int _eventType);

        vector<string> retrieveDueList();
        vector<string> retrieveScheduleList();
        vector<string> retrieveUrgentDueList();
        vector<string> retrieveUrgentScheduleList();
        vector<string> retrieveExpiredDueList ();
        vector<string> retrieveExpiredScheduledList ();

        void formatForDynamicWindow(vector<EventData> &_incoming);
        vector<string> retrieveDynamicWindowString();

};

#endif	/* EVENTLIST_H */

