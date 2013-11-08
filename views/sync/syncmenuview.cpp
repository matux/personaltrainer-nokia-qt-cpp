#include "syncmenuview.h"
#include "synclegalview.h"
#include "syncview.h"

SyncMenuView::SyncMenuView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("SyncMenuView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(QApplication::desktop()->height());

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/sync_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(QApplication::desktop()->height());

    SIButton *verLegalButton = new SIButton(centralWidget);
    verLegalButton->setObjectName(QString().sprintf("verLegalButton%p", verLegalButton));
    verLegalButton->setGeometry(94, 398, 167, 54);
    verLegalButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    verLegalButton->setNormalStatePix(":/images/res/sync_boton_legal.png");
    verLegalButton->setPressedStatePix(":/images/res/sync_boton_legal_on.png");
    connect(verLegalButton, SIGNAL(clicked()), this, SLOT(showLegal()));

    SIButton *acceptButton = new SIButton(centralWidget);
    acceptButton->setObjectName(QString().sprintf("acceptButton%p", acceptButton));
    acceptButton->setGeometry(92, 465, 171, 52);
    acceptButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    acceptButton->setNormalStatePix(":/images/res/sync_boton_aceptar.png");
    acceptButton->setPressedStatePix(":/images/res/sync_boton_aceptar_on.png");
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptPressed()));

}

SyncMenuView::~SyncMenuView()
{

}

void SyncMenuView::showEvent(QShowEvent *)
{
    qDebug("SyncMenuView::showEvent");

    tabBar()->hideBar();
    navigationController()->hideBar();

}

void SyncMenuView::hideEvent(QHideEvent *)
{
    qDebug("SyncMenuView::hideEvent");

    tabBar()->showBar();
    navigationController()->showBar();

}


void SyncMenuView::showLegal()
{
    navigationController()->pushView(new SyncLegalView());
}

void SyncMenuView::acceptPressed()
{
    navigationController()->pushView(new SyncView());
}
