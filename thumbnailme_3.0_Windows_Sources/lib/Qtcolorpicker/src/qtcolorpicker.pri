include(../common.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

qtcolorpicker-uselib:!qtcolorpicker-buildlib {
    LIBS += -L$$QTCOLORPICKER_LIBDIR -l$$QTCOLORPICKER_LIBNAME
} else {
    SOURCES += $$PWD/qtcolorpicker.cpp
    HEADERS += $$PWD/qtcolorpicker.h
}

win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTCOLORPICKER_EXPORT
    else:qtcolorpicker-uselib:DEFINES += QT_QTCOLORPICKER_IMPORT
}
