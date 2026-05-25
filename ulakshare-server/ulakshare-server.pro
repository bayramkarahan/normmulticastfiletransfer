QT       += core gui network concurrent
TARGET = ulakshare-server
TEMPLATE = app
#LIBS += -lz
#CONFIG += console c++17

CONFIG += c++17
LIBS += -lnorm
LIBS += -lprotokit
LIBS += -lpthread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    multicastfileserver.cpp \
    normbandwidthestimator.cpp \
    normnetworkprobe.cpp \
    normsender.cpp \
    normsenderworker.cpp \
    progressdialog.cpp

HEADERS += \
    multicastfileserver.h \
    normbandwidthestimator.h \
    normnetworkprobe.h \
    normsender.h \
    normsenderworker.h \
    progressdialog.h \
    type.h


target.path = /usr/bin
service.files = multicastfiletransferclient.service
service.path = /lib/systemd/system/

udpmem.files = data/98-multicast-transfer.conf
udpmem.path = /etc/sysctl.d/

nemomenu.files = data/nemomenu/*
nemomenu.path = /usr/share/nemo/actions/

nautilusmenu.files = data/nautilusmenu/*
nautilusmenu.path = /usr/share/nautilus/scripts/

dolphinmenu.files = data/dolphinmenu/*
dolphinmenu.path = /usr/share/kservices5/ServiceMenus/

thunarmenu.files = data/thunarmenu/*
thunarmenu.path = /usr/share/Thunar/

auto_start.files = data/multicasttransfer.desktop
auto_start.path = /etc/xdg/autostart/

INSTALLS += target service nemomenu nautilusmenu \
dolphinmenu thunarmenu udpmem auto_start

RESOURCES += \
    icons.qrc
