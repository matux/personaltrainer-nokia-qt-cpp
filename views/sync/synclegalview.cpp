#include "synclegalview.h"
#include "syncview.h"

SyncLegalView::SyncLegalView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("SyncLegalView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(QApplication::desktop()->height());

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/sync_legal.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(QApplication::desktop()->height());

    QString legalText("Por el solo hecho de sincronizar mis datos personales con el sitio web www.fordpersonaltrainer.com.ar, consiento que dichos datos sean tratados y utilizados por Ford Argentina S.C.A (en adelante Ford). Cuyo domicilio es Av. De Mayo 651, Ciudad de Buenos Aires, para los fines de la presente actividad promocional, así como también para realizar en el futuro campañas publicitarias y/o de marketing tendientes a mantenerme actualizado sobre nuevos productos, promociones y/o distintos servicios que ofrezca por sí, o a través de terceras personas como: A) Su red oficial de concesionarios y/o de eventos y/o de promociones. B) Con empresas que le provean cualquier tipo de servicios informáticos y/o archivo de información electrónica y/o física. C) Empresas que operen su centro de asistencia al cliente. D) Plan Ovalo S.A de ahorro para fines determinados, Ford Crecit compañía financiera S.A. y/o cualquier otra empresa que ofrezca líneas de crédito o financiación para su gama de productos. E) Empresas relacionadas o vinculadas a Ford. Autorizo expresamente que las empresas referidas en los puntos A) a E) puedan localizar mis datos tanto en Argentina como en terceros países. Por otra parte, acepto el compromiso de Ford de que incluirá en sus acuerdos con estas empresas la obligación de respetar las disposiciones en materia de protección de datos personales vigentes en Argentina, así como también las políticas de Ford en materia de protección de la privacidad, seguridad y confidencialidad de la información. Por último, declaro conocer y aceptar que para actualizar y/o modificar y/o pedir la supresión de los mencionados datos podré comunicarme al 0800-888-FORD (3673)");

    QTextBrowser *textBrowser = new QTextBrowser(centralWidget);
    textBrowser->setObjectName(QString().sprintf("textBrowser%p", textBrowser));
    textBrowser->setGeometry(QRect(22, 222, 320, 264));
    textBrowser->setFrameShape(QFrame::Panel);
    textBrowser->setFrameShadow(QFrame::Raised);
    textBrowser->setLineWidth(2);
    textBrowser->setContentsMargins(40, 40, 40, 40);
    textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setStyleSheet(QString::fromUtf8("QTextBrowser#%1 { background-color: rgba(255,0,0,0); font: 75 16px \"AvantGardeMdITCTT\"; color: rgb(222,222,222) }").arg(textBrowser->objectName()));
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
            "</html>").arg(legalText));

    SIButton *acceptButton = new SIButton(centralWidget);
    acceptButton->setObjectName(QString().sprintf("acceptButton%p", acceptButton));
    acceptButton->setGeometry(114, 553, 126, 48);
    acceptButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    acceptButton->setNormalStatePix(":/images/res/legal_bot_aceptar.png");
    acceptButton->setPressedStatePix(":/images/res/legal_bot_aceptar_pressed.png");
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptPressed()));

}

SyncLegalView::~SyncLegalView()
{

}

void SyncLegalView::showEvent(QShowEvent *)
{
    qDebug("SyncLegalView::showEvent");

    tabBar()->hideBar();
    navigationController()->hideBar();

}

void SyncLegalView::hideEvent(QHideEvent *)
{
    qDebug("SyncLegalView::hideEvent");

    tabBar()->showBar();
    navigationController()->showBar();

}

void SyncLegalView::acceptPressed()
{
    navigationController()->pushView(new SyncView());
}
