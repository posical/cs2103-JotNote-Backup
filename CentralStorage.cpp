/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   CentralStorage.cpp
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

#include "CentralStorage.h"

struct CompareEndDateEndTime
{
    bool operator() (const EventData &E1, const EventData &E2)
    {
        return ((E1._endYear < E2._endYear)
                || ((E1._endYear == E2._endYear) && (E1._endMonth < E2._endMonth))
                || ((E1._endYear == E2._endYear) && (E1._endMonth == E2._endMonth) && (E1._endDate < E2._endDate))
                || ((E1._endYear == E1._endYear) && (E1._endMonth == E2._endMonth) && (E1._endDate == E2._endDate) && (E1._endTime < E2._endTime)));
    }
};

CentralStorage::CentralStorage()
{
    _allContainers.push_back(&_masterList);
    _allContainers.push_back(&_dueUrgentEvents);
    _allContainers.push_back(&_expiredDueEvents);
    _allContainers.push_back(&_dueEvents);

    _allContainers.push_back(&_expiredScheduledEvents);
    _allContainers.push_back(&_scheduledUrgentEvents);
    _allContainers.push_back(&_scheduledEvents);
    _allContainers.push_back(&_doneEvents);

    retrieveDataFromExtractDatabase();
    removeDoneEventFromMasterList();
    distDueEventScheduledEvent();
    sortDueEventByEndDateEndTime();
    sortscheduledEventByEndDateEndTime();
    extractAnnouncementEvents();
    extractExpiredEvents ();
    sortAllIndividualVector();
    keepBackUp();
}

CentralStorage::~CentralStorage()
{ 
    mergeEverythingToMasterList();
    transferDataToExtractDatabase();
}

string CentralStorage::addEvent(EventData _eventData)
{
    keepBackUp();
    for (unsigned int i=1; i<=7;i++)
    {
        for (_it=_allContainers[i]->begin();_it<_allContainers[i]->end();_it++)
        {
            if (_it->_taskName==_eventData._taskName)
                return ERROR_ADD_NAME_CLASH;
        }
    }

    if (_eventData._stTime==DEFAULT )
    {
        _dueEvents.push_back (_eventData);
        sortDueEventByEndDateEndTime();
    }

    else
    {
        if (checkForTimingClash (_eventData) ==ERROR_ADD_TIME_CLASH)
            return ERROR_ADD_TIME_CLASH;
        else
        {
            _scheduledEvents.push_back (_eventData);
            sortscheduledEventByEndDateEndTime();
        }
    }


    mergeEverythingToMasterList();

    transferDataToExtractDatabase();
    extractAnnouncementEvents ();
    return NO_ERROR;
}

string CentralStorage::removeEventByName(string _taskName)
{
    keepBackUp();
    bool _isFound;
    _isFound=0;

    for (unsigned int i=1; i<=7;i++)
    {
        for (_it=_allContainers[i]->begin();_it<_allContainers[i]->end();_it++)
        {
            if (_it->_taskName==_taskName)
            {
                _allContainers[i]->erase(_it);
                _isFound=1;
            }
        }
    }


    mergeEverythingToMasterList();
    transferDataToExtractDatabase();

    if (_isFound){
        extractAnnouncementEvents ();
        return NO_ERROR;
    }
    else return ERROR_REMOVE_NOT_FOUND;

}

string CentralStorage::removeEventById(string _eventType,unsigned int _id)
{
    keepBackUp();
    bool _isError;
    _isError=0;

    if(_eventType=="scheduled")
    {
        _it=_expiredScheduledEvents.begin();
        if(_id<=_expiredScheduledEvents.size())
        {
            _expiredScheduledEvents.erase(_it+_id-1);
        }
        else
        {
            _id=_id-_expiredScheduledEvents.size();
            if(_id<=_scheduledUrgentEvents.size())
            {
                _it=_scheduledUrgentEvents.begin();
                _scheduledUrgentEvents.erase(_it+_id-1);
            }
            else
            {
                _id=_id-_scheduledUrgentEvents.size();
                if(_id<=_scheduledEvents.size())
                {
                    _it=_scheduledEvents.begin();
                    _scheduledEvents.erase(_it+_id-1);
                }
                else _isError=1;
            }
        }
    }

    else if(_eventType=="due")
    {
        _it=_expiredDueEvents.begin();
        if(_id<=_expiredDueEvents.size())
        {
            _expiredDueEvents.erase(_it+_id-1);
        }
        else
        {
            _id=_id-_expiredDueEvents.size();
            if(_id<=_dueUrgentEvents.size())
            {
                _it=_dueUrgentEvents.begin();
                _dueUrgentEvents.erase(_it+_id-1);
            }
            else
            {
                _id=_id-_dueUrgentEvents.size();
                if(_id<=_dueEvents.size())
                {
                    _it=_dueEvents.begin();
                    _dueEvents.erase(_it+_id-1);
                }
                else _isError=1;
            }
        }
    }

    else _isError=1;

    mergeEverythingToMasterList();
    transferDataToExtractDatabase();

    if(!(_isError))
    {
        extractAnnouncementEvents ();
        return NO_ERROR;
    }
    else return ERROR_REMOVE_NOT_FOUND;
}

string CentralStorage::modifyEvent(EventData _eventData)
{
    keepBackUp();
    string _status;
    _status=removeEventByName(_eventData._taskName);

    if(_status==NO_ERROR){
        if(_eventData._stTime==DEFAULT)
        {
            _dueEvents.push_back (_eventData);
            sortDueEventByEndDateEndTime();
            mergeEverythingToMasterList();
        }

        else
        {
            if(checkForTimingClash(_eventData)==ERROR_ADD_TIME_CLASH)
                return ERROR_ADD_TIME_CLASH;
            else
            {
                _scheduledEvents.push_back(_eventData);
                sortscheduledEventByEndDateEndTime();
                mergeEverythingToMasterList();
            }
        }

        transferDataToExtractDatabase();
        extractAnnouncementEvents();
        return NO_ERROR;
    }
    else return _status;
}

string CentralStorage::markEvent(EventData _eventData)
{
    keepBackUp();
    bool _isFound;
    _isFound=0;
    string _taskName=_eventData._taskName;

    for(unsigned int i=1; i<=6;i++)
    {
        for(_it=_allContainers[i]->begin();_it<_allContainers[i]->end();_it++)
        {
            if(_it->_taskName==_taskName)
            {
                _it->done=true;
                _doneEvents.push_back(*_it);
                _allContainers[i]->erase (_it);
                _isFound=1;
            }
        }
    }

    mergeEverythingToMasterList();
    transferDataToExtractDatabase();

    if(_isFound)
    {
        extractAnnouncementEvents ();
        return NO_ERROR;
    }
    else return ERROR_REMOVE_NOT_FOUND;
}

void CentralStorage::searchEvent(string _cmd)
{
    _searchResult.clear();

    stringstream _inp(_cmd);
    string _word;

    _inp>>_word;
    if(_word!="search")
        return;

    if(_inp>>_word)
    {
        string _taskName, _details, _combined,_keyword;
        _keyword=_word;

        for(unsigned int i=1; i<=6;i++)
        {
            for(_it=_allContainers[i]->begin();_it<_allContainers[i]->end();_it++)
            {
                _taskName=_it->_taskName;
                _details=_it->_details;
                _combined=_taskName + " " + _details;

                _combined = convertStringToUpper(_combined);
                _keyword = convertStringToUpper(_keyword);

                size_t _pos;
                _pos=_combined.find(_keyword);
                if (_pos==string::npos)
                    continue;
                else _searchResult.push_back(*_it);
            }
        }
    }
}

string CentralStorage::checkForTimingClash(EventData _eventData)
{
    for(unsigned int i=4; i<_allContainers.size()-1;i++)                     // Go through scheduled type data only
    {
        for(_it=_allContainers[i]->begin();_it<_allContainers[i]->end();_it++)
        {
            if(isLaterOrEqual (_it->_stTime,_it->_stDate,_it->_stMonth,_it->_stYear, _eventData._stTime,_eventData._stDate,_eventData._stMonth,_eventData._stYear ))
                if(isEarlierOrEqual(_it->_endTime-1,_it->_endDate,_it->_endMonth,_it->_endYear,_eventData._stTime,_eventData._stDate,_eventData._stMonth,_eventData._stYear))
                    return ERROR_ADD_TIME_CLASH;

            if(isLaterOrEqual (_it->_stTime+1,_it->_stDate,_it->_stMonth,_it->_stYear, _eventData._endTime,_eventData._endDate,_eventData._endMonth,_eventData._endYear ))
                if(isEarlierOrEqual(_it->_endTime,_it->_endDate,_it->_endMonth,_it->_endYear,_eventData._endTime,_eventData._endDate,_eventData._endMonth,_eventData._endYear))
                    return ERROR_ADD_TIME_CLASH;
        }
    }

    return NO_ERROR;
}


bool CentralStorage::isEarlierOrEqual(int _fixedTime, int _fixedDate, int _fixedMonth, int _fixedYear, int _checkTime, int _checkDate, int _checkMonth, int _checkYear)
{
    if(_checkYear!=_fixedYear)
        return(_checkYear<=_fixedYear);
    else
    {
        if(_checkMonth!=_fixedMonth)
            return(_checkMonth<=_fixedMonth);
        else
        {
            if(_checkDate!=_fixedDate)
                return(_checkDate<=_fixedDate);
            else return(_checkTime<=_fixedTime);
        }
    }
}

bool CentralStorage::isLaterOrEqual(int _fixedTime, int _fixedDate, int _fixedMonth, int _fixedYear, int _checkTime, int _checkDate, int _checkMonth, int _checkYear)
{
    if(_checkYear!=_fixedYear)
        return (_checkYear>=_fixedYear);
    else
    {
        if(_checkMonth!=_fixedMonth)
            return(_checkMonth>=_fixedMonth);
        else
        {
            if(_checkDate!=_fixedDate)
                return(_checkDate>=_fixedDate);
            else return(_checkTime>=_fixedTime);
        }
    }
}

vector<EventData> CentralStorage::retrieveDueEvent()
{
    return _dueEvents;
}

vector<EventData> CentralStorage::retrieveScheduledEvent()
{
    return _scheduledEvents;
}

vector<EventData> CentralStorage::retrieveMasterList()
{
    return _masterList;
}

vector<EventData> CentralStorage::retrieveUrgentDueEvent()
{
    return _dueUrgentEvents;
}

vector<EventData> CentralStorage::retrieveUrgentScheduledEvent()
{
    return _scheduledUrgentEvents;
}

vector<EventData> CentralStorage::retrieveMissedDueEvent()
{
    return _expiredDueEvents;
}

vector<EventData> CentralStorage::retrieveMissedScheduledEvent()
{
    return _expiredScheduledEvents;
}

vector<EventData> CentralStorage::retrieveDoneEvents()
{
    return _doneEvents;
}

int CentralStorage::retrieveDueUrgentEventNumber()
{
    return _dueUrgentEvents.size();
}

int CentralStorage::retrieveScheduledUrgentEventNumber()
{
    return _scheduledUrgentEvents.size();
}

int CentralStorage::retrieveMissedDueEventNumber()
{
    return _expiredDueEvents.size();
}

int CentralStorage::retrieveMissedScheduledEventNumber()
{
    return _expiredScheduledEvents.size();
}

vector<string> CentralStorage::extractFreeTimeSlots()
{
    return _freeTimeSlots;
}

vector<EventData> CentralStorage::retrieveSearchResult()
{
    return _searchResult;
}

void CentralStorage::extractAnnouncementEvents()
{
    time_t _now;
    time (&_now);
    _now+= (DAYS_ANNOUNCEMENT)*24*3600;
    struct tm *_nextDay;
    _nextDay = localtime(&_now);

    for(_it=_dueEvents.begin();_it<_dueEvents.end();_it++)
    {
        if((_it->_endYear < _nextDay->tm_year+1900)
                || ((_it->_endYear == _nextDay->tm_year+1900) && (_it->_endMonth < _nextDay->tm_mon+1))
                || ((_it->_endYear == _nextDay->tm_year+1900) && (_it->_endMonth == _nextDay->tm_mon+1) && (_it->_endDate < _nextDay->tm_mday))){
            _dueUrgentEvents.push_back(*_it);
            _dueEvents.erase(_it);
            _it--;
        }
    }

    for(_it=_scheduledEvents.begin();_it<_scheduledEvents.end();_it++)
    {
        if((_it->_endYear < _nextDay->tm_year+1900)
                || ((_it->_endYear == _nextDay->tm_year+1900) && (_it->_endMonth < _nextDay->tm_mon+1))
                || ((_it->_endYear == _nextDay->tm_year+1900) && (_it->_endMonth == _nextDay->tm_mon+1) && (_it->_endDate < _nextDay->tm_mday)))
        {
            _scheduledUrgentEvents.push_back(*_it);
            _scheduledEvents.erase(_it);
            _it--;
        }
    }
}

void CentralStorage::retrieveDataFromExtractDatabase()
{
    ExtractDatabase _receiveData;
    _masterList = _receiveData.addEventFromDatabaseToExtractDatabase();
}

void CentralStorage::transferDataToExtractDatabase()
{
    vector <EventData> _masterListTemp(_masterList);
    ExtractDatabase _transferData;
    _transferData.transferFromExtractDatabaseToDatabase(_masterListTemp);
}

void CentralStorage::sortDueEventByEndDateEndTime()
{
    vector <EventData> _sortTemp = _dueEvents;
    sort(_sortTemp.begin(),_sortTemp.end(),CompareEndDateEndTime());
    _dueEvents = _sortTemp;
}

void CentralStorage::sortscheduledEventByEndDateEndTime()
{
    vector <EventData> _sortTemp = _scheduledEvents;
    sort(_sortTemp.begin(),_sortTemp.end(),CompareEndDateEndTime());
    _scheduledEvents = _sortTemp;
}


void CentralStorage::distDueEventScheduledEvent()
{
    vector <EventData> _sortTemp = _masterList;
    _masterList.clear();
    _dueEvents.clear();
    _scheduledEvents.clear();

    EventData _eventTemp;
    CurrentTime _currentDayMonthYear;

    while(!_sortTemp.empty())
    {
        _eventTemp = _sortTemp.back();

        if(_eventTemp._stDate==-1)
        {_dueEvents.push_back(_eventTemp);}

        else
        {_scheduledEvents.push_back(_eventTemp);}

        _sortTemp.pop_back();
    }
}

void CentralStorage::removeDoneEventFromMasterList()
{
    vector <EventData> _masterListTemp, _doneEventTemp,_unDoneEventTemp;
    vector <EventData> _oldDoneEvent, _oldUnDoneEvent;
    EventData _eventTemp;

    while(!_masterList.empty())
    {
        _eventTemp = _masterList.back();

        if(_eventTemp.done == true)
        {
            _doneEventTemp.push_back(_eventTemp);
            _masterList.pop_back();
        }

        else
        {
            _unDoneEventTemp.push_back(_eventTemp);
            _masterList.pop_back();
        }
    }

    _masterList = _unDoneEventTemp;
    _doneEvents = _doneEventTemp;
}

void CentralStorage::extractExpiredEvents()
{
    CurrentTime _current;
    EventData _temp;

    int _currentDate =_current.currentDate();
    int _currentMonth =_current.currentMonth();
    int _currentYear =_current.currentYear();
    int _currentTime = _current.currentTime();


    for(_it=_dueUrgentEvents.begin();_it<_dueUrgentEvents.end();)
    {
        _temp=*_it;
        if ((_temp._endYear < _currentYear)
                || ((_temp._endYear == _currentYear) && (_temp._endMonth < _currentMonth))
                || ((_temp._endYear == _currentYear) && (_temp._endMonth == _currentMonth) && (_temp._endDate < _currentDate))
                || ((_temp._endYear == _currentYear) && (_temp._endMonth == _currentMonth) && (_temp._endDate == _currentDate) && (_temp._endTime < _currentTime)))
        {
            _expiredDueEvents.push_back(*_it);
            _dueUrgentEvents.erase(_it);
        }
        else _it++;
    }

    for(_it=_scheduledUrgentEvents.begin();_it<_scheduledUrgentEvents.end();)
    {
        _temp=*_it;
        if ((_temp._endYear < _currentYear)
                || ((_temp._endYear == _currentYear) && (_temp._endMonth < _currentMonth))
                || ((_temp._endYear == _currentYear) && (_temp._endMonth == _currentMonth) && (_temp._endDate < _currentDate))
                || ((_temp._endYear == _currentYear) && (_temp._endMonth == _currentMonth) && (_temp._endDate == _currentDate) && (_temp._endTime < _currentTime)))
        {
            _expiredScheduledEvents.push_back(*_it);
            _scheduledUrgentEvents.erase(_it);
        }
        else _it++;
    }
}

void CentralStorage::sortDoneEventByEndDateEndTime()
{
    vector <EventData> _sortTemp = _doneEvents;
    sort(_sortTemp.begin(),_sortTemp.end(),CompareEndDateEndTime());
    _doneEvents = _sortTemp;
}

void CentralStorage::sortAllIndividualVector()
{
    sort(_masterList.begin(),_masterList.end(),CompareEndDateEndTime());
    sort(_dueEvents.begin(),_dueEvents.end(),CompareEndDateEndTime());
    sort(_dueUrgentEvents.begin(),_dueUrgentEvents.end(),CompareEndDateEndTime());
    sort(_scheduledEvents.begin(),_scheduledEvents.end(),CompareEndDateEndTime());
    sort(_scheduledUrgentEvents.begin(),_scheduledUrgentEvents.end(),CompareEndDateEndTime());
    sort(_doneEvents.begin(),_doneEvents.end(),CompareEndDateEndTime());
    sort(_expiredDueEvents.begin(),_expiredDueEvents.end(),CompareEndDateEndTime());
    sort(_expiredScheduledEvents.begin(),_expiredScheduledEvents.end(),CompareEndDateEndTime());
}

void CentralStorage:: findFreeTimeSlots (int _stDate, int _stMonth, int _stYear)
{
    vector <EventData> _events;
    _freeTimeSlots.clear();

    if(_scheduledEvents.size()==0 && _scheduledUrgentEvents.size()==0)
        _freeTimeSlots.push_back("No Events Scheduled");

    else if(_scheduledEvents.size()>0 && _scheduledUrgentEvents.size()>0)
    {
        if ((_scheduledEvents[0]._stYear < _stYear)
                || ((_scheduledEvents[0]._stYear == _stYear) && (_scheduledEvents[0]._stMonth < _stMonth))
                || ((_scheduledEvents[0]._stYear == _stYear) && (_scheduledEvents[0]._stMonth == _stMonth) && (_scheduledEvents[0]._stDate <= _stDate)))
        {
            _events=_scheduledEvents;
        }
        else
        {
            _events=_scheduledUrgentEvents;
        }
    }

    else if(_scheduledEvents.size()>0)
    {
        _events=_scheduledEvents;
    }
    else
    {
        _events=_scheduledUrgentEvents;
    }

    stringstream _out;
    _out<<_stDate<<"/"<<_stMonth<<"/"<<_stYear;
    _freeTimeSlots.push_back(_out.str());
    _out.str("");

    unsigned int i=0;
    while(i<_events.size()  &&  _events[i]._stDate!=_stDate )
        i++;

    if(i==_events.size())
        _freeTimeSlots.push_back("Whole Day Free");

    else
    {
        if(i<_events.size()  &&  _events[i]._stDate == _stDate )
            if(_events[i]._stTime> START_OF_DAY)
            {
                _out<<START_OF_DAY;
                _out<<" to ";
                _out<<_events[i]._stTime;
                _freeTimeSlots.push_back(_out.str());
                _out.str("");
            }

        for(;i+1<_events.size();i++)
        {
            if(_events[i]._stDate == _stDate && _events[i+1]._stDate == _stDate)
            {
                _out<<_events[i]._stDate<<"/"<<_events[i]._stMonth<<"/"<<_events[i]._stYear<<" ";
                _out<<_events[i]._endTime;
                _out<<" to ";
                _out<<_events[i+1]._stTime;
                _freeTimeSlots.push_back(_out.str());
                _out.str("");
            }
        }

        if(i<_events.size()  &&  _events[i]._stDate == _stDate)
        {
            if(_events[i]._endTime < END_OF_DAY)
            {
                _out<<_events[i]._endTime;
                _out<<" to ";
                _out<<END_OF_DAY;
                _freeTimeSlots.push_back(_out.str());
                _out.str("");
            }
        }

        if(_freeTimeSlots.size()==0)
            _freeTimeSlots.push_back("No Free Slots");
    }
}

void CentralStorage::mergeEverythingToMasterList()
{
    vector<EventData>::iterator _ContainerIter;
    vector<EventData> _forMasterList;

    for(_ContainerIter = _dueEvents.begin(); _ContainerIter < _dueEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _dueUrgentEvents.begin(); _ContainerIter < _dueUrgentEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _scheduledEvents.begin(); _ContainerIter < _scheduledEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _scheduledUrgentEvents.begin(); _ContainerIter < _scheduledUrgentEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _expiredDueEvents.begin(); _ContainerIter < _expiredDueEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _expiredScheduledEvents.begin(); _ContainerIter < _expiredScheduledEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }

    for(_ContainerIter = _doneEvents.begin(); _ContainerIter < _doneEvents.end(); _ContainerIter++)
    {
        _forMasterList.push_back(*_ContainerIter);
    }
    _masterList = _forMasterList;


}

string CentralStorage::convertStringToUpper(string _recString)
{
    string _processString;
    string _CompletedString;
    for(unsigned int i=0; i < _recString.length(); i++)
    {
        _processString =  toupper(_recString[i]);
        _CompletedString = _CompletedString + _processString;
    }
    return _CompletedString;
}

string CentralStorage::convertStringToLower(string _recString)
{
    string _processString;
    string _CompletedString;
    for(unsigned int i=0; i < _recString.length(); i++)
    {
        _processString =  tolower(_recString[i]);
        _CompletedString = _CompletedString + _processString;
    }
    return _CompletedString;
}



void CentralStorage::keepBackUp()
{
    _masterListBackup.clear();
    _masterList.clear();
    mergeEverythingToMasterList();
    _masterListBackup=_masterList;
    cout<<_masterListBackup.size()<<" "<<_masterList.size()<<endl;

}


void CentralStorage::undo()
{

    _masterList=_masterListBackup;

    for (unsigned int i=1; i<=7;i++)
    {
        _allContainers[i]->clear();
    }


    removeDoneEventFromMasterList();
    distDueEventScheduledEvent();
    sortDueEventByEndDateEndTime();
    sortscheduledEventByEndDateEndTime();
    extractAnnouncementEvents();
    extractExpiredEvents ();
    sortAllIndividualVector();


}


