/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan
 *  File:   API.cpp
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

#include "API.h"

API::API(QWidget *parent) : QWidget(parent)
{}

API::API(int _theme, QWidget *parent) : QWidget(parent)
{
    _toDo = new MainWindow(_theme,this);
    _toDo->show();
    connect(_toDo, SIGNAL(pushCmd()), this, SLOT(passCmd()));
    connect(this, SIGNAL(pushDynamic()), _toDo, SLOT(displayDynamic()));
    connect(this, SIGNAL(printList()),_toDo, SLOT(printDisplay()));
    connect(_toDo, SIGNAL(findHelp()), this, SLOT(loadHelp()));
    connect(_toDo, SIGNAL(findSlot()), this, SLOT(loadFindSlots()));
    connect(_toDo, SIGNAL(pushSearch()), this, SLOT(passSearchString()));
    connect(_toDo, SIGNAL(pushWordCheck()), this, SLOT(loadWordCheck()));
    connect(_toDo, SIGNAL(hist()), this, SLOT(loadHistory()));
    connect(_toDo, SIGNAL(clearCache()), this, SLOT(clearAllCacheInWordList()));

    _err = new ErrorClass(this);

    connect(_err, SIGNAL(sigWrongCmd()), _toDo, SLOT(errWrongCmd()));
    connect(_err, SIGNAL(sigInvDate()), _toDo, SLOT(errInvalDate()));
    connect(_err, SIGNAL(sigIncCmd()), _toDo, SLOT(errIncompleteCmd()));
    connect(_err, SIGNAL(sigNameClash()), _toDo, SLOT(errNameClash()));
    connect(_err, SIGNAL(sigTimeClash()), _toDo, SLOT(errTimeClash()));
    connect(_err, SIGNAL(sigRemoveNotFound()), _toDo, SLOT(errRemoveNot()));
    connect(_err, SIGNAL(sigInvTime()), _toDo, SLOT(errInvalTime()));

    _wordIdent = new WordIdentifier();
    _centralStorage = new CentralStorage();
    runUpdateLoop();
}

API::~API()
{
    _centralStorage->transferDataToExtractDatabase();
    delete _toDo;
    _toDo = NULL;
    delete _centralStorage;
    _centralStorage = NULL;

}

MainWindow *API::returnMWpointer()
{
    return _toDo;
}

void API::processCommand()
{
    int _checkFlag = 0;
    string _checkMsgError;

    string task=_textUI.processCommand(_incomingCmd);
    _eventData=_textUI.getEventInfo();

    vector <string> _doneEvents, _freeSlots;
    vector <EventData> _temp;

    if(task==COMMAND_ADD_TASK) {_checkFlag = 1;}
    if(task==COMMAND_MODIFY_TASK) {_checkFlag = 2;}
    if(task==COMMAND_REMOVE_TASK_BY_NAME) {_checkFlag = 3;}
    if(task==COMMAND_REMOVE_TASK_BY_ID) {_checkFlag = 4;}
    if(task==COMMAND_MARK_DONE) {_checkFlag = 5;}
    if(task==COMMAND_UNDO) {_checkFlag = 6;}
    if(task==COMMAND_FIND_SLOT) {_checkFlag = 7;}
    if(task==COMMAND_LIST_HISTORY) {_checkFlag = 8;}
    if(task==MESSAGE_WRONG_COMMAND) {_checkFlag = 9;}
    if(task==MESSAGE_INCOMPLETE_COMMAND) {_checkFlag = 10;}
    if(task==MESSAGE_INVALID_DATE) {_checkFlag = 11;}
    if(task==MESSAGE_INVALID_TIME) {_checkFlag = 12;}

    switch(_checkFlag)
    {
    case 1:
        _checkMsgError = _centralStorage->addEvent(_eventData);
        if(_checkMsgError == ERROR_ADD_NAME_CLASH) { _err->nameClash(); }
        if(_checkMsgError == ERROR_ADD_TIME_CLASH) { _err->timeClash(); }
        break;
    case 2:
        _checkMsgError = _centralStorage->modifyEvent(_eventData);
        if(_checkMsgError == ERROR_ADD_NAME_CLASH) { _err->nameClash(); }
        if(_checkMsgError == ERROR_ADD_TIME_CLASH) { _err->timeClash(); }
        if(_checkMsgError == ERROR_REMOVE_NOT_FOUND) { _err->removeNotFound(); }
        break;
    case 3:
        _checkMsgError = _centralStorage->removeEventByName(_textUI.getRmvEventName());
        if(_checkMsgError == ERROR_REMOVE_NOT_FOUND) { _err->removeNotFound(); }
        break;
    case 4:
        _checkMsgError = _centralStorage->removeEventById(_textUI.getRmvEventType(), _textUI.getRmvEventId());
        if(_checkMsgError == ERROR_REMOVE_NOT_FOUND) { _err->removeNotFound(); }
        break;
    case 5:
        _centralStorage->markEvent(_eventData);
        break;
    case 6:
        _centralStorage->undo();
        break;
    case 7:
        _centralStorage->findFreeTimeSlots(_textUI.getFindSlotStDate(), _textUI.getFindSlotStMonth(), _textUI.getFindSlotStYear() );
        _freeSlots=_centralStorage->extractFreeTimeSlots();
        _toDo->setDynamicAttribute(_freeSlots);
        emit pushDynamic();
        break;
    case 8:
        _temp=_centralStorage->retrieveDoneEvents();
        _eventList.formatForDynamicWindow(_temp);
        _doneEvents=_eventList.retrieveDynamicWindowString();
        _toDo->setDynamicAttribute(_doneEvents);
        emit pushDynamic();
        break;
    case 9:
        _err->wrongCmd();
        break;
    case 10:
        _err->incCmd();
        break;
    case 11:
        _err->invDate();
        break;
    case 12:
        _err->invTime();
        break;
    default:
        break;
    }

    if(_checkFlag >= 1 && _checkFlag <= 6)
    {
        runUpdateLoop();
    }
}

void API::passCmd()
{
    _incomingCmd = _toDo->retrieveCmd();
    processCommand();
}

void API::loadHelp()
{
    vector<string> _help;
    _help = _helpFile.getHelpDetails();
    _toDo->setDynamicAttribute(_help);
    emit pushDynamic();
}

void API::loadFindSlots()
{
    _incomingCmd = COMMAND_FIND_SLOT;
    processCommand();
}

void API::runUpdateLoop()
{
    _dueEventList = _centralStorage->retrieveDueEvent();
    _eventList.formatString(_dueEventList,_centralStorage->retrieveMissedDueEventNumber()+_centralStorage->retrieveDueUrgentEventNumber()+1, EVENT_TYPE_DUE);
    _scheduleEventList = _centralStorage->retrieveScheduledEvent();
    _eventList.formatString(_scheduleEventList,_centralStorage->retrieveMissedScheduledEventNumber()+_centralStorage->retrieveScheduledUrgentEventNumber()+1,EVENT_TYPE_SCHEDULED);

    _dueUrgentEventList = _centralStorage->retrieveUrgentDueEvent();
    _eventList.formatString(_dueUrgentEventList, _centralStorage->retrieveMissedDueEventNumber()+1 , EVENT_TYPE_DUE_URGENT );
    _scheduleUrgentEventList = _centralStorage->retrieveUrgentScheduledEvent();
    _eventList.formatString(_scheduleUrgentEventList, _centralStorage->retrieveMissedScheduledEventNumber()+1 , EVENT_TYPE_SCHEDULED_URGENT );


    _missedDueEventList = _centralStorage->retrieveMissedDueEvent();
    _eventList.formatString(_missedDueEventList,1, EVENT_TYPE_MISSED_DUE);
    _missedScheduledEventList = _centralStorage->retrieveMissedScheduledEvent();
    _eventList.formatString(_missedScheduledEventList,1,EVENT_TYPE_MISSED_SCHEDULED);


    _eventDueStringVector = _eventList.retrieveDueList();
    _toDo->setDueListAttribute(_eventDueStringVector);
    _eventScheduleStringVector = _eventList.retrieveScheduleList();
    _toDo->setScheduleListAttribute(_eventScheduleStringVector);

    _eventDueStringUrgent = _eventList.retrieveUrgentDueList();
    _toDo->setUrgentDueListAttribute(_eventDueStringUrgent);
    _eventScheduleStringUrgent = _eventList.retrieveUrgentScheduleList();
    _toDo->setUrgentScheduleListAttribute(_eventScheduleStringUrgent);

    _eventMissedDueString = _eventList.retrieveExpiredDueList();
    _toDo->setMissedDueListAttribute(_eventMissedDueString);
    _eventMissedScheduledString = _eventList.retrieveExpiredScheduledList() ;
    _toDo->setMissedScheduleListAttribute(_eventMissedScheduledString);

    emit printList();
}

void API::passSearchString()
{
    vector<EventData> _temp;
    vector<string> _search;
    _searchString = _toDo->retrieveSearchString();
    _centralStorage->searchEvent(_searchString);
    _temp = _centralStorage->retrieveSearchResult();
    _eventList.formatForDynamicWindow(_temp);
    _search = _eventList.retrieveDynamicWindowString();
    _toDo->setDynamicAttribute(_search);
    emit pushDynamic();
}

void API::loadWordCheck()
{
    vector<string> _findWord;
    string _checkWord;
    _checkWord = _toDo->retrieveWordCheck();
    _findWord = _wordIdent->findRecommendedWord(_checkWord);
    _toDo->setDynamicAttribute(_findWord);
    emit pushDynamic();
}

void API::loadHistory()
{
    _incomingCmd = COMMAND_LIST_HISTORY;
    processCommand();
}

void API::clearAllCacheInWordList()
{
    _wordIdent->clearLearnedAndPendingLearn();
}
