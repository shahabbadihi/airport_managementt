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
    AirplaneItemModel.cpp \
    AirplanesPage.cpp \
    Carrier.cpp \
    DataMapperPage.cpp \
    DeleteAirline.cpp \
    DeleteAirplane.cpp \
    Employee.cpp \
    Flight.cpp \
    FlightItem.cpp \
    Host.cpp \
    HostItemModel.cpp \
    HostsPage.cpp \
    MyAbstractItemModel.cpp \
    Passenger.cpp \
    Pilot.cpp \
    Recorder.cpp \
    ThreadedJob.cpp \
    Seat.cpp \
    Ticket.cpp \
    addairlinedialog.cpp \
    addairplanedialog.cpp \
    addcarrierdialog.cpp \
    addflightdialog.cpp \
    addhost.cpp \
    addticket.cpp \
    airlineitemmodel.cpp \
    airlinespage.cpp \
    attachticket.cpp \
    delaydialog.cpp \
    delegate.cpp \
    deletecarrier.cpp \
    deleteflight.cpp \
    deletehost.cpp \
    deletepilot.cpp \
    deleteticket.cpp \
    detailspage.cpp \
    dialog.cpp \
    editSeas.cpp \
    flightlistmodel.cpp \
    flightstatusdialog.cpp \
    flighttablemodel.cpp \
    flighttablepage.cpp \
    hostlistmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    pd1.cpp \
    pd2.cpp \
    pd3.cpp \
    pu2.cpp \
    p2_12.cpp \
    po12.cpp \
    GetPassengerFactory.cpp \
    pilotitemmodel.cpp \
    pilotlistmodel.cpp \
    pilotspage.cpp \
    ticketlistmodel.cpp \
    ticketpage.cpp

HEADERS += \
    Airline.h \
    Airplane.h \
    AirplaneItemModel.h \
    AirplanesPage.h \
    Carrier.h \
    DataMapperPage.h \
    DeleteAirline.h \
    DeleteAirplane.h \
    Employee.h \
    Flight.h \
    FlightItem.h \
    Host.h \
    HostItemModel.h \
    HostsPage.h \
    MyAbstractItemModel.h \
    Object.h \
    Passenger.h \
    Pilot.h \
    Recorder.h \
    Seat.h \
    SignalSlotRecorder.h \
    ThreadedJob.h \
    Ticket.h \
    addairlinedialog.h \
    addairplanedialog.h \
    addcarrierdialog.h \
    addflightdialog.h \
    addhost.h \
    addticket.h \
    airlineitemmodel.h \
    airlinespage.h \
    attachticket.h \
    delaydialog.h \
    delegate.h \
    deletecarrier.h \
    deleteflight.h \
    deletehost.h \
    deletepilot.h \
    deleteticket.h \
    detailspage.h \
    dialog.h \
    editSeas.h \
    flightlistmodel.h \
    flightstatusdialog.h \
    flighttablemodel.h \
    flighttablepage.h \
    hostlistmodel.h \
    mainwindow.h \
    pd1.h \
    pd2.h \
    pd3.h \
    PO12.h \
    PU2.h \
    P2_12.h \
    GetPassengerFactory.h \
    pilotitemmodel.h \
    pilotlistmodel.h \
    pilotspage.h \
    ticketlistmodel.h \
    ticketpage.h

FORMS += \
    AirplanesPage.ui \
    DeleteAirline.ui \
    DeleteAirplane.ui \
    HostsPage.ui \
    addairlinedialog.ui \
    addairplanedialog.ui \
    addcarrierdialog.ui \
    addflightdialog.ui \
    addhost.ui \
    addticket.ui \
    airlinespage.ui \
    attachticket.ui \
    delaydialog.ui \
    deletecarrier.ui \
    deleteflight.ui \
    deletehost.ui \
    deletepilot.ui \
    deleteticket.ui \
    detailspage.ui \
    dialog.ui \
    editSeas.ui \
    flightstatusdialog.ui \
    flighttablepage.ui \
    mainwindow.ui \
    pilotspage.ui \
    ticketpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc \
    img.qrc
