QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    muparser/muParser.cpp \
    muparser/muParserBase.cpp \
    muparser/muParserBytecode.cpp \
    muparser/muParserCallback.cpp \
    muparser/muParserDLL.cpp \
    muparser/muParserError.cpp \
    muparser/muParserInt.cpp \
    muparser/muParserTest.cpp \
    muparser/muParserTokenReader.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    muparser/muParser.h \
    muparser/muParserBase.h \
    muparser/muParserBytecode.h \
    muparser/muParserCallback.h \
    muparser/muParserDLL.h \
    muparser/muParserDef.h \
    muparser/muParserError.h \
    muparser/muParserFixes.h \
    muparser/muParserInt.h \
    muparser/muParserTemplateMagic.h \
    muparser/muParserTest.h \
    muparser/muParserToken.h \
    muparser/muParserTokenReader.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_CXXFLAGS += -Wno-error=implicit-function-declaration