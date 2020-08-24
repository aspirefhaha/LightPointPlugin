CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(LightPoint)
TEMPLATE    = lib

HEADERS     = lightpointplugin.h
SOURCES     = lightpointplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

#AFTER_LINK_CMD_LINE = copy release\LightPoint.dll C:\Qt\Qt5.11.1\5.11.1\msvc2015\plugins\designer
#QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE)

#AFTER_LINK_CMD_LINE1 = copy release\LightPoint.dll C:\Qt\Qt5.11.1\Tools\QtCreator\bin\plugins\designer
#QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE1)

include(LightPoint.pri)
