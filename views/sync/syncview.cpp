#include "syncview.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "model/planinfo.h"
#include "model/network/network.h"

SyncView::SyncView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("SyncView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(QApplication::desktop()->height());

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/sync_base2.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(QApplication::desktop()->height());

    QWidget *syncTextWidget = new QWidget(centralWidget);
    syncTextWidget->setObjectName(QString().sprintf("syncTextWidget%p", syncTextWidget));
    syncTextWidget->setGeometry(62, 200, 237, 34);
    syncTextWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/sync_txt.png); }").arg(syncTextWidget->objectName()));
    syncTextWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
/*
    SIButton *skipButton = new SIButton(centralWidget);
    skipButton->setObjectName(QString().sprintf("skipButton%p", skipButton));
    skipButton->setGeometry(150, 565, 171, 52);
    skipButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    skipButton->setNormalStatePix(":/images/res/test_skip.png");
    skipButton->setPressedStatePix(":/images/res/test_skip_on.png");
    connect(skipButton, SIGNAL(clicked()), this, SLOT(skipPressed()));
*/
    SIActivityIndicator *spinner = new SIActivityIndicator(":/images/res/general_spinner.gif", centralWidget);
    spinner->move(164, 334);
    spinner->start();
/*
    QTimer *timer = new QTimer();
    timer->setInterval(60000);
    timer->setSingleShot(true);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutSync()));
*/

    connect(&Network::instanceA(), SIGNAL(finished()), this, SLOT(skipPressed()));

}

SyncView::~SyncView()
{

}

void SyncView::showEvent(QShowEvent *)
{
    qDebug("SyncView::showEvent");

    tabBar()->hideBar();
    navigationController()->hideBar();

    int planId = GlobalDataObject::instance().userInfo().objectiveIndex();

    if( GlobalDataObject::instance().userRegistered() )
    {
        qDebug("SyncView::showEvent(): USER IS REGISTERED");
        if( !GlobalDataObject::instance().planInfo(planId).isEmpty() && Network::instanceA().internetAvailable() )
        {
            qDebug("SyncView::showEvent(): PLAN INFORMATION AVAILABLE FOR SYNC");
            Network::instanceA().syncUser();
        }
        else
        {
            qDebug("SyncView::showEvent(): NO PLAN INFORMATION AVAILABLE FOR SYNC");
            showMessage("Tu usuario y rutinas ya fueron sincronizados! Sincronizá luego de haber terminado más rutinas.");
            QTimer *timer = new QTimer();
            timer->setInterval(1500);
            timer->setSingleShot(true);
            timer->start();
            connect(timer, SIGNAL(timeout()), this, SLOT(skipPressed()));
        }
    }
    else
    {
        if( GlobalDataObject::instance().planInfo(planId).isEmpty() && Network::instanceA().internetAvailable() )
        {
            qDebug("SyncView::showEvent(): NO PLAN INFORMATION AVAILABLE FOR SYNC - REGISTRATION ONLY");
            Network::instanceA().registerUser();
        }
        else
        {
            qDebug("SyncView::showEvent(): PLAN INFORMATION AVAILABLE FOR SYNC - REGISTRATION AND SYNC");
            Network::instanceA().registerAndSync();
        }
    }

}

void SyncView::hideEvent(QHideEvent *)
{
    qDebug("SyncView::hideEvent");

    tabBar()->showBar();
    navigationController()->showBar();

}

void SyncView::skipPressed()
{
    navigationController()->popToRootView();
}

void SyncView::showMessage(const QString &msg)
{
#ifdef _SIMULATOR_BUILD
        qWarning("\n>>>>>>>>>>>>>>>>>> %s\n", msg.toAscii().constData());
#else
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
#endif

}
