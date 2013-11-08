#include "agendaview.h"
#include "customcalendarwidget.h"
#include "agendadetailview.h"
#include "model/globaldataobject.h"

QString months[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

AgendaView::AgendaView(QWidget *parent)
    :SIView(parent)
{
    const QDateTime &dateTime = QDateTime::currentDateTime();
    setCurrentMonth((Month)(dateTime.date().month() - 1));

    setObjectName(QString().sprintf("AgendaView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    //centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/screens/agenda.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    m_monthLabel = new QLabel(centralWidget);
    m_monthLabel->setObjectName(QString().sprintf("monthLabel%p", m_monthLabel));
    m_monthLabel->setGeometry(QRect(0, 19, 360, 20));
    m_monthLabel->setStyleSheet(QString::fromUtf8("QLabel#%1 { font: 75 20px \"AvantGardeMdITCTT\"; color: rgb(222,222,222) }").arg(m_monthLabel->objectName()));
    m_monthLabel->setWordWrap(false);
    m_monthLabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    m_monthLabel->setText(months[currentMonth()].toUpper());

    QPushButton *buttonLeft = new QPushButton(centralWidget);
    buttonLeft->setObjectName("buttonLeft");
    buttonLeft->setGeometry(0, 0, 54, 54);
    buttonLeft->setText("");
    buttonLeft->setFlat(true);
    buttonLeft->setStyleSheet(QString("QPushButton#buttonLeft { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonLeft, SIGNAL(clicked()), this, SLOT(backMonthPressed()));

    QPushButton *buttonRight = new QPushButton(centralWidget);
    buttonRight->setObjectName("buttonRight");
    buttonRight->setGeometry(306, 0, 54, 54);
    buttonRight->setText("");
    buttonRight->setFlat(true);
    buttonRight->setStyleSheet(QString("QPushButton#buttonRight { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonRight, SIGNAL(clicked()), this, SLOT(forwardMonthPressed()));

    m_calendarWidget = new CustomCalendarWidget(centralWidget);
    m_calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
    m_calendarWidget->setGeometry(QRect(5, 20, 350, 325));
    m_calendarWidget->setGridVisible(false);
    m_calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
    m_calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    m_calendarWidget->setNavigationBarVisible(true);
    m_calendarWidget->setDateEditEnabled(false);
    m_calendarWidget->setLocale(QLocale(QLocale::Spanish, QLocale::Argentina));
    m_calendarWidget->setAutoFillBackground(false);
    m_calendarWidget->setStyleSheet(QString("CustomCalendarWidget#calendarWidget { background-color: rgba(0,255,0,0); alternate-background-color: rgba(255, 255, 0, 0); selection-color: rgb(255, 255, 0); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    QTextCharFormat format;
    format.setForeground(QColor(190,190,190));
    format.setBackground(QColor(255,0,0,0));
    format.setFontCapitalization(QFont::AllLowercase);
    m_calendarWidget->setHeaderTextFormat(format);
    format.setForeground(QColor(150,150,150));
    format.setBackground(QColor(255,0,0,0));
    format.setFontPointSize(6);
    m_calendarWidget->setWeekdayTextFormat(Qt::Monday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Tuesday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Wednesday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Thursday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Friday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
    m_calendarWidget->setWeekdayTextFormat(Qt::Sunday, format);
    m_calendarWidget->setDateList(&GlobalDataObject::instance().datesExercisedList());
    connect(m_calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(dateSelected(QDate)));

    QWidget *labelTip = new QWidget(centralWidget);
    labelTip->setObjectName(QString().sprintf("labelTip%p", labelTip));
    labelTip->setGeometry(0, 375, 264, 26);
    labelTip->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/agenda_tip.png); }").arg(labelTip->objectName()));
    labelTip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

}

AgendaView::~AgendaView()
{

}

void AgendaView::backMonthPressed()
{
    setCurrentMonth(currentMonth() == AgendaView::Jan ? AgendaView::Dec : (Month)(currentMonth() - 1));
    m_monthLabel->setText(months[currentMonth()].toUpper());
    m_monthLabel->repaint();

}

void AgendaView::forwardMonthPressed()
{
    setCurrentMonth(currentMonth() == AgendaView::Dec ? AgendaView::Jan : (Month)(currentMonth() + 1));
    m_monthLabel->setText(months[currentMonth()].toUpper());
    m_monthLabel->repaint();

}

void AgendaView::dateSelected(const QDate &date)
{
    AgendaDetailView *agendaDetailView = new AgendaDetailView(date);
    navigationController()->pushView(agendaDetailView);
}
