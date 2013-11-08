#include "routineexercisecomposition.h"

RoutineExerciseComposition::RoutineExerciseComposition(QObject *parent)
    :RoutineElement(parent)
{

}

RoutineExerciseComposition::~RoutineExerciseComposition()
{
    m_exerciseList.clear();
}

int RoutineExerciseComposition::addExercise(RoutineElement *routineElement)
{
    routineElement->setParent(this);
    m_exerciseList.append(routineElement);

    return m_exerciseList.count();

}

QString const RoutineExerciseComposition::type() const
{
    return "RoutineExerciseComposition";
}

QString const RoutineExerciseComposition::name() const
{
    return QString().sprintf("%d pasadas de:", count());
}
