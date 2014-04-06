# This is a test makefile that I want to use to fix a problem I have with Qt

#Compiler, tools and options

PROJECT_NAME = ISSF

QT_INCLUDE = /home/donny/QtSDK/5.1.1/gcc_64/include/
QT_MKSPEC = /home/donny/QtSDK/5.1.1/gcc_64/mkspec/
QT_LIB = /home/donny/QtSDK/5.1.1/gcc_64/lib/
QT_QMAKE = /home/donny/QtSDK/5.1.1/gcc_64/bin/

CC = gcc
CXX = g++
DEFINES = -DQT_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS = -pipe -02 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS =  -pipe -02 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH = -I$(QTMKSPEC)linux-g++ -I../$(PROJECT_NAME)  -I$(QT_INCLUDE)QtCore -I$(QT_INCLUDE)QtGui -I$(QT_INCLUDE) -I.
LINK = g++
LFLAGS = -W1, -01 -W1, -rpath, $(QT_LIB)
LIBS = $(SUBLIBS) -L$(QT_LIBS) -lQtGui -L$(QT_LIB) -L/usr/lib/ -lQtCore -lpthread
AR = ar cqs
QMAKE = $(QT_QMAKE)qmake
TAR = tar -cf
COMPRESS = gzip -f
COPY = cp -f
SED = sed
COPY_FILE = $(COPY)
COPY_DIR = $(COPY) -r
STRIP = strip
INSTALL_FILE = install -m 644 -p
INSTALL_DIR = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE = rm -f
SYMLINK = ln -f -s
DEL_DIR = rmdir -f
MOVE = mv -f
CHK_DIR_EXISTS = test -d
MKDIR = mkdir -p

#### Output directory
OBJECTS_DIR = ./Debug


###Files

SOURCES = ../$(PROJECT_NAME)/main.cpp \
          ../$(PROJECT_NAME)/EthernetFrame.cpp \
          ../$(PROJECT_NAME)/HelperFunctions.cpp \
          ../$(PROJECT_NAME)/IPPacket.cpp \
          ../$(PROJECT_NAME)/TCPSegment.cpp \
          ../$(PROJECT_NAME)/WLANFrame.cpp \
          ../$(PROJECT_NAME)/Window.cpp \
          ../$(PROJECT_NAME)/findname.cpp \
          ../$(PROJECT_NAME)/UI/ProcessButtonSegment.cpp \
          ../$(PROJECT_NAME)/UI/SimpleButtonSegment.cpp

HEADERS = ../$(PROJECT_NAME)/include/LinkLayerData.h \
          ../$(PROJECT_NAME)/EthernetFrame.h \
          ../$(PROJECT_NAME)/HeaderTypes.h \
          ../$(PROJECT_NAME)/HelperFunctions.h \
          ../$(PROJECT_NAME)/IPPacket.h \
          ../$(PROJECT_NAME)/ISSF.h \
          ../$(PROJECT_NAME)/Menu.h \
          ../$(PROJECT_NAME)/TCPSegment.h \
          ../$(PROJECT_NAME)/WLANFrame.h \
          ../$(PROJECT_NAME)/findname.h \
          ../$(PROJECT_NAME)/UI/Button.h \
          ../$(PROJECT_NAME)/ProcessButtonsSegment.h \
          ../$(PROJECT_NAME)/SimplePushButton.h \
          ../$(PROJECT_NAME)/Window.h



DIST = $(QT_MKSPECS)common/unix.conf \
        $(QT_MKSPECS)common/linux.conf \
        $(QT_MKSPECS)common/gcc-base.conf \
        $(QT_MKSPECS)common/gcc-base-unix.conf \
        $(QT_MKSPECS)common/g++-base.conf \
        $(QT_MKSPECS)common/g++-unix.conf \
        $(QT_MKSPECS)qconfig.pri \
        $(QT_MKSPECS)modules/qt_webkit_version.pri \
        $(QT_MKSPECS)features/qt_functions.prf \
        $(QT_MKSPECS)features/qt_config.prf \
        $(QT_MKSPECS)features/exclusive_builds.prf \
        $(QT_MKSPECS)features/default_pre.prf \
        $(QT_MKSPECS)features/release.prf \
        $(QT_MKSPECS)features/default_post.prf \
        $(QT_MKSPECS)features/unix/gdb_dwarf_index.prf \
        $(QT_MKSPECS)features/warn_on.prf \
        $(QT_MKSPECS)features/qt.prf \
        $(QT_MKSPECS)features/unix/thread.prf \
        $(QT_MKSPECS)features/moc.prf \
        $(QT_MKSPECS)features/resources.prf \
        $(QT_MKSPECS)features/uic.prf \
        $(QT_MKSPECS)features/yacc.prf \
        $(QT_MKSPECS)features/lex.prf \
        $(QT_MKSPECS)features/include_source_dir.prf \
        ../$(PROJECT_NAME)/$(PROJECT_NAME).pro

QMAKE_TARGET = $(PROJECT_NAME)Debug
DESTDIR = $(OBJECTS_DIR)
TARGET = $(PROJECT_NAME)

first:all

###

all: Makefile $(TARGET)

$(TARGET): $(OBJECTS)
    $(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ../$(PROJECT_NAME)/$(PROJECT_NAME).pro  $(QT_MKSPECS)linux-g++/qmake.conf $(QT_MKSPECS)common/unix.conf \
        $(QT_MKSPECS)common/linux.conf \
        $(QT_MKSPECS)common/gcc-base.conf \
        $(QT_MKSPECS)common/gcc-base-unix.conf \
        $(QT_MKSPECS)common/g++-base.conf \
        $(QT_MKSPECS)common/g++-unix.conf \
        $(QT_MKSPECS)qconfig.pri \
        $(QT_MKSPECS)modules/qt_webkit_version.pri \
        $(QT_MKSPECS)features/qt_functions.prf \
        $(QT_MKSPECS)features/qt_config.prf \
        $(QT_MKSPECS)features/exclusive_builds.prf \
        $(QT_MKSPECS)features/default_pre.prf \
        $(QT_MKSPECS)features/release.prf \
        $(QT_MKSPECS)features/default_post.prf \
        $(QT_MKSPECS)features/unix/gdb_dwarf_index.prf \
        $(QT_MKSPECS)features/warn_on.prf \
        $(QT_MKSPECS)features/qt.prf \
        $(QT_MKSPECS)features/unix/thread.prf \
        $(QT_MKSPECS)features/moc.prf \
        $(QT_MKSPECS)features/resources.prf \
        $(QT_MKSPECS)features/uic.prf \
        $(QT_MKSPECS)features/yacc.prf \
        $(QT_MKSPECS)features/lex.prf \
        $(QT_MKSPECS)features/include_source_dir.prf \
        $(QT_LIB)/libQtGui.prl \
        $(QT_LIB)/libQtCore.prl
    $(QMAKE) -spec $(QT_MKSPEC)linux-g++ -o Makefile ../$(PROJECT_NAME)/$(PROJECT_NAME).pro

$(QT_MKSPECS)common/unix.conf:
$(QT_MKSPECS)common/linux.conf:
$(QT_MKSPECS)common/gcc-base.conf:
$(QT_MKSPECS)common/gcc-base-unix.conf:
$(QT_MKSPECS)common/g++-base.conf:
$(QT_MKSPECS)common/g++-unix.conf:
$(QT_MKSPECS)qconfig.pri:
$(QT_MKSPECS)modules/qt_webkit_version.pri:
$(QT_MKSPECS)features/qt_functions.prf:
$(QT_MKSPECS)features/qt_config.prf:
$(QT_MKSPECS)features/exclusive_builds.prf:
$(QT_MKSPECS)features/default_pre.prf:
$(QT_MKSPECS)features/release.prf:
$(QT_MKSPECS)features/default_post.prf:
$(QT_MKSPECS)features/unix/gdb_dwarf_index.prf:
$(QT_MKSPECS)features/warn_on.prf:
$(QT_MKSPECS)features/qt.prf:
$(QT_MKSPECS)features/unix/thread.prf:
$(QT_MKSPECS)features/moc.prf:
$(QT_MKSPECS)features/resources.prf:
$(QT_MKSPECS)features/uic.prf:
$(QT_MKSPECS)features/yacc.prf:
$(QT_MKSPECS)features/lex.prf:
$(QT_MKSPECS)features/include_source_dir.prf:
$(QT_LIB)/libQtGui.prl:
$(QT_LIB)/libQtCore.prl:

qmake: FORCE
    @$(QMAKE) -spec $(QT_MKSPEC)linux-g++ -o Makefile ../$(PROJECT_NAME)/$(PROJECT_NAME).pro

dist:
    @$(CHK_DIR_EXISTS) .tmp/$(PROJECT_NAME)1.0.0 || $(MKDIR) .tmp/$(PROJECT_NAME)1.0.0
    $(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/$(PROJECT_NAME)1.0.0/ &&
