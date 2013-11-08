#ifndef AGENDAVIEW_H
#define AGENDAVIEW_H

#include <SIKit/SIKit.h>

class CustomCalendarWidget;

class AgendaView : public SIView
{
    Q_OBJECT
public:
    enum Month { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
    //static QString months[12];

    explicit AgendaView(QWidget *parent = 0);
    virtual ~AgendaView();

    inline Month currentMonth() const { return m_currentMonth; }
    inline void setCurrentMonth(Month month) { m_currentMonth = month; }

signals:

public slots:
    void backMonthPressed();
    void forwardMonthPressed();

    void dateSelected(const QDate &);

private:
    Month m_currentMonth;

    QLabel *m_monthLabel;
    CustomCalendarWidget *m_calendarWidget;
};

#endif // AGENDAVIEW_H
