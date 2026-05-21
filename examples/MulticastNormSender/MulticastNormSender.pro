QT += core

CONFIG += console c++17

LIBS += -lnorm
LIBS += -lprotokit
LIBS += -lpthread

#INCLUDEPATH += /usr/local/include
#INCLUDEPATH += $$PWD/protolib/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    normbandwidthestimator.cpp \
    normnetworkprobe.cpp \
    normratecontroller.cpp \
    normsender.cpp \
    normsenderworker.cpp

HEADERS += \
    normbandwidthestimator.h \
    normnetworkprobe.h \
    normratecontroller.h \
    normsender.h \
    normsenderworker.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
