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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef QDEVICEPROFILE_LINUX_P_H
#define QDEVICEPROFILE_LINUX_P_H

#include <qdeviceprofile.h>

#if !defined(QT_NO_JSONDB)
#include <qjsondbwrapper_p.h>
#endif //QT_NO_JSONDB

QT_BEGIN_NAMESPACE

class QDeviceProfilePrivate : public QObject
{
    Q_OBJECT

public:
    QDeviceProfilePrivate(QDeviceProfile *parent);
    ~QDeviceProfilePrivate();

    bool isVibrationActivated();
    int messageRingtoneVolume();
    int voiceRingtoneVolume();
    QDeviceProfile::ProfileType currentProfileType();

Q_SIGNALS:
    void vibrationActivatedChanged(bool activated);
    void messageRingtoneVolumeChanged(int volume);
    void voiceRingtoneVolumeChanged(int volume);
    void currentProfileTypeChanged(QDeviceProfile::ProfileType profile);

protected:
    void connectNotify(const char *signal);
    void disconnectNotify(const char *signal);

private:
    QDeviceProfile * const q_ptr;
    Q_DECLARE_PUBLIC(QDeviceProfile)

#if !defined(QT_NO_JSONDB)
    QJsonDbWrapper jsondbWrapper;
#endif //QT_NO_JSONDB
};

QT_END_NAMESPACE

#endif // QDEVICEPROFILE_LINUX_P_H
