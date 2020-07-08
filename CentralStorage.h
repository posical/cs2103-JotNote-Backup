/**
 *  CS2103 Special Semester 1 Main Project 
 *  Project Group C1
 *
 *  Source File Author(s): Ong Wei Xiang & Hassan Ali Askari
 *  File:   CentralStorage.h
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

#ifndef CENTRALSTORAGE_H
#define	CENTRALSTORAGE_H

#include "EventData.h"
#include "ExtractDatabase.h"
#include <vector>
#include <algorithm>
#include "CurrentTime.h"
#include <iomanip>
#include "ErrorMessage.h"
#include "EventType.h"

#define DAYS_ANNOUNCEMENT 3
#define START_OF_DAY 800
#define END_OF_DAY 2200

using namespace std;

class CentralStorage
{
    private:
        vector<EventData> _masterList;
        vector<EventData> _dueEvents, _dueUrgentEvents, _scheduledEvents, _scheduledUrgentEvents ;
        vector<EventData> _doneEvents;
        vector<EventData> _expiredDueEvents, _expiredScheduledEvents;

        vector<EventData> _masterListBackup;


        vector<vector<EventData>*> _allContainers;

        vector<string> _freeTimeSlots;
        vector<EventData> _searchResult;

        vector<EventData>::iterator _it;

        bool isEarlierOrEqual(int _fixedTime, int _fixedDate, int _fixedMonth, int _fixedYear, int _checkTime, int _checkDate, int _checkMonth, int _checkYear);
        bool isLaterOrEqual(int _fixedTime, int _fixedDate, int _fixedMonth, int _fixedYear, int _checkTime, int _checkDate, int _checkMonth, int _checkYear);

    public:
        CentralStorage();
        virtual ~CentralStorage();
        string addEvent(EventData _eventData);
        string removeEventByName(string _taskName);
        string removeEventById(string _eventType, unsigned int Id);
        string modifyEvent(EventData _eventData);
        string markEvent(EventData _eventData);
        string checkForTimingClash (EventData _eventData);

        void findFreeTimeSlots (int _stDate, int _stMonth, int _stYear);
        vector<string> extractFreeTimeSlots ();

        void searchEvent(string _keyword);
        vector<EventData> retrieveSearchResult();

        void keepBackUp ();
        void undo();

        void retrieveDataFromExtractDatabase();
		void transferDataToExtractDatabase();
        void sortDueEventByEndDateEndTime();
		void sortscheduledEventByEndDateEndTime();
		void distDueEventScheduledEvent();
		
        void removeDoneEventFromMasterList();
        void sortDoneEventByEndDateEndTime();
        void sortAllIndividualVector();
        
        void extractExpiredEvents ();
        
        vector<EventData> retrieveMasterList();
        vector<EventData> retrieveDueEvent();
        vector<EventData> retrieveScheduledEvent();
        vector<EventData> retrieveUrgentDueEvent();
        vector<EventData> retrieveUrgentScheduledEvent();
        vector<EventData> retrieveMissedDueEvent();
        vector<EventData> retrieveMissedScheduledEvent();
        vector<EventData> retrieveDoneEvents();

        int retrieveDueUrgentEventNumber();
        int retrieveScheduledUrgentEventNumber();
        int retrieveMissedDueEventNumber();
        int retrieveMissedScheduledEventNumber();

        void mergeEverythingToMasterList();
        string convertStringToUpper(string);
        string convertStringToLower(string);

        void extractAnnouncementEvents();

};

#endif	/* CENTRALSTORAGE_H */


