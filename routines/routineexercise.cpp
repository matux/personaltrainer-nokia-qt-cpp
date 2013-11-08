#include "routineexercise.h"

#include "model/exercises/exercise.h"
#include "model/exercises/exercisemanager.h"

RoutineExercise::RoutineExercise(QObject *parent)
    :RoutineElement(parent),
    m_actualExercise(NULL),
    m_exerciseId(-1),
    m_time(0),
    m_series(1),
    m_distance(0),
    m_special(0)
{

}

RoutineExercise::~RoutineExercise()
{

}

QString const RoutineExercise::type() const
{
    return "RoutineExercise";
}

QString const RoutineExercise::name() const
{
    return m_actualExercise->name();
}

void RoutineExercise::setExerciseId(const int exerciseId)
{
    m_exerciseId = exerciseId;
    m_actualExercise = ExerciseManager::instance().list().at(exerciseId - 1);

}
