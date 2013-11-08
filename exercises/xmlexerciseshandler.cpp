#include "xmlexerciseshandler.h"

#include <SIKit/xml/siixmlhandlerdelegate.h>

#include "exercise.h"

XmlExercisesHandler::XmlExercisesHandler()
    :SIXmlVerboseHandler(),
    currentExercise(NULL)
{

}

XmlExercisesHandler::~XmlExercisesHandler()
{

}

bool XmlExercisesHandler::startDocument()
{
    return true;
}

bool XmlExercisesHandler::endDocument()
{
    return true;
}

bool XmlExercisesHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if( qName == "exercise" )
    {
        currentExercise = new Exercise();
        currentExercise->setName(atts.value(0));
        currentExercise->setDescription(atts.value(1));
        currentExercise->setTitleFilename(atts.value(2));
        currentExercise->setFigureFilename(atts.value(3));
    }
    else if( qName == "properties" )
    {
        currentExercise->setProperties(atts.value(0).toInt(),
                                       atts.value(1).toInt(),
                                       atts.value(2).toInt(),
                                       atts.value(3).toInt(),
                                       atts.value(4).toInt());

        delegate().elementFound(dynamic_cast<QObject *>(currentExercise));
        currentExercise = NULL;
    }

    return true;
}

bool XmlExercisesHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    return true;
}
