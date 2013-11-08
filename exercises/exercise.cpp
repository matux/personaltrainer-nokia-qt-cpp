#include "exercise.h"

Exercise::Exercise(QObject *parent)
    :QObject(parent),
    m_id(-1)
{
    setProperties();
}

Exercise::Exercise(const QString &name, const QString &description, const QString &titleFilename, const QString &figureFilename, QObject *parent)
    :QObject(parent),
     m_id(0),
     m_name(name),
     m_description(description),
     m_titleFilename(titleFilename),
     m_figureFilename(figureFilename)
{
    setProperties();

}

Exercise::~Exercise()
{

}

void Exercise::_print()
{
    qDebug("Printing Exercise (%s):\nDescription: %s\nTitle File: %s\nFigure File: %s",
           m_name.toAscii().constData(), m_description.toAscii().constData(), m_titleFilename.toAscii().constData(), m_figureFilename.toAscii().constData());

}
