//
//  SITabBarItem.h
//  SITabBarItem
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SITABBARITEM_H
#define SITABBARITEM_H

#include <QWidget>

#include "SIView.h"
#include "SINavigationController.h"

class SITabBarItem : public SIView
{
    Q_OBJECT
public:
    explicit SITabBarItem(int index, QWidget *parent = 0);
    virtual ~SITabBarItem();

    // Events
    virtual void mousePressEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);

    // Properties
    inline void setIcon(const QString &fileName) { m_icon.load(fileName); }
    inline QPixmap const &icon() const { return m_icon; }

    inline void setIconSelected(const QString &fileName) { m_iconSelected.load(fileName); }
    inline QPixmap const &iconSelected() const { return m_iconSelected; }

    inline void setSelected(bool isSelected) { m_isSelected = isSelected; }
    inline bool isSelected() const { return m_isSelected; }

    inline void setAssociatedNavigationController(QPointer<SINavigationController> const &associatedNavigationController) { m_associatedNavigationController = associatedNavigationController; }
    inline QPointer<SINavigationController> &associatedNavigationController() { return m_associatedNavigationController; }

    inline int index() const { return m_index; }

public slots:

signals:
    void buttonPressed(int);

protected:
    QPointer<SINavigationController> m_associatedNavigationController;

    QPixmap m_icon;
    QPixmap m_iconSelected;
    bool m_isSelected;
    int m_index;

};

#endif // SITABBARITEM_H
