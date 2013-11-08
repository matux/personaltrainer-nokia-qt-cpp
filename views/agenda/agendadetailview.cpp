#include "agendadetailview.h"
#include "model/globaldataobject.h"
#include "model/planinfo.h"
#include "model/userinfo.h"

AgendaDetailView::AgendaDetailView(const QDate &date, QWidget *parent)
    :SIView(parent),
    m_date(date)
{
    setObjectName(QString().sprintf("AgendaView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    QWidget *infoBaseWidget = new QWidget(centralWidget);
    infoBaseWidget->setObjectName(QString().sprintf("infoTest%p", infoBaseWidget));
    infoBaseWidget->setGeometry(0, 35, 360, 319);
    infoBaseWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/agenda_detalle_base.png); }").arg(infoBaseWidget->objectName()));
    infoBaseWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *labelDate = new QLabel(centralWidget);
    labelDate->setObjectName(QString().sprintf("labelDate%p", labelDate));
    labelDate->setGeometry(0, 49, 360, 52);
    labelDate->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    labelDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelDate->setText(QString().sprintf("%d %s", date.day(), QDate::longMonthName(date.month()).toUpper().toAscii().constData()));
    labelDate->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(250, 250, 250); font: 75 21px \"AvantGardeMdITCTT\"; }").arg(labelDate->objectName()));

    QLabel *labelEnt = new QLabel(centralWidget);
    labelEnt->setObjectName(QString().sprintf("labelEnt%p", labelDate));
    labelEnt->setGeometry(65, 150, 360, 52);
    labelEnt->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    labelEnt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelEnt->setText("ENTRENAMIENTO");
    labelEnt->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(250, 250, 250); font: 75 21px \"AvantGardeMdITCTT\"; }").arg(labelEnt->objectName()));

    // Search for a routine
    PlanInfo::RoutineInfo *routineInfoFinal = NULL;
    bool thereIsNoDate = true;
    if( GlobalDataObject::instance().datesExercisedList().count() > 0 )
    {
        QDate &lastDateExercised = *GlobalDataObject::instance().datesExercisedList().last();
        if( lastDateExercised.operator ==(date) )
        {
            for( int p = 0; p < PLAN_COUNT; ++p )
            {
                QList<PlanInfo::RoutineInfo *> &routineInfoList = GlobalDataObject::instance().planInfo(p).routineInfoList();
                for( int i = 0; i < routineInfoList.count() /*&& !routineInfoFinal*/; ++i )
                {
                    PlanInfo::RoutineInfo &routineInfo = *routineInfoList.at(i);
                    if( routineInfo.date == date )
                    {
                        routineInfoFinal = &routineInfo;
                        thereIsNoDate = false;
                    }
                }
            }

        }
    }

    QLabel *labelWarn = new QLabel(centralWidget);
    labelWarn->setObjectName(QString().sprintf("labelWarn%p", labelDate));
    labelWarn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelWarn->setWordWrap(true);
    labelWarn->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 17px \"AvantGardeMdITCTT\"; }").arg(labelWarn->objectName()));

    if( thereIsNoDate )
    {
        labelWarn->setGeometry(10, 195, 340, 152);
        labelWarn->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        labelWarn->setText("Si querés más información de tus estadísticas, sincroniza tus resultados e ingresá a www.fordpersonaltrainer.com.ar");
    }
    else
    {
        int distance = 0, speed = 0;
        for( int i = 0; i < routineInfoFinal->exerciseInfo.count(); ++i )
        {
            PlanInfo::ExerciseInfo &exerciseInfo = *routineInfoFinal->exerciseInfo.at(i);
            distance += exerciseInfo.distance;
            if( exerciseInfo.speed > speed )
                speed = exerciseInfo.speed;
        }

        labelWarn->setGeometry(30, 195, 300, 152);
        labelWarn->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        labelWarn->setText(QString().sprintf("DISTANCIA RECORRIDA\t            %.2fkm\n\nVELOCIDAD\t            %dkm/h", ((float)distance / 1000.f), speed));
    }

}
