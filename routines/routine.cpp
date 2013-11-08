#include "routine.h"
#include "routineelement.h"
#include "routineexercise.h"
#include "routineexercisecomposition.h"

Routine::Routine(QObject *parent)
    :QObject(parent),
    m_id(-1),
    m_cachedCount(0)
{

}

Routine::~Routine()
{
    m_exerciseList.clear();

}

int Routine::addExercise(RoutineElement *routineElement)
{
    routineElement->setParent(this);
    m_exerciseList.append(routineElement);
    return m_exerciseList.count();

}

void Routine::cacheExerciseCount()
{
    for( int i = 0; i < exerciseCountWithoutComposition(); ++i )
    {
        const RoutineElement &routineElement = exerciseAt(i);
        if( routineElement.type().compare("RoutineExerciseComposition") == 0 )
        {
            const RoutineExerciseComposition &routineComposition = dynamic_cast<const RoutineExerciseComposition &>(routineElement);
            m_cachedCount += routineComposition.exerciseCount();
        }
        else
            m_cachedCount++;
    }
}

int Routine::exerciseCount() const
{
    if( !m_cachedCount )
        const_cast<Routine &>(*this).cacheExerciseCount();

    return m_cachedCount;

}
