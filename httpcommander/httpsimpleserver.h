/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stürz <simon.stuerz@guh.io>                   *
 *  Copyright (C) 2014 Michael Zanetti <michael_zanetti@gmx.net>           *
 *  Copyright (C) 2019 Bernhard Trinnes <bernhard.trinnes@nymea.io>        *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HTTPSIMPLESERVER_H
#define HTTPSIMPLESERVER_H

#include "typeutils.h"

#include <QTcpServer>
#include <QUuid>
#include <QDateTime>

class Device;
class DevicePlugin;

class HttpSimpleServer : public QTcpServer
{
    Q_OBJECT
public:
    HttpSimpleServer(QObject* parent = nullptr);
    ~HttpSimpleServer();
    void incomingConnection(qintptr socket) override;

signals:
    void disappear();
    void reconfigureAutodevice();
    void getRequestReceied(QUrl url);

private slots:
    void readClient();
    void discardClient();

private:
    QString generateHeader();

};

#endif // HttpSimpleServer_H
