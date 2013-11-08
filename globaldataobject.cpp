#include "globaldataobject.h"
#include "userinfo.h"
#include "planinfo.h"

#include <QtCore>
#include <QSettings>
#include <QDate>

GlobalDataObject &GlobalDataObject::instance()
{
    static GlobalDataObject theInstance;
    return theInstance;
}

GlobalDataObject::~GlobalDataObject()
{
    qDebug("Destroying GlobalDataObject");

    if( m_userInfo )
        delete m_userInfo;
    for( int i = 0; i < PLAN_COUNT; ++i )
        if( m_planInfo[i] )
            delete m_planInfo[i];

}

void GlobalDataObject::loadDefaults()
{
    m_firstTime = true;
    m_userRegistered = false;
    m_datesExercised.clear();
    resetPlanInfo();
}

void GlobalDataObject::loadApplicationSettings()
{
    qDebug("Loading Application Settings...");

    if( !m_userInfo )
        m_userInfo = new UserInfo();
    for( int i = 0; i < PLAN_COUNT; ++i )
        if( !m_planInfo[i] )
        {
            m_planInfo[i] = new PlanInfo();
            m_planInfo[i]->setPlanId(i);
        }


    if( m_forceReset )
    {
        qDebug(" *** RESETTING Application Settings!");
        loadDefaults();
        saveApplicationSettings();
    }
    else
    {
        QSettings settings;
        settings.setPath(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::applicationDirPath());

        settings.beginGroup("general");
        m_firstTime = settings.value("firstTime", true).toBool();
        m_todayIsTheDay = settings.value("todayIsTheDay", false).toBool();
        m_userRegistered = settings.value("userRegistered", false).toBool();
        settings.endGroup();

        if( m_firstTime )
            qDebug("Application is being executed for the first time...");

        settings.beginGroup("user");
        userInfo().loadFromSettings(settings);
        settings.endGroup();

        // Plan Info
        for( int i = 0; i < PLAN_COUNT; ++i )
        {
            settings.beginGroup(QString().sprintf("plan_%d", i));
            m_planInfo[i]->loadFromSettings(settings);
            settings.endGroup();
        }

        userInfo()._print();

        // Exercise dates for the Calendar
        settings.beginGroup("datesExercised");
        int datesCount = settings.value("datesCount", 0).toInt();
        settings.beginReadArray("datesExercisedArray");
        for( int i = 0; i < datesCount; ++i )
        {
            settings.setArrayIndex(i);
            QDate *exerciseDate = new QDate(settings.value("exerciseDate", QDate()).toDate());
            m_datesExercised.append(exerciseDate);
        }
        settings.endArray();
        settings.endGroup();

    }

    qDebug("Done Loading Application Settings...\n");

}

void GlobalDataObject::saveApplicationSettings()
{
    qDebug("Saving Application Settings...");

    if( !m_userInfo )
        m_userInfo = new UserInfo();
    for( int i = 0; i < PLAN_COUNT; ++i )
        if( !m_planInfo[i] )
        {
            m_planInfo[i] = new PlanInfo();
            m_planInfo[i]->setPlanId(i);
        }

    QSettings settings;
    settings.setPath(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::applicationDirPath());

    settings.beginGroup("general");
    settings.setValue("firstTime", m_firstTime);
    settings.setValue("todayIsTheDay", m_todayIsTheDay);
    settings.setValue("userRegistered", m_userRegistered);
    settings.endGroup();

    settings.beginGroup("user");
    userInfo().saveToSettings(settings);
    settings.endGroup();

    // Plan Info
    for( int i = 0; i < PLAN_COUNT; ++i )
    {
        settings.beginGroup(QString().sprintf("plan_%d", i));
        //if( !m_planInfo[i]->isEmpty() )
            m_planInfo[i]->saveToSettings(settings);
        settings.endGroup();
    }

    settings.beginGroup("datesExercised");
    settings.setValue("datesCount", m_datesExercised.count());
    settings.beginReadArray("datesExercisedArray");
    for( int i = 0; i < m_datesExercised.count(); ++i )
    {
        settings.setArrayIndex(i);
        settings.setValue("exerciseDate", *m_datesExercised.at(i));
    }
    settings.endArray();
    settings.endGroup();

    settings.sync();

    qDebug("Done Saving Application Settings...\n");

}

void GlobalDataObject::resetPlanInfo()
{
    // Reset dates exercised
    m_datesExercised.clear();

    for( int i = 0; i < PLAN_COUNT; ++i )
        m_planInfo[i]->reset();

}

bool GlobalDataObject::planInfoIsEmpty()
{
    int a = 0;

    for( int i = 0; i < PLAN_COUNT; ++i )
        if( !m_planInfo[i]->isEmpty() ) ++a;

    return !(bool)a;

}
