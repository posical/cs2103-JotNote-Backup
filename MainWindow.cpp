/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan
 *  File:   MainWindow.cpp
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

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "API.h"
#include "Utility.h"
#include <QLabel>

MainWindow::MainWindow(int _theme, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(writeText(QString)));
    setPaletteDesign(_theme);
    _util = new Utility(this);
}

MainWindow::~MainWindow()
{
    delete _util;
    _util = NULL;
    delete ui;
    ui = NULL;
}

void MainWindow::setPaletteDesign(int _theme)
{
    palette = new QPalette();

    switch(_theme)
    {
    case 0:
        palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(BACKGROUND1)))));
        break;
    case 1:
        palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(BACKGROUND2)))));
        break;
    case 2:
        palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(BACKGROUND3)))));
        break;
    case 3:
        palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(BACKGROUND4)))));
        break;
    default:
        break;
    }
    setPalette(*palette);
}

void MainWindow::on_lineEdit_returnPressed()
{
    _cmdString = _textLine;
    ui->lineEdit->clear();
    emit pushCmd();
}

void MainWindow::writeText(QString _textString)
{
    _textLine = _textString.toStdString();
}

string MainWindow::retrieveCmd()
{
    return _cmdString;
}

string MainWindow::retrieveHintString()
{
    return _textLine;
}

string MainWindow::retrieveWordCheck()
{
    return _textLine;
}

string MainWindow::retrieveSearchString()
{
    return _searchString;
}

void MainWindow::setDynamicAttribute(vector<string> _dyna)
{
    _retDyna = _dyna;
}

void MainWindow::setDueListAttribute(vector<string> _dueList)
{
    _retDue = _dueList;
}

void MainWindow::setScheduleListAttribute(vector<string> _scheduleList)
{
    _retSchedule = _scheduleList;
}

void MainWindow::setUrgentDueListAttribute(vector<string> _dueUrgent)
{
    _retUrgentDue = _dueUrgent;
}

void MainWindow::setUrgentScheduleListAttribute(vector<string> _scheduleUrgent)
{
    _retUrgentSchedule = _scheduleUrgent;
}

void MainWindow::setMissedDueListAttribute(vector<string> _missedDue)
{
    _retMissedDue = _missedDue;
}

void MainWindow::setMissedScheduleListAttribute(vector<string> _missedSchedule)
{
    _retMissedSchedule = _missedSchedule;
}

void MainWindow::displayDynamic()
{
    QString _dyna;

    ui->textDynamic->clear();
    for(unsigned int i = 0; i < _retDyna.size(); i++)
    {
        _dyna = _dyna.fromStdString(_retDyna[i]);
        _dyna = _util->BOLD(_dyna);
        _dyna = _util->_color->FUCHSIA(_dyna);
        ui->textDynamic->insertHtml(_dyna + _util->LINEBREAK());
    }

    _retDyna.clear();
}

void MainWindow::displayEvent()
{
    QString _scheduleEvent,_urgentSchedule,_missedSchedule;
    QString _dueEvent,_urgentDue,_missedDue;

    ui->textSchedule->clear();

    for(unsigned int i = 0; i< _retMissedSchedule.size();i++)
    {
        _missedSchedule = _missedSchedule.fromStdString(_retMissedSchedule[i]);
        _missedSchedule = _util->_color->PURPLE(_missedSchedule);
        ui->textSchedule->insertHtml(_missedSchedule);
    }

    for(unsigned int i = 0; i< _retUrgentSchedule.size();i++)
    {
        _urgentSchedule = _urgentSchedule.fromStdString(_retUrgentSchedule[i]);
        _urgentSchedule = _util->_color->RED(_urgentSchedule);
        ui->textSchedule->insertHtml(_urgentSchedule);
    }

    for(unsigned int i = 0; i < _retSchedule.size(); i++)
    {
        _scheduleEvent = _scheduleEvent.fromStdString(_retSchedule[i]);
        _scheduleEvent = _util->_color->TEAL(_scheduleEvent);
        ui->textSchedule->insertHtml(_scheduleEvent);
    }

    ui->textDue->clear();

    for(unsigned int i = 0; i< _retMissedDue.size();i++)
    {
        _missedDue = _missedDue.fromStdString(_retMissedDue[i]);
        _missedDue = _util->_color->PURPLE(_missedDue);
        ui->textDue->insertHtml(_missedDue);
    }

    for(unsigned int i = 0; i < _retUrgentDue.size(); i++)
    {
        _urgentDue = _urgentDue.fromStdString(_retUrgentDue[i]);
        _urgentDue = _util->_color->RED(_urgentDue);
        ui->textDue->insertHtml(_urgentDue);
    }

    for(unsigned int i = 0; i < _retDue.size(); i++)
    {
        _dueEvent = _dueEvent.fromStdString(_retDue[i]);
        _dueEvent = _util->_color->BLUE(_dueEvent);
        ui->textDue->insertHtml(_dueEvent);
    }

    _retSchedule.clear();
    _retDue.clear();
    _retUrgentDue.clear();
    _retUrgentSchedule.clear();
    _retMissedDue.clear();
    _retMissedSchedule.clear();
}

void MainWindow::printDisplay()
{
    displayEvent();
}

void MainWindow::on_pushSomething_clicked()
{
    ui->textDynamic->clear();
    emit findSlot();
}

void MainWindow::on_pushSearch_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("search ");
}

void MainWindow::on_pushModify_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("mod ");
}

void MainWindow::on_pushRemove_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("rmv ");
}

void MainWindow::on_pushAdd_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("add ");
}

void MainWindow::on_lineEdit_textChanged(const QString &_arg1)
{
    _searchString = _arg1.toStdString();

    istringstream _checker(_searchString);
    string _subChecker;
    _checker >> _subChecker;
    if(_subChecker == "search")
    {
        emit pushSearch();
    }
    else
    {
        emit pushWordCheck();
    }
}

void MainWindow::printErrorMsg(string _errPrint)
{
    QString _msg;
    ui->textDynamic->clear();
    _msg = _msg.fromStdString(_errPrint);
    _msg = _util->BOLD(_msg);
    _msg = _util->_color->RED(_msg);
    ui->textDynamic->insertHtml(_msg);
}

void MainWindow::errWrongCmd()
{
    printErrorMsg(MESSAGE_WRONG_COMMAND);
}

void MainWindow::errIncompleteCmd()
{
    printErrorMsg(MESSAGE_INCOMPLETE_COMMAND);
}

void MainWindow::errInvalDate()
{
    printErrorMsg(MESSAGE_INVALID_DATE);
}

void MainWindow::errInvalTime()
{
    printErrorMsg(MESSAGE_INVALID_TIME);
}

void MainWindow::errNameClash()
{
    printErrorMsg(ERROR_ADD_NAME_CLASH);

}
void MainWindow::errTimeClash()
{
    printErrorMsg(ERROR_ADD_TIME_CLASH);
}
void MainWindow::errRemoveNot()
{
    printErrorMsg(ERROR_REMOVE_NOT_FOUND);
}

void MainWindow::on_actionNeon_triggered()
{
    emit pushNeon();
}

void MainWindow::on_actionSakura_triggered()
{
    emit pushSakura();
}

void MainWindow::on_actionKona_triggered()
{
    emit pushKona();
}

void MainWindow::on_actionCheckered_triggered()
{
    emit pushCheckered();
}

void MainWindow::on_actionHelp_Info_triggered()
{
    ui->textDynamic->clear();
    emit findHelp();
}

void MainWindow::on_pushHistory_clicked()
{
    emit hist();
}

void MainWindow::on_actionClear_Cache_triggered()
{
    emit clearCache();
}
