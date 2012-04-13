/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include "qdeclarativebatteryinfo_p.h"
#include "qdeclarativedeviceinfo_p.h"
#include "qdeclarativedeviceprofile_p.h"
#include "qdeclarativedisplayinfo_p.h"
#include "qdeclarativenetworkinfo_p.h"
#include <qscreensaver.h>
#include "qdeclarativestorageinfo_p.h"

QT_BEGIN_NAMESPACE

class QSystemInfoDeclarativeModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "systeminfo.json")

public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtSystemInfo"));

        int major = 5;
        int minor = 0;
        qmlRegisterType<QDeclarativeBatteryInfo>(uri, major, minor, "BatteryInfo");
        qmlRegisterType<QDeclarativeDeviceInfo>(uri, major, minor, "DeviceInfo");
        qmlRegisterType<QDeclarativeDeviceProfile>(uri, major, minor, "DeviceProfile");
        qmlRegisterType<QDeclarativeDisplayInfo>(uri, major, minor, "DisplayInfo");
        qmlRegisterType<QDeclarativeNetworkInfo>(uri, major, minor, "NetworkInfo");
        qmlRegisterType<QScreenSaver>(uri, major, minor, "ScreenSaver");
        qmlRegisterType<QDeclarativeStorageInfo>(uri, major, minor, "StorageInfo");
    }
};

QT_END_NAMESPACE

#include "qsysteminfo.moc"

/*!
    \qmlclass ScreenSaver QScreenSaver
    \inqmlmodule QtSystemInfo
    \ingroup qml-systeminfo
    \brief The ScreenSaver element provides information about the screen saver.
*/

/*!
    \qmlproperty bool ScreenSaver::screenSaverEnabled

    This property holds whether or not the screen saver is enabled.

    On certain platforms, if screen saver is disabled, deep system sleep won't be automatically triggered,
    and the display won't be automatically turned off, etc.
*/
