/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   API.h
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


#ifndef API_H
#define API_H

#include <QtCore/QObject>
#include "MainWindow.h"
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <string>
#include <vector>
#include "CentralStorage.h"
#include "EventData.h"
#include "TextUI.h"
#include "EventList.h"
#include "HelpInfo.h"
#include "ErrorClass.h"
#include "WordIdentifier.h"

using namespace std;

class API : public QWidget
{
    Q_OBJECT

    private:
        TextUI _textUI;
        string _incomingCmd;
        string _wordString;
        string _searchString;
        HelpInfo _helpFile;
        EventList _eventList;
        EventData _eventData;
        ErrorClass* _err;
        MainWindow *_toDo;
        CentralStorage *_centralStorage;
        WordIdentifier *_wordIdent;
        vector<string> _eventDueStringVector, _eventDueStringUrgent, _eventMissedDueString;
        vector<string> _eventScheduleStringVector, _eventScheduleStringUrgent, _eventMissedScheduledString;
        vector<EventData> _masterEventList;
        vector<EventData> _scheduleEventList, _scheduleUrgentEventList, _missedScheduledEventList;
        vector<EventData> _dueEventList, _dueUrgentEventList, _missedDueEventList;

        void processCommand();
        void runUpdateLoop();

    public:
        API(QWidget *parent = 0);
        API(int, QWidget *parent = 0);
        virtual ~API();
        MainWindow* returnMWpointer();

    signals:
        void pushDynamic();
        void cmdErrorWC();
        void cmdErrorIncC();
        void cmdErrorInvDate();
        void printList();

    private slots:
        void passCmd();
        void loadHelp();
        void loadFindSlots();
        void passSearchString();
        void loadWordCheck();
        void loadHistory();
        void clearAllCacheInWordList();

};

#endif	/* API_H */

