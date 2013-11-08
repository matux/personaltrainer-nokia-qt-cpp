//
//  SIView.h
//  SIView
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SIVIEW_H
#define SIVIEW_H

#include <QWidget>

/**
 *  SIView
 *
 *  Notes:
 *      * This class uses a "centralWidget", we recommend using it but you may skip it.
 *
 */
class SITabBar;
class SINavigationController;

class SIView : public QWidget
{
    Q_OBJECT
public:
    explicit SIView(QWidget *parent = 0);
    virtual ~SIView();

    //inline void setTabBar(const QSharedPointer<SITabBar> &tabBar) { m_tabBar = tabBar; }
    //inline QSharedPointer<SITabBar> const &tabBar() const { return m_tabBar; }

    inline void setTabBar(SITabBar *tabBar) { m_tabBar = tabBar; }
    inline SITabBar *tabBar() const { return m_tabBar; }

    inline void setNavigationController(SINavigationController *navigationController) { m_navigationController = navigationController; }
    inline SINavigationController *navigationController() const { return m_navigationController; }

    inline void setTag(int tag) { m_tag = tag; }
    inline int tag() const { return m_tag; }

    virtual void setBackgroundImage(const QString &filename);

signals:
    void viewWillAppear();
    //void viewDidAppear();
    void viewWillDisappear();
    //void viewDidDisappear();

public slots:

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

    inline QWidget *centralWidget() const { return m_centralWidget; }

    QWidget *m_centralWidget;
    int m_tag;
    SITabBar *m_tabBar;
    SINavigationController *m_navigationController;

};

#endif // SIVIEW_H
