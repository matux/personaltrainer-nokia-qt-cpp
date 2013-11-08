#include "prefview.h"
#include "formview.h"
#include "formobjectiveview.h"
#include "views/sync/syncmenuview.h"
#include "mainwindow.h"

PrefView::PrefView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("PrefView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); image: url(:/images/res/preferencias_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    QPushButton *buttonObjetivo = new QPushButton(centralWidget);
    buttonObjetivo->setObjectName("buttonObjetivo");
    buttonObjetivo->setGeometry(15, 35, 334, 65);
    buttonObjetivo->setText("CAMBIAR OBJETIVO");
    buttonObjetivo->setFlat(true);
    buttonObjetivo->setStyleSheet(QString("QPushButton#buttonObjetivo { text-align:left; margin-left:40px; background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonObjetivo, SIGNAL(clicked()), this, SLOT(objetivoPressed()));

    QPushButton *buttonNuevoUser = new QPushButton(centralWidget);
    buttonNuevoUser->setObjectName("buttonNuevoUser");
    buttonNuevoUser->setGeometry(15, 120, 334, 65);
    buttonNuevoUser->setText("GENERAR NUEVO USUARIO");
    buttonNuevoUser->setFlat(true);
    buttonNuevoUser->setStyleSheet(QString("QPushButton#buttonNuevoUser { text-align:left; margin-left:40px; background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonNuevoUser, SIGNAL(clicked()), this, SLOT(nuevoUsuarioPressed()));

    QPushButton *buttonSincro = new QPushButton(centralWidget);
    buttonSincro->setObjectName("buttonSincro");
    buttonSincro->setGeometry(15, 203, 334, 65);
    buttonSincro->setText("SINCRONIZAR DATOS");
    buttonSincro->setFlat(true);
    buttonSincro->setStyleSheet(QString("QPushButton#buttonSincro { text-align:left; margin-left:40px; background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonSincro, SIGNAL(clicked()), this, SLOT(sincroDatosPressed()));

    QPushButton *buttonIntro = new QPushButton(centralWidget);
    buttonIntro->setObjectName("buttonIntro");
    buttonIntro->setGeometry(15, 288, 334, 65);
    buttonIntro->setText("SALUDO INICIAL");
    buttonIntro->setFlat(true);
    buttonIntro->setStyleSheet(QString("QPushButton#buttonIntro { text-align:left; margin-left:40px; background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }"));
    connect(buttonIntro, SIGNAL(clicked()), this, SLOT(videoIntroPressed()));

}

PrefView::~PrefView()
{

}

void PrefView::objetivoPressed()
{
    // Create the new Form
    FormObjectiveView *formObjectiveView = new FormObjectiveView();
    formObjectiveView->setProcessOnlyForm(true);
    formObjectiveView->setHeaderView(MainWindow::instanceA()->headerViewAt(5));
    // Reset the navigation controller and push the new Form
    SINavigationController *navController = MainWindow::instanceA()->getTabBarView()->navigationControllerAtTab(5);
    navController->removeViewsInCascadeFrom(0);
    navController->pushView(formObjectiveView);
    // Show it
    MainWindow::instanceA()->getTabBarView()->setSelectedIndex(5);
    MainWindow::instanceA()->getTabBarView()->show();

}

void PrefView::nuevoUsuarioPressed()
{
    // Create the new Form
    FormView *formView = new FormView();
    formView->setProcessOnlyForm(true);
    formView->setHeaderView(MainWindow::instanceA()->headerViewAt(5));
    // Reset the navigation controller and push the new Form
    SINavigationController *navController = MainWindow::instanceA()->getTabBarView()->navigationControllerAtTab(5);
    navController->removeViewsInCascadeFrom(0);
    navController->pushView(formView);
    // Show it
    MainWindow::instanceA()->getTabBarView()->setSelectedIndex(5);
    MainWindow::instanceA()->getTabBarView()->show();

}

void PrefView::sincroDatosPressed()
{
    navigationController()->pushView(new SyncMenuView());

}

void PrefView::videoIntroPressed()
{
    // Connect the media player to us
    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(videoEnded()));

#ifdef Q_OS_SYMBIAN
        CAknAppUi *appUi = dynamic_cast<CAknAppUi *>(CEikonEnv::Static()->AppUi());
        appUi->SetOrientationL(CAknAppUi::EAppUiOrientationLandscape);
#endif

    if( !SIMediaPlayer::instance().playVideoFile("e:/Data/Others/PersonalTrainer/intro.mp4", true, NULL) )
        videoEnded();

}

void PrefView::videoEnded()
{
    // Keeping this connection could be dangerous
    disconnect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(videoEnded()));

#ifdef Q_OS_SYMBIAN
    CAknAppUi *appUi = dynamic_cast<CAknAppUi *>(CEikonEnv::Static()->AppUi());
    appUi->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait);
#endif

}
