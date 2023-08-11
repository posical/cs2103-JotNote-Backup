/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   ExtractDatabase.cpp
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


#include "ExtractDatabase.h"

using namespace std;

ExtractDatabase::ExtractDatabase()
{}

ExtractDatabase::~ExtractDatabase()
{}

vector <EventData> ExtractDatabase::addEventFromDatabaseToExtractDatabase()       
{
    ifstream _readFile(INPUT_DATABASE);
    EventData _d;
    string _recieveString,_stringTemp, _stringTemp2;
    string _checkerString;
    //int _checkerInt;

    while(getline(_readFile,_recieveString))
    {
        istringstream in(_recieveString);

        in >> _checkerString;

        if(_checkerString == CORRECT )
        {_d.done = true; }
        else
        {_d.done = false;}

        in >> _checkerString;
        _d._stDate = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _d._stMonth = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _d._stYear = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _d._endDate = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _d._endMonth = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _d._endYear = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _stringTemp = checkStringInputForDefault(_checkerString);

        if(_stringTemp == DEFAULT_NEG)
        {
            _d._details = DEFAULT_NEG;
            in >> _checkerString;     //load one more (ideally should be start time)
        }

        else
        {
            _stringTemp += " ";
            while(in >> _checkerString)
            {
                if((isdigit(_checkerString[0])) || (isdigit(_checkerString[1])))
                {
                    _stringTemp.erase(_stringTemp.size()-1,1);
                    _d._details = _stringTemp;
                    break;
                }
                else
                {_stringTemp = _stringTemp + _checkerString + " ";}
            }//end of while
        }//end of else

        _stringTemp.clear();

        _d._stTime = checkIntInputForDefault(_checkerString);

        in >> _checkerString;

        _d._endTime = checkIntInputForDefault(_checkerString);

        in >> _checkerString;
        _stringTemp = checkStringInputForDefault(_checkerString);

        if(_stringTemp == DEFAULT_NEG)
        {
            _d._taskName = DEFAULT_NEG;
        }

        else
        {
            _stringTemp += " ";
            while(in >> _checkerString)
            {
                _stringTemp = _stringTemp + _checkerString + " ";
            }//end of while
            _stringTemp.erase(_stringTemp.size()-1,1);
            _d._taskName = _stringTemp;
        }//end of else

        _stringTemp.clear();
        _rawDataFromDatabase.push_back(_d);
    }//end of big while

    _readFile.close();
    return _rawDataFromDatabase;
} 

void ExtractDatabase::transferFromExtractDatabaseToDatabase(vector <EventData> _rD)
{
    _rawDataFromDatabase = _rD;
    EventData  _retEventData;
    EventData *_ptrToCurrentData;
    ofstream _writeFile(OUTPUT_DATABASE);

    while(!_rawDataFromDatabase.empty())
    {
        bool _adjustForLeadingZero(false);
        int _intTemp;
        string _stringTemp;
        _retEventData = _rawDataFromDatabase.back();
        _ptrToCurrentData = &_retEventData;
        _adjustForLeadingZero = checkEventDataForLeadingZero(_ptrToCurrentData);

        if(_retEventData.done == true)
        { _writeFile << "T" << " "; }

        else
        { _writeFile << "F" << " "; }

        _writeFile << setfill('0') << setw(2) << _retEventData._stDate << " ";
        _writeFile << setfill('0') << setw(2) << _retEventData._stMonth << " ";
        _writeFile << setfill('0') << setw(2) << _retEventData._stYear << " ";
        _writeFile << setfill('0') << setw(2) << _retEventData._endDate << " ";
        _writeFile << setfill('0') << setw(2) << _retEventData._endMonth << " ";
        _writeFile << setfill('0') << setw(2) << _retEventData._endYear << " ";

        _stringTemp = _retEventData._details;

        if((_stringTemp == DEFAULT_NEG) || (_stringTemp == ""))
        { _writeFile << DEFAULT_NEG << " "; }
        else
        {_writeFile << _retEventData._details << " "; }

        if(_adjustForLeadingZero)
        {
            _intTemp = _retEventData._stTime;
            if(_intTemp == DEFAULT)
            {_writeFile << setfill('0') << setw(2) << _retEventData._stTime << " "; }
            else
            {_writeFile << setfill('0') << setw(4)  << _retEventData._stTime << " "; }
        }

        else
        {_writeFile << setfill('0') << setw(4) << _retEventData._stTime << " "; }

        _writeFile << setfill('0') << setw(4) << _retEventData._endTime << " ";   //erase the bracket

        _stringTemp = _retEventData._taskName;

        if(_stringTemp == DEFAULT_NEG)
        { _writeFile << DEFAULT_NEG << endl; }
        else
        {_writeFile << _retEventData._taskName << endl;}

        _rawDataFromDatabase.pop_back();
        _adjustForLeadingZero = false;
    }
    _writeFile.close();
}

int ExtractDatabase::checkIntInputForDefault(string _inputPara)
{
    int _returnIntValue;
    
    if(_inputPara == DEFAULT_NEG)
    { _returnIntValue = DEFAULT; }
    else
    { _returnIntValue = atoi(_inputPara.c_str()); }
    
    return _returnIntValue;
}

string ExtractDatabase::checkStringInputForDefault(string _inputPara)
{
    string _returnStringValue;
    
    if(_inputPara == DEFAULT_NEG)
    { _returnStringValue = DEFAULT_NEG; }
    else
    { _returnStringValue = _inputPara; }
    
    return _returnStringValue;
}

bool ExtractDatabase::checkEventDataForLeadingZero(EventData *_dataForCheck)
{
    bool _detectedwithLeadingZero, _startTimeWithLeadingZero; // _endTimeWithLeadingZero;
    int _intTemp;

    _intTemp = _dataForCheck->_stTime;
    _startTimeWithLeadingZero = markLeadingZero(_intTemp);
    
    return _detectedwithLeadingZero = _startTimeWithLeadingZero; //+ _endTimeWithLeadingZero;
}

bool ExtractDatabase::markLeadingZero(int _dataOfLeadingZero)
{
    bool _result;
    return _result = (_dataOfLeadingZero == -1)?true:false;
}
