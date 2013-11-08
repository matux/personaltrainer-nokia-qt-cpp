#include "xmlroutineshandler.h"

#include <SIKit/xml/siixmlhandlerdelegate.h>

#include "plan.h"
#include "planlevel.h"
#include "routine.h"
#include "routineelement.h"
#include "routineexercise.h"
#include "routineexercisecomposition.h"
#include "routinemanager.h"

XmlRoutinesHandler::XmlRoutinesHandler()
    :SIXmlVerboseHandler(),
    m_showOutput(false)
{

}

XmlRoutinesHandler::~XmlRoutinesHandler()
{

}

bool XmlRoutinesHandler::startDocument()
{
    m_currentPlan = NULL;
    m_currentPlanLevel = NULL;
    m_currentRoutine = NULL;
    m_currentRoutineExercise = NULL;
    m_currentRoutineExerciseComposition = NULL;
    m_currentRoutineExerciseWithinExerciseComposition = NULL;
    m_inRoot = m_inPlan = m_inLevel = m_inRoutine = m_inExercise = m_inExerciseComposition = m_inExerciseWithinExerciseComposition = false;
    return true;
}

bool XmlRoutinesHandler::endDocument()
{
    return true;
}

bool XmlRoutinesHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if( !isInRoot() && qName == "root" )
    {
        m_inRoot = true;
        if( m_showOutput )
            qDebug("Found XML root");
    }
    else if( !isInPlan() && qName == "plan" )
    {
        m_inPlan = true;
        m_currentPlan = new Plan();
        m_currentPlan->setName(atts.value("name"));

        RoutineManager::instance().plans().append(m_currentPlan);

        if( m_showOutput )
            qDebug("\tPlan: %s", m_currentPlan->name().toAscii().constData());
    }
    else if( !isInLevel() && qName == "level" )
    {
        m_inLevel = true;
        m_currentPlanLevel = new PlanLevel();
        m_currentPlanLevel->setName(atts.value("name"));
        if( !m_currentPlan->hasBeginnerLevel() )
            m_currentPlan->setBeginnerLevel(m_currentPlanLevel);
        else if( !m_currentPlan->hasIntermediateLevel() )
            m_currentPlan->setIntermediateLevel(m_currentPlanLevel);
        else if( !m_currentPlan->hasAdvancedLevel() )
            m_currentPlan->setAdvancedLevel(m_currentPlanLevel);

        if( m_showOutput )
            qDebug("\t\tLevel: %s", m_currentPlanLevel->name().toAscii().constData());
    }
    else if( !isInRoutine() && qName == "rutina" )
    {
        m_inRoutine = true;
        m_currentRoutine = new Routine();
        int id = m_currentPlanLevel->addRoutine(m_currentRoutine);
        m_currentRoutine->setId(id);

        if( m_showOutput )
            qDebug("\t\t\tRoutine: %d", id);
    }
    else if( !isInExercise() && !isInExerciseComposition() && qName == "ejercicio" )
    {
        m_inExercise = true;
        m_currentRoutineExercise = new RoutineExercise();
        int id = m_currentRoutine->addExercise(m_currentRoutineExercise);
        m_currentRoutineExercise->setId(id);
        int i = -1;
        if( (i = atts.index("type")) >= 0 )
            m_currentRoutineExercise->setExerciseId(atts.value(i).toInt());
        if( (i = atts.index("time")) >= 0 )
            m_currentRoutineExercise->setTime(atts.value(i).toInt());
        if( (i = atts.index("distance")) >= 0 )
            m_currentRoutineExercise->setDistance(atts.value(i).toInt());
        if( (i = atts.index("special")) >= 0 )
            m_currentRoutineExercise->setSpecial(atts.value(i).toInt());
        if( (i = atts.index("series")) >= 0 )
            m_currentRoutineExercise->setSeries(atts.value(i).toInt());

        if( m_showOutput )
            qDebug("\t\t\t\tEjercicio (%d) type:%d time:%d series:%d distance:%d special:%d", id,
                   m_currentRoutineExercise->exerciseId(),
                   m_currentRoutineExercise->time(),
                   m_currentRoutineExercise->series(),
                   m_currentRoutineExercise->distance(),
                   m_currentRoutineExercise->special());

    }
    else if( !isInExerciseComposition() && qName == "ejercicioCompuesto" )
    {
        m_inExerciseComposition = true;
        m_currentRoutineExerciseComposition = new RoutineExerciseComposition();
        int id = m_currentRoutine->addExercise(m_currentRoutineExerciseComposition);
        m_currentRoutineExerciseComposition->setId(id);
        m_currentRoutineExerciseComposition->setCount(atts.value("count").toInt());

        if( m_showOutput )
            qDebug("\t\t\t\tEjercicio Compuesto (%d) count:%d", id, m_currentRoutineExerciseComposition->count());

    }
    else if( !isInExerciseWithinExerciseComposition() && qName == "ejercicio" )
    {
        m_inExerciseWithinExerciseComposition = true;
        m_currentRoutineExerciseWithinExerciseComposition = new RoutineExercise();
        int id = m_currentRoutineExerciseComposition->addExercise(m_currentRoutineExerciseWithinExerciseComposition);
        m_currentRoutineExerciseWithinExerciseComposition->setId(id);
        int i = -1;
        if( (i = atts.index("type")) >= 0 )
            m_currentRoutineExerciseWithinExerciseComposition->setExerciseId(atts.value(i).toInt());
        if( (i = atts.index("time")) >= 0 )
            m_currentRoutineExerciseWithinExerciseComposition->setTime(atts.value(i).toInt());
        if( (i = atts.index("distance")) >= 0 )
            m_currentRoutineExerciseWithinExerciseComposition->setDistance(atts.value(i).toInt());
        if( (i = atts.index("special")) >= 0 )
            m_currentRoutineExerciseWithinExerciseComposition->setSpecial(atts.value(i).toInt());
        if( (i = atts.index("series")) >= 0 )
            m_currentRoutineExerciseWithinExerciseComposition->setSeries(atts.value(i).toInt());

        if( m_showOutput )
            qDebug("\t\t\t\t\tEjercicio (%d) type:%d time:%d series:%d disance:%d special:%d", id,
                   m_currentRoutineExerciseWithinExerciseComposition->exerciseId(),
                   m_currentRoutineExerciseWithinExerciseComposition->time(),
                   m_currentRoutineExerciseWithinExerciseComposition->series(),
                   m_currentRoutineExerciseWithinExerciseComposition->distance(),
                   m_currentRoutineExerciseWithinExerciseComposition->special());

    }

    return true;

}

bool XmlRoutinesHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if( qName == "root" )
        m_inRoot = false;
    else if( qName == "plan" )
        m_inPlan = false;
    else if( qName == "level" )
        m_inLevel = false;
    else if( qName == "rutina" )
        m_inRoutine = false;
    else if( qName == "ejercicio" && !isInExerciseWithinExerciseComposition() )
        m_inExercise = false;
    else if( qName == "ejercicioCompuesto" )
        m_inExerciseComposition = false;
    else if( qName == "ejercicio" && isInExerciseWithinExerciseComposition() )
        m_inExerciseWithinExerciseComposition = false;

    return true;

}
