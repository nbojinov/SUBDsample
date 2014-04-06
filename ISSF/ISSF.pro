#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T15:07:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ISSF
TEMPLATE = app

QMAKE_CXXFLAGS += -O0

SOURCES +=\
        MainWindow.cpp \
    WLANFrame.cpp \
    TCPSegment.cpp \
    IPPacket.cpp \
    findname.cpp \
    EthernetFrame.cpp \
    dialog.cpp \
    UI/SimpleButton.cpp \
    UI/ProcessButtonSegment.cpp \
    main.cpp \
    UI/FilterSegment.cpp \
    ThreadControll/Thread.cpp \
    SharedMemoryClasses/Packet.cpp \
    SharedMemoryClasses/SharedMemoryController.cpp \
    ISSF.cpp \
    SharedMemoryClasses/PacketVector.cpp \
    Filter.cpp \
    FilterEther.cpp \
    FilterIP.cpp \
    FilterTCP.cpp \
    HelperFunctions.cpp \
    HTTPPacket.cpp

HEADERS  += MainWindow.h \
    WLANFrame.h \
    TCPSegment.h \
    Menu.h \
    ISSF.h \
    IPPacket.h \
    HelperFunctions.h \
    HeaderTypes.h \
    findname.h \
    EthernetFrame.h \
    dialog.h \
    UI/SimplePushButton.h \
    UI/ProcessButtonsSegment.h \
    UI/Button.h \
    include/LinkLayerData.h \
    UI/FilterSegment.h \
    SharedMemoryClasses/SharedMemoryController.h \
    SharedMemoryClasses/Packet.h \
    SharedMemoryClasses/PacketVector.h \
    ThreadControll/Thread.h \
    PcapLoop.h \
    include/AbstractHeader.h \
    Filter.h \
    FilterEther.h \
    FilterIP.h \
    FilterTCP.h \
    FilterMacrosHeader.h \
    HTTPPacket.h
FORMS    += MainWindow.ui \
    dialog.ui

OTHER_FILES += \
    Untitled1 \
    Makefile \
    ISSF.pro.user \
    ISSF.layout.cbTemp \
    ISSF.layout \
    ISSF.depend \
    ISSF.cbp.cbTemp \
    ISSF.cbp \
    HelperFunctions \
    gmon.out

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/release/pcap.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/debug/pcap.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/libpcap.a


INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/release/boost_thread.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/debug/boost_thread.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/libboost_thread.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcap

INCLUDEPATH += $$PWD/../../../usr/include/pcap
DEPENDPATH += $$PWD/../../../usr/include/pcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lpcap

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/release/pcap.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/debug/pcap.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/libpcap.a

INCLUDEPATH += $$PWD/../../../usr/include/boost
DEPENDPATH += $$PWD/../../../usr/include/boost

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lboost_thread
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lboost_thread
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lboost_thread

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/release/boost_system.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/debug/boost_system.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/libboost_system.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../../../usr/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/ -lcppnetlib-client-connections
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/ -lcppnetlib-client-connections
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/ -lcppnetlib-client-connections

INCLUDEPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/cppnetlib-client-connections.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/cppnetlib-client-connections.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/libcppnetlib-client-connections.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/ -lcppnetlib-server-parsers
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/ -lcppnetlib-server-parsers
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/ -lcppnetlib-server-parsers

INCLUDEPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/cppnetlib-server-parsers.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/cppnetlib-server-parsers.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/libcppnetlib-server-parsers.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/ -lcppnetlib-uri
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/ -lcppnetlib-uri
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/x86_64-linux-gnu/ -lcppnetlib-uri

INCLUDEPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/local/lib/x86_64-linux-gnu

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/release/cppnetlib-uri.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/debug/cppnetlib-uri.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/x86_64-linux-gnu/libcppnetlib-uri.a
