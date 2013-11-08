#include "ejercicioview.h"
#include "views/headerview.h"
#include "model/location/geodistancecalc.h"
#include "model/routines/routine.h"
#include "model/routines/routinemanager.h"
#include "model/routines/routineexercise.h"
#include "model/routines/routineexercisecomposition.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "model/exercises/exercise.h"
#include "model/exercises/exercisemanager.h"
#include "model/planinfo.h"
#include "views/trainer/trainerdetailedview.h"
#include "rutinaaudiofinview.h"
#include "mainwindow.h"

#include <QDateTime>

EjercicioView::EjercicioView(int exerciseNumber, bool autoInitUi, QWidget *parent)
    :SIView(parent),
    m_exerciseNumber(exerciseNumber),
    m_routineExercise(NULL),
    m_routineComposition(NULL)
{
    m_startButton = NULL;
    m_pauseButton = NULL;
    m_finishedButton = NULL;
    m_counterTimer = NULL;
    m_sessionTimer = NULL;
    m_pasadaNumber = 0;

    m_labelPanel = NULL;
    m_labelDistanceLabel = NULL;
    m_labelDistance = NULL;
    m_labelTimeLabel = NULL;
    m_labelTime = NULL;
    m_labelSessionTimeLabel = NULL;
    m_labelSessionTime = NULL;
    m_labelStepsLabel = NULL;
    m_labelSteps = NULL;
    m_labelGPS = NULL;

    m_finishedButtonTimer = NULL;

    m_sessionChronometer.setHMS(0, 0, 0, 0);

    m_fireNextPhraseTime = 100;

    setObjectName(QString().sprintf("EjercicioView%p", this));

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

    destroySessionTimer();
    m_countSessionTime = false;
    m_sessionTimer = new QTimer();
    m_sessionTimer->setInterval(1000);
    m_sessionTimer->setSingleShot(false);
    //m_sessionTimer->start();
    connect(m_sessionTimer, SIGNAL(timeout()), this, SLOT(sessionTimerUpdated()));

    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));

    if( autoInitUi )
        initUi();

}

EjercicioView::~EjercicioView()
{

}

void EjercicioView::initUi()
{
    const Routine &currentRoutine = GlobalDataObject::instance().userInfo().currentRoutine();
    m_routineExercise = &((m_routineComposition)?
                             dynamic_cast<const RoutineExercise &>(m_routineComposition->exerciseAt(m_subExerciseNumber)):
                             dynamic_cast<const RoutineExercise &>(currentRoutine.exerciseAt(m_exerciseNumber)));

    //QWidget *figure = new QWidget(m_centralWidget);
    SIButton *figure = new SIButton(m_centralWidget);
    figure->setObjectName(QString().sprintf("figureTest%p", figure));
    figure->setGeometry(0, 33, 360, 154);
    QString figurin = RoutineManager::instance().figureFilename(m_routineExercise->exerciseId());
    //QString styleSheet(QString("QWidget#%1 { image: url(:/images/res/%2); }").arg(figure->objectName()).arg(figurin));
    //figure->setStyleSheet(styleSheet);
    figure->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    figure->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    figure->setNormalStatePix(QString().sprintf(":/images/res/%s", figurin.toAscii().constData()));
    figure->setPressedStatePix(QString().sprintf(":/images/res/%s", figurin.toAscii().constData()));
    QObject::connect(figure, SIGNAL(clicked()), this, SLOT(figurePressed()));


    QWidget *infoBaseWidget = new QWidget(m_centralWidget);
    infoBaseWidget->setObjectName(QString().sprintf("infoTest%p", infoBaseWidget));
    infoBaseWidget->setGeometry(0, 159, 360, 319);
    infoBaseWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/rutina_ejercicio_base.png); }").arg(infoBaseWidget->objectName()));
    infoBaseWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

#ifndef _RELEASE
    SIButton *labelTest = new SIButton(m_centralWidget);
    labelTest->setObjectName(QString().sprintf("testLabel%p", labelTest));
    labelTest->setGeometry(10, 25, 80, 40);
    labelTest->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelTest->setText("Skip");
    labelTest->setNormalStatePix(":/images/res/test_skip.png");
    labelTest->setPressedStatePix(":/images/res/test_skip_on.png");
    labelTest->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 50 10px \"AvantGardeMdITCTT\"; }").arg(labelTest->objectName()));
    connect(labelTest, SIGNAL(clicked()), this, SLOT(nextExercise()));
#endif

    /***************************************************************************/

    QLabel *labelExerciseName = new QLabel(m_centralWidget);
    labelExerciseName->setObjectName(QString().sprintf("labelExerciseName%p", labelExerciseName));
    labelExerciseName->move(18, 0);
    labelExerciseName->resize(281, 24);
    labelExerciseName->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    labelExerciseName->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelExerciseName->setText(m_routineExercise->name().toUpper());
    labelExerciseName->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 19px \"AvantGardeMdITCTT\"; }").arg(labelExerciseName->objectName()));

    QLabel *labelExerciseCount = new QLabel(m_centralWidget);
    labelExerciseCount->setObjectName(QString().sprintf("labelExerciseName%p", labelExerciseCount));
    labelExerciseCount->move(300, 0);
    labelExerciseCount->resize(56, 24);
    labelExerciseCount->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    labelExerciseCount->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelExerciseCount->setText(QString().sprintf("%d/%d", m_exerciseNumber + 1, currentRoutine.exerciseCountWithoutComposition()));
    labelExerciseCount->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font-size: 19px; font-family: \"AvantGardeMdITCTT\"; }").arg(labelExerciseCount->objectName()));

    if( m_routineComposition )
    {
        QLabel *labelPasadaCount = new QLabel(m_centralWidget);
        labelPasadaCount->setObjectName(QString().sprintf("labelPasadaCount%p", labelPasadaCount));
        labelPasadaCount->move(225, 28);
        labelPasadaCount->resize(120, 24);
        labelPasadaCount->setAlignment(Qt::AlignTop|Qt::AlignRight);
        labelPasadaCount->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        labelPasadaCount->setText(QString().sprintf("PASADA %d/%d", m_pasadaNumber, m_routineComposition->count()));
        labelPasadaCount->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font-size: 17px; font-family: \"AvantGardeMdITCTT\"; }").arg(labelPasadaCount->objectName()));
    }

    /***************************************************************************/

    m_startButton = new SIButton(m_centralWidget);
    m_startButton->setObjectName(QString::fromUtf8("startButton"));
    m_startButton->setGeometry(QRect(135, 380, 120, 48));
    m_startButton->setNormalStatePix(":/images/res/rutina_ejercicio_bot_start.png");
    m_startButton->setPressedStatePix(":/images/res/rutina_ejercicio_bot_start_on.png");
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startPressed()));

    m_pauseButton = new SIButton(m_centralWidget);
    m_pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
    m_pauseButton->setGeometry(QRect(135, 380, 120, 48));
    m_pauseButton->setNormalStatePix(":/images/res/rutina_ejercicio_bot_pause.png");
    m_pauseButton->setPressedStatePix(":/images/res/rutina_ejercicio_bot_pause_on.png");
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(pausePressed()));

    m_finishedButton = new SIButton(m_centralWidget);
    m_finishedButton->setObjectName(QString::fromUtf8("m_finishedButton"));
    m_finishedButton->setGeometry(QRect(114, 367, 133, 59));
    m_finishedButton->setNormalStatePix(":/images/res/rutina_boton_terminado.png");
    m_finishedButton->setPressedStatePix(":/images/res/rutina_boton_terminado_on.png");
    m_finishedButton->hide();
    connect(m_finishedButton, SIGNAL(clicked()), this, SLOT(nextExercise()));

    initControlPanel();

    m_chronometer.setHMS(0, 0, 0, 0);

}

void EjercicioView::initControlPanel()
{
    const Exercise &exercise = m_routineExercise->actualExercise();

    // First, figure out how many labels we need to display
    // We always assume 2 because Session Time and Control Panel title are always constant
    int labelCount = 2 + (int)(exercise.requiresGPS()||exercise.showsDistance()) + (int)exercise.showsTime() + (int)exercise.showsReps() + (int)exercise.showsSteps();
    // Figure out the position and space available
    const int initialY = 216;
    const int availableHeight = 125;
    int heightPerItem = availableHeight / labelCount;
    int y = initialY + (heightPerItem / 2);

    // Control Panel Title //
    {
        if( !m_labelPanel )
        {
            m_labelPanel = new QLabel(m_centralWidget);
            m_labelPanel->setObjectName(QString().sprintf("m_labelPanel%p", m_labelPanel));
            m_labelPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelPanel->setText("PANEL DE CONTROL");
            m_labelPanel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: bold 20px \"AvantGardeITCTT\"; }").arg(m_labelPanel->objectName()));
        }

        m_labelPanel->setGeometry(32, y, 300, 28);

        y += heightPerItem;
    }

    if( exercise.requiresGPS() && m_routineExercise->time() > 0  )
    {
        if( !m_labelDistanceLabel )
        {
            m_labelDistanceLabel = new QLabel(m_centralWidget);
            m_labelDistanceLabel->setObjectName(QString().sprintf("m_labelDistanceLabel%p", m_labelDistanceLabel));
            m_labelDistanceLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelDistanceLabel->setText("DISTANCIA RECORRIDA:");
            m_labelDistanceLabel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(200, 200, 200); font: normal 19px \"AvantGardeMdITCTT\"; }").arg(m_labelDistanceLabel->objectName()));
        }
        m_labelDistanceLabel->setGeometry(32, y, 210, 25);

        if( !m_labelDistance )
        {
            m_labelDistance = new QLabel(m_centralWidget);
            m_labelDistance->setObjectName(QString().sprintf("m_labelDistance%p", m_labelDistance));
            m_labelDistance->setAlignment(Qt::AlignTop|Qt::AlignRight);
            m_labelDistance->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelDistance->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 20px \"AvantGardeMdITCTT\"; }").arg(m_labelDistance->objectName()));
        }
        m_labelDistance->setText("- MTS");
        m_labelDistance->setGeometry(232, y, 95, 25);

        if( !m_labelGPS )
        {
            m_labelGPS = new QLabel(m_centralWidget);
            m_labelGPS->setObjectName(QString().sprintf("m_labelGPS%p", m_labelTime));
            m_labelGPS->setGeometry(0, 380, 360, 48);
            m_labelGPS->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
            m_labelGPS->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelGPS->setText("ESPERANDO GPS...");
            m_labelGPS->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(240, 240, 240); font: normal 24px \"AvantGardeMdITCTT\"; }").arg(m_labelGPS->objectName()));
        }

        m_startButton->hide();

        destroyTimer();
        m_counterTimer = new QTimer();
        m_counterTimer->setInterval(1000);
        m_counterTimer->setSingleShot(false);
        m_counterTimer->start();
        connect(m_counterTimer, SIGNAL(timeout()), this, SLOT(gpsTimerCheck()));

        y += heightPerItem;

    }

    if( exercise.showsTime() && m_routineExercise->time() > 0 )
    {
        if( !m_labelTimeLabel )
        {
            m_labelTimeLabel = new QLabel(m_centralWidget);
            m_labelTimeLabel->setObjectName(QString().sprintf("m_labelTimeLabel%p", m_labelTimeLabel));
            m_labelTimeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelTimeLabel->setText("TIEMPO EJERCICIO");
            m_labelTimeLabel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(200, 200, 200); font: normal 19px \"AvantGardeMdITCTT\"; }").arg(m_labelTimeLabel->objectName()));
        }
        m_labelTimeLabel->setGeometry(32, y, 210, 25);

        if( !m_labelTime )
        {
            m_labelTime = new QLabel(m_centralWidget);
            m_labelTime->setObjectName(QString().sprintf("m_labelTime%p", m_labelTime));
            m_labelTime->setAlignment(Qt::AlignTop|Qt::AlignRight);
            m_labelTime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelTime->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 20px \"AvantGardeMdITCTT\"; }").arg(m_labelTime->objectName()));
        }
        m_labelTime->setGeometry(172, y, 155, 25);
        m_labelTime->setText(QString().sprintf("00' 00\" .00 / %d'", m_routineExercise->time()));

        y += heightPerItem;

    }

    if( exercise.showsReps() )
    {
        m_labelRepsLabel = new QLabel(m_centralWidget);
        m_labelRepsLabel->setObjectName(QString().sprintf("m_labelRepsLabel%p", m_labelRepsLabel));
        m_labelRepsLabel->setGeometry(32, y, 210, 25);
        m_labelRepsLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_labelRepsLabel->setText("SERIES / REPETICIONES");
        m_labelRepsLabel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(200, 200, 200); font: normal 19px \"AvantGardeMdITCTT\"; }").arg(m_labelRepsLabel->objectName()));

        m_labelReps = new QLabel(m_centralWidget);
        m_labelReps->setObjectName(QString().sprintf("m_labelReps%p", m_labelReps));
        m_labelReps->setGeometry(232, y, 95, 25);
        m_labelReps->setAlignment(Qt::AlignTop|Qt::AlignRight);
        m_labelReps->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_labelReps->setText(QString().sprintf("%d / %d", m_routineExercise->series(), m_routineExercise->time()));
        m_labelReps->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 20px \"AvantGardeMdITCTT\"; }").arg(m_labelReps->objectName()));

        y += heightPerItem;

    }

    if( exercise.showsTime() && m_routineExercise->time() == 0 && m_routineExercise->special() > 0 )
    {
        m_labelStepsLabel = new QLabel(m_centralWidget);
        m_labelStepsLabel->setObjectName(QString().sprintf("m_labelStepsLabel%p", m_labelRepsLabel));
        m_labelStepsLabel->setGeometry(32, y, 210, 25);
        m_labelStepsLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_labelStepsLabel->setText("PASOS");
        m_labelStepsLabel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(200, 200, 200); font: normal 19px \"AvantGardeMdITCTT\"; }").arg(m_labelStepsLabel->objectName()));

        m_labelSteps = new QLabel(m_centralWidget);
        m_labelSteps->setObjectName(QString().sprintf("m_labelSteps%p", m_labelReps));
        m_labelSteps->setGeometry(232, y, 95, 25);
        m_labelSteps->setAlignment(Qt::AlignTop|Qt::AlignRight);
        m_labelSteps->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_labelSteps->setText(QString().sprintf("%d", m_routineExercise->special()));
        m_labelSteps->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: normal 20px \"AvantGardeMdITCTT\"; }").arg(m_labelSteps->objectName()));

        y += heightPerItem;

    }

    // Show Session Time //
    {
        if( !m_labelSessionTimeLabel )
        {
            m_labelSessionTimeLabel = new QLabel(m_centralWidget);
            m_labelSessionTimeLabel->setObjectName(QString().sprintf("m_labelSessionTimeLabel%p", m_labelSessionTimeLabel));
            m_labelSessionTimeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
            m_labelSessionTimeLabel->setText("TIEMPO DE LA RUTINA");
            m_labelSessionTimeLabel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(200, 200, 200); font: 75 19px \"AvantGardeMdITCTT\"; }").arg(m_labelSessionTimeLabel->objectName()));
        }
        m_labelSessionTimeLabel->setGeometry(32, y, 210, 25);

        synchronized(mutex)
        {
            if( !m_labelSessionTime )
            {
                m_labelSessionTime = new QLabel(m_centralWidget);
                m_labelSessionTime->setObjectName(QString().sprintf("m_labelSessionTime%p", m_labelTime));
                m_labelSessionTime->setAlignment(Qt::AlignTop|Qt::AlignRight);
                m_labelSessionTime->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
                m_labelSessionTime->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(m_labelSessionTime->objectName()));
            }
            m_labelSessionTime->setGeometry(232, y, 95, 25);
            m_labelSessionTime->setText(QString().sprintf("%d' %d\"", m_sessionChronometer.minute(), m_sessionChronometer.second()));
        }

    }

}

void EjercicioView::showEvent(QShowEvent *)
{
    qDebug("EjercicioView::showEvent");

    MainWindow::instanceA()->headerViewAt(0)->backButton().setHidden(true);
    MainWindow::instanceA()->headerViewAt(0)->homeButton().setHidden(false);

    m_voxStep = 0;
    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Ejercicios/%1.mp3").arg(m_routineExercise->actualExercise().id()));

    const Exercise &exercise = m_routineExercise->actualExercise();
    if( exercise.showsReps() || (exercise.showsSteps() || (exercise.showsTime() && m_routineExercise->time() == 0 && m_routineExercise->special() > 0)) )
    {
        m_pauseButton->hide();
        m_startButton->hide();
        //m_finishedButton->show();
        m_willShowFinishedButton = true;
        startPressed();

        m_finishedButtonTimer = new QTimer();
        m_finishedButtonTimer->setInterval(5000);
        m_finishedButtonTimer->setSingleShot(true);
        connect(m_finishedButtonTimer, SIGNAL(timeout()), this, SLOT(timerShowFinishedButton()));
        m_finishedButtonTimer->start();
    }
    else
    {
        m_willShowFinishedButton = false;
        m_pauseButton->hide();
        m_finishedButton->hide();
    }

}

void EjercicioView::reachedEndOfMedia()
{
    const Exercise &exercise = m_routineExercise->actualExercise();

    if( m_voxStep == 0 )
    {
        m_voxStep++;
        if( m_routineComposition && m_pasadaNumber == 1 && m_subExerciseNumber == 0 )
        {
            int c = m_routineComposition->count();
            SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Pas/%1.mp3").arg(c));
            return;
        }

    }

    if( m_voxStep == 1 )
    {
        m_voxStep++;

        if( exercise.showsTime() )
        {
            // Steps
            if( m_routineExercise->time() == 0 && m_routineExercise->special() > 0 )
            {
                int s = m_routineExercise->special();
                SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Steps/%1.mp3").arg(s));
            }
            else
            {
                int t = m_routineExercise->time();
                SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Min/%1.mp3").arg(t));
            }
        }
        else if( exercise.showsReps() )
        {
            if( m_routineExercise->series() > 1 )
            {
                int s = m_routineExercise->series();
                int r = m_routineExercise->time();
                if( r == 10 )
                    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Vez/%1x%2.mp3").arg(s).arg(r));
                else
                    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Series/%1x%2.mp3").arg(s).arg(r));
            }
            else
            {
                int r = m_routineExercise->time();
                SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Reps/%1.mp3").arg(r));
            }
        }
    }

}

void EjercicioView::hideEvent(QShowEvent *)
{
    qDebug("void EjercicioView::hideEvent(QShowEvent *)");
}

void EjercicioView::destroyTimer()
{
    if( m_counterTimer )
    {
        m_counterTimer->stop();
        delete m_counterTimer;
        m_counterTimer = NULL;

    }

}

void EjercicioView::destroySessionTimer()
{
    if( m_sessionTimer )
    {
        m_sessionTimer->stop();
        delete m_sessionTimer;
        m_sessionTimer = NULL;

    }

}

void EjercicioView::timerShowFinishedButton()
{
    m_finishedButton->show();
}

void EjercicioView::gpsTimerCheck()
{
    if( m_routineExercise->actualExercise().requiresGPS() &&
        (GeoDistanceCalc::instance().acquired() || !GeoDistanceCalc::instance().gpsAvailable()) )
    {
        destroyTimer();
        m_labelGPS->hide();
        m_startButton->show();

    }

}

void EjercicioView::timerUpdated()
{
    // Ejercicio
    const QTime &time = QTime::currentTime();
    int msecs = m_startSnapshotTime.msecsTo(time);
    m_startSnapshotTime = time;

    // Rutina
    if( m_countSessionTime )
    {
        //int msecsRutina = m_sessionSnapshotTime.msecsTo(time);
        m_sessionSnapshotTime = time;
        m_sessionChronometer = m_sessionChronometer.addMSecs(msecs);

        //synchronized(mutex)
        //{
            m_labelSessionTime->setText(QString().sprintf("%d' %d\"", m_sessionChronometer.minute(), m_sessionChronometer.second()));
            m_labelSessionTime->repaint();
        //}
    }

    if( m_labelTime )
    {
        m_chronometer = m_chronometer.addMSecs(msecs);

        QString timeString = m_chronometer.toString("mm'' ss\" .zzz");
        timeString = timeString.left(timeString.count() - 1);
        m_labelTime->setText(QString().sprintf("%s / %d'", timeString.toAscii().constData(), m_routineExercise->time()));
        m_labelTime->repaint();
    }

    if( m_fireNextPhraseTime == 100 )
        m_fireNextPhraseTime = 300000; // 5 minutos
    else
        m_fireNextPhraseTime -= msecs;
    if( m_fireNextPhraseTime <= 0 )
    {
        int r = (rand() % 18) + 1;
        SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/RitmoBueno/%1.mp3").arg(r));
        m_fireNextPhraseTime = 300000; // 5 minutos

        qDebug("next in %d", m_fireNextPhraseTime);
    }

    if( m_labelDistance && m_routineExercise->actualExercise().requiresGPS() )
    {
        int distance = (int)GeoDistanceCalc::instance().distanceInMeters();
        QString strDist = QString().sprintf("%d MTS", distance);
        if( distance == 0 )
            strDist = QString("- MTS");

        m_labelDistance->setText(strDist);
        m_labelDistance->repaint();
    }

    if( m_labelTime && (m_chronometer.minute() >= m_routineExercise->time() && m_chronometer.second() >= 0) )
        nextExercise();

}

void EjercicioView::sessionTimerUpdated()
{
    if( m_countSessionTime )
    {
        const QTime &time = QTime::currentTime();
        int msecs = m_sessionSnapshotTime.msecsTo(time);
        m_sessionSnapshotTime = time;
        m_sessionChronometer = m_sessionChronometer.addMSecs(msecs);

        synchronized(mutex)
        {
            m_labelSessionTime->setText(QString().sprintf("%d' %d\"", m_sessionChronometer.minute(), m_sessionChronometer.second()));
            m_labelSessionTime->repaint();
        }

    }

}

void EjercicioView::startPressed()
{
    navigationController()->tabBar()->setUserInteractionEnabled(false);
    MainWindow::instanceA()->headerViewAt(0)->setUserInteractionEnabled(false);

    if( !m_willShowFinishedButton )
    {
        m_startButton->hide();
        m_pauseButton->show();
    }

    if( m_routineExercise->actualExercise().requiresGPS() )
    {
        if( !GeoDistanceCalc::instance().isPaused() )
            GeoDistanceCalc::instance().start();
        else
            GeoDistanceCalc::instance().resume();
    }

    m_startSnapshotTime = QTime::currentTime();
    m_sessionSnapshotTime = QTime::currentTime();

    destroyTimer();
    m_counterTimer = new QTimer();
    m_counterTimer->setInterval(10);
    m_counterTimer->setSingleShot(false);
    m_counterTimer->start();
    connect(m_counterTimer, SIGNAL(timeout()), this, SLOT(timerUpdated()));

    m_countSessionTime = true;

}

void EjercicioView::pausePressed()
{
    navigationController()->tabBar()->setUserInteractionEnabled(true);
    MainWindow::instanceA()->headerViewAt(0)->setUserInteractionEnabled(true);

    if( m_routineExercise->actualExercise().requiresGPS() )
        GeoDistanceCalc::instance().pause();

    m_startButton->show();
    m_pauseButton->hide();

    destroyTimer();

    m_countSessionTime = false;
}

void EjercicioView::nextExercise()
{
    // Save plan info data
    qDebug("RutinaAudioIntro::showEvent(): About to Save Routine Info...");
    int planId = GlobalDataObject::instance().userInfo().objectiveIndex();
    int routineId = GlobalDataObject::instance().userInfo().currentRoutineNumber(planId);
    int exerciseId = m_routineExercise->actualExercise().id();
    int exerciseSpeed = nearbyint(GeoDistanceCalc::instance().maxSpeed());
    int exerciseDistance = 0;
    int exerciseTime = 0;
    int exerciseCalories = 0;
    if( m_labelTime )
    {
        QTime zeroTime(0, 0, 0, 0);
        exerciseTime = zeroTime.secsTo(m_chronometer) / 60; // minutes
    }
    if( m_labelDistance && m_routineExercise->actualExercise().requiresGPS() )
    {
        exerciseDistance = (int)GeoDistanceCalc::instance().distanceInMeters(); // meters
    }
    // 75 is the magic number, for every 75mt you do in 1 minute you burn 6 calories
    // This equation compensates for exercise that burn less like walking and
    // for high burning exercise like short distance running.
    if( exerciseDistance > 0 )
        exerciseCalories = nearbyint((((float)exerciseDistance / 75.f) * (float)exerciseTime) / 10.f);
    else
        // For every minute we do, we burn 4 calories
        exerciseCalories = nearbyint((float)exerciseTime / 4.f);
    PlanInfo::ExerciseInfo &exerciseInfo = GlobalDataObject::instance().planInfo(planId).exerciseInfo(routineId, exerciseId);
    qDebug("<<<<<<< PREVIOUS >>>>>>>>>");
    //exerciseInfo._print();
    qDebug("<<<<<<<<<<<<>>>>>>>>>>>>>>");
    exerciseInfo.set(exerciseTime, exerciseDistance, exerciseCalories, exerciseSpeed);
    qDebug("<<<<<<<<< NEW >>>>>>>>>>>");
    //exerciseInfo._print();
    qDebug("<<<<<<<<<<<>>>>>>>>>>>>>>");

    GlobalDataObject::instance().saveApplicationSettings();
    qDebug("EjercicioView::nextExercise(): Routine and Exercise Info Saved!");

    navigationController()->tabBar()->setUserInteractionEnabled(true);
    MainWindow::instanceA()->headerViewAt(0)->setUserInteractionEnabled(true);

    // Reset us
    //if( m_routineExercise->actualExercise().requiresGPS() )
    GeoDistanceCalc::instance().reset();
    GeoDistanceCalc::instance().pause();
    m_countSessionTime = false;
    m_chronometer.setHMS(0, 0, 0, 0);
    m_sessionChronometer.setHMS(m_sessionChronometer.hour(), m_sessionChronometer.minute(), m_sessionChronometer.second(), 0);
    if( !m_willShowFinishedButton )
    {
        m_pauseButton->hide();
        m_startButton->show();
    }
    destroyTimer();

    // First, we check if we're inside a composite exercise
    if( m_routineComposition )
    {
        qDebug("EjercicioView: Inside composition.");
        // if we're, we need to keep iterating inside the composition.
        //
        // first, we check if we're at the end of it
        if( m_subExerciseNumber + 1 >= m_routineComposition->exerciseCount() )
        {
            qDebug("EjercicioView: \tLast exercise in composition.");
            // if we're at the end, we need to check how many pasadas are left
            if( m_pasadaNumber + 1 > m_routineComposition->count() )
            {
                qDebug("EjercicioView: \t\tLast pasada in composition. END.-");
                // if there're no pasadas left, the next EjercicioView
                // will be the next root exercise in the stack
                EjercicioView *ejercicioView = new EjercicioView(m_exerciseNumber + 1, false);
                ejercicioView->setSessionChronometer(m_sessionChronometer);
                ejercicioView->initUi();
                navigationController()->pushView(ejercicioView);
            }
            else
            {
                qDebug("EjercicioView: \t\tCalling first exercise of the next pasada.");
                // if there're pasdas left, we reset the current exercise and
                // go to the next pasada
                EjercicioView *ejercicioView = new EjercicioView(m_exerciseNumber, false);
                ejercicioView->setRoutineComposition(m_routineComposition);
                ejercicioView->setPasadaNumber(m_pasadaNumber + 1); // next pasada
                ejercicioView->setSubExerciseNumber(0); // first exercise of the next pasada
                ejercicioView->setSessionChronometer(m_sessionChronometer);
                ejercicioView->initUi();
                navigationController()->pushView(ejercicioView);
            }
        }
        else
        {
            qDebug("EjercicioView: \tNext exercise in this pasada.");
            // if we're not at the end, we just go to the next exercise within this pasada
            EjercicioView *ejercicioView = new EjercicioView(m_exerciseNumber, false);
            ejercicioView->setRoutineComposition(m_routineComposition);
            ejercicioView->setPasadaNumber(m_pasadaNumber);
            ejercicioView->setSubExerciseNumber(m_subExerciseNumber + 1); // next exercise within this pasada
            ejercicioView->setSessionChronometer(m_sessionChronometer);
            ejercicioView->initUi();
            navigationController()->pushView(ejercicioView);
        }
    }
    else
    {
        const Routine &currentRoutine = GlobalDataObject::instance().userInfo().currentRoutine();

        // // if we're not inside a composite exercise, we check if this is the last exercise
        if( m_exerciseNumber + 1 >= currentRoutine.exerciseCountWithoutComposition() )
        {
            qDebug("EjercicioView: This was the final exercise. END.-");
            // we quit
            RutinaAudioFinView *rutinaAudioFinView = new RutinaAudioFinView();
            QTime *sessionTime = new QTime(m_sessionChronometer.hour(), m_sessionChronometer.minute(), m_sessionChronometer.second());
            rutinaAudioFinView->sessionTime = sessionTime;
            navigationController()->pushView(rutinaAudioFinView);
        }
        else
        {
            qDebug("EjercicioView: Normal exercise.");
            // if we're not inside a composite exercise, we check the next exercise in the stack
            const RoutineElement &routineElement = currentRoutine.exerciseAt(m_exerciseNumber + 1);

            // we check if the next exercise is a composite one
            if( routineElement.type().compare("RoutineExerciseComposition", Qt::CaseInsensitive) == 0 )
            {
                qDebug("EjercicioView: \tFound composite exercise.");
                // if it is, we call the first exercise and the first pasada inside the composition
                const RoutineExerciseComposition *routineExerciseComposition = dynamic_cast<const RoutineExerciseComposition *>(&routineElement);
                EjercicioView *ejercicioView = new EjercicioView(m_exerciseNumber + 1, false);
                ejercicioView->setRoutineComposition(routineExerciseComposition);
                ejercicioView->setPasadaNumber(1);
                ejercicioView->setSubExerciseNumber(0);
                ejercicioView->setSessionChronometer(m_sessionChronometer);
                ejercicioView->initUi();
                navigationController()->pushView(ejercicioView);
            }
            else
            {
                qDebug("EjercicioView: \tNext element is a normal exercise.");
                // if it isn't, we simply display the next exercise
                EjercicioView *ejercicioView = new EjercicioView(m_exerciseNumber + 1, false);
                ejercicioView->setSessionChronometer(m_sessionChronometer);
                ejercicioView->initUi();
                navigationController()->pushView(ejercicioView);

            }

        }

    }

}

void EjercicioView::figurePressed()
{
    if( m_pauseButton->isHidden() || !m_finishedButton->isHidden() )
    {
        MainWindow::instanceA()->headerViewAt(0)->backButton().setHidden(false);
        MainWindow::instanceA()->headerViewAt(0)->homeButton().setHidden(true);
        Exercise *exercise = const_cast<Exercise *>(&m_routineExercise->actualExercise());
        navigationController()->pushView(new TrainerDetailedView(exercise, NULL));
    }

}
