TEMPLATE = lib

QT -= gui
QT += xml

DEFINES += COUPLING_LIB

TARGET = coupling

DESTDIR = ../../../lib

CONFIG(debug, debug|release) {

    TARGET = $$join(TARGET,,,_d)
    LIBS += -L../../../lib -lCfgReader_d
    LIBS += -L../../../lib -lphysics_d

} else {

    LIBS += -L../../../lib -lCfgReader
    LIBS += -L../../../lib -lphysics
}

INCLUDEPATH += ./include
INCLUDEPATH += ../physics/include
INCLUDEPATH += ../../CfgReader/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)

