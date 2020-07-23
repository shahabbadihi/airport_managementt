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
    Airline.cpp \
    Airplane.cpp \
    Carrier.cpp \
    Employee.cpp \
    Flight.cpp \
    Host.cpp \
    Passenger.cpp \
    Pilot.cpp \
    Recorder.cpp \
    Ticket.cpp \
    _observer.cpp \
    _subject.cpp \
    addairlinedialog.cpp \
    addairplanedialog.cpp \
    addcarrierdialog.cpp \
    addflightdialog.cpp \
    addhost.cpp \
    addticket.cpp \
    delaydialog.cpp \
    delegate.cpp \
    deletecarrier.cpp \
    deleteflight.cpp \
    deletehost.cpp \
    deletepilot.cpp \
    deleteticket.cpp \
    dialog.cpp \
    flightlistmodel.cpp \
    flightstatusdialog.cpp \
    flighttablemodel.cpp \
    flighttablepage.cpp \
    getpassengerfactory.cpp \
    hostlistmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    p2_12.cpp \
    pd1.cpp \
    pd2.cpp \
    pd3.cpp \
    pilotitemmodel.cpp \
    pilotlistmodel.cpp \
    pilotspage.cpp \
    po12.cpp \
    pu2.cpp \
    seat.cpp \
    ticketlistmodel.cpp

HEADERS += \
    Airline.h \
    Airplane.h \
    Carrier.h \
    Employee.h \
    Flight.h \
    Host.h \
    Object.h \
    Passenger.h \
    Pilot.h \
    Price.h \
    Recorder.h \
    SignalSlotRecorder.h \
    Ticket.h \
    _observer.h \
    _subject.h \
    addairlinedialog.h \
    addairplanedialog.h \
    addcarrierdialog.h \
    addflightdialog.h \
    addhost.h \
    addticket.h \
    delaydialog.h \
    delegate.h \
    deletecarrier.h \
    deleteflight.h \
    deletehost.h \
    deletepilot.h \
    deleteticket.h \
    dialog.h \
    flightlistmodel.h \
    flightstatusdialog.h \
    flighttablemodel.h \
    flighttablepage.h \
    getpassengerfactory.h \
    hostlistmodel.h \
    mainwindow.h \
    p2_12.h \
    pd1.h \
    pd2.h \
    pd3.h \
    pilotitemmodel.h \
    pilotlistmodel.h \
    pilotspage.h \
    po12.h \
    pu2.h \
    seat.h \
    ticketlistmodel.h

FORMS += \
    addairlinedialog.ui \
    addairplanedialog.ui \
    addcarrierdialog.ui \
    addflightdialog.ui \
    addhost.ui \
    addticket.ui \
    delaydialog.ui \
    deletecarrier.ui \
    deleteflight.ui \
    deletehost.ui \
    deletepilot.ui \
    deleteticket.ui \
    dialog.ui \
    flightstatusdialog.ui \
    flighttablepage.ui \
    mainwindow.ui \
    pilotspage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
