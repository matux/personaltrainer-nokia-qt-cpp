//
//  GlobalDataObject.h
//  GlobalDataObject
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef GLOBALDATAOBJECT_H
#define GLOBALDATAOBJECT_H

#define PLAN_COUNT 4

#include <QObject>

class UserInfo;
class PlanInfo;
class QDate;

/**
 *  Stores application data
 *
 *  Meyer's Singleton
 *
 */
class GlobalDataObject : QObject
{
    Q_OBJECT;
public:
    static GlobalDataObject &instance();

    void loadDefaults();
    void loadApplicationSettings();
    void saveApplicationSettings();

    inline bool forceReset() const { return m_forceReset; }
    inline void setForceReset(bool forceReset) { m_forceReset = forceReset; }

    inline void setFirstTimeRun(bool value) { m_firstTime = value; }
    inline bool firstTimeRun() const { return m_firstTime; }

    inline void setTodayIsTheDay(bool value) { m_todayIsTheDay = value; }
    inline bool todayIsTheDay() const { return m_todayIsTheDay; }

    inline void setUserRegistered(bool value) { m_userRegistered = value; }
    inline bool userRegistered() const { return m_userRegistered; }

    inline UserInfo &userInfo() { return *m_userInfo; }
    inline PlanInfo &planInfo(int planId) { return *m_planInfo[planId]; }
    inline PlanInfo **planInfoFull() { return m_planInfo; }

    void resetPlanInfo();
    bool planInfoIsEmpty();

    inline QList<QDate *> &datesExercisedList() { return m_datesExercised; }

signals:

public slots:

private:
    GlobalDataObject(QObject *parent = 0):QObject(parent), m_forceReset(false), m_userInfo(NULL)
    { m_planInfo[0] = m_planInfo[1] = m_planInfo[2] = m_planInfo[3] = NULL;  }
    GlobalDataObject(GlobalDataObject const &, QObject *parent = 0) {}
    GlobalDataObject &operator =(GlobalDataObject const &);
    ~GlobalDataObject();

    bool m_forceReset;

    // Settings
    UserInfo *m_userInfo;
    PlanInfo *m_planInfo[PLAN_COUNT];
    bool m_userRegistered;
    bool m_firstTime;
    bool m_todayIsTheDay;

    QList<QDate *> m_datesExercised;

};

#endif // GLOBALDATAOBJECT_H
