#include "trainerdetailedview.h"
#include "mainwindow.h"
#include "views/headerview.h"
#include "model/exercises/exercise.h"

TrainerDetailedView::TrainerDetailedView(QWidget *parent)
    :SIView(parent),
     m_exercise(NULL)
{
    initUi();
}

TrainerDetailedView::TrainerDetailedView(Exercise *exercise, QWidget *parent)
    :SIView(parent),
     m_exercise(exercise)
{
    initUi();
}

TrainerDetailedView::~TrainerDetailedView()
{

}

void TrainerDetailedView::initUi()
{
    setObjectName(QString().sprintf("TrainerDetailedView%p", this));

    //m_centralWidget = new QWidget(this);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    if( m_exercise )
        initDetail(centralWidget);

}

void TrainerDetailedView::initDetail(QWidget *centralWidget)
{
    QWidget *figure = new QWidget(centralWidget);
    figure->setObjectName(QString().sprintf("figure%p", figure));
    figure->setGeometry(0, 0, 360, 154);
    QString styleSheet(QString("QWidget#%1 { image: url(:/images/res/%2); }").arg(figure->objectName()).arg(m_exercise->figureFilename()));
    figure->setStyleSheet(styleSheet);
    figure->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget *infoBaseWidget = new QWidget(centralWidget);
    infoBaseWidget->setObjectName(QString().sprintf("info%p", infoBaseWidget));
    infoBaseWidget->setGeometry(0, 154, 360, 319);
    infoBaseWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/ejercicios_detalle_base.png); }").arg(infoBaseWidget->objectName()));
    infoBaseWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *title = new QLabel(infoBaseWidget);
    title->setObjectName(QString().sprintf("title%p", title));
    title->setGeometry(QRect(35, 0, 325, 99));
    title->setStyleSheet(QString::fromUtf8("QLabel#%1 { font: 75 20px \"AvantGardeMdITCTT\"; color: rgb(199,199,199) }").arg(title->objectName()));
    title->setWordWrap(true);
    title->setText(m_exercise->name().toUpper());

    QWidget *infoLineaWidget = new QWidget(centralWidget);
    infoLineaWidget->setObjectName(QString().sprintf("info%p", infoLineaWidget));
    infoLineaWidget->setGeometry(0, 100, 360, 319);
    infoLineaWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/ejercicios_detalle_linea.png); }").arg(infoLineaWidget->objectName()));
    infoLineaWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QTextBrowser *textBrowser = new QTextBrowser(centralWidget);
    textBrowser->setObjectName(QString().sprintf("textBrowser%p", textBrowser));
    textBrowser->setGeometry(QRect(35, 290, 295, 135));
    textBrowser->setFrameShape(QFrame::NoFrame);
    textBrowser->setFrameShadow(QFrame::Plain);
    textBrowser->setLineWidth(0);
    textBrowser->setContentsMargins(40, 40, 40, 40);
    textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setStyleSheet(QString::fromUtf8("QTextBrowser#%1 { background-color: rgba(255,0,0,0); font: 75 16px \"AvantGardeMdITCTT\"; color: rgb(199,199,199) }").arg(textBrowser->objectName()));
    textBrowser->setHtml(QString(
            "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
            "<html>"
            "<head>"
            "<meta name=\"qrichtext\" content=\"1\" />"
            "<style type=\"text/css\">\n"
                "p, li { white-space: pre-wrap; }\n"
            "</style>"
            "</head>"
            "<body>\n"
            "<p>%1</p>"
            "</body>"
            "</html>").arg(m_exercise->description()));

}

void TrainerDetailedView::showEvent(QShowEvent *)
{
    MainWindow::instanceA()->headerViewAt(0)->setUserInteractionEnabled(true);
    //SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Ejercicios/%1.mp3").arg(m_exercise->id()));
}
