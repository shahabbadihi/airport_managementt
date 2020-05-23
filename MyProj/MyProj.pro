QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Employee.cpp \
    Flight.cpp \
    Host.cpp \
    Passenger.cpp \
    Pilot.cpp \
    Ticket.cpp \
    _observer.cpp \
    _subject.cpp \
    addflightdialog.cpp \
    addhost.cpp \
    addticket.cpp \
    deletehost.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Airplane.h \
    Deliverier.h \
    Employee.h \
    Flight.h \
    Host.h \
    Object.h \
    Passenger.h \
    Pilot.h \
    Price.h \
    Recorder.h \
    TList.h \
    Ticket.h \
    Vehicle.h \
    _observer.h \
    _subject.h \
    addflightdialog.h \
    addhost.h \
    addticket.h \
    deletehost.h \
    dialog.h \
    mainwindow.h

FORMS += \
    addflightdialog.ui \
    addhost.ui \
    addticket.ui \
    deletehost.ui \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
