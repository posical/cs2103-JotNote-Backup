/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:  CurrentTime.cpp
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

#include "CurrentTime.h"

CurrentTime::CurrentTime()
{}
CurrentTime::~CurrentTime()
{}

int CurrentTime::currentDate()
{
    time(&_now);
    _current = localtime(&_now);
    return _current->tm_mday ;
}

int CurrentTime::currentMonth()
{
    time(&_now);
    _current = localtime(&_now);
    return _current->tm_mon +1;
}

int CurrentTime::currentYear()
{
    time(&_now);
    _current = localtime(&_now);
    return _current->tm_year+1900;
}

int CurrentTime::currentDay()
{
    time(&_now);
    _current = localtime(&_now);
    return _current->tm_wday;
}

int CurrentTime::currentTime()
{
    time(&_now);
    _current = localtime(&_now);
    return _current->tm_hour*100 + _current->tm_min;
}
