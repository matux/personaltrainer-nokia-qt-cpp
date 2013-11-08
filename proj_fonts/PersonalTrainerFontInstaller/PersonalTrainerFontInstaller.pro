#-------------------------------------------------
#
# Project created by QtCreator 2010-08-02T04:31:30
#
#-------------------------------------------------

QT       += core gui

TARGET = PersonalTrainerFontInstaller
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

ICON = icon.svg

symbian {
    TARGET.UID3 = 0xedb3aeae
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000

    # Fonts
    font0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\fonts\PersonalTrainerFontInstaller\AvantGardeDemi.ttf
    font0.path = e:\Resource\Fonts
    font1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\fonts\PersonalTrainerFontInstaller\AvantGardeMd.ttf
    font1.path = e:\Resource\Fonts
    font2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\fonts\PersonalTrainerFontInstaller\AvantGardeMdBold.ttf
    font2.path = e:\Resource\Fonts

    DEPLOYMENT += font0 + font1 + font2

}
