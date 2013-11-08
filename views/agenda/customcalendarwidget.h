#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QtGui>

class CustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CustomCalendarWidget(QWidget *parent = 0);

    inline void setDateList(QList<QDate *> *datesExercised) { m_datesExercised = datesExercised; }
    inline QList<QDate *> &dateList() const { return *m_datesExercised; }

signals:

public slots:

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

    QPixmap m_button;
    QPixmap m_buttonOn;

private:
    QList<QDate *> *m_datesExercised;

};

#endif // CUSTOMCALENDARWIDGET_H
