#include "userinfo.h"
#include "routines/routinemanager.h"
#include "routines/plan.h"
#include "routines/planlevel.h"
#include "routines/routine.h"

#include <QSettings>

UserInfo::UserInfo(QObject *parent)
    :QObject(parent)
{
    resetRoutines();

    m_age = 0;
    m_gender = UserInfo::G_MALE;
    m_objectiveIndex = 0;
    m_metersCoveredInTest = 0;

    m_townMap.insert("CAPITAL FEDERAL", 0);
    m_townMap.insert("BUENOS AIRES", 1);
    m_townMap.insert("CATAMARCA", 2);
    m_townMap.insert("CORDOBA", 3);
    m_townMap.insert("CORRIENTES", 4);
    m_townMap.insert("ENTRE RIOS", 5);
    m_townMap.insert("JUJUY", 6);
    m_townMap.insert("MENDOZA", 7);
    m_townMap.insert("LA RIOJA", 8);
    m_townMap.insert("SALTA", 9);
    m_townMap.insert("SAN JUAN", 10);
    m_townMap.insert("SAN LUIS", 11);
    m_townMap.insert("SANTA FE", 12);
    m_townMap.insert("SANTIAGO DEL ESTERO", 13);
    m_townMap.insert("TUCUMAN", 14);
    m_townMap.insert("CHACO", 16);
    m_townMap.insert("CHUBUT", 17);
    m_townMap.insert("FORMOSA", 18);
    m_townMap.insert("MISIONES", 19);
    m_townMap.insert("NEUQUEN", 20);
    m_townMap.insert("LA PAMPA", 21);
    m_townMap.insert("RIO NEGRO", 22);
    m_townMap.insert("SANTA CRUZ", 23);
    m_townMap.insert("TIERRA DEL FUEGO", 24);

}

void UserInfo::resetRoutines()
{
    m_currentRoutineNumber[0] = 0;
    m_currentRoutineNumber[1] = 0;
    m_currentRoutineNumber[2] = 0;
    m_currentRoutineNumber[3] = 0;
    m_currentLevel[0] = UserInfo::L_BEGINNER;
    m_currentLevel[1] = UserInfo::L_BEGINNER;
    m_currentLevel[2] = UserInfo::L_BEGINNER;

}

void UserInfo::loadFromSettings(const QSettings &settings)
{
    setFullName(settings.value("fullName", "").toString());
    setEMail(settings.value("eMail", "").toString());
    setHomeTown(settings.value("homeTown", "").toString());
    setWeight(settings.value("weight", "").toString());
    setHeight(settings.value("height", "").toString());
    setPassword(settings.value("password", "").toString());
    setAge(settings.value("age", 0).toInt());
    setGender((Gender)settings.value("gender", 0).toInt());
    setObjectiveIndex(settings.value("objectiveIndex", 0).toInt());
    setMetersCoveredInTest(settings.value("metersCoveredInTest", 0).toInt());
    setCurrentRoutineNumber(0, settings.value("currentRoutineNumber0", 0).toInt());
    setCurrentRoutineNumber(1, settings.value("currentRoutineNumber1", 0).toInt());
    setCurrentRoutineNumber(2, settings.value("currentRoutineNumber2", 0).toInt());
    setCurrentRoutineNumber(3, settings.value("currentRoutineNumber3", 0).toInt());
    setLevel(0, (Level)settings.value("level0", 0).toInt());
    setLevel(1, (Level)settings.value("level1", 0).toInt());
    setLevel(2, (Level)settings.value("level2", 0).toInt());
    setLevel(3, (Level)settings.value("level3", 0).toInt());

}

void UserInfo::saveToSettings(QSettings &settings) const
{
    settings.setValue("fullName", fullName());
    settings.setValue("eMail", eMail());
    settings.setValue("homeTown", homeTown());
    settings.setValue("weight", weight());
    settings.setValue("height", height());
    settings.setValue("password", password());
    settings.setValue("age", age());
    settings.setValue("gender", gender());
    settings.setValue("objectiveIndex", objectiveIndex());
    settings.setValue("metersCoveredInTest", metersCoveredInTest());
    settings.setValue("currentRoutineNumber0", currentRoutineNumber(0));
    settings.setValue("currentRoutineNumber1", currentRoutineNumber(1));
    settings.setValue("currentRoutineNumber2", currentRoutineNumber(2));
    settings.setValue("currentRoutineNumber3", currentRoutineNumber(3));
    settings.setValue("level0", level(0));
    settings.setValue("level1", level(1));
    settings.setValue("level2", level(2));
    settings.setValue("level3", level(3));

}

UserInfo::Level UserInfo::resolveLevel() const
{
    /**
     * Cooper Test
     *
     */
    if( gender() == UserInfo::G_MALE )
    {
        if( age() < 30 )
        {
            if( metersCoveredInTest() <= 2700 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 40 )
        {
            if( metersCoveredInTest() <= 2600 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 50 )
        {
            if( metersCoveredInTest() <= 2500 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 60 )
        {
            if( metersCoveredInTest() <= 2300 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else
        {
            if( metersCoveredInTest() <= 2200 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }

    }
    else //if( gender() == UserInfo::G_FEMALE )
    {
        if( age() < 30 )
        {
            if( metersCoveredInTest() <= 2350 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 40 )
        {
            if( metersCoveredInTest() <= 2250 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 50 )
        {
            if( metersCoveredInTest() <= 2150 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else if( age() < 60 )
        {
            if( metersCoveredInTest() <= 1950 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }
        else
        {
            if( metersCoveredInTest() <= 1850 )
                return UserInfo::L_BEGINNER;
            else
                return UserInfo::L_INTERMEDIATE;
        }

    }

}

QString UserInfo::levelStr() const
{
    return RoutineManager::instance().levelName(objectiveIndex(), level(objectiveIndex()));
}

QString UserInfo::planName() const
{
    return RoutineManager::instance().planName(objectiveIndex());
}

Routine const &UserInfo::currentRoutine() const
{
    int currentRoutineNumber = m_currentRoutineNumber[objectiveIndex()];

    const PlanLevel &planLevel = RoutineManager::instance().plans().at(objectiveIndex())->levelAt(level(objectiveIndex()));
    if( currentRoutineNumber >= planLevel.routineCount() )
        currentRoutineNumber = planLevel.routineCount() - 1;

    return planLevel.routineAt(currentRoutineNumber);

}

QString UserInfo::homeTownKey() const
{
    int k = m_townMap.value(homeTown());
    QString ks = QString().sprintf("%d", k);
    if( k < 10 ) ks.prepend("0");
    return ks;
}

void UserInfo::_print()
{
    qDebug("UserInfo Object\n\tfullName: %s\n\teMail: %s\n\thomeTown: %s\n\tweight: %s\n\theight: %s\n\tobjective: %d",
           fullName().toAscii().constData(), eMail().toAscii().constData(), homeTown().toAscii().constData(),
           weight().toAscii().constData(), height().toAscii().constData(), objectiveIndex());

}
