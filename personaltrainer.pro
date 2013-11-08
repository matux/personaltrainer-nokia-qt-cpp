#-------------------------------------------------
#
# Project created by QtCreator 2010-07-19T03:24:36
#
#-------------------------------------------------

QT += \
    core \
    gui \
    xml \
    network

TARGET = personaltrainer
TEMPLATE = app

ICON = icon.svg

SOURCES += main.cpp\
        mainwindow.cpp \
    qfreestyleapplication.cpp \
    SIKit/SIView.cpp \
    SIKit/SITabBarItem.cpp \
    SIKit/SITabBar.cpp \
    SIKit/SIButton.cpp \
    SIKit/SIMediaPlayer.cpp \
    views/legalview.cpp \
    views/headerview.cpp \
    views/rutina/rutinaview.cpp \
    views/trainer/trainerview.cpp \
    views/agenda/agendaview.cpp \
    views/musica/musicaview.cpp \
    views/pref/prefview.cpp \
    constants.cpp \
    SIKit/SINavigationController.cpp \
    SIKit/SINavigationBar.cpp \
    views/mainmenuview.cpp \
    model/exercises/exercisemanager.cpp \
    model/exercises/exercise.cpp \
    SIKit/xml/sixmlverbosehandler.cpp \
    model/exercises/xmlexerciseshandler.cpp \
    SIKit/xml/siixmlhandlerdelegate.cpp \
    views/trainer/trainerdetailedview.cpp \
    views/pref/formview.cpp \
    model/userinfo.cpp \
    model/globaldataobject.cpp \ 
    views/pref/testview.cpp \
    views/pref/testresultsview.cpp \
    views/rutina/rutinaaudiointro.cpp \
    views/videointroview.cpp \
    model/routines/plan.cpp \
    model/routines/routine.cpp \
    model/routines/xmlroutineshandler.cpp \
    model/routines/planlevel.cpp \
    model/routines/routineexercise.cpp \
    model/routines/routineexercisecomposition.cpp \
    model/routines/routineelement.cpp \
    model/routines/routinemanager.cpp \
    model/location/geodistancecalc.cpp \
    SIKit/SISwitchButton.cpp \
    views/rutina/ejercicioview.cpp \
    views/rutina/rutinaaudiofinview.cpp \
    views/listwidgetitemwithroutine.cpp \
    views/agenda/customcalendarwidget.cpp \
    views/agenda/agendadetailview.cpp \
    SIKit/SIFileScanner.cpp \
    SIKit/SILock.cpp \
    views/pref/formobjectiveview.cpp \
    model/planinfo.cpp \
    views/sync/syncmenuview.cpp \
    views/sync/synclegalview.cpp \
    views/sync/syncview.cpp \
    SIKit/SIActivityIndicator.cpp \
    model/network/network.cpp \
    SIKit/SIMediaKeyObserver.cpp \
    views/gpslegalview.cpp

HEADERS  += 	mainwindow.h \
    qfreestyleapplication.h \
    SIKit/SIButton.h \
    SIKit/SIView.h \
    SIKit/SITabBarItem.h \
    SIKit/SITabBar.h \
		SIKit/SIKit.h \
		SIKit/SIMediaPlayer.h \
    views/legalview.h \
    views/headerview.h \
    views/rutina/rutinaview.h \
    views/trainer/trainerview.h \
    views/agenda/agendaview.h \
    views/musica/musicaview.h \
    views/pref/prefview.h \
    constants.h \ 
    SIKit/SINavigationController.h \
    SIKit/SINavigationBar.h \
    views/mainmenuview.h \
    model/exercises/exercisemanager.h \
    model/exercises/exercise.h \
    SIKit/xml/sixmlverbosehandler.h \
    model/exercises/xmlexerciseshandler.h \
    SIKit/xml/siixmlhandlerdelegate.h \
    views/trainer/trainerdetailedview.h \
    views/pref/formview.h \
    model/userinfo.h \
    model/globaldataobject.h \ 
    views/pref/testview.h \
    views/pref/testresultsview.h \
    views/rutina/rutinaaudiointro.h \
    views/videointroview.h \
    model/routines/plan.h \
    model/routines/routine.h \
    model/routines/xmlroutineshandler.h \
    model/routines/planlevel.h \
    model/routines/routineexercise.h \
    model/routines/routineexercisecomposition.h \
    model/routines/routineelement.h \
    model/routines/routinemanager.h \
    model/location/geodistancecalc.h \
    SIKit/SISwitchButton.h \
    views/rutina/ejercicioview.h \
    views/rutina/rutinaaudiofinview.h \
    views/listwidgetitemwithroutine.h \
    views/agenda/customcalendarwidget.h \
    views/agenda/agendadetailview.h \
    SIKit/SIFileScanner.h \
    SIKit/SILock.h \
    views/pref/formobjectiveview.h \
    model/planinfo.h \
    views/sync/syncmenuview.h \
    views/sync/synclegalview.h \
    views/sync/syncview.h \
    SIKit/SIActivityIndicator.h \
    model/network/network.h \
    SIKit/SIMediaKeyObserver.h \
    views/gpslegalview.h

FORMS    += mainwindow.ui

#CONFIG += console
CONFIG += mobility
MOBILITY +=  \
    multimedia \
    location

win32 {
    message(Building for Symbian Simulator (Win32))

    # Symbian System settings
    TARGET.UID3 = 0xe7f07997
    TARGET.CAPABILITY += NetworkServices Location

    QMAKE_CXXFLAGS += -D_SIMULATOR_BUILD -D_DEBUG -D_FAKE_LOCATION_API
    #-D_FAKE_LOCATION_API
    #-D_DEBUG
}

symbian {
    message(Building for Symbian Device)

    # Symbian System settings
    TARGET.UID3 = 0xe7f07997
    TARGET.CAPABILITY += NetworkServices Location
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000

    # Required Symbian libraries
    # cone.lib, eikcore.lib and avkon.lib Symbian libraries
    LIBS += -lcone -leikcore -lavkon -leikcoctl -lcommdb
            #-lremconinterfacebase -lremconcoreapi

    # Work around for Qt/Symbian library warnings
    QMAKE_CXXFLAGS += -Wno-attributes -Wno-parentheses -D_DEVICE_BUILD -D_RELEASE
#-D_DEBUG -D_FAKE_LOCATION_API
#-D_FAKE_LOCATION_API
#-D_RELEASE
     #-D_DEBUG

    # Vendor info
    vendorinfo = \
         "%{\"Ford\"}" \
         ":\"Ford\""
    my_deployment.pkg_prerules = vendorinfo

    # Make it only support S60 5.0
    supported_platforms = \
        "; This demo only supports S60 5.0" \
        "[0x1028315F],0,0,0,{\"S60ProductID\"}"

    # Store our deployment options
    default_deployment.pkg_prerules -= pkg_platform_dependencies
    my_deployment.pkg_prerules += supported_platforms
    DEPLOYMENT += my_deployment

}

RESOURCES += res.qrc
