/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   Config.cpp
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

#include "Config.h"

Config::Config(QWidget *parent) : QWidget(parent)
{
    ifstream _readConfig(CONFIG);
    string _receiver;
    int _checkerIdentifier;

    while(getline(_readConfig,_receiver))
    {
        istringstream _checker(_receiver);

        _checker >> _checkerIdentifier;

        switch(_checkerIdentifier)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            _theme = _checkerIdentifier;
            break;

        default:
            _theme = 0;
            cout << " ERROR : Theme Value Out of Range" << endl;
            break;
        }

    }

    _runInstance = new API(_theme,this);
    _readConfig.close();

    connect(_runInstance->returnMWpointer(), SIGNAL(pushNeon()), this, SLOT(setNeon()));
    connect(_runInstance->returnMWpointer(), SIGNAL(pushSakura()), this, SLOT(setSakura()));
    connect(_runInstance->returnMWpointer(), SIGNAL(pushKona()), this, SLOT(setKona()));
    connect(_runInstance->returnMWpointer(), SIGNAL(pushCheckered()), this, SLOT(setCheckered()));
}

Config::~Config()
{
    delete _runInstance;
    _runInstance = NULL;
}

void Config::setNeon()
{
    writeConfigValue(0);
}

void Config::setSakura()
{
    writeConfigValue(1);
}

void Config::setKona()
{
    writeConfigValue(2);
}

void Config::setCheckered()
{
    writeConfigValue(3);
}

void Config::writeConfigValue(int _intTheme)
{
    ofstream _writeConfig(CONFIG);

    _writeConfig << _intTheme << endl;

    _writeConfig.close();
}
