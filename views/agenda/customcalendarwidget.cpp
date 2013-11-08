#include "customcalendarwidget.h"
#include "model/globaldataobject.h"

CustomCalendarWidget::CustomCalendarWidget(QWidget *parent)
    :QCalendarWidget(parent),
    m_button(":/images/res/agenda_boton_apagado.png"),
    m_buttonOn(":/images/res/agenda_boton_encendido.png")
{


}

void CustomCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    painter->fillRect(rect, QColor(21,25,67));

    bool todayWasExercised = false;
    QList<QDate *> &dateList = GlobalDataObject::instance().datesExercisedList();
    for( int i = 0; i < dateList.count() && !todayWasExercised; ++i )
    {
        QDate *exDate = dateList.at(i);
        if( exDate->operator ==(date) )
        {
            todayWasExercised = true;
            painter->drawPixmap(rect, m_buttonOn);
        }
    }

    if( !todayWasExercised )
        painter->drawPixmap(rect, m_button);

    //painter->setBrush(QColor(123,123,123));
    QPen thePen(painter->pen());
    QColor previousColor(thePen.color());
    if( todayWasExercised )
        thePen.setColor(QColor(167,208,220));
    else
        thePen.setColor(QColor(123,123,123));
    painter->setPen(thePen);
    painter->setFont(QFont("AvantGardeMdITCTT", 7, 60, false));
    painter->drawText(rect, QString().sprintf("%d",date.day()), QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
    thePen.setColor(previousColor);
    painter->setPen(thePen);

}
