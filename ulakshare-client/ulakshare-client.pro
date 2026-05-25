QT       += core network
CONFIG += console
CONFIG += c++17
LIBS += -lnorm
LIBS += -lprotokit
LIBS += -lpthread

#LIBS += -lz
TARGET = ulakshare-client
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    multicastfileclient.cpp \
    normreceiver.cpp \
    normreceiverworker.cpp \
    userprivilegehelper.cpp

HEADERS += \
    multicastfileclient.h \
    normreceiver.h \
    normreceiverworker.h \
    userprivilegehelper.h


udpmem.files = data/99-ulakshare-transfer.conf
udpmem.path = /etc/sysctl.d/

target.path = /usr/bin
service.files = data/ulakshare-client.service
service.path = /lib/systemd/system/

debscriptservice.files = data/ulaksharedebinstaller@.service
debscriptservice.path = /lib/systemd/system/

debscript.files = data/scriptulaksharescript
debscript.path = /usr/share/ulakshare/

scriptscriptservice.files = data/ulaksharescriptexec@.service
scriptscriptservice.path = /lib/systemd/system/

scriptscript.files = data/debulaksharescript
scriptscript.path = /usr/share/ulakshare/


INSTALLS += target service udpmem \
debscript scriptscriptservice scriptscript debscriptservice
