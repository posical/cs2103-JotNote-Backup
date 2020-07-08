/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan
 *  File:   Color.cpp
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

#include "Color.h"

Color::Color(QWidget *parent) : QWidget(parent)
{}

Color::~Color()
{}

QString Color::BLACK(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#000000\">" + _text + "</font>";
    return _textMsg;
}

QString Color::GRAY(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#000000\">" + _text + "</font>";
    // #808080;
    return _textMsg;
}

QString Color::SILVER(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#000000\">" + _text + "</font>";
    // #C0C0C0;
    return _textMsg;
}

QString Color::WHITE(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#FFFFFF\">" + _text + "</font>";
    return _textMsg;
}

QString Color::MAROON(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#800000\">" + _text + "</font>";
    return _textMsg;
}

QString Color::RED(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#FF0000\">" + _text + "</font>";
    return _textMsg;
}

QString Color::OLIVE(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#808000\">" + _text + "</font>";
    return _textMsg;
}

QString Color::YELLOW(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#FFFF00\">" + _text + "</font>";
    return _textMsg;
}

QString Color::GREEN(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#008000\">" + _text + "</font>";
    return _textMsg;
}

QString Color::LIME(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#00FF00\">" + _text + "</font>";
    return _textMsg;
}

QString Color::TEAL(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#008080\">" + _text + "</font>";
    return _textMsg;
}

QString Color::AQUA(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#00FFFF\">" + _text + "</font>";
    return _textMsg;
}

QString Color::NAVY(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#000080\">" + _text + "</font>";
    return _textMsg;
}

QString Color::BLUE(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#0000FF\">" + _text + "</font>";
    return _textMsg;
}

QString Color::PURPLE(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#800080\">" + _text + "</font>";
    return _textMsg;
}

QString Color::FUCHSIA(QString _text)
{
    QString _textMsg;
    _textMsg ="<FONT COLOR=\"#FF00FF\">" + _text + "</font>";
    return _textMsg;
}

QString Color::randomColor(QString _text)
{
    QString _randColor;
    QString _colorValue;
    int _hexaCheck;

    srand((unsigned int)time(NULL));

    _colorValue = "";

    for(int i = 0; i<6 ; i++)
    {
        _hexaCheck = (rand()%16);
        _colorValue = _colorValue + hexaMap(_hexaCheck);
    }

    _randColor = "<FONT COLOR =\"#" + _colorValue + "\">" + _text + "</font>";

    //qDebug()<< "#" + _colorValue;

    return _randColor;
}

QString Color::hexaMap(int _hex)
{
    QString _str;

    switch(_hex)
    {
    case 0:
        _str = "0";
        break;
    case 1:
        _str = "1";
        break;
    case 2:
        _str = "2";
        break;
    case 3:
        _str = "3";
        break;
    case 4:
        _str = "5";
        break;
    case 5:
        _str = "5";
        break;
    case 6:
        _str = "6";
        break;
    case 7:
        _str = "7";
        break;
    case 8:
        _str = "8";
        break;
    case 9:
        _str = "9";
        break;
    case 10:
        _str = "A";
        break;
    case 11:
        _str = "B";
        break;
    case 12:
        _str = "C";
        break;
    case 13:
        _str = "D";
        break;
    case 14:
        _str = "E";
        break;
    case 15:
        _str = "F";
        break;
    default:
        break;
    }

    return _str;
}
