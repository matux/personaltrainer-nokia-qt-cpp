#include "rutinaview.h"
#include "constants.h"
#include "rutinaaudiointro.h"
#include "model/routines/routine.h"
#include "model/routines/routinemanager.h"
#include "model/routines/routineexercise.h"
#include "model/routines/routineexercisecomposition.h"
#include "model/exercises/exercisemanager.h"
#include "model/exercises/exercise.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "views/trainer/trainerdetailedview.h"
#include "views/listwidgetitemwithroutine.h"

#include <QPainter>

RutinaView::RutinaView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("RutinaView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); image: url(:/images/res/rutina_fondo.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    m_startButton = new SIButton(centralWidget);
    m_startButton->setObjectName(QString::fromUtf8("startButton"));
    m_startButton->setGeometry(QRect(245, 77, 94, 39));
    m_startButton->setText(QString::fromUtf8("START"));
    m_startButton->setNormalStatePix(":/images/res/rutina_boton_start.png");
    m_startButton->setPressedStatePix(":/images/res/rutina_boton_start_on.png");
    connect(m_startButton, SIGNAL(clicked()), this, SLOT(startPressed()));

    m_labelPlan = new QLabel(centralWidget);
    m_labelPlan->setObjectName(QString().sprintf("m_labelPlan%p", m_labelPlan));
    m_labelPlan->setGeometry(35, 17, 320, 20);
    m_labelPlan->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_labelPlan->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelPlan->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(139, 139, 139); font: 75 18px \"AvantGardeMdITCTT\"; }").arg(m_labelPlan->objectName()));

    m_labelLevel = new QLabel(centralWidget);
    m_labelLevel->setObjectName(QString().sprintf("m_labelLevel%p", m_labelLevel));
    m_labelLevel->setGeometry(35, 40, 320, 20);
    m_labelLevel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_labelLevel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelLevel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(139, 139, 139); font: 75 18px \"AvantGardeMdITCTT\"; }").arg(m_labelLevel->objectName()));

    m_labelRutina = new QLabel(centralWidget);
    m_labelRutina->setObjectName(QString().sprintf("m_labelRutina%p", m_labelRutina));
    m_labelRutina->setGeometry(35, 86, 200, 24);
    m_labelRutina->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_labelRutina->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_labelRutina->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 25px \"AvantGardeMdITCTT\"; }").arg(m_labelRutina->objectName()));

    m_listWidget = new QListWidget(centralWidget);
    m_listWidget->setObjectName("m_listWidget");
    m_listWidget->setGeometry(QRect(45, 145, 280, 266));
    m_listWidget->setFrameShape(QFrame::NoFrame);
    m_listWidget->setFrameShadow(QFrame::Plain);
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listWidget->setProperty("showDropIndicator", QVariant(false));
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWidget->setStyleSheet(QString("QListWidget#m_listWidget { color: rgb(222, 222, 222); font: 75 17px \"AvantGardeMdITCTT\"; }"));
    m_listWidget->setSpacing(3);
    connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(exerciseSelected(QListWidgetItem*)));

}

RutinaView::~RutinaView()
{

}

void RutinaView::startPressed()
{
    navigationController()->pushView(new RutinaAudioIntro());

}

void RutinaView::showEvent(QShowEvent *)
{
    qDebug("RutinaView::showEvent");
    navigationController()->removeViewsInCascadeFrom(1);

    const Routine &currentRoutine = GlobalDataObject::instance().userInfo().currentRoutine();
    int rrr = rand() % 3;
    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Rutinas/rutinaintro%1.mp3").arg(rrr++));

    m_labelPlan->setText(GlobalDataObject::instance().userInfo().planName().toUpper());
    m_labelLevel->setText(QString("NIVEL %1").arg(GlobalDataObject::instance().userInfo().levelStr().toUpper()));
    m_labelRutina->setText(QString("RUTINA %1").arg(currentRoutine.id()));

    m_listWidget->clear();
    for( int i = 0; i < currentRoutine.exerciseCountWithoutComposition(); ++i )
    {
        const RoutineElement &element = currentRoutine.exerciseAt(i);
        ListWidgetItemWithRoutine *newItem = new ListWidgetItemWithRoutine(m_listWidget);
        newItem->setText(element.name().toUpper());
        newItem->setRoutineElement(element);
        m_listWidget->addItem(newItem);

        if( element.type().compare("RoutineExerciseComposition", Qt::CaseInsensitive) == 0 )
        {
            const RoutineExerciseComposition &composition = dynamic_cast<const RoutineExerciseComposition &>(element);
            for( int j = 0; j < composition.exerciseCount(); ++j )
            {
                const RoutineElement &subElement = composition.exerciseAt(j);
                ListWidgetItemWithRoutine *newSubItem = new ListWidgetItemWithRoutine(m_listWidget);
                newSubItem->setText(QString("     %1").arg(subElement.name().toUpper()));
                newSubItem->setRoutineElement(subElement);
                m_listWidget->addItem(newSubItem);

            }

        }

    }

}

void RutinaView::hideEvent(QHideEvent *hideEvent)
{

}

void RutinaView::exerciseSelected(QListWidgetItem *pItem)
{
    navigationController()->removeViewAt(1);

    ListWidgetItemWithRoutine *item = dynamic_cast<ListWidgetItemWithRoutine *>(pItem);

    if( item->routineElement().type().compare("RoutineExercise", Qt::CaseInsensitive) == 0 )
    {
        const RoutineExercise &routineExercise = dynamic_cast<const RoutineExercise &>(item->routineElement());
        Exercise *exercise = const_cast<Exercise *>(&routineExercise.actualExercise());
        navigationController()->pushView(new TrainerDetailedView(exercise, NULL));
    }

}
