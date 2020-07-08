/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  Source File Author(s): Kenneth Pan
 *  File:   Color.h
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

#ifndef COLOR_H
#define COLOR_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <cstdlib>
#include <ctime>

using namespace std;

class Color : public QWidget
{
    Q_OBJECT

    private :
        QString hexaMap(int);

    public:
        Color(QWidget *parent = 0);
        ~Color();

        QString BLACK(QString);     //#000000
        QString GRAY(QString);      //#808080
        QString SILVER(QString);    //#C0C0C0
        QString WHITE(QString);     //#FFFFFF

        QString MAROON(QString);    //#800000
        QString RED(QString);       //#FF0000
        QString OLIVE(QString);     //#808000
        QString YELLOW(QString);    //#FFFF00

        QString GREEN(QString);     //#008000
        QString LIME(QString);      //#00FF00
        QString TEAL(QString);      //#008080
        QString AQUA(QString);      //#008080

        QString NAVY(QString);      //#000080
        QString BLUE(QString);      //#0000FF
        QString PURPLE(QString);    //#800080
        QString FUCHSIA(QString);   //#FF00FF

        QString randomColor(QString);

};

#endif /* COLOR_H */
