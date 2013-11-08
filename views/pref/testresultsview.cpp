#include "testresultsview.h"
#include "views/headerview.h"
#include "model/routines/routinemanager.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "model/routines/plan.h"
#include "model/network/network.h"
#include "views/mainmenuview.h"
#include "mainwindow.h"

TestResultsView::TestResultsView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("TestResultsView%p", this));

    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName(QString().sprintf("%p", m_centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    m_centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(m_centralWidget->objectName()));
    m_centralWidget->resize(size());
    m_centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    m_centralWidget->setMinimumWidth(QApplication::desktop()->width());
    m_centralWidget->setMinimumHeight(436);

    QLabel *labelTest = new QLabel(m_centralWidget);
    labelTest->setObjectName(QString().sprintf("resultLabel%p", labelTest));
    labelTest->resize(200, 15);
    labelTest->move(30, 5);
    labelTest->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelTest->setText("RESULTADOS");
    labelTest->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 20px \"AvantGardeMdITCTT\"; }").arg(labelTest->objectName()));

    QWidget *infoBaseWidget = new QWidget(m_centralWidget);
    infoBaseWidget->setObjectName(QString().sprintf("infoResultados%p", infoBaseWidget));
    infoBaseWidget->setGeometry(0, 80, 360, 303);
    infoBaseWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/test_resultado_base.png); }").arg(infoBaseWidget->objectName()));
    infoBaseWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *labelPlan = new QLabel(m_centralWidget);
    labelPlan->setObjectName(QString().sprintf("resultLabelPlan%p", labelPlan));
    labelPlan->resize(200, 26);
    labelPlan->move(58, 123);
    labelPlan->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelPlan->setText("PLAN");
    labelPlan->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 26px \"AvantGardeMdITCTT\"; }").arg(labelPlan->objectName()));

    QLabel *labelNivel = new QLabel(m_centralWidget);
    labelNivel->setObjectName(QString().sprintf("resultLabelNivel%p", labelNivel));
    labelNivel->resize(200, 26);
    labelNivel->move(58, 242);
    labelNivel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelNivel->setText("NIVEL");
    labelNivel->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 26px \"AvantGardeMdITCTT\"; }").arg(labelNivel->objectName()));

    // Plan Desc actual text
    int obj = GlobalDataObject::instance().userInfo().objectiveIndex();
    const QString &planDesc = RoutineManager::instance().plans()[obj]->name().toUpper();

    QLabel *labelPlanDesc = new QLabel(m_centralWidget);
    labelPlanDesc->setObjectName(QString().sprintf("resultLabelPlanDesc%p", labelPlanDesc));
    labelPlanDesc->resize(300, 30);
    labelPlanDesc->move(33, 180);
    labelPlanDesc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelPlanDesc->setAlignment(Qt::AlignHCenter);
    labelPlanDesc->setText(planDesc);
    labelPlanDesc->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 26px \"AvantGardeMdITCTT\"; }").arg(labelPlanDesc->objectName()));

    QLabel *labelNivelDesc = new QLabel(m_centralWidget);
    labelNivelDesc->setObjectName(QString().sprintf("resultLabelNivelDesc%p", labelNivelDesc));
    labelNivelDesc->resize(300, 30);
    labelNivelDesc->move(33, 299);
    labelNivelDesc->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    labelNivelDesc->setAlignment(Qt::AlignHCenter);
    labelNivelDesc->setText(QString("NIVEL %1").arg(GlobalDataObject::instance().userInfo().levelStr().toUpper()));
    labelNivelDesc->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 26px \"AvantGardeMdITCTT\"; }").arg(labelNivelDesc->objectName()));

    SIButton *okButton = new SIButton(m_centralWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    okButton->setGeometry(QRect(0, 390, 360, 48));
    okButton->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    okButton->setText(QString::fromUtf8("ACEPTAR"));
    okButton->setNormalStatePix(":/images/res/legal_bot_aceptar.png");
    okButton->setPressedStatePix(":/images/res/legal_bot_aceptar_pressed.png");
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonPressed()));

}

TestResultsView::~TestResultsView()
{

}

void TestResultsView::okButtonPressed()
{
    // Sync log in
    //if( Network::instanceA().internetAvailable() )
    //    Network::instanceA().registerUser();

    navigationController()->tabBar()->setUserInteractionEnabled(true);
    MainWindow::instanceA()->headerViewAt(5)->homeButton().setHidden(false);

    //MainWindow::instanceA()->getTabBarView()->hide();
    //MainWindow::instanceA()->mainMenuView()->show();
    MainWindow::instanceA()->homeButtonPressed();

}

void TestResultsView::showEvent(QShowEvent *)
{
    MainWindow::instanceA()->headerViewAt(5)->backButton().setHidden(true);

    m_headerView->setTitleImageFilename(":/images/res/header_titulo_objetivo.png");
    m_headerView->repaint();

    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Test/tevoyasacarbueno.mp3"));
}

void TestResultsView::hideEvent(QHideEvent *)
{
    MainWindow::instanceA()->headerViewAt(5)->backButton().setHidden(false);
}
