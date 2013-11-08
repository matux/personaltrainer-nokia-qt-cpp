//
//  SINavigationBar.h
//  SINavigationBar
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SINAVIGATIONBAR_H
#define SINAVIGATIONBAR_H

#include <QtGui>

class SINavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit SINavigationBar(QWidget *parent = 0);
    //virtual ~SINavigationBar();

    void setBackground(const QString &fileName);
    void addSubview(QWidget *subview);

signals:

public slots:

protected:
    QWidget *centralWidget;

};

#endif // SINAVIGATIONBAR_H
