#include "routinemanager.h"
#include "xmlroutineshandler.h"
#include "plan.h"
#include "planlevel.h"
#include "routine.h"

#include <iostream>

RoutineManager &RoutineManager::instance()
{
    static RoutineManager theInstance;
    return theInstance;
}

RoutineManager::RoutineManager(QObject *parent)
    :QObject(parent)
{

}

RoutineManager::~RoutineManager()
{
    qDeleteAll(m_plans.begin(), m_plans.end());
    m_plans.clear();

}

void RoutineManager::load()
{
    // Load the XML
    XmlRoutinesHandler *handler = new XmlRoutinesHandler();
    //handler->setDelegate(this);

    QFile xmlFile(":/xml/res/xml/rutinas.xml");
    if( !xmlFile.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        qWarning() << "Exercises::Could not open file :/xml/res/xml/rutinas.xml. Error level: " << xmlFile.error();
        return;
    }

    QXmlSimpleReader xmlReader;
    xmlReader.setContentHandler(handler);
    xmlReader.setErrorHandler(handler);

    QXmlInputSource *source = new QXmlInputSource(&xmlFile);

    if( !xmlReader.parse(source) )
    {
        qDebug("RoutineManager::XML Parsing failed.");
    }

    xmlFile.close();

    delete source;
    delete handler;

}

Routine const &RoutineManager::routine(int planIndex, int planLevel, int routineNumber)
{
    return plans().at(planIndex)->levelAt(planLevel).routineAt(routineNumber);


}

QString RoutineManager::figureFilename(int exerciseId)
{
    switch( exerciseId )
    {
    case 0:
    case 1:
        return "fig_entrada_calor.png"; break;
    case 2:
    case 3:
    case 4:
    case 7:
    case 8:
        return "fig_stretching.png"; break;
    case 5:
        return "fig_stret_cuadri.png"; break;
    case 6:
        return "fig_stret_isquio.png"; break;
    case 9:
    case 10:
    case 11:
    case 12:
        return "fig_caminata.png"; break;
    case 13:
    case 14:
    case 15:
    case 16:
        return "fig_trote.png"; break;
    case 17:
    case 18:
    case 19:
        return "fig_abd.png"; break;
    case 20:
    case 21:
    case 22:
        return "fig_lagartijas.png"; break;
    case 23:
        return "fig_galope_lat.png"; break;
    case 24:
        return "fig_nados.png"; break;
    case 25:
        return "fig_carrera.png"; break;
    case 26:
        return "fig_skipping.png"; break;
    case 27:
        return "fig_espinales.png"; break;
    case 28:
    case 29:
        return "fig_sentadillas.png"; break;
    case 30:
        return "fig_superman.png"; break;
    case 31:
        return "fig_relajacion.png"; break;
    default:
        return "fig_entrada_calor.png";
        break;

    }

}

QString RoutineManager::planName(int index)
{
    return plans().at(index)->name();
}

QString RoutineManager::levelName(int planIndex, int levelIndex)
{
    return plans().at(planIndex)->levelAt(levelIndex).name();
}
