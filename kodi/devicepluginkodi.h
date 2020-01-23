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

#ifndef DEVICEPLUGINKODI_H
#define DEVICEPLUGINKODI_H

#include "devices/deviceplugin.h"
#include "plugintimer.h"
#include "kodi.h"

#include <QHash>
#include <QDebug>
#include <QTcpSocket>

class ZeroConfServiceBrowser;

class DevicePluginKodi : public DevicePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "io.nymea.DevicePlugin" FILE "devicepluginkodi.json")
    Q_INTERFACES(DevicePlugin)

public:
    explicit DevicePluginKodi();
    ~DevicePluginKodi();

    void init() override;
    void setupDevice(DeviceSetupInfo *info) override;
    void deviceRemoved(Device *device) override;
    void discoverDevices(DeviceDiscoveryInfo *info) override;
    void executeAction(DeviceActionInfo *info) override;

    void browseDevice(BrowseResult *result) override;
    void browserItem(BrowserItemResult *result) override;
    void executeBrowserItem(BrowserActionInfo *info) override;
    void executeBrowserItemAction(BrowserItemActionInfo *info) override;

private:
    PluginTimer *m_pluginTimer;
    QHash<Kodi*, Device*> m_kodis;
    QHash<Kodi*, DeviceSetupInfo*> m_asyncSetups;
    ZeroConfServiceBrowser *m_serviceBrowser = nullptr;
    ZeroConfServiceBrowser *m_httpServiceBrowser = nullptr;

    QHash<int, DeviceActionInfo*> m_pendingActions;
    QHash<int, BrowserActionInfo*> m_pendingBrowserActions;
    QHash<int, BrowserItemActionInfo*> m_pendingBrowserItemActions;

private slots:
    void onPluginTimer();
    void onConnectionChanged(bool connected);
    void onStateChanged();
    void onActionExecuted(int actionId, bool success);
    void onBrowserItemExecuted(int actionId, bool success);
    void onBrowserItemActionExecuted(int actionId, bool success);

    void onPlaybackStatusChanged(const QString &playbackStatus);
};

#endif // DEVICEPLUGINKODI_H
