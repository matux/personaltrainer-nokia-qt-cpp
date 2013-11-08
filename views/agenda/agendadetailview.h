#ifndef AGENDADETAILVIEW_H
#define AGENDADETAILVIEW_H

#include <SIKit/SIKit.h>

class AgendaDetailView : public SIView
{
    Q_OBJECT
public:
    explicit AgendaDetailView(const QDate &date, QWidget *parent = 0);

    //inline void setDate(const QDate &date) { m_date = date; }
    inline QDate const &date() const { return m_date; }

signals:

public slots:

private:
    const QDate &m_date;

};

#endif // AGENDADETAILVIEW_H
