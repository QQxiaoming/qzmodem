/*
 * This file is part of the https://github.com/QQxiaoming/qzmodem.git
 * project.
 *
 * Copyright (C) 2024 Quard <2014500726@smail.xtu.edu.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation; either version 3 of the 
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef QZMODEM_H
#define QZMODEM_H

#include <QObject>
#include <zglobal.h>

class QZmodem : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        SEND,
        RECV
    }dir_t;
    explicit QZmodem(dir_t dir=SEND, QObject *parent = nullptr);
    ~QZmodem(){};

public:
    dir_t m_dir;
};

#endif // QZMODEM_H
