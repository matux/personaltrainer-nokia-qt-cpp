#ifndef ROUTINEEXERCISECOMPOSITION_H
#define ROUTINEEXERCISECOMPOSITION_H

#include <QObject>
#include "routineelement.h"

class RoutineExerciseComposition : public RoutineElement
{
    Q_OBJECT
public:
    explicit RoutineExerciseComposition(QObject *parent = 0);
    virtual ~RoutineExerciseComposition();

    virtual QString const type() const;
    virtual QString const name() const;

    int addExercise(RoutineElement *routineElement);
    inline int exerciseCount() const { return m_exerciseList.count(); }
    inline RoutineElement const &exerciseAt(int i) const { return *(m_exerciseList.at(i)); }

    inline int count() const { return m_count; }
    inline void setCount(const int count) { m_count = count; }

signals:

public slots:

private:
    int m_count;

    QList<RoutineElement *> m_exerciseList;

};

#endif // ROUTINEEXERCISECOMPOSITION_H
