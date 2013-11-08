//
//  SIXmlVerboseHandler.cpp
//  SIXmlVerboseHandler
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "sixmlverbosehandler.h"

#include <QDebug>

SIXmlVerboseHandler::SIXmlVerboseHandler()
    :m_showWarnings(true),
     m_showErrors(true),
     m_delegate(NULL)
{

}

SIXmlVerboseHandler::~SIXmlVerboseHandler()
{

}

bool SIXmlVerboseHandler::warning(const QXmlParseException &exception)
{
    if( m_showWarnings )
        qWarning() << "SIXmlVerboseHandler::Warning on line" << exception.lineNumber()
                   << ", column" << exception.columnNumber() << ":"
                   << exception.message();

    return false;
}

bool SIXmlVerboseHandler::error(const QXmlParseException &exception)
{
    if( m_showErrors )
        qWarning() << "SIXmlVerboseHandler::Error on line" << exception.lineNumber()
                   << ", column" << exception.columnNumber() << ":"
                   << exception.message();

    return false;
}

bool SIXmlVerboseHandler::fatalError(const QXmlParseException &exception)
{
    if( m_showErrors )
        qWarning() << "SIXmlVerboseHandler::Fatal error on line" << exception.lineNumber()
                   << ", column" << exception.columnNumber() << ":"
                   << exception.message();

    return false;
}
