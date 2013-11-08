#ifndef XMLROUTINESHANDLER_H
#define XMLROUTINESHANDLER_H

#include <SIKit/xml/sixmlverbosehandler.h>

class Plan;
class PlanLevel;
class Routine;
class RoutineExercise;
class RoutineExerciseComposition;

class XmlRoutinesHandler : public SIXmlVerboseHandler
{
public:
    explicit XmlRoutinesHandler();
    virtual ~XmlRoutinesHandler();

    bool startDocument();
    bool endDocument();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

private:
    inline bool isInRoot() const { return m_inRoot; }
    inline bool isInPlan() const { return m_inPlan && !m_inLevel; }
    inline bool isInLevel() const { return m_inLevel && !m_inRoutine; }
    inline bool isInRoutine() const { return m_inRoutine && !(m_inExercise || m_inExerciseComposition); }
    inline bool isInExercise() const { return m_inExercise; }
    inline bool isInExerciseComposition() const { return m_inExerciseComposition && !m_inExerciseWithinExerciseComposition; }
    inline bool isInExerciseWithinExerciseComposition() const { return m_inExerciseWithinExerciseComposition; }

private:
    bool m_inRoot;
    bool m_inPlan;
    bool m_inLevel;
    bool m_inRoutine;
    bool m_inExercise;
    bool m_inExerciseComposition;
    bool m_inExerciseWithinExerciseComposition;

    Plan *m_currentPlan;
    PlanLevel *m_currentPlanLevel;
    Routine *m_currentRoutine;
    RoutineExercise *m_currentRoutineExercise;
    RoutineExerciseComposition *m_currentRoutineExerciseComposition;
    RoutineExercise *m_currentRoutineExerciseWithinExerciseComposition;

    bool m_showOutput;

};

#endif // XMLROUTINESHANDLER_H
