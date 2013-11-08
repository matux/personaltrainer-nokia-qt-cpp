//
//  SITabBarView.h
//  SITabBarView
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//
//  Notes:
//      Could we use QTabWidget for this?
//

#ifndef SITABBAR_H
#define SITABBAR_H

#include <QtCore>
#include <QtGui>
#include <iostream>

#include "SIView.h"

class SITabBarItem;
class SINavigationController;

class SITabBar : public SIView
{
    Q_OBJECT
public:
    explicit SITabBar(QWidget *parent = 0);
    virtual ~SITabBar();

    void setBackgroundImage(const QString &fileName);

    // Tab Bar Buttons
    inline QVarLengthArray<SITabBarItem *, 6> const &tabBarButtons() const { return m_tabBarButtons; }
    SITabBarItem &addTabBarButton(const bool hidden = false);

    QPointer<SINavigationController> const &navigationControllerAtTab(int index) const;

    inline void hideBar() { m_tabBarContainer->hide(); }
    inline void showBar() { m_tabBarContainer->show(); }

    void setSelectedIndex(int index);
    inline int selectedIndex() const { return m_selectedIndex; }

    inline void setUserInteractionEnabled(bool value) { m_userInteractionEnabled = value; }
    inline int userInteractionEnabled() const { return m_userInteractionEnabled; }

    inline void setBarItemSize(const QSize &size) { m_barItemSize = size; }
    inline QSize const &barItemSize() const { return m_barItemSize; }

    inline void setDefaultHeaderImage(const QString &fileName) { m_defaultHeaderImage = fileName; }
    inline QString const &defaultHeaderImage() const { return m_defaultHeaderImage; }

    //inline void setLayout(const QPointer<QHBoxLayout> &layout) { m_layout = layout; }
    inline QPointer<QHBoxLayout> const &layout() const { return m_layout; }

signals:
    void selectionChanged(int index);

private slots:
    void tabBarButtonPressed(int index);

protected:
    QString m_defaultHeaderImage;

    QVarLengthArray<SITabBarItem *, 6> m_tabBarButtons;
    QVarLengthArray<SINavigationController *, 6> m_tabBarViews;
    int m_selectedIndex;
    bool m_userInteractionEnabled;
    QSize m_barItemSize;

    QPointer<QStackedWidget> m_navigationControllerContainer;
    QPointer<QWidget> m_tabBarContainer;

    QPointer<QVBoxLayout> m_internalLayout;
    QPointer<QHBoxLayout> m_layout;

};

#endif // SITABBARVIEW_H
