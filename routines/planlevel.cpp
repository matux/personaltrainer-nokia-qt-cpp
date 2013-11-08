#include "planlevel.h"
#include "routine.h"

PlanLevel::PlanLevel(QObject *parent)
    :QObject(parent),
     m_name("None")
{

}

PlanLevel::~PlanLevel()
{
    m_routineList.clear();

}

int PlanLevel::addRoutine(Routine *routine)
{
    routine->setParent(this);
    m_routineList.append(routine);
    return m_routineList.count();

}
