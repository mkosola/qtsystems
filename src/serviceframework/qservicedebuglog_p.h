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



#ifndef QSERVICEDEBUGLOG_P_H
#define QSERVICEDEBUGLOG_P_H

#include <QString>
#include <QStringList>
#include <QBuffer>
#include <QDataStream>
#include <QSharedPointer>
#include <QMutex>
#include <QVector>

QT_BEGIN_NAMESPACE

class QServiceDebugMessage
{
public:
    enum DataType {
        Int32Type = 1,
        FloatType = 2,
        StringType = 3
    };

    QServiceDebugMessage();
    ~QServiceDebugMessage();

    QBuffer *buffer;
    QDataStream ds;
};

class QServiceDebugValue;
class QServiceDebugKey;
class QUdpSocket;

class QServiceDebugLog
{
public:
    QServiceDebugLog();

    static QServiceDebugLog* instance();

    QServiceDebugValue operator<<(const char *key);
    void logMessage(QServiceDebugMessage *msg);

private:
    QList<QBuffer *> queue;
    QVector<QUdpSocket *> sockets;
    void makeSockets();
    QMutex socketLock;
};

inline QServiceDebugLog &qServiceLog()
{
    return (*QServiceDebugLog::instance());
}

class QServiceDebugKey
{
public:
    inline QServiceDebugKey(const QSharedPointer<QServiceDebugMessage> &ptr)
        : ptr(ptr) {}
    QServiceDebugValue operator<<(const char *key);
private:
    QSharedPointer<QServiceDebugMessage> ptr;
};

class QServiceDebugValue
{
public:
    inline QServiceDebugValue(const QSharedPointer<QServiceDebugMessage> &ptr)
        : ptr(ptr) {}
    QServiceDebugKey operator<<(const qint32 &val);
    QServiceDebugKey operator<<(const float &val);
    QServiceDebugKey operator<<(const QString &val);
    QServiceDebugKey operator<<(const char *val);
private:
    QSharedPointer<QServiceDebugMessage> ptr;
};

inline QServiceDebugValue QServiceDebugKey::operator<<(const char *key)
{
    ptr->ds.writeBytes(key, ::strlen(key));
    return QServiceDebugValue(ptr);
}

inline QServiceDebugKey QServiceDebugValue::operator<<(const qint32 &val)
{
    ptr->ds << (qint8)QServiceDebugMessage::Int32Type;
    ptr->ds << val;
    return QServiceDebugKey(ptr);
}

inline QServiceDebugKey QServiceDebugValue::operator<<(const float &val)
{
    ptr->ds << (qint8)QServiceDebugMessage::FloatType;
    ptr->ds << val;
    return QServiceDebugKey(ptr);
}

inline QServiceDebugKey QServiceDebugValue::operator<<(const QString &val)
{
    ptr->ds << (qint8)QServiceDebugMessage::StringType;
    QByteArray ba = val.toLatin1();
    ptr->ds.writeBytes(ba.constData(), ba.size());
    return QServiceDebugKey(ptr);
}

inline QServiceDebugKey QServiceDebugValue::operator<<(const char *val)
{
    ptr->ds << (qint8)QServiceDebugMessage::StringType;
    ptr->ds.writeBytes(val, ::strlen(val));
    return QServiceDebugKey(ptr);
}

inline QServiceDebugValue QServiceDebugLog::operator<<(const char *key)
{
    QSharedPointer<QServiceDebugMessage> msg(new QServiceDebugMessage());
    return (QServiceDebugKey(msg) << key);
}

QT_END_NAMESPACE

#endif // QSERVICEDEBUGLOG_P_H
