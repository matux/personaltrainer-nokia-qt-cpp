//
//  SIXmlVerboseHandler.h
//  SIXmlVerboseHandler
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SIXMLVERBOSEHANDLER_H
#define SIXMLVERBOSEHANDLER_H

#include <QXmlDefaultHandler>
#include "siixmlhandlerdelegate.h"

class SIXmlVerboseHandler : public QXmlDefaultHandler
{
public:
    explicit SIXmlVerboseHandler();
    virtual ~SIXmlVerboseHandler();

    virtual bool warning(const QXmlParseException &exception);
    virtual bool error(const QXmlParseException &exception);
    virtual bool fatalError(const QXmlParseException &exception);

    inline bool showWarnings() const { return m_showWarnings; }
    inline bool showErrors() const { return m_showErrors; }
    inline void setShowWarnings(bool show) { m_showWarnings = show; }
    inline void setShowErrors(bool show) { m_showErrors = show; }

    inline void setDelegate(SIIXmlHandlerDelegate *delegate) { m_delegate = delegate; }
    inline SIIXmlHandlerDelegate &delegate() { return *m_delegate; }

protected:
    bool m_showWarnings;
    bool m_showErrors;

    SIIXmlHandlerDelegate *m_delegate;

};

#endif // SIXMLVERBOSEHANDLER_H
