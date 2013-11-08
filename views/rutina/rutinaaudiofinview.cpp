#include "rutinaaudiofinview.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "mainwindow.h"
#include "views/agenda/customcalendarwidget.h"
#include "views/headerview.h"
#include "model/routines/routinemanager.h"
#include "model/routines/plan.h"
#include "model/routines/planlevel.h"
#include "model/location/geodistancecalc.h"
#include "model/planinfo.h"

RutinaAudioFinView::RutinaAudioFinView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("RutinaAudioFinView%p", parent));

    sessionTime = NULL;

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(QApplication::desktop()->height());

    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(QApplication::desktop()->height());

    m_showLevelEnd = false;
    m_showPlanEnd = false;

    // Mark this routine as done
    int planId = GlobalDataObject::instance().userInfo().objectiveIndex();
    int routineId = GlobalDataObject::instance().userInfo().currentRoutineNumber(planId);
    PlanInfo::RoutineInfo &routineInfo = GlobalDataObject::instance().planInfo(planId).routineInfo(routineId);
    routineInfo.routineDone = true;
    GlobalDataObject::instance().saveApplicationSettings();
    qDebug("RutinaAudioIntro::showEvent(): Routine Info Saved (routineDone UPDATED)!");

    // Go to the next routine
    int plan = GlobalDataObject::instance().userInfo().objectiveIndex();
    int level = GlobalDataObject::instance().userInfo().level(plan);
    int routineCount = RoutineManager::instance().plans().at(plan)->levelAt(level).routineCount();
    int currentRoutine = GlobalDataObject::instance().userInfo().currentRoutineNumber(plan);

    currentRoutine++;
    if( currentRoutine >= routineCount )
    {
        level++;
        if( level >= 3 )
        {
            currentRoutine = 0;
            level = 0;
            centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/rutina_plan_cierre.png); }").arg(centralWidget->objectName()));
            m_showPlanEnd = true;
        }
        else
        {
            currentRoutine = 0;
            centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/rutina_nivel_cierre.png); }").arg(centralWidget->objectName()));
            m_showLevelEnd = true;
        }
    }
    else
        centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/rutina_audio_cierre_2.png); }").arg(centralWidget->objectName()));

    GlobalDataObject::instance().userInfo().setLevel(plan, (UserInfo::Level)level);
    GlobalDataObject::instance().userInfo().setCurrentRoutineNumber(plan, currentRoutine);

    if( m_showPlanEnd || m_showLevelEnd )
    {
        SIButton *nextButton = new SIButton(centralWidget);
        nextButton->setObjectName(QString().sprintf("nextButton%p", nextButton));
        nextButton->setGeometry(116, 593, 128, 43);
        nextButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        nextButton->setNormalStatePix(":/images/res/rutina_boton_siguiente.png");
        nextButton->setPressedStatePix(":/images/res/rutina_boton_siguiente_on.png");
        nextButton->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 50 10px \"AvantGardeMdITCTT\"; }").arg(nextButton->objectName()));
        connect(nextButton, SIGNAL(clicked()), this, SLOT(endRoutine()));
    }

}

RutinaAudioFinView::~RutinaAudioFinView()
{

}

void RutinaAudioFinView::showEvent(QShowEvent *showEvent)
{
    qDebug("RutinaAudioFinView::showEvent");

    GeoDistanceCalc::instance().stop();

    if( m_showLevelEnd || m_showPlanEnd )
    {
        int r = 11 + (rand() % 3);
        SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Bien/%1.mp3").arg(r));
    }
    else
    {
        //int g = rand() % 2;
        int g = 0;
        if( sessionTime->hour() > 1 ) g = 1; // Si tardó 2 horas o más, mal
        else if( sessionTime->hour() == 1 && sessionTime->minute() > 12 ) g = 1; // Si tarda más de 1 hora, 12 minutos (20% de 1 hora), mal

        if( g == 0 )
        {
            int r = (rand() % 13) + 1;
            SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Bien/%1.mp3").arg(r));
        }
        else
        {
            int r = (rand() % 8) + 1;
            SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/Mal/h%1.mp3").arg(r));
        }
    }

    tabBar()->hideBar();
    navigationController()->hideBar();

    if( !(m_showLevelEnd || m_showPlanEnd) )
    {
        QTimer *m_counterTimer = new QTimer();
        m_counterTimer->setInterval(4000);
        m_counterTimer->setSingleShot(true);
        m_counterTimer->start();
        connect(m_counterTimer, SIGNAL(timeout()), this, SLOT(endRoutine()));
    }

    QDateTime dateTime = QDateTime().currentDateTime();
    // Save date of exercise
    GlobalDataObject::instance().datesExercisedList().append(new QDate(dateTime.date()));
    GlobalDataObject::instance().saveApplicationSettings();

}

void RutinaAudioFinView::hideEvent(QHideEvent *hideEvent)
{
    qDebug("RutinaAudioFinView::hideEvent");
    tabBar()->showBar();
    navigationController()->showBar();

}

void RutinaAudioFinView::endRoutine()
{
    GlobalDataObject::instance().saveApplicationSettings();
    GlobalDataObject::instance().setTodayIsTheDay(true);

    MainWindow::instanceA()->headerViewAt(0)->backButton().setHidden(false);
    MainWindow::instanceA()->homeButtonPressed();
    navigationController()->showViewAtIndex(0);

}
