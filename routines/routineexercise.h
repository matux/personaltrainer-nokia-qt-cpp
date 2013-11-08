#ifndef ROUTINEEXERCISE_H
#define ROUTINEEXERCISE_H

#include <QObject>
#include "routineelement.h"

class Exercise;

class RoutineExercise : public RoutineElement
{
    Q_OBJECT
public:
    explicit RoutineExercise(QObject *parent = 0);
    virtual ~RoutineExercise();

    virtual QString const type() const;
    virtual QString const name() const;

    inline Exercise const &actualExercise() const { return *m_actualExercise; }
    inline int exerciseId() const { return m_exerciseId; }
    inline int time() const { return m_time; }
    inline int series() const { return m_series; }
    inline int distance() const { return m_distance; }
    inline int special() const { return m_special; }

    void setExerciseId(const int exerciseId);
    inline void setTime(const int time) { m_time = time; }
    inline void setSeries(const int series) { m_series = series; }
    inline void setDistance(const int distance) { m_distance = distance; }
    inline void setSpecial(int special) { m_special = special; }

signals:

public slots:

private:
    Exercise *m_actualExercise;

    int m_exerciseId;
    int m_time;
    int m_series;
    int m_distance;
    int m_special;

};

#endif // ROUTINEEXERCISE_H
