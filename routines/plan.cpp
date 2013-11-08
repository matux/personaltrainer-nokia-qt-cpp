#include "plan.h"
#include "planlevel.h"

Plan::Plan(QObject *parent)
    :QObject(parent),
    m_name("None"),
    m_beginnerLevel(NULL),
    m_intermediateLevel(NULL),
    m_advancedLevel(NULL)
{

}

Plan::~Plan()
{

}

void Plan::setBeginnerLevel(PlanLevel *beginnerLevel)
{
    m_beginnerLevel = beginnerLevel;
    m_beginnerLevel->setParent(this);

}

void Plan::setIntermediateLevel(PlanLevel *intermediateLevel)
{
    m_intermediateLevel = intermediateLevel;
    m_intermediateLevel->setParent(this);

}

void Plan::setAdvancedLevel(PlanLevel *advancedLevel)
{
    m_advancedLevel = advancedLevel;
    m_advancedLevel->setParent(this);

}

PlanLevel const &Plan::levelAt(int index) const
{
    switch( index )
    {
    case 0: return *m_beginnerLevel; break;
    case 1: return *m_intermediateLevel; break;
    case 2: return *m_advancedLevel; break;
    default:
        return *m_beginnerLevel;
        break;

    }

}
