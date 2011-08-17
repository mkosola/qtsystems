#-------------------------------------------------
#
# Project created by QtCreator 2011-02-10T13:14:47
#
#-------------------------------------------------

QT       += testlib
QT       += jsondb
QT       += jsondb-private
QT       -= gui

# JSON DB DEPENDENCIES ############################################################################
#LIBS += -lmtcore
###################################################################################################

#QMAKE_CXXFLAGS+=-fprofile-arcs
#QMAKE_CXXFLAGS+=-ftest-coverage

#LIBS += -lgcov

TARGET = tst_testpublishsubscribe
QMAKE_EXTRA_TARGETS = check
check.depends = $$TARGET
check.commands = ./$$TARGET

CONFIG   += console
CONFIG   += qtestlib
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../../../include/QtPublishSubscribe $$PWD/../../../src/publishsubscribe

SOURCES += tst_valuespace_jsondb.cpp \
    $$PWD/../../../src/publishsubscribe/jsondblayer.cpp \
    $$PWD/../../../src/publishsubscribe/qvaluespace.cpp \
    $$PWD/../../../src/publishsubscribe/qvaluespacepublisher.cpp \
    $$PWD/../../../src/publishsubscribe/qvaluespacemanager.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    $$PWD/../../../src/publishsubscribe/jsondblayer_p.h \
    $$PWD/../../../src/publishsubscribe/qvaluespace_p.h \
    $$PWD/../../../src/publishsubscribe/qvaluespacepublisher.h \
    $$PWD/../../../src/publishsubscribe/qvaluespacemanager_p.h

QMAKE_EXTRA_TARGETS = check
check.depends = $$TARGET
check.commands = ./$$TARGET