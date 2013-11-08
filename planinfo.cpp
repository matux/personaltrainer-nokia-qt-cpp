#include "planinfo.h"

#include <QSettings>

PlanInfo::PlanInfo(QObject *parent)
    :QObject(parent)
{
    m_planId = 0;
}

void PlanInfo::loadFromSettings(QSettings &settings)
{
    qDebug("PlanInfo::loadToSettings...");

    QString group(QString().sprintf("planInfo_%d", planId()));
    settings.beginGroup(group);
    int routineCount = settings.value("routineCount", 0).toInt();

//    qDebug("\tGROUP: %s", group.toAscii().constData());
//    qDebug("\t\troutineCount: %d", routineCount);

    for( int i = 0; i < routineCount; ++i )
    {
        QString planGroup(QString().sprintf("routineInfo_%d", i));
        settings.beginGroup(planGroup);
        int exerciseCount = settings.value("exerciseCount", 0).toInt();
        RoutineInfo *routineInfo = new RoutineInfo();
        routineInfo->id = settings.value("id", 0).toInt();
        routineInfo->date = settings.value("date", QDate()).toDate();
        routineInfo->time = settings.value("time", "").toString();
        m_routineInfo.append(routineInfo);
        /*
        qDebug("\t\tGROUP: %s", planGroup.toAscii().constData());
        qDebug("\t\t\texerciseCount:\t%d", exerciseCount);
        qDebug("\t\t\tid:\t%d", routineInfo->id);
        qDebug("\t\t\tdate:\t%s", routineInfo->date.toAscii().constData());
        qDebug("\t\t\ttime:\t%s", routineInfo->time.toAscii().constData());

        qDebug("\t\t\tARRAY: %s", "exerciseInfo");
        */
        settings.beginReadArray("exerciseInfo");
        for( int j = 0; j < exerciseCount; ++j )
        {
            settings.setArrayIndex(j);
            PlanInfo::ExerciseInfo *exerciseInfo = new PlanInfo::ExerciseInfo();
            exerciseInfo->id = settings.value("id", 0).toInt();
            exerciseInfo->time = settings.value("time", 0).toInt();
            exerciseInfo->distance = settings.value("distance", 0).toInt();
            exerciseInfo->calories = settings.value("calories", 0).toInt();
            exerciseInfo->speed = settings.value("speed", 0).toInt();
            routineInfo->exerciseInfo.append(exerciseInfo);
            /*
            qDebug("\t\t\t\tid: %d", exerciseInfo->id);
            qDebug("\t\t\t\ttime: %d", exerciseInfo->time);
            qDebug("\t\t\t\tdistance: %d", exerciseInfo->distance);
            qDebug("\t\t\t\tcalories: %d", exerciseInfo->calories);
            */
        }
        settings.endArray();

        settings.endGroup();
    }

    settings.endGroup();

}

void PlanInfo::saveToSettings(QSettings &settings) const
{
    qDebug("PlanInfo::saveToSettings...");

    QString group(QString().sprintf("planInfo_%d", planId()));
    settings.beginGroup(group);
    settings.setValue("routineCount", m_routineInfo.count());

    //qDebug("\tGROUP: %s", group.toAscii().constData());
    //qDebug("\t\troutineCount: %d", m_routineInfo.count());

    for( int i = 0; i < m_routineInfo.count(); ++i )
    {
        QString planGroup(QString().sprintf("routineInfo_%d", i));
        settings.beginGroup(planGroup);
        RoutineInfo &routineInfo = *m_routineInfo.at(i);
        settings.setValue("exerciseCount", routineInfo.exerciseInfo.count());
        settings.setValue("id", routineInfo.id);
        settings.setValue("date", routineInfo.date);
        settings.setValue("time", routineInfo.time);
        /*
        qDebug("\t\tGROUP: %s", planGroup.toAscii().constData());
        qDebug("\t\t\texerciseCount:\t%d", routineInfo.exerciseInfo.count());
        qDebug("\t\t\tid:\t%d", routineInfo.id);
        qDebug("\t\t\tdate:\t%s", routineInfo.date.toAscii().constData());
        qDebug("\t\t\ttime:\t%s", routineInfo.time.toAscii().constData());

        qDebug("\t\t\tARRAY: %s", "exerciseInfo");
        */
        settings.beginWriteArray("exerciseInfo");
        for( int j = 0; j < routineInfo.exerciseInfo.count(); ++j )
        {
            settings.setArrayIndex(j);
            ExerciseInfo &exerciseInfo = *routineInfo.exerciseInfo.at(j);
            settings.setValue("id", exerciseInfo.id);
            settings.setValue("time", exerciseInfo.time);
            settings.setValue("distance", exerciseInfo.distance);
            settings.setValue("speed", exerciseInfo.speed);
            settings.setValue("calories", exerciseInfo.calories);
            /*
            qDebug("\t\t\t\tid: %d", exerciseInfo.id);
            qDebug("\t\t\t\ttime: %d", exerciseInfo.time);
            qDebug("\t\t\t\tdistance: %d", exerciseInfo.distance);
            qDebug("\t\t\t\tcalories: %d", exerciseInfo.calories);
            */
        }
        settings.endArray();

        settings.endGroup();
    }

    settings.endGroup();

}

void PlanInfo::reset()
{
    m_routineInfo.clear();
}

PlanInfo::RoutineInfo &PlanInfo::routineInfo(int withId)
{
    qDebug("PlanInfo::routineInfo: Retrieve routine info with Id %d", withId);
    for( int i = 0; i < m_routineInfo.count(); ++i )
    {
        RoutineInfo &routineInfo = *m_routineInfo.at(i);
        if( routineInfo.id == withId )
        {
            qDebug("\tPlanInfo::routineInfo: Routine Found!");
            return routineInfo;
        }
    }

    qDebug("\tPlanInfo::routineInfo: Routine Not found, creating new one!");
    RoutineInfo *routineInfo = new RoutineInfo();
    routineInfo->id = withId;
    m_routineInfo.append(routineInfo);

    return *routineInfo;

}

PlanInfo::ExerciseInfo &PlanInfo::exerciseInfo(int fromRoutineId, int withId)
{
    qDebug("PlanInfo::exerciseInfo: Retrieve exercise info from Routine Id %d with exercise Id %d", fromRoutineId, withId);
    PlanInfo::RoutineInfo &_routineInfo = routineInfo(fromRoutineId);

    for( int i = 0; i < _routineInfo.exerciseInfo.count(); ++i )
    {
        ExerciseInfo &exerciseInfo = *_routineInfo.exerciseInfo.at(i);
        if( exerciseInfo.id == withId )
        {
            qDebug("\tPlanInfo::exerciseInfo: Exercise Found!");
            return exerciseInfo;
        }
    }

    qDebug("\tPlanInfo::exerciseInfo: Exercise Not found, creating a new one!");
    ExerciseInfo *exerciseInfo = new ExerciseInfo();
    exerciseInfo->id = withId;
    _routineInfo.exerciseInfo.append(exerciseInfo);

    return *exerciseInfo;
}
