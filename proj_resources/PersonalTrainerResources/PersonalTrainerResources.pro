#-------------------------------------------------
#
# Project created by QtCreator 2010-08-09T08:43:06
#
#-------------------------------------------------

QT       += core gui

TARGET = PersonalTrainerResources
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

ICON = icon.svg

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xe86db845
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000

    # Fonts Installation
    #font0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\fonts\AvantGardeDemi.ttf
    #font0.path = e:\Resource\Fonts
    #font1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\fonts\AvantGardeMd.ttf
    #font1.path = e:\Resource\Fonts
    #font2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\fonts\AvantGardeMdBold.ttf
    #font2.path = e:\Resource\Fonts

    #DEPLOYMENT += font0 + font1 + font2

    # Resource installation
    audio_rutina_num1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina1.mp3
    audio_rutina_num1.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina2.mp3
    audio_rutina_num2.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina3.mp3
    audio_rutina_num3.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina4.mp3
    audio_rutina_num4.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina5.mp3
    audio_rutina_num5.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina6.mp3
    audio_rutina_num6.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina7.mp3
    audio_rutina_num7.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina8.mp3
    audio_rutina_num8.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina9.mp3
    audio_rutina_num9.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina10.mp3
    audio_rutina_num10.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina11.mp3
    audio_rutina_num11.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina12.mp3
    audio_rutina_num12.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina13.mp3
    audio_rutina_num13.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num14.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina14.mp3
    audio_rutina_num14.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num15.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina15.mp3
    audio_rutina_num15.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num16.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina16.mp3
    audio_rutina_num16.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num17.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina17.mp3
    audio_rutina_num17.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_num18.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutina18.mp3
    audio_rutina_num18.path = e:\Data\Others\PersonalTrainer\Rutinas

    DEPLOYMENT += audio_rutina_num1 + audio_rutina_num2 + audio_rutina_num3 + audio_rutina_num4 + audio_rutina_num5 + audio_rutina_num6 + \
                    audio_rutina_num7 + audio_rutina_num8 + audio_rutina_num9 + audio_rutina_num10 + audio_rutina_num11 + audio_rutina_num12 + \
                    audio_rutina_num13 + audio_rutina_num14 + audio_rutina_num15 + audio_rutina_num16 + audio_rutina_num17 + audio_rutina_num18

    audio_rutina_intro0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutinaintro0.mp3
    audio_rutina_intro0.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_intro1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutinaintro1.mp3
    audio_rutina_intro1.path = e:\Data\Others\PersonalTrainer\Rutinas
    audio_rutina_intro2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\rutinaintro2.mp3
    audio_rutina_intro2.path = e:\Data\Others\PersonalTrainer\Rutinas

    DEPLOYMENT += audio_rutina_intro0 + audio_rutina_intro1 + audio_rutina_intro2

    audio_test0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\test\buenoavisame.mp3
    audio_test0.path = e:\Data\Others\PersonalTrainer\Test
    audio_test1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\test\test0.mp3
    audio_test1.path = e:\Data\Others\PersonalTrainer\Test
    audio_test2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\test\test2.mp3
    audio_test2.path = e:\Data\Others\PersonalTrainer\Test
    audio_test3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\test\tevoyasacarbueno.mp3
    audio_test3.path = e:\Data\Others\PersonalTrainer\Test
    audio_test4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\test\test1.mp3
    audio_test4.path = e:\Data\Others\PersonalTrainer\Test

    DEPLOYMENT += audio_test0 + audio_test1 + audio_test2 + audio_test3 + audio_test4

    audio_plan0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0.mp3
    audio_plan0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan0m0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0-m0.mp3
    audio_plan0m0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan0m1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0-m1.mp3
    audio_plan0m1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan0f0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0-f0.mp3
    audio_plan0f0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan0f1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0-f1.mp3
    audio_plan0f1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan0f2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan0-f2.mp3
    audio_plan0f2.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan1.mp3
    audio_plan1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan1m0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan1-m0.mp3
    audio_plan1m0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan1m1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan1-m1.mp3
    audio_plan1m1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan1f0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan1-f0.mp3
    audio_plan1f0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan1f1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan1-f1.mp3
    audio_plan1f1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan2.mp3
    audio_plan2.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan2m0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan2-m0.mp3
    audio_plan2m0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan2m1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan2-m1.mp3
    audio_plan2m1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan2f0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan2-f0.mp3
    audio_plan2f0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan2f1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan2-f1.mp3
    audio_plan2f1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan3.mp3
    audio_plan3.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan3m0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan3-m0.mp3
    audio_plan3m0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan3m1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan3-m1.mp3
    audio_plan3m1.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan3f0.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan3-f0.mp3
    audio_plan3f0.path = e:\Data\Others\PersonalTrainer\Planes
    audio_plan3f1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\planes\plan3-f1.mp3
    audio_plan3f1.path = e:\Data\Others\PersonalTrainer\Planes

    DEPLOYMENT += audio_plan0 + audio_plan0m0 + audio_plan0m1 + audio_plan0f0 + audio_plan0f1 + audio_plan0f2 + \
                  audio_plan1 + audio_plan1m0 + audio_plan1m1 + audio_plan1f0 + audio_plan1f1 + \
                  audio_plan2 + audio_plan2m0 + audio_plan2m1 + audio_plan2f0 + audio_plan2f1 + \
                  audio_plan3 + audio_plan3m0 + audio_plan3m1 + audio_plan3f0 + audio_plan3f1

    audio_rutina_time1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\1.mp3
    audio_rutina_time1.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\2.mp3
    audio_rutina_time2.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\3.mp3
    audio_rutina_time3.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\4.mp3
    audio_rutina_time4.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\5.mp3
    audio_rutina_time5.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\6.mp3
    audio_rutina_time6.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\7.mp3
    audio_rutina_time7.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\9.mp3
    audio_rutina_time8.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\10.mp3
    audio_rutina_time9.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\12.mp3
    audio_rutina_time10.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\15.mp3
    audio_rutina_time11.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\17.mp3
    audio_rutina_time12.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\18.mp3
    audio_rutina_time13.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time14.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\20.mp3
    audio_rutina_time14.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time15.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\22.mp3
    audio_rutina_time15.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time16.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\24.mp3
    audio_rutina_time16.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time17.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\25.mp3
    audio_rutina_time17.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time18.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\26.mp3
    audio_rutina_time18.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time19.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\28.mp3
    audio_rutina_time19.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time20.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\30.mp3
    audio_rutina_time20.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time21.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\35.mp3
    audio_rutina_time21.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time22.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\36.mp3
    audio_rutina_time22.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time23.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\40.mp3
    audio_rutina_time23.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time24.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\45.mp3
    audio_rutina_time24.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time25.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\50.mp3
    audio_rutina_time25.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time26.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\55.mp3
    audio_rutina_time26.path = e:\Data\Others\PersonalTrainer\Rutinas\Min
    audio_rutina_time27.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\min\60.mp3
    audio_rutina_time27.path = e:\Data\Others\PersonalTrainer\Rutinas\Min

    DEPLOYMENT += audio_rutina_time1 + audio_rutina_time2 + audio_rutina_time3 + audio_rutina_time4 + audio_rutina_time5 + audio_rutina_time6 + \
                  audio_rutina_time7 + audio_rutina_time8 + audio_rutina_time9 + audio_rutina_time10 + audio_rutina_time11 + audio_rutina_time12 + \
                  audio_rutina_time13 + audio_rutina_time14 + audio_rutina_time15 + audio_rutina_time16 + audio_rutina_time17 + audio_rutina_time18 + \
                  audio_rutina_time19 + audio_rutina_time20 + audio_rutina_time21 + audio_rutina_time22 + audio_rutina_time24 + audio_rutina_time25 + \
                  audio_rutina_time26 + audio_rutina_time27

    audio_rutina_reps1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\3.mp3
    audio_rutina_reps1.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\5.mp3
    audio_rutina_reps2.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\7.mp3
    audio_rutina_reps3.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\8.mp3
    audio_rutina_reps4.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\10.mp3
    audio_rutina_reps5.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\12.mp3
    audio_rutina_reps6.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\15.mp3
    audio_rutina_reps7.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\20.mp3
    audio_rutina_reps8.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\25.mp3
    audio_rutina_reps9.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\30.mp3
    audio_rutina_reps10.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\40.mp3
    audio_rutina_reps11.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\50.mp3
    audio_rutina_reps12.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\60.mp3
    audio_rutina_reps13.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps
    audio_rutina_reps14.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\reps\75.mp3
    audio_rutina_reps14.path = e:\Data\Others\PersonalTrainer\Rutinas\Reps

    DEPLOYMENT += audio_rutina_reps1 + audio_rutina_reps2 + audio_rutina_reps3 + audio_rutina_reps4 + audio_rutina_reps5 + audio_rutina_reps6 + \
                  audio_rutina_reps7 + audio_rutina_reps8 + audio_rutina_reps9 + audio_rutina_reps10 + audio_rutina_reps11 + audio_rutina_reps12 + \
                  audio_rutina_reps13 + audio_rutina_reps14

    audio_rutina_steps1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\steps\20.mp3
    audio_rutina_steps1.path = e:\Data\Others\PersonalTrainer\Rutinas\Steps
    audio_rutina_steps2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\steps\22.mp3
    audio_rutina_steps2.path = e:\Data\Others\PersonalTrainer\Rutinas\Steps
    audio_rutina_steps3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\steps\24.mp3
    audio_rutina_steps3.path = e:\Data\Others\PersonalTrainer\Rutinas\Steps
    audio_rutina_steps4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\steps\30.mp3
    audio_rutina_steps4.path = e:\Data\Others\PersonalTrainer\Rutinas\Steps

    DEPLOYMENT += audio_rutina_steps1 + audio_rutina_steps2 + audio_rutina_steps3 + audio_rutina_steps4

    audio_rutina_km1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\km\7.mp3
    audio_rutina_km1.path = e:\Data\Others\PersonalTrainer\Rutinas\Km
    audio_rutina_km2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\km\8.mp3
    audio_rutina_km2.path = e:\Data\Others\PersonalTrainer\Rutinas\Km
    audio_rutina_km3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\km\9.mp3
    audio_rutina_km3.path = e:\Data\Others\PersonalTrainer\Rutinas\Km
    audio_rutina_km4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\km\10.mp3
    audio_rutina_km4.path = e:\Data\Others\PersonalTrainer\Rutinas\Km

    DEPLOYMENT += audio_rutina_km1 + audio_rutina_km2 + audio_rutina_km3 + audio_rutina_km4

    audio_rutina_pas1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\2.mp3
    audio_rutina_pas1.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas
    audio_rutina_pas2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\3.mp3
    audio_rutina_pas2.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas
    audio_rutina_pas3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\4.mp3
    audio_rutina_pas3.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas
    audio_rutina_pas4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\6.mp3
    audio_rutina_pas4.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas
    audio_rutina_pas5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\7.mp3
    audio_rutina_pas5.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas
    audio_rutina_pas6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\pas\8.mp3
    audio_rutina_pas6.path = e:\Data\Others\PersonalTrainer\Rutinas\Pas

    DEPLOYMENT += audio_rutina_pas1 + audio_rutina_pas2 + audio_rutina_pas3 + audio_rutina_pas4 + audio_rutina_pas5 + audio_rutina_pas6

    audio_rutina_series1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\2x30.mp3
    audio_rutina_series1.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\2x40.mp3
    audio_rutina_series2.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\2x50.mp3
    audio_rutina_series3.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\3x30.mp3
    audio_rutina_series4.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\3x40.mp3
    audio_rutina_series5.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\3x50.mp3
    audio_rutina_series6.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\3x60.mp3
    audio_rutina_series7.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\4x30.mp3
    audio_rutina_series8.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\4x40.mp3
    audio_rutina_series9.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\4x50.mp3
    audio_rutina_series10.path = e:\Data\Others\PersonalTrainer\Rutinas\Series
    audio_rutina_series11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\series\4x60.mp3
    audio_rutina_series11.path = e:\Data\Others\PersonalTrainer\Rutinas\Series

    DEPLOYMENT += audio_rutina_series1 + audio_rutina_series2 + audio_rutina_series3 + audio_rutina_series4 + audio_rutina_series5 + audio_rutina_series6 + \
                  audio_rutina_series7 + audio_rutina_series8 + audio_rutina_series9 + audio_rutina_series10 + audio_rutina_series11

    audio_rutina_vez1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\vez\4x10.mp3
    audio_rutina_vez1.path = e:\Data\Others\PersonalTrainer\Rutinas\Vez
    audio_rutina_vez2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\vez\5x10.mp3
    audio_rutina_vez2.path = e:\Data\Others\PersonalTrainer\Rutinas\Vez
    audio_rutina_vez3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\vez\6x10.mp3
    audio_rutina_vez3.path = e:\Data\Others\PersonalTrainer\Rutinas\Vez

    DEPLOYMENT += audio_rutina_vez1 + audio_rutina_vez2 + audio_rutina_vez3

    audio_rutina_ritmobueno1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\1.mp3
    audio_rutina_ritmobueno1.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\2.mp3
    audio_rutina_ritmobueno2.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\3.mp3
    audio_rutina_ritmobueno3.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\4.mp3
    audio_rutina_ritmobueno4.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\5.mp3
    audio_rutina_ritmobueno5.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\6.mp3
    audio_rutina_ritmobueno6.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\7.mp3
    audio_rutina_ritmobueno7.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\8.mp3
    audio_rutina_ritmobueno8.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\9.mp3
    audio_rutina_ritmobueno9.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\10.mp3
    audio_rutina_ritmobueno10.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\11.mp3
    audio_rutina_ritmobueno11.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\12.mp3
    audio_rutina_ritmobueno12.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\13.mp3
    audio_rutina_ritmobueno13.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno14.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\14.mp3
    audio_rutina_ritmobueno14.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno15.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\15.mp3
    audio_rutina_ritmobueno15.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno16.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\16.mp3
    audio_rutina_ritmobueno16.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno17.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\17.mp3
    audio_rutina_ritmobueno17.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno
    audio_rutina_ritmobueno18.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\ritmobueno\18.mp3
    audio_rutina_ritmobueno18.path = e:\Data\Others\PersonalTrainer\Rutinas\RitmoBueno

    DEPLOYMENT += audio_rutina_ritmobueno1 + audio_rutina_ritmobueno2 + audio_rutina_ritmobueno3 + audio_rutina_ritmobueno4 + audio_rutina_ritmobueno5 + \
                  audio_rutina_ritmobueno6 + audio_rutina_ritmobueno7 + audio_rutina_ritmobueno8 + audio_rutina_ritmobueno9 + audio_rutina_ritmobueno10 + \
                  audio_rutina_ritmobueno11 + audio_rutina_ritmobueno12 + audio_rutina_ritmobueno13 + audio_rutina_ritmobueno14 + audio_rutina_ritmobueno15 + \
                  audio_rutina_ritmobueno16 + audio_rutina_ritmobueno17 + audio_rutina_ritmobueno18 

    audio_rutina_bien1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\1.mp3
    audio_rutina_bien1.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\2.mp3
    audio_rutina_bien2.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\3.mp3
    audio_rutina_bien3.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\4.mp3
    audio_rutina_bien4.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\5.mp3
    audio_rutina_bien5.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\6.mp3
    audio_rutina_bien6.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\7.mp3
    audio_rutina_bien7.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\8.mp3
    audio_rutina_bien8.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\9.mp3
    audio_rutina_bien9.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\10.mp3
    audio_rutina_bien10.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\11.mp3
    audio_rutina_bien11.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\12.mp3
    audio_rutina_bien12.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien
    audio_rutina_bien13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\bien\13.mp3
    audio_rutina_bien13.path = e:\Data\Others\PersonalTrainer\Rutinas\Bien

    DEPLOYMENT += audio_rutina_bien1 + audio_rutina_bien2 + audio_rutina_bien3 + audio_rutina_bien4 + audio_rutina_bien5 + audio_rutina_bien6 \
                + audio_rutina_bien7 + audio_rutina_bien8 + audio_rutina_bien9 + audio_rutina_bien10 + audio_rutina_bien11 + audio_rutina_bien12 \
                + audio_rutina_bien13

    audio_rutina_malh1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h1.mp3
    audio_rutina_malh1.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h2.mp3
    audio_rutina_malh2.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h3.mp3
    audio_rutina_malh3.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h4.mp3
    audio_rutina_malh4.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h5.mp3
    audio_rutina_malh5.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh6.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h6.mp3
    audio_rutina_malh6.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh7.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h7.mp3
    audio_rutina_malh7.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malh8.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\h8.mp3
    audio_rutina_malh8.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal

    DEPLOYMENT += audio_rutina_malh1 + audio_rutina_malh2 + audio_rutina_malh3 + audio_rutina_malh4 + audio_rutina_malh5 + audio_rutina_malh6 \
                + audio_rutina_malh7 + audio_rutina_malh8

    audio_rutina_malm1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\m1.mp3
    audio_rutina_malm1.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malm2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\m2.mp3
    audio_rutina_malm2.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malm3.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\m3.mp3
    audio_rutina_malm3.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malm4.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\m4.mp3
    audio_rutina_malm4.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal
    audio_rutina_malm5.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\rutinas\mal\m5.mp3
    audio_rutina_malm5.path = e:\Data\Others\PersonalTrainer\Rutinas\Mal

    DEPLOYMENT += audio_rutina_malm1 + audio_rutina_malm2 + audio_rutina_malm3 + audio_rutina_malm4 + audio_rutina_malm5

    audio_ejercicio1.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\1.mp3
    audio_ejercicio1.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio2.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\2.mp3
    audio_ejercicio2.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio9.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\9.mp3
    audio_ejercicio9.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio10.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\10.mp3
    audio_ejercicio10.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio11.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\11.mp3
    audio_ejercicio11.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio12.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\12.mp3
    audio_ejercicio12.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio13.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\13.mp3
    audio_ejercicio13.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio14.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\14.mp3
    audio_ejercicio14.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio15.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\15.mp3
    audio_ejercicio15.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio16.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\16.mp3
    audio_ejercicio16.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio17.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\17.mp3
    audio_ejercicio17.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio18.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\18.mp3
    audio_ejercicio18.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio19.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\19.mp3
    audio_ejercicio19.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio20.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\20.mp3
    audio_ejercicio20.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio21.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\21.mp3
    audio_ejercicio21.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio22.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\22.mp3
    audio_ejercicio22.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio23.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\23.mp3
    audio_ejercicio23.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio24.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\24.mp3
    audio_ejercicio24.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio25.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\25.mp3
    audio_ejercicio25.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio26.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\26.mp3
    audio_ejercicio26.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio27.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\27.mp3
    audio_ejercicio27.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio28.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\28.mp3
    audio_ejercicio28.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio29.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\29.mp3
    audio_ejercicio29.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio30.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\30.mp3
    audio_ejercicio30.path = e:\Data\Others\PersonalTrainer\Ejercicios
    audio_ejercicio31.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\ejercicios\31.mp3
    audio_ejercicio31.path = e:\Data\Others\PersonalTrainer\Ejercicios

    DEPLOYMENT += audio_ejercicio1 + audio_ejercicio2 + audio_ejercicio9 + audio_ejercicio10 + audio_ejercicio11 + audio_ejercicio12 + \
                     audio_ejercicio13 + audio_ejercicio14 + audio_ejercicio15 + audio_ejercicio16 + audio_ejercicio17 + audio_ejercicio18 + \
                     audio_ejercicio19 + audio_ejercicio20 + audio_ejercicio21 + audio_ejercicio22 + audio_ejercicio23 + audio_ejercicio24 + \
                     audio_ejercicio25 + audio_ejercicio26 + audio_ejercicio27 + audio_ejercicio28 + audio_ejercicio29 + audio_ejercicio30 + \
                     audio_ejercicio31

    audio_intro.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\sfx\sfx_hola.mp3
    audio_intro.path = e:\Data\Others\PersonalTrainer
    video.sources = c:\OneForceMobileSVN\iphoideas\ecosport_freestyle\personaltrainer\proj_resources\video\intro.mp4
    video.path = e:\Data\Others\PersonalTrainer

    DEPLOYMENT += audio_intro + video

}
