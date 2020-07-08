/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan
 *  File:   MainWindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <string>
#include "ErrorMessage.h"
#include "Utility.h"

#define BACKGROUND1 "images/abc0.jpg"
#define BACKGROUND2 "images/abc1.jpg"
#define BACKGROUND3 "images/abc2.jpg"
#define BACKGROUND4 "images/abc3.jpg"

using namespace std;

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QPalette *palette;
        string _searchString;
        string _cmdString;
        string _textLine;
        vector<string> _retDyna;
        vector<string> _retDue, _retUrgentDue, _retMissedDue;
        vector<string> _retSchedule, _retUrgentSchedule, _retMissedSchedule;

        void displayEvent();
        void setPaletteDesign(int);
        void printErrorMsg(string);

    public:
        Ui::MainWindow *ui;
        Utility *_util;
        MainWindow(QWidget *parent = 0);
        MainWindow(int, QWidget *parent = 0);
        ~MainWindow();

        string retrieveCmd();
        string retrieveSearchString();
        string retrieveHintString();
        string retrieveWordCheck();

        void setDynamicAttribute(vector<string> _dyna);

        void setDueListAttribute(vector<string> _dueList);
        void setScheduleListAttribute(vector<string> _scheduleList);

        void setUrgentDueListAttribute(vector<string> _dueUrgent);
        void setUrgentScheduleListAttribute(vector<string> _scheduleUrgent);

        void setMissedDueListAttribute(vector<string> _missedDue);
        void setMissedScheduleListAttribute(vector<string> _missedSchedule);

    signals:
        void pushCmd();
        void findHelp();
        void findSlot();
        void pushSearch();
        void pushWordCheck();
        void hist();
        void clearCache();

        void pushNeon();
        void pushSakura();
        void pushKona();
        void pushCheckered();

    private slots:
        void on_lineEdit_returnPressed();
        void displayDynamic();
        void writeText(QString _textString);
        void printDisplay();

        void on_pushSomething_clicked();
        void on_lineEdit_textChanged(const QString &arg1);

        void errWrongCmd();
        void errIncompleteCmd();
        void errInvalDate();
        void errInvalTime();
        void errNameClash();
        void errTimeClash();
        void errRemoveNot();

        void on_pushSearch_clicked();
        void on_pushModify_clicked();
        void on_pushRemove_clicked();
        void on_pushAdd_clicked();

        void on_actionNeon_triggered();
        void on_actionSakura_triggered();
        void on_actionKona_triggered();
        void on_actionCheckered_triggered();
        void on_actionHelp_Info_triggered();
        void on_pushHistory_clicked();
        void on_actionClear_Cache_triggered();

};

#endif /* MAINWINDOW_H */
