//
//  SIIXmlHandlerDelegate.h
//  SIIXmlHandlerDelegate
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SIIXMLHANDLERDELEGATE_H
#define SIIXMLHANDLERDELEGATE_H

#include <QObject>

class SIIXmlHandlerDelegate
{
public:
    virtual ~SIIXmlHandlerDelegate() = 0;

    virtual void elementFound(QObject *element) = 0;

protected:


};

#endif // IXMLHANDLERDELEGATE_H
