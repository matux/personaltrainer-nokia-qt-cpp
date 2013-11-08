#include "exercisemanager.h"
#include "exercise.h"

#include "xmlexerciseshandler.h"
#include <iostream>

ExerciseManager &ExerciseManager::instance()
{
    static ExerciseManager theInstance;
    return theInstance;
}

ExerciseManager::ExerciseManager(QObject *parent)
    :QObject(parent)
{

}

void ExerciseManager::load()
{
    // Load the XML
    XmlExercisesHandler *handler = new XmlExercisesHandler();
    handler->setDelegate(this);

    QFile xmlFile(":/xml/res/xml/exercises.xml");
    if( !xmlFile.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        qWarning() << "Exercises::Could not open file :/xml/res/xml/exercises.xml. Error level: " << xmlFile.error();
        return;
    }

    QXmlSimpleReader xmlReader;
    xmlReader.setContentHandler(handler);
    xmlReader.setErrorHandler(handler);

    QXmlInputSource *source = new QXmlInputSource(&xmlFile);

    if( !xmlReader.parse(source) )
    {
        qDebug("ExerciseManager::XML Parsing failed.");
    }

    xmlFile.close();

    delete source;
    delete handler;

}

ExerciseManager::~ExerciseManager()
{
    //while( !m_exercises.isEmpty() )
    //    delete m_exercises.takeFirst();
    qDeleteAll(m_exercises.begin(), m_exercises.end()); // same as above
    m_exercises.clear();
}

void ExerciseManager::elementFound(QObject *element)
{
    Exercise *exercise = static_cast<Exercise *>(element);
    m_exercises.append(exercise);
    exercise->setId(m_exercises.count());
}
