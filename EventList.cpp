/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   EventList.cpp
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

#include "EventList.h"

EventList::EventList()
{}

EventList::~EventList()
{}

void EventList::formatString(vector<EventData> &_incoming, int _stId, int _eventType)
{
    string _outgoing;
    stringstream _stTime,_endTime,_stDate,_stMonth,_stYear,_endDate, _endMonth, _endYear, _id;
    string _defaultStringView("-1");


    if(_incoming.size()!=0)
    {
        for(unsigned int i = 0; i < _incoming.size(); i++)
        {
            if (_incoming[i]._stTime != DEFAULT)
                _stTime << setw (4) <<setfill('0')<<_incoming[i]._stTime;

            _endTime << setw (4) <<setfill('0')<< _incoming[i]._endTime;

            if ((_incoming[i]._stTime!=DEFAULT))
            {
                _stDate << setw (2) <<setfill('0')<< _incoming[i]._stDate;
                _stMonth << setw (2) <<setfill('0')<< _incoming[i]._stMonth;
                _stYear << setw (2) <<setfill('0')<<(_incoming[i]._stYear%100);
            }

            _endDate << setw (2) <<setfill('0')<< _incoming[i]._endDate;
            _endMonth << setw (2) <<setfill('0')<< _incoming[i]._endMonth;
            _endYear << setw (2) <<setfill('0')<< (_incoming[i]._endYear%100);
            _id << (_stId+i)<<". ";

            //_formattedStTime<<

            _outgoing.append("<table width=\"100%\"><tr><td align=\"left\">");
            _outgoing.append(_id.str());
            _outgoing.append("<b>");
            _outgoing.append(_incoming[i]._taskName);
            _outgoing.append("</b>");
            _outgoing.append("</td>");

            _outgoing.append("<td align=\"right\">");
            if ((_incoming[i]._stTime==DEFAULT))
            {/*DO NOTHING*/}
            else
            {
                _outgoing.append(_stTime.str());
                _outgoing.append(" to ");
            }

            _outgoing.append(_endTime.str());

            _outgoing.append("</td></tr></table>");

            _outgoing.append("<table width=\"100%\"><tr><td align=\"left\">");
            if(_incoming[i]._details == _defaultStringView)
            {/*DO NOTHING*/ }

            else
            {
                _outgoing.append("&nbsp;&nbsp;<i>");
                _outgoing.append(_incoming[i]._details);
            }
            _outgoing.append("</i></td>");

            _outgoing.append("<td align=\"right\">");
            if ((_incoming[i]._stTime==DEFAULT))
            {/*DO NOTHING*/}
            else
            {
                if (_incoming[i]._stDate!=_incoming[i]._endDate || _incoming[i]._stMonth!=_incoming[i]._endMonth  || _incoming[i]._stYear!=_incoming[i]._endYear)
                {
                    _outgoing.append(_stDate.str());
                    _outgoing.append("/");
                    _outgoing.append(_stMonth.str());
                    _outgoing.append("/");
                    _outgoing.append(_stYear.str());
                    _outgoing.append(" to ");
                }
            }

            _outgoing.append(_endDate.str());
            _outgoing.append("/");
            _outgoing.append(_endMonth.str());
            _outgoing.append("/");
            _outgoing.append(_endYear.str());
            _outgoing.append("</td></tr></table>");
            _outgoing.append("<hr>");

            if (_eventType==EVENT_TYPE_DUE)
                _formattedDueEvents.push_back(_outgoing);
            else if (_eventType==EVENT_TYPE_DUE_URGENT)
                _formattedUrgentDueEvents.push_back(_outgoing);
            else if (_eventType==EVENT_TYPE_SCHEDULED)
                _formattedScheduledEvents.push_back(_outgoing);
            else if (_eventType==EVENT_TYPE_SCHEDULED_URGENT)
                _formattedUrgentScheduledEvents.push_back(_outgoing);
            else if (_eventType==EVENT_TYPE_MISSED_DUE)
                _formattedMissedDueEvents.push_back(_outgoing);
            else if (_eventType==EVENT_TYPE_MISSED_SCHEDULED)
                _formattedMissedScheduledEvents.push_back(_outgoing);

            _outgoing = "";
            _stTime.str("");
            _endTime.str("");
            _stDate.str("");
            _stMonth.str("");
            _stYear.str("");
            _endDate.str("");
            _endMonth.str("");
            _endYear.str("");
            _id.str("");
        }
    }
}

vector<string> EventList::retrieveDueList()
{
    vector<string> _temp;
    _temp = _formattedDueEvents;

    while(!_formattedDueEvents.empty())
    {
        _formattedDueEvents.pop_back();
    }
    return _temp;
}

vector<string> EventList::retrieveScheduleList()
{
    vector<string> _temp;
    _temp = _formattedScheduledEvents;

    while(!_formattedScheduledEvents.empty())
    {
        _formattedScheduledEvents.pop_back();
    }
    return _temp;
}

vector<string> EventList::retrieveUrgentDueList()
{
    vector<string> _temp;
    _temp = _formattedUrgentDueEvents;

    while(!_formattedUrgentDueEvents.empty())
    {
        _formattedUrgentDueEvents.pop_back();
    }
    return _temp;
}

vector<string> EventList::retrieveUrgentScheduleList()
{
    vector<string> _temp;
    _temp = _formattedUrgentScheduledEvents;

    while(!_formattedUrgentScheduledEvents.empty())
    {
        _formattedUrgentScheduledEvents.pop_back();
    }
    return _temp;
}

vector<string> EventList::retrieveExpiredDueList()
{
    vector<string> _temp;
    _temp = _formattedMissedDueEvents;

    while(!_formattedMissedDueEvents.empty())
    {
        _formattedMissedDueEvents.pop_back();
    }
    return _temp;
}

vector<string> EventList::retrieveExpiredScheduledList()
{
    vector<string> _temp;
    _temp = _formattedMissedScheduledEvents;

    while(!_formattedMissedScheduledEvents.empty())
    {
        _formattedMissedScheduledEvents.pop_back();
    }
    return _temp;
}

void EventList::formatForDynamicWindow( vector<EventData> &_incoming)
{
    string _outgoing;
    stringstream _stTime,_endTime,_stDate,_stMonth,_stYear,_endDate, _endMonth, _endYear;
    string _defaultStringView("-1");

    _dynamicWindowString.clear();

    if(_incoming.size()!=0)
    {
        for(unsigned int i = 0; i < _incoming.size(); i++)
        {
            _stTime << _incoming[i]._stTime;
            _endTime << _incoming[i]._endTime;
            _stDate << _incoming[i]._stDate;
            _stMonth << _incoming[i]._stMonth;
            _stYear << _incoming[i]._stYear;
            _endDate << _incoming[i]._endDate;
            _endMonth << _incoming[i]._endMonth;
            _endYear << _incoming[i]._endYear;

            _outgoing.append("TASK NAME: ");

            _outgoing.append(_incoming[i]._taskName + "<br>");

            if(_stTime.str() == _defaultStringView)
            {/*DO NOTHING*/}
            else
            {
                _outgoing.append("Start Time: ");
                _outgoing.append(_stTime.str() + " ");
            }

            if(_endTime.str() == _defaultStringView)
            {/*DO NOTHING*/}
            else
            {
                _outgoing.append("End Time: ");
                _outgoing.append(_endTime.str() + " " + "<br>");
            }

            if(_stDate.str() == _defaultStringView)
            {/*DO NOTHING*/}
            else
            {
                _outgoing.append("Start Date: ");
                _outgoing.append(_stDate.str());
                _outgoing.append("/");
                _outgoing.append(_stMonth.str());
                _outgoing.append("/");
                _outgoing.append(_stYear.str() + " ");
            }

            if(_endDate.str() == _defaultStringView)
            {/*DO NOTHING*/}

            else
            {
                _outgoing.append("End Date: ");
                _outgoing.append(_endDate.str());
                _outgoing.append("/");
                _outgoing.append(_endMonth.str());
                _outgoing.append("/");
                _outgoing.append(_endYear.str() + "<br>");
            }
            
            if(_incoming[i]._details == _defaultStringView)
            {/*DO NOTHING*/ }

            else
            {
                _outgoing.append("DETAILS: ");
                _outgoing.append(_incoming[i]._details + "<br>");
            }

            _dynamicWindowString.push_back(_outgoing);
            _outgoing = "";
            _stTime.str("");
            _endTime.str("");
            _stDate.str("");
            _stMonth.str("");
            _stYear.str("");
            _endDate.str("");
            _endMonth.str("");
            _endYear.str("");
        }
    }
}

vector<string> EventList::retrieveDynamicWindowString()
{
    return _dynamicWindowString;
}
