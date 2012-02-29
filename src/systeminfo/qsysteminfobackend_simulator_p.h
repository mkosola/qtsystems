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

#ifndef QSYSTEMINFOBACKEND_SIMULATOR_P_H
#define QSYSTEMINFOBACKEND_SIMULATOR_P_H


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

#include "qsysteminfodata_simulator_p.h"

QT_BEGIN_NAMESPACE

// QBatteryInfoSimulatorBackend

class Q_SYSTEMINFO_EXPORT QBatteryInfoSimulatorBackend : public QObject
{
    Q_OBJECT

private:
    QBatteryInfoSimulatorBackend(QObject *parent = 0);
    Q_DISABLE_COPY(QBatteryInfoSimulatorBackend)

public:
    ~QBatteryInfoSimulatorBackend();
    static QBatteryInfoSimulatorBackend *getSimulatorBackend();

    int getBatteryCount();
    int getCurrentFlow(int battery);
    int getMaximumCapacity(int battery);
    int getRemainingCapacity(int battery);
    int getRemainingChargingTime(int battery);
    int getVoltage(int battery);
    QBatteryInfo::ChargingState getChargingState(int battery);
    QBatteryInfo::ChargerType getChargerType();
    QBatteryInfo::EnergyUnit getEnergyUnit();
    QBatteryInfo::BatteryStatus getBatteryStatus(int battery);

    void setCurrentFlow(int flow);
    void setMaximumCapacity(int capacity);
    void setRemainingCapacity(int capacity);
    void setRemainingChargingTime(int time);
    void setVoltage(int vol);
    void setChargingState(QBatteryInfo::ChargingState state);
    void setChargerType(QBatteryInfo::ChargerType type);
    void setEnergyUnit(QBatteryInfo::EnergyUnit unit);
    void setBatteryStatus(QBatteryInfo::BatteryStatus status);

Q_SIGNALS:
    void batteryCountChanged(int count);
    void currentFlowChanged(int battery, int flow);
    void remainingCapacityChanged(int battery, int capacity);
    void remainingChargingTimeChanged(int battery, int seconds);
    void voltageChanged(int battery, int voltage);
    void chargingStateChanged(int battery, QBatteryInfo::ChargingState state);
    void chargerTypeChanged(QBatteryInfo::ChargerType type);
    void batteryStatusChanged(int battery, QBatteryInfo::BatteryStatus status);

private:
    static QBatteryInfoSimulatorBackend *globalSimulatorBackend;
    QBatteryInfoData data;
};


// QDeviceInfoSimulatorBackend

class Q_SYSTEMINFO_EXPORT QDeviceInfoSimulatorBackend : public QObject
{
    Q_OBJECT

private:
    QDeviceInfoSimulatorBackend(QObject *parent = 0);
    Q_DISABLE_COPY(QDeviceInfoSimulatorBackend)

public:
    ~QDeviceInfoSimulatorBackend();
    static QDeviceInfoSimulatorBackend *getSimulatorBackend();

    bool hasFeature(QDeviceInfo::Feature);
    int getImeiCount();
    QDeviceInfo::LockTypeFlags getActivatedLocks();
    QDeviceInfo::LockTypeFlags getEnabledLocks();
    QDeviceInfo::ThermalState getThermalState();
    QString getImei(int num);
    QString getManufacturer();
    QString getModel();
    QString getProductName();
    QString getUniqueDeviceID();
    QString getVersion(QDeviceInfo::Version);

    void setFeature(QDeviceInfo::Feature feature, bool enable);
    void setActivatedLocks(QDeviceInfo::LockTypeFlags flag);
    void setEnabledLocks(QDeviceInfo::LockTypeFlags flag);
    void setThermalState(QDeviceInfo::ThermalState state);
    void setImei(int num, QString imei);
    void setManufacturer(QString manufacturer);
    void setModel(QString model);
    void setProductName(QString name);
    void setUniqueDeviceID(QString id);
    void setVersion(QDeviceInfo::Version version, QString versionString);

Q_SIGNALS:
    void activatedLocksChanged(QDeviceInfo::LockTypeFlags);
    void enabledLocksChanged(QDeviceInfo::LockTypeFlags);
    void thermalStateChanged(QDeviceInfo::ThermalState);

private:
    QDeviceInfoData data;
    static QDeviceInfoSimulatorBackend *globalSimulatorBackend;

    void initFeatureList();
    void initImeiList();
    void initVersionList();
};


// QStorageInfoSimulatorBackend

class Q_SYSTEMINFO_EXPORT QStorageInfoSimulatorBackend : public QObject
{
    Q_OBJECT

private:
    QStorageInfoSimulatorBackend(QObject *parent = 0);
    Q_DISABLE_COPY(QStorageInfoSimulatorBackend)

public:
    ~QStorageInfoSimulatorBackend();
    static QStorageInfoSimulatorBackend *getSimulatorBackend();

    qlonglong getAvailableDiskSpace(const QString &drive);
    qlonglong getTotalDiskSpace(const QString &drive);
    QString getUriForDrive(const QString &drive);
    QStringList getAllLogicalDrives();
    QStorageInfo::DriveType getDriveType(const QString &drive);

    void setAvailableDiskSpace(const QString &drive, qlonglong space);
    void setTotalDiskSpace(const QString &drive, qlonglong space);
    void setUriForDrive(const QString &drive, QString uri);
    void setDriveType(const QString &drive, QStorageInfo::DriveType);

    bool addDrive(const QString &drive);
    bool addDrive(const QString &drive, QStorageInfo::DriveType type,
                  qint64 totalSpace, qint64 availableSpace,
                  const QString &uri);
    bool removeDrive(const QString &drive);

Q_SIGNALS:
    void logicalDriveChanged(const QString &drive, bool added);

private:
    QStorageInfoData data;
    static QStorageInfoSimulatorBackend *globalSimulatorBackend;

    QStorageInfoData::DriveInfo getDriveInfo(const QString &drive);
    bool hasDriveInfo(const QString &drive);
};


// QNetworkInfoSimulatorBackend

class Q_SYSTEMINFO_EXPORT QNetworkInfoSimulatorBackend : public QObject
{
    Q_OBJECT

private:
    QNetworkInfoSimulatorBackend(QNetworkInfo *parent = 0);
    Q_DISABLE_COPY(QNetworkInfoSimulatorBackend)

public:
    ~QNetworkInfoSimulatorBackend();
    static QNetworkInfoSimulatorBackend *getSimulatorBackend();

    int getNetworkInterfaceCount(QNetworkInfo::NetworkMode mode);
    int getNetworkSignalStrength(QNetworkInfo::NetworkMode mode, int interface);
    QNetworkInfo::CellDataTechnology getCurrentCellDataTechnology(int interface);
    QNetworkInfo::NetworkMode getCurrentNetworkMode();
    QString getImsi(int interface);
    QNetworkInfo::NetworkStatus getNetworkStatus(QNetworkInfo::NetworkMode mode, int interface);
#ifndef QT_NO_NETWORKINTERFACE
    QNetworkInterface getInterfaceForMode(QNetworkInfo::NetworkMode mode, int interface);
#endif // QT_NO_NETWORKINTERFACE
    QString getCellId(int interface);
    QString getCurrentMobileCountryCode(int interface);
    QString getCurrentMobileNetworkCode(int interface);
    QString getHomeMobileCountryCode(int interface);
    QString getHomeMobileNetworkCode(int interface);
    QString getLocationAreaCode(int interface);
    QString getMacAddress(QNetworkInfo::NetworkMode mode, int interface);
    QString getNetworkName(QNetworkInfo::NetworkMode mode, int interface);
    QNetworkInfo::NetworkMode getMode(QNetworkInfo::NetworkMode mode, int interface);

    void setImsi(int interface, const QString &id);
    void setCellId(int interface, const QString &id);
    void setLocationAreaCode(int interface, const QString &code);
    void setCurrentMobileCountryCode( int interface, const QString &code);
    void setCurrentMobileNetworkCode(int interface, const QString &code);
    void setHomeMobileCountryCode(int interface, const QString &code);
    void setHomeMobileNetworkCode(int interface, const QString &code);
    void setCellDataTechnology(int interface, QNetworkInfo::CellDataTechnology cellData);
    void setMode(int interface, QNetworkInfo::NetworkMode mode);
    void setNetworkName(QNetworkInfo::NetworkMode mode, int interface, const QString &name);
    void setNetworkMacAddress(QNetworkInfo::NetworkMode mode, int interface, const QString &mac);
    void setNetworkSignalStrength(QNetworkInfo::NetworkMode mode, int interface, int strength);
    void setNetworkStatus(QNetworkInfo::NetworkMode mode, int interface, QNetworkInfo::NetworkStatus status);

    void addEthernetInterface(QNetworkInfoData::EthernetInfo info);
    void addWlanInterface(QNetworkInfoData::WLanInfo info);
    void addCellularInterface(QNetworkInfoData::CellularInfo info);
    void addBluetoothInterface(QNetworkInfoData::BluetoothInfo info);
    void removeInterface(QNetworkInfo::NetworkMode mode, int interface);
    void clearInterface(QNetworkInfo::NetworkMode mode);

Q_SIGNALS:
    void cellIdChanged(int interface, const QString &id);
    void currentCellDataTechnologyChanged(int interface, QNetworkInfo::CellDataTechnology tech);
    void currentMobileCountryCodeChanged(int interface, const QString &mcc);
    void currentMobileNetworkCodeChanged(int interface, const QString &mnc);
    void currentNetworkModeChanged(QNetworkInfo::NetworkMode mode);
    void locationAreaCodeChanged(int interface, const QString &lac);
    void networkInterfaceCountChanged(QNetworkInfo::NetworkMode mode, int count);
    void networkNameChanged(QNetworkInfo::NetworkMode mode, int interface, const QString &name);
    void networkSignalStrengthChanged(QNetworkInfo::NetworkMode mode, int interface, int strength);
    void networkStatusChanged(QNetworkInfo::NetworkMode mode, int interface, QNetworkInfo::NetworkStatus status);

private:
    static QNetworkInfoSimulatorBackend *globalSimulatorBackend;
    QNetworkInfoData data;

    QNetworkInfoData::BasicNetworkInfo *basicNetworkInfo(QNetworkInfo::NetworkMode mode, int interface);
    bool isValidInterface(QNetworkInfo::NetworkMode mode, int interface);
    void clearOrRemoveInterface(QNetworkInfo::NetworkMode mode, int interface, bool clear);
};

QT_END_NAMESPACE

#endif // QSYSTEMINFOBACKEND_SIMULATOR_P_H
