/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2020, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SUNNYWEBBOX_H
#define SUNNYWEBBOX_H

#include "integrations/thing.h"
#include "sunnywebboxcommunication.h"

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>

class SunnyWebBox : public QObject
{
    Q_OBJECT

public:
    struct Overview {
        int power;
        double dailyYield;
        int totalYield;
        QString status;
        QString error;
    };

    struct Device {
        QString key;
        QString name;
        QList<Device> childrens;
    };

    struct Channel {
        QString meta;
        QString name;
        QVariant value;
        QString unit;
    };

    explicit SunnyWebBox(SunnyWebBoxCommunication *communication, const QHostAddress &hostAddress, QObject *parrent = 0);

    int getPlantOverview();
    int getDevices();
    int getProcessDataChannels(const QString &deviceKey);
    int getProcessData(const QStringList &deviceKeys);
    int getParameterChannels(const QString &deviceKey);
    int getParameters(const QStringList &deviceKeys);

    void setHostAddress();
    QHostAddress hostAddress();

private:

    QHostAddress m_hostAddresss;
    SunnyWebBoxCommunication *m_communication = nullptr;

public slots:
    void onDatagramReceived(const QByteArray &data);
    void onMessageReceived(const QHostAddress &address, int messageId, const QString &messageType, const QVariantMap &result);

signals:
    void connectedChanged(bool connected);

    void plantOverviewReceived(int messageId, Overview overview);
    void devicesReceived(int messageId, QList<Device> devices);
    void processDataReceived(int messageId, const QString &deviceKey, const QHash<QString, QVariant> &channels);
    void parameterChannelsReceived(int messageId, const QString &deviceKey, QStringList parameterChannels);
};

#endif // SUNNYWEBBOX_H
