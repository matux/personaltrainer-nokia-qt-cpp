#include "testview.h"
#include "testresultsview.h"
#include "views/headerview.h"
#include "model/location/geodistancecalc.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"

#include <QDateTime>

TestView::TestView(QWidget *parent)
    :SIView(parent)
{
    m_startButton = NULL;
    m_pauseButton = NULL;
    m_counterTimer = NULL;
    m_fireNextPhraseTime = 100;
    m_showTestMessage = true;

    setObjectName(QString().sprintf("TestView%p", this));

    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName(QString().sprintf("%p", m_centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    m_centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(m_centralWidget->objectName()));
    m_centralWidget->resize(size());
    m_centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_centralWidget->setMinimumWidth(QApplication::desktop()->width());
    m_centralWidget->setMinimumHeight(436);

    QWidget *figure = new QWidget(m_centralWidget);
    figure->setObjectName(QString().sprintf("figureTest%p", figure));
    figure->setGeometry(0, 10, 360, 154);
    QString styleSheet(QString("QWidget#%1 { image: url(:/images/res/test_figurin.png); }").arg(figure->objectName()));
    figure->setStyleSheet(styleSheet);
    figure->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *labelSearching = new QLabel(m_centralWidget);
    labelSearching->setObjectName(QString().sprintf("labelSearching%p", labelSearching));
    labelSearching->setGeometry(0, 170, 360, 48);
    labelSearching->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    labelSearching->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelSearching->setText("Hacé este test de desempeño a tu mejor\nritmo ya sea caminando o trotando.");
    labelSearching->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 18px \"AvantGardeMdITCTT\"; }").arg(labelSearching->objectName()));


    QWidget *infoBaseWidget = new QWidget(m_centralWidget);
    infoBaseWidget->setObjectName(QString().sprintf("infoTest%p", infoBaseWidget));
    infoBaseWidget->setGeometry(0, 159, 360, 319);
    infoBaseWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/test_base.png); }").arg(infoBaseWidget->objectName()));
    infoBaseWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

#ifndef _RELEASE
    SIButton *labelTest = new SIButton(m_centralWidget);
    labelTest->setObjectName(QString().sprintf("testLabel%p", labelTest));
    labelTest->resize(80, 40);
    labelTest->move(10, 5);
    labelTest->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelTest->setText("Skip");
    labelTest->setNormalStatePix(":/images/res/test_skip.png");
    labelTest->setPressedStatePix(":/images/res/test_skip_on.png");
    labelTest->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 50 10px \"AvantGardeMdITCTT\"; }").arg(labelTest->objectName()));
    connect(labelTest, SIGNAL(clicked()), this, SLOT(skipPressed()));
#endif

    /***************************************************************************/

    QLabel *labelDistRecorrida = new QLabel(m_centralWidget);
    labelDistRecorrida->setObjectName(QString().sprintf("labelDistRecorrida%p", labelDistRecorrida));
    labelDistRecorrida->resize(210, 25);
    labelDistRecorrida->move(32, 254);
    labelDistRecorrida->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelDistRecorrida->setText("DISTANCIA RECORRIDA:");
    labelDistRecorrida->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(labelDistRecorrida->objectName()));

    m_labelDistance = new QLabel(m_centralWidget);
    m_labelDistance->setObjectName(QString().sprintf("m_labelDistance%p", m_labelDistance));
    m_labelDistance->resize(95, 25);
    m_labelDistance->move(232, 254);
    m_labelDistance->setAlignment(Qt::AlignTop|Qt::AlignRight);
    m_labelDistance->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelDistance->setText("- MTS");
    m_labelDistance->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(m_labelDistance->objectName()));

    /***************************************************************************/

    QLabel *labelTiempo = new QLabel(m_centralWidget);
    labelTiempo->setObjectName(QString().sprintf("labelTiempo%p", labelTiempo));
    labelTiempo->resize(210, 25);
    labelTiempo->move(32, 298);
    labelTiempo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelTiempo->setText("TIEMPO:");
    labelTiempo->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(labelTiempo->objectName()));

    m_labelTime = new QLabel(m_centralWidget);
    m_labelTime->setObjectName(QString().sprintf("m_labelTime%p", m_labelTime));
    m_labelTime->resize(95, 25);
    m_labelTime->move(232, 298);
    m_labelTime->setAlignment(Qt::AlignTop|Qt::AlignRight);
    m_labelTime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelTime->setText("00' 00\" .00");
    m_labelTime->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(m_labelTime->objectName()));

    /***************************************************************************/

    m_labelGPS = new QLabel(m_centralWidget);
    m_labelGPS->setObjectName(QString().sprintf("m_labelGPS%p", m_labelTime));
    m_labelGPS->setGeometry(QRect(0, 365, 360, 48));
    m_labelGPS->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_labelGPS->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelGPS->setText("ESPERANDO GPS...");
    m_labelGPS->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 24px \"AvantGardeMdITCTT\"; }").arg(m_labelGPS->objectName()));

    m_startButton = new SIButton(m_centralWidget);
    m_startButton->setObjectName(QString::fromUtf8("startButton"));
    m_startButton->setGeometry(QRect(135, 360, 120, 48));
    m_startButton->setText(QString::fromUtf8("START"));
    m_startButton->setNormalStatePix(":/images/res/rutina_ejercicio_bot_start.png");
    m_startButton->setPressedStatePix(":/images/res/rutina_ejercicio_bot_start_on.png");
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startPressed()));
    m_startButton->hide();

    m_pauseButton = new SIButton(m_centralWidget);
    m_pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
    m_pauseButton->setGeometry(QRect(135, 360, 120, 48));
    m_pauseButton->setText(QString::fromUtf8("PAUSE"));
    m_pauseButton->setNormalStatePix(":/images/res/rutina_ejercicio_bot_pause.png");
    m_pauseButton->setPressedStatePix(":/images/res/rutina_ejercicio_bot_pause_on.png");
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(pausePressed()));
    m_pauseButton->hide();

    m_chronometer.setHMS(0, 0, 0, 0);

    destroyTimer();
    m_counterTimer = new QTimer();
    m_counterTimer->setInterval(1000);
    m_counterTimer->setSingleShot(false);
    m_counterTimer->start();
    connect(m_counterTimer, SIGNAL(timeout()), this, SLOT(gpsTimerCheck()));

}

TestView::~TestView()
{

}

void TestView::showEvent(QShowEvent *)
{/*
    if( m_showTestMessage )
    {
        QString title("Test de Cooper");
        QString msg("Corré durante 12 minutos para que conozca tu nivel.");
        m_showTestMessage = false;
#ifdef _SIMULATOR_BUILD
        qWarning("\n>>>>>>>>>>>>>>>>>> %s\n", msg.toAscii().constData());
#else
        QMessageBox msgBox;
        msgBox.setText(title);
        msgBox.setInformativeText(msg);
        msgBox.exec();
#endif
    }*/

    m_firstTime = true;

    m_headerView->setTitleImageFilename(":/images/res/header_titulo_test.png");
    m_headerView->repaint();

    SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/Test/buenoavisame.mp3");

}

void TestView::destroyTimer()
{
    if( m_counterTimer )
    {
        m_counterTimer->stop();
        delete m_counterTimer;
        m_counterTimer = NULL;
    }

}

void TestView::gpsTimerCheck()
{
    if( GeoDistanceCalc::instance().acquired() || !GeoDistanceCalc::instance().gpsAvailable() )
    {
        destroyTimer();
        m_labelGPS->hide();
        m_startButton->show();

    }

}

void TestView::timerUpdated()
{
    const QTime &time = QTime::currentTime();
    int msecs = m_startSnapshotTime.msecsTo(time);
    m_startSnapshotTime = time;
    m_chronometer = m_chronometer.addMSecs(msecs);

    QString timeString = m_chronometer.toString("mm'' ss\" .zzz");
    timeString = timeString.left(timeString.count()-1);
    m_labelTime->setText(timeString);
    m_labelTime->repaint();

    int distance = (int)GeoDistanceCalc::instance().distanceInMeters();
    QString strDist = QString().sprintf("%d MTS", distance);
    if( distance == 0 )
        strDist = QString("- MTS");

    m_labelDistance->setText(strDist);
    m_labelDistance->repaint();

    if( m_fireNextPhraseTime == 100 )
        m_fireNextPhraseTime = 300000; // 5 minutos  // ((rand() % 30) + 30) * 1000;
    else
        m_fireNextPhraseTime -= msecs;
    if( m_fireNextPhraseTime <= 0 )
    {
        int r = (rand() % 3);
        //SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Test/test%1.mp3").arg(r));
        m_fireNextPhraseTime = 300000; // 5 minutos  // ((rand() % 30) + 30) * 1000;

        qDebug("next in %d", m_fireNextPhraseTime);
    }

    if( m_chronometer.minute() >= 12 && m_chronometer.second() >= 0 )
        skipPressed();

}

void TestView::startPressed()
{
    if( m_firstTime )
        SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/min/12.mp3"));

    m_startButton->hide();
    m_pauseButton->show();

    if( GeoDistanceCalc::instance().isPaused() )
        GeoDistanceCalc::instance().resume();
    else
        GeoDistanceCalc::instance().start();

    m_startSnapshotTime = QTime::currentTime();

    destroyTimer();
    m_counterTimer = new QTimer();
    m_counterTimer->setInterval(10);
    m_counterTimer->setSingleShot(false);
    m_counterTimer->start();
    connect(m_counterTimer, SIGNAL(timeout()), this, SLOT(timerUpdated()));

}

void TestView::pausePressed()
{
    GeoDistanceCalc::instance().pause();
    m_startButton->show();
    m_pauseButton->hide();

    destroyTimer();

}

void TestView::skipPressed()
{
    //GeoDistanceCalc::instance().stop();
    GeoDistanceCalc::instance().reset();
    GeoDistanceCalc::instance().pause();

    destroyTimer();

    GlobalDataObject::instance().setUserRegistered(false);
    GlobalDataObject::instance().userInfo().resetRoutines();
    GlobalDataObject::instance().userInfo().setMetersCoveredInTest((int)GeoDistanceCalc::instance().distanceInMeters());
    GlobalDataObject::instance().resetPlanInfo();
    GlobalDataObject::instance().userInfo().setLevel(
            GlobalDataObject::instance().userInfo().objectiveIndex(),
            GlobalDataObject::instance().userInfo().resolveLevel());
    GlobalDataObject::instance().setFirstTimeRun(false);
    GlobalDataObject::instance().saveApplicationSettings();

    TestResultsView *testResultsView = new TestResultsView();
    testResultsView->setHeaderView(m_headerView);
    navigationController()->pushView(testResultsView);

}
