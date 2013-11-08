//
//  SINavigationController.h
//  SINavigationController
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SINAVIGATIONCONTROLLER_H
#define SINAVIGATIONCONTROLLER_H

#include <QtCore>
#include <QtGui>

#include "SINavigationBar.h"
#include "SITabBar.h"

class SIView;

class SINavigationController : public QWidget
{
    Q_OBJECT
public:
    explicit SINavigationController(QWidget *parent = 0);
    virtual ~SINavigationController();

    inline void setTabBar(SITabBar *tabBar) { m_tabBar = tabBar; }
    inline SITabBar *tabBar() const { return m_tabBar; }

    inline SINavigationBar &navigationBar() const { return *m_navigationBar; }
    inline SINavigationBar *navigationBarPtr() const { return m_navigationBar; }

    inline void hideBar() { m_navigationBar->hide(); }
    inline void showBar() { m_navigationBar->show(); }

    inline void showViewAtIndex(int index) { m_stackedWidget->setCurrentIndex(index); }

    int  addView(SIView *view);
    void removeViewAt(int index);
    void removeViewsInCascadeFrom(int index);
    void pushView(SIView *view);
    QWidget *popView();
    QWidget *popToRootView();

signals:

public slots:

protected:
    QVBoxLayout *m_verticalLayout;
    QStackedWidget *m_stackedWidget;

private:
    SITabBar *m_tabBar;
    SINavigationBar *m_navigationBar;

};

#endif // SINAVIGATIONCONTROLLER_H
