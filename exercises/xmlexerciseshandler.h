#ifndef XMLEXERCISESHANDLER_H
#define XMLEXERCISESHANDLER_H

#include <SIKit/xml/sixmlverbosehandler.h>

class Exercise;

class XmlExercisesHandler : public SIXmlVerboseHandler
{
public:
    explicit XmlExercisesHandler();
    virtual ~XmlExercisesHandler();

    bool startDocument();
    bool endDocument();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

private:
    Exercise *currentExercise;

};

#endif // XMLEXERCISESHANDLER_H
