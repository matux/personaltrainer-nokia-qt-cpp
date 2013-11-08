#ifndef PLANINFO_H
#define PLANINFO_H

#include <QObject>
#include <QDate>

class QSettings;

class PlanInfo : public QObject
{
    Q_OBJECT
public:
    struct ExerciseInfo
    {
        ExerciseInfo():id(0),time(0),distance(0),calories(0) {}
        void set(int _time, int _distance, int _calories, int _speed) { time+=_time; distance+=_distance; calories+=_calories; speed=_speed; }
        int id;
        int time;
        int distance;
        int speed;
        int calories;

        inline void _print() {
#ifdef _DEBUG
            qDebug("******************\nExerciseInfo:\n\tid: %d\n\ttime: %d\n\tdistance: %d\n\tcalories: %d\n******************", id, time, distance, calories);
#endif
        }

    };

    struct RoutineInfo
    {
        RoutineInfo() {}
        void set(const QDate &_date, const QString &_time, bool _routineDone) { date=_date; time=_time; routineDone = _routineDone; }
        int id;
        bool routineDone;
        QDate date;
        QString time;
        QList<ExerciseInfo *> exerciseInfo;

        inline void _print() {
#ifdef _DEBUG
            qDebug("******************\nRoutineInfo:\n\tid: %d\n\tdate: %s\n\ttime: %s\n******************", id, date.toString("yyyy-MM-dd").toAscii().constData(), time.toAscii().constData());
#endif
        }
    };

public:
    explicit PlanInfo(QObject *parent = 0);

    void loadFromSettings(QSettings &settings);
    void saveToSettings(QSettings &settings) const;

    inline QList<RoutineInfo *> &routineInfoList() { return m_routineInfo; }
    RoutineInfo &routineInfo(int withId);
    ExerciseInfo &exerciseInfo(int fromRoutineId, int withId);

    inline int planId() const { return m_planId; }
    inline void setPlanId(int planId) { m_planId = planId; }

    void reset();
    inline bool isEmpty() const { return m_routineInfo.isEmpty(); }

signals:

public slots:

private:
    QList<RoutineInfo *> m_routineInfo;

    int m_planId;

};

#endif // PLANINFO_H
