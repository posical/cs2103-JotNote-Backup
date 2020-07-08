/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Hassan Ali Askari
 *  File:   TextUI.h
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

#ifndef TEXTUI_H
#define	TEXTUI_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "EventData.h"
#include "CurrentTime.h"
#include "ErrorMessage.h"
#include "CommandTask.h"

using namespace std;

class TextUI
{
    private:
        vector <string> _months[13];
        vector <string> _days[8];
        EventData _event;
        CurrentTime _currentTime;
        int _findSlotStDate,_findSlotStMonth,_findSlotStYear;
        string _rmvEventName, _rmvEventType;
        int _rmvEventId;

        string processAddCommand(string _inp);
        string processRmvCommand(string _inp);
        string processModCommand(string _inp);
        string processMarkCommand(string _inp);
        string processFindSlotCommand(string _inp);
        string processSearchCommand(string _inp);
        string processListHistoryCommand();
        string processUndoCommand();

        bool isDateValid();
        bool isTimeValid();
        string collectEventInfo(string _taskName,int _stTime,int _endTime,int _stDate,int _stMonth,int _stYear,int _endDate,int _endMonth,int _endYear,string _details);

        int currentDate();
        int currentMonth();
        int currentYear();
        int currentDay();
        int currentTime();

        int processMonth(string _date);
        int processDate(string _date, string *_month, int *_year);
        bool matchString(vector <string>, string);

    public:
        TextUI();
        virtual ~TextUI();

        string processCommand(string _command);
        EventData getEventInfo();
        int getFindSlotStDate();
        int getFindSlotStMonth();
        int getFindSlotStYear();
        string getRmvEventName();
        string getRmvEventType();
        int getRmvEventId();

};

#endif	/* TEXTUI_H */

