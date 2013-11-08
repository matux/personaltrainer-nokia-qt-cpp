//
//  SIButton.h
//  SIButton
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SIBUTTON_H
#define SIBUTTON_H

#include <QtCore>
#include <QtGui>

#include <iostream>

class SIButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SIButton(QWidget *parent = 0);
    SIButton(const QString &text, QWidget *parent = 0);
    SIButton(const QIcon &icon, const QString &text, QWidget *parent = 0);
    virtual ~SIButton();

    // Effect
    inline void setAeroEffect(bool useAero)     { m_useAero = useAero; }
    inline void setColor(QColor &color)         { m_color = color; }
    inline void setHighlight(QColor &highlight) { m_highlight = highlight; }
    inline void setShadow(QColor &shadow)       { m_shadow = shadow; }
    inline void setRoundness(int roundness)     { m_roundness = roundness; } // Range: 0 [rectangle] - 99 [oval]

    //Range: 0.0 [invisible] - 1.0 [opaque]
    inline void setOpacity(qreal opacity)        { m_opacity = opacity; }

    inline void setAlignment(Qt::Alignment alignment) { m_alignment = alignment; }
    inline Qt::Alignment const alignment() const { return m_alignment; }

    // Custom button
    inline void setNormalStatePix(const QString &filename) { m_normalStatePix.load(filename); }
    inline QPixmap const &normalStatePix() const { return m_normalStatePix; }
    inline void setPressedStatePix(const QString &filename) { m_pressedStatePix.load(filename); }
    inline QPixmap const &pressedStatePix() const { return m_pressedStatePix; }

 protected:
    virtual void paintEvent(QPaintEvent *paintEvent);
    virtual void paintAero(QPaintEvent *paintEvent);
    virtual void paintCustom(QPaintEvent *paintEvent);

    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

 private:
    QRect calculateIconPosition(QRect button_rect, QSize icon_size);

 private:
    void initInternal();

    bool m_hovered;
    bool m_pressed;
    bool m_useAero;

    QColor m_color;
    QColor m_highlight;
    QColor m_shadow;

    qreal m_opacity;

    int m_roundness;
    Qt::Alignment m_alignment;

    QPixmap m_normalStatePix;
    QPixmap m_pressedStatePix;

signals:

public slots:

};

#endif // SIBUTTON_H
