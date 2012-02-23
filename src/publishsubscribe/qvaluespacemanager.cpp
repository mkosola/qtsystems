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

#include "qvaluespacemanager_p.h"
#include "gconflayer_p.h"
#include "jsondblayer_p.h"
#include "registrylayer_win_p.h"

QT_BEGIN_NAMESPACE

Q_GLOBAL_STATIC(QValueSpaceManager, valueSpaceManager)

QValueSpaceManager *QValueSpaceManager::instance()
{
    return valueSpaceManager();
}

QValueSpaceManager::QValueSpaceManager()
    : initialized(false)
{
}

void QValueSpaceManager::init()
{
    if (initialized)
        return;
    initialized = true;

    // make sure layers are installed in the priority order from high to low
#if defined(Q_OS_LINUX)
#if !defined(QT_NO_GCONFLAYER)
    layers.append(GConfLayer::instance());
#endif
#if !defined(QT_NO_JSONDBLAYER)
    layers.append(JsonDbLayer::instance());
#endif
#elif defined(Q_OS_WIN)
    layers.append(NonVolatileRegistryLayer::instance());
    layers.append(VolatileRegistryLayer::instance());
#endif

    for (int ii = 0; ii < layers.count(); ++ii) {
        if (!layers.at(ii)->startup()) {
            layers.removeAt(ii);
            --ii;
        }
    }
}

QList<QAbstractValueSpaceLayer *> const &QValueSpaceManager::getLayers()
{
    init(); // Fallback init

    return layers;
}

QT_END_NAMESPACE
