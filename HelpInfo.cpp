/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   HelpInfo.cpp
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


#include "HelpInfo.h"

HelpInfo::HelpInfo()
{}

HelpInfo::~HelpInfo()
{}

void HelpInfo::extractHelpFromReadMe()
{
    ifstream readFile(HELP_README);
    string _extractString;
    while(getline(readFile,_extractString))
    { _helpInString.push_back(_extractString);}
    readFile.close();
}

string HelpInfo::pop_back_string()
{
    string _retString;
    _retString = _helpInString.back();
    _helpInString.pop_back();
    return _retString;
}

bool HelpInfo::isEmpty()
{ return _helpInString.empty();}

void HelpInfo::swapFrontAndBack()
{
    vector <string> _helpTemp;
    while(!_helpInString.empty())
    {
        string stringTemp;
        stringTemp = _helpInString.back();
        _helpTemp.push_back(stringTemp);
        _helpInString.pop_back();
    }
    _helpInString = _helpTemp;
}

vector <string> HelpInfo::getHelpDetails()
{
    vector<string> _helpTemp;
    extractHelpFromReadMe();
    _helpTemp = _helpInString;
    _helpInString.clear();
    return _helpTemp;
}
