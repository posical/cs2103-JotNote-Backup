/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   TextUI.cpp
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

#include "TextUI.h"

TextUI::TextUI()
{
    _months[1].push_back("Jan");
    _months[2].push_back("Feb");
    _months[3].push_back("Mar");
    _months[4].push_back("Apr");
    _months[5].push_back("May");
    _months[6].push_back("Jun");
    _months[7].push_back("Jul");
    _months[8].push_back("Aug");
    _months[9].push_back("Sep");
    _months[10].push_back("Oct");
    _months[11].push_back("Nov");
    _months[12].push_back("Dec");

    _days[1].push_back("Sun");
    _days[2].push_back("Mon");
    _days[3].push_back("Tue");
    _days[4].push_back("Wed");
    _days[5].push_back("Thu");
    _days[6].push_back("Fri");
    _days[7].push_back("Sat");
}

TextUI::~TextUI()
{}

string TextUI::processCommand(string _inp)
{
    _inp.append(" ");

    istringstream _commandLine;
    _commandLine.str(_inp);
    string _task,_shorterCommand="";

    // input command
    _commandLine>>_task;

    _shorterCommand=_inp.substr(_task.size() , _inp.size()-_task.size()-1 );
    if(_task==COMMAND_ADD_TASK)
    {
        _task=processAddCommand(_shorterCommand);
    }
    else if(_task==COMMAND_MODIFY_TASK)
    {
        _task=processModCommand(_shorterCommand);
    }
    else if(_task==COMMAND_REMOVE_TASK)
    {
        _task=processRmvCommand(_shorterCommand);
    }
    else if(_task==COMMAND_MARK_DONE)
    {
        _task=processMarkCommand(_shorterCommand);
    }
    else if(_task==COMMAND_FIND_SLOT)
    {
        _task=processFindSlotCommand(_shorterCommand);
    }
    else if(_task==COMMAND_SEARCH)
    {
        // Do nothing
    }
    else if(_task==COMMAND_LIST_HISTORY)
    {
        _task=processListHistoryCommand();
    }
    else if(_task==COMMAND_UNDO)
    {
        // Do nothing
    }
    else return MESSAGE_WRONG_COMMAND;

    return _task;
} 

string TextUI::processAddCommand(string _inp)
{
    istringstream _commandLine;
    _commandLine.str(_inp);

    string _taskName="",_timeFormat="",_details="", _word, _endMonth="-1", _stMonth="-1", _stDate="-1", _endDate="-1";
    int _stTime=DEFAULT, _endTime=DEFAULT;
    int _stYear=DEFAULT, _endYear=DEFAULT;


    //input heading of the task
    while(_commandLine>>_word)
    {
        if(_word==COMMAND_DUE || _word==COMMAND_STARTING_TIME)
        {
            _timeFormat=_word;
            break;
        }
        else
        {
            _taskName.append(_word);
            _taskName.append(" ");
        }
    }
    if(_timeFormat=="" || _taskName=="")
        return MESSAGE_INCOMPLETE_COMMAND;



    //input timings
    if(_timeFormat==COMMAND_DUE)
    {
        _commandLine>>_endTime;
        if(_endTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;

    }

    else
    {
        _commandLine>>_stTime;
        if(_stTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;
        _commandLine>>_endTime;
        if(_endTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;
    }

    //input date
    int i=0;
    while(_commandLine>>_word)
    {
        if(_word==COMMAND_DETAILS)
            break;
        istringstream _temp(_word);
        if(i==0)
            _temp>>_endDate;
        else if(i==1)
            _temp>>_endMonth;
        else if(i==2)
            _temp>>_endYear;
        else if(i==3)
        {
            _stDate=_endDate;	_temp>>_endDate;
        }
        else if(i==4)
        {
            _stMonth=_endMonth;		_temp>>_endMonth;
        }
        else if(i==5)
        {
            _stYear=_endYear;	_temp>>_endYear;
        }

        i++;
    }

    // set starting dates equal to end dates if only 1 is given for a scheduled event
    if(_stTime!=DEFAULT && i==3)
    {
        _stDate=_endDate;
        _stMonth=_endMonth;
        _stYear=_endYear;
    }


    //input details
    while(_commandLine>>_word)
    {
        _details.append(_word);
        _details.append(" ");
    }

    int _processedEndDate=processDate(_endDate,&_endMonth,&_endYear);
    int _processedStDate=processDate(_stDate,&_stMonth,&_stYear);

    _taskName=_taskName.substr(0,_taskName.size()-1);
    string _error;

    _error=collectEventInfo(_taskName, _stTime, _endTime, _processedStDate, processMonth(_stMonth), _stYear, _processedEndDate, processMonth(_endMonth), _endYear, _details);


    if (_error==NO_ERROR)
    {
        return COMMAND_ADD_TASK;
    }
    else  return _error;

}

string TextUI::processRmvCommand(string _inp){

    string _word,_taskName;
    istringstream _commandLine;
    _commandLine.str(_inp);

    _rmvEventId=DEFAULT;
    while(_commandLine>>_word)
    {
        if(_word==COMMAND_SHEDULED)
        {
            _rmvEventType="scheduled";
            _commandLine>>_rmvEventId;
            break;
        }
        else if(_word==COMMAND_DUE)
        {
            _rmvEventType="due";
            _commandLine>>_rmvEventId;
            break;
        }
        else
        {
            _taskName.append(_word);
            _taskName.append(" ");
        }
    }

    if(_taskName=="" && _rmvEventId==DEFAULT)
        return MESSAGE_INCOMPLETE_COMMAND;

    else if(_taskName!="")
    {
        _rmvEventName =_taskName.substr(0,_taskName.size()-1);
        return COMMAND_REMOVE_TASK_BY_NAME;
    }
    else return COMMAND_REMOVE_TASK_BY_ID;

}

string TextUI::processModCommand(string _inp)
{

    istringstream _commandLine;
    _commandLine.str(_inp);

    string _taskName="",_timeFormat="",_details="", _word, _endMonth="-1", _stMonth="-1", _stDate="-1", _endDate="-1";
    int _stTime=DEFAULT, _endTime=DEFAULT;
    int _stYear=DEFAULT, _endYear=DEFAULT;


    //input heading of the task
    while(_commandLine>>_word)
    {
        if (_word==COMMAND_DUE || _word==COMMAND_STARTING_TIME)
        {
            _timeFormat=_word;
            break;
        }
        else
        {
            _taskName.append(_word);
            _taskName.append(" ");
        }
    }
    if(_timeFormat=="" || _taskName=="")
        return MESSAGE_INCOMPLETE_COMMAND;



    //input timings
    if(_timeFormat==COMMAND_DUE)
    {
        _commandLine>>_endTime;
        if (_endTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;
    }

    else
    {
        _commandLine>>_stTime;
        if(_stTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;
        _commandLine>>_endTime;
        if(_endTime==DEFAULT)
            return MESSAGE_INCOMPLETE_COMMAND;
    }

    //input date
    int i=0;
    while(_commandLine>>_word)
    {
        if(_word==COMMAND_DETAILS)
            break;
        istringstream _temp(_word);
        if(i==0)
            _temp>>_endDate;
        else if(i==1)
            _temp>>_endMonth;
        else if(i==2)
            _temp>>_endYear;
        else if(i==3)
        {
            _stDate=_endDate;	_temp>>_endDate;
        }
        else if (i==4)
        {
            _stMonth=_endMonth;		_temp>>_endMonth;
        }
        else if (i==5)
        {
            _stYear=_endYear;	_temp>>_endYear;
        }

        i++;
    }

    // set starting dates equal to end dates if only 1 is given for a scheduled event
    if(_stTime!=DEFAULT && i==3)
    {
        _stDate=_endDate;
        _stMonth=_endMonth;
        _stYear=_endYear;
    }


    //input details
    while(_commandLine>>_word)
    {
        _details.append(_word);
        _details.append(" ");
    }

    int _processedEndDate=processDate(_endDate,&_endMonth,&_endYear);
    int _processedStDate=processDate(_stDate,&_stMonth,&_stYear);

    _taskName=_taskName.substr(0,_taskName.size()-1);
    string _error;

    _error=collectEventInfo(_taskName, _stTime, _endTime, _processedStDate, processMonth(_stMonth), _stYear, _processedEndDate, processMonth(_endMonth), _endYear, _details);


    if(_error==NO_ERROR)
    {
        return COMMAND_MODIFY_TASK;
    }

    else  return _error;
}

string TextUI::processMarkCommand(string _inp)
{
    string _word,_taskName;
    istringstream _commandLine;
    _commandLine.str(_inp);

    while(_commandLine>>_word)
    {
        _taskName.append(_word);
        _taskName.append(" ");
    }
    if(_taskName=="")
        return MESSAGE_INCOMPLETE_COMMAND;

    _taskName=_taskName.substr(0,_taskName.size()-1);

    collectEventInfo(_taskName, DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT, DEFAULT,DEFAULT,DEFAULT,"");

    return COMMAND_MARK_DONE;
}

string TextUI::processFindSlotCommand(string _inp)
{
    _findSlotStDate=DEFAULT;
    _findSlotStMonth=DEFAULT;
    _findSlotStYear=DEFAULT;

    istringstream _commandLine;
    _commandLine.str(_inp);
    _commandLine>>_findSlotStDate>>_findSlotStMonth>>_findSlotStYear;

    if(_findSlotStDate==DEFAULT)
    {
        _findSlotStDate=_currentTime.currentDate();
    }
    if(_findSlotStMonth==DEFAULT)
    {
        _findSlotStMonth=_currentTime.currentMonth();
    }
    if(_findSlotStYear==DEFAULT)
    {
        _findSlotStYear=_currentTime.currentYear();
    }

    return COMMAND_FIND_SLOT;
}

string TextUI::processListHistoryCommand()
{
    return COMMAND_LIST_HISTORY;
}

string TextUI::collectEventInfo(string _taskName,int _stTime,int _endTime,int _stDate,int _stMonth,int _stYear,int _endDate,int _endMonth,int _endYear,string _details)
{
    _event._taskName=_taskName;
    _event._stTime=_stTime;
    _event._endTime=_endTime;

    if(_endDate==DEFAULT)
        _event._endDate=currentDate();
    else _event._endDate=_endDate;

    if(_endMonth==DEFAULT)
    {
        if(_endDate<currentDate())
            _event._endMonth=currentMonth();
        else _event._endMonth=currentMonth();
    }
    else _event._endMonth=_endMonth;

    if(_endYear==DEFAULT)
        _event._endYear=currentYear();
    else _event._endYear=_endYear;


    if(_stTime==DEFAULT)
    {               //Due Event
        _event._stDate=_stDate;
        _event._stMonth=_stMonth;
        _event._stYear=_stYear;
    }
    else
    {                              //Scheduled Event
        if(_stDate==DEFAULT)
        {
            _event._stDate=_event._endDate;
            _event._stMonth=_event._endMonth;
            _event._stYear=_event._endYear;
        }
        else
        {
            _event._stDate=_stDate;
            _event._stMonth=_stMonth;
            _event._stYear=_stYear;
        }
    }
    _event._details=_details;

    //check date
    if(!isDateValid())
        return MESSAGE_INVALID_DATE;

    //check time
    else if(!isTimeValid())
        return MESSAGE_INVALID_TIME;

    else return NO_ERROR;

}

EventData TextUI::getEventInfo()
{
    return _event;
}

int TextUI::getFindSlotStDate()
{
    return _findSlotStDate;
}

int TextUI::getFindSlotStMonth()
{
    return _findSlotStMonth;
}

int TextUI::getFindSlotStYear()
{
    return _findSlotStYear;
}

string TextUI::getRmvEventName()
{
    return _rmvEventName;
}
string TextUI::getRmvEventType()
{
    return _rmvEventType;
}

int TextUI::getRmvEventId()
{
    return _rmvEventId;
}

int TextUI::currentDate()
{
    return _currentTime.currentDate();
}

int TextUI::currentMonth()
{
    return _currentTime.currentMonth();
}

int TextUI::currentYear()
{
    return _currentTime.currentYear();
}

int TextUI::currentDay()
{
    return _currentTime.currentDay();
}

int TextUI::currentTime()
{
    return _currentTime.currentTime();
}


int TextUI::processMonth(string _month)
{
    for(int i=1;i<=12;i++)
    {
        if(matchString(_months[i], _month)==true)
            return i;
    }

    istringstream _temp(_month);
    int _ans;
    _temp>>_ans;
    return _ans;
}

int TextUI::processDate(string _date, string *_month, int *_year)
{
    int _nDays;
    stringstream _extractedMonth;//create a stringstream

    for(int i=1;i<=7;i++){
        if(matchString(_days[i], _date)==true)
        {
            if (i-1>=currentDay())
                _nDays=i-1-currentDay();
            else _nDays=(7-currentDay()) + i-1;

            time_t _now;
            time (&_now);
            _now+= (_nDays)*24*3600;
            struct tm *_nextDay;
            _nextDay = localtime(&_now);

            _extractedMonth<<(_nextDay->tm_mon)+1;
            _month->clear();
            _month->append(_extractedMonth.str());

            *_year=_nextDay->tm_year+1900;
            return _nextDay->tm_mday;
        }
    }

    istringstream _temp(_date);
    int _ans;
    _temp>>_ans;
    return _ans;
}

bool TextUI::matchString(vector <string> _vectorString, string _word)
{
    bool b = 0;

    for(unsigned int i=0;i<_vectorString.size();i++)
    {
        if(_vectorString[i]==_word)
        {
            b = 1;
        }
        else
        {
            b = 0;
        }
    }
    return b;
}

bool TextUI::isDateValid()
{
    int _noDaysInMonths[13]={0,31,28,31,30,31,30,31,30,31,30,31,30};

    //check for leap year
    if(_event._endYear%400 ==0 || (_event._endYear%100 != 0 && _event._endYear%4 == 0))
        _noDaysInMonths[2]=29;
    else _noDaysInMonths[2]=28;

    //check validity
    if(_event._endDate>_noDaysInMonths[_event._endMonth] ||  _event._endDate<1)
        return false;
    if(_event._endMonth>12 || _event._endMonth<1)
        return false;

    if(_event._stTime != DEFAULT)
    {       // valid for scheduled events only
        // check for leap year
        if(_event._stYear%400 ==0 || (_event._stYear%100 != 0 && _event._stYear%4 == 0))
            _noDaysInMonths[2]=29;
        else _noDaysInMonths[2]=28;

        if(_event._stDate>_noDaysInMonths[_event._stMonth] ||  _event._stDate<1)
            return false;
        if(_event._stMonth>12 || _event._stMonth<1)
            return false;
    }

    // Check dates are not in the past
    if(_event._endYear<currentYear())
        return false;
    if(_event._endMonth<currentMonth()  && _event._endYear==currentYear())
        return false;
    if(_event._endDate<currentDate()  && _event._endMonth==currentMonth()  &&  _event._endYear==currentYear())
        return false;
    if(_event._endTime<currentTime()  && _event._endDate==currentDate()  &&  _event._endMonth==currentMonth() &&  _event._endYear==currentYear())
        return false;

    if(_event._stTime != DEFAULT)
    {       // valid for scheduled events only
        if(_event._stYear<currentYear())
            return false;
        if(_event._stMonth<currentMonth()  && _event._stYear==currentYear())
            return false;
        if(_event._stDate<currentDate()  && _event._stMonth==currentMonth()  &&  _event._stYear<currentYear())
            return false;
        if(_event._stTime<currentTime()  && _event._endDate==currentDate()  && _event._stMonth==currentMonth()  &&  _event._stYear<currentYear())
            return false;
    }



    // Check start date does not exceed end date in case of scheduled events
    if(_event._stTime != DEFAULT)
    {
        if((_event._stYear*1000 + _event._stMonth*100 + _event._stDate*10) > (_event._endYear*1000 + _event._endMonth*100 + _event._endDate*10))
            return false;
    }

    return true;
}

bool TextUI::isTimeValid()
{
    //check _endTime
    if(_event._endTime<0 || _event._endTime>2400)
        return false;
    if(_event._endTime%100>=60)
        return false;

    //check _stTime
    if(_event._stTime==DEFAULT)
        return true;
    else
    {
        if(_event._stTime<0 || _event._stTime>2400)
            return false;
        if(_event._stTime%100>=60)
            return false;
    }

    return true;
}
