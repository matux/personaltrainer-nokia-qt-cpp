#include "rutinaaudiointro.h"
#include "model/routines/routine.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "ejercicioview.h"
#include "mainwindow.h"
#include "views/headerview.h"
#include "model/planinfo.h"

RutinaAudioIntro::RutinaAudioIntro(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("RutinaAudioIntro%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(QApplication::desktop()->height());

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/rutina_audio_intro_2.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(QApplication::desktop()->height());

    QPushButton *startButton = new QPushButton(centralWidget);
    startButton->setObjectName(QString::fromUtf8("startButton"));
    startButton->setGeometry(QRect(145, 550, 94, 69));
    startButton->setText("");
    startButton->setFlat(true);
    startButton->setStyleSheet(QString("QPushButton#startButton { background-color: rgba(255,0,0,0); color: rgba(255,0,0,0); }"));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startRoutine()));

}

RutinaAudioIntro::~RutinaAudioIntro()
{

}

void RutinaAudioIntro::showEvent(QShowEvent *)
{
    qDebug("RutinaAudioIntro::showEvent");

    tabBar()->hideBar();
    navigationController()->hideBar();

    m_voxStep = 0;
    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));

    qDebug("RutinaAudioIntro::showEvent");
    int planNumber = GlobalDataObject::instance().userInfo().objectiveIndex();
    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Planes/plan%1.mp3").arg(planNumber));

    // Save Plan Info data
    qDebug("RutinaAudioIntro::showEvent(): About to Save Routine Info...");
    int planId = GlobalDataObject::instance().userInfo().objectiveIndex();
    int routineId = GlobalDataObject::instance().userInfo().currentRoutineNumber(planId);
    QDateTime dateTime = QDateTime().currentDateTime();
    //QString date = dateTime.date().toString("yyyy-MM-dd");
    QString time = dateTime.time().toString("HH:mm");
    PlanInfo::RoutineInfo &routineInfo = GlobalDataObject::instance().planInfo(planId).routineInfo(routineId);
    routineInfo.set(dateTime.date(), time, false);
    //routineInfo._print();
    // Save date of exercise
    //GlobalDataObject::instance().datesExercisedList().append(new QDate(dateTime.date()));
    GlobalDataObject::instance().saveApplicationSettings();
    qDebug("RutinaAudioIntro::showEvent(): Routine Info Saved!");


}

void RutinaAudioIntro::hideEvent(QHideEvent *hideEvent)
{
    qDebug("RutinaAudioIntro::hideEvent");

    tabBar()->showBar();
    navigationController()->showBar();

    disconnect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));

}

void RutinaAudioIntro::reachedEndOfMedia()
{
    switch( m_voxStep )
    {
    case 0:
        {
            const Routine &currentRoutine = GlobalDataObject::instance().userInfo().currentRoutine();
            if( currentRoutine.id() == 1 )
            {
                m_voxStep++;

                // Set up
                QString genre = GlobalDataObject::instance().userInfo().gender() == UserInfo::G_MALE ? "m" : "f";
                int plan = GlobalDataObject::instance().userInfo().objectiveIndex();
                int r = rand() % 2;
                if( plan == 0 && (genre.compare("f") == 0) )
                    r = rand() % 3;

                // play
                SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Planes/plan%1-%2%3.mp3").arg(plan).arg(genre).arg(r));

            }
            else
            {
                m_voxStep++;
                reachedEndOfMedia();
            }
        }
        break;
    case 1:
        {
            m_voxStep++;

            const Routine &currentRoutine = GlobalDataObject::instance().userInfo().currentRoutine();
            SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/rutina%1.mp3").arg(currentRoutine.id()));
        }
        break;
    case 2:
        startRoutine();
        break;
    }

}

void RutinaAudioIntro::startRoutine()
{
    MainWindow::instanceA()->headerViewAt(0)->backButton().setHidden(true);
    navigationController()->pushView(new EjercicioView(0));
}
