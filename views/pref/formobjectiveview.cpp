#include "formobjectiveview.h"
#include "model/globaldataobject.h"
#include "model/userinfo.h"
#include "views/pref/testview.h"
#include "views/headerview.h"
#include "mainwindow.h"

static FormObjectiveView *m_instance = NULL;

FormObjectiveView *FormObjectiveView::instanceA()
{
    return m_instance;
}

FormObjectiveView::FormObjectiveView(QWidget *parent)
    :SIView(parent),
    m_headerView(NULL),
    objOne(NULL), objTwo(NULL), objThree(NULL), objFour(NULL)
{
    m_processOnlyForm = false;

    setObjectName(QString().sprintf("FormObjectiveView%p", parent));

    // Create UI
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

    QWidget *layoutContainer = new QWidget(centralWidget);
    layoutContainer->setObjectName("formLayoutContainer");
    layoutContainer->setStyleSheet(QString("QWidget#formLayoutContainer { background-color: rgba(255,0,0,0); }"));
    //layoutContainer->resize(QApplication::desktop()->width(), 800);
    layoutContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layoutContainer->setMinimumWidth(QApplication::desktop()->width());
    layoutContainer->setMinimumHeight(436);

    QVBoxLayout *formLayout = new QVBoxLayout(layoutContainer);
    formLayout->setSpacing(0);
    formLayout->setContentsMargins(12, 4, 0, 0);

    formLayout->addItem(new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum));

    QLabel *label = new QLabel(centralWidget);
    label->setObjectName(QString().sprintf("FormLabel%p", label));
    label->resize(300, 15);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label->setText("SELECCIONE UN OBJETIVO");
    label->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 19px \"AvantGardeMdITCTT\"; }").arg(label->objectName()));
    formLayout->addWidget(label);

    formLayout->addItem(new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum));

    objOne   = addSwitchButton(formLayout, "formulario_objetivo_perdida", centralWidget);
    objTwo   = addSwitchButton(formLayout, "formulario_objetivo_defmusc", centralWidget);
    objThree = addSwitchButton(formLayout, "formulario_objetivo_running", centralWidget);
    objFour  = addSwitchButton(formLayout, "formulario_objetivo_antistress", centralWidget);

    connect(objOne, SIGNAL(stateSwitched()), this, SLOT(objOneSwitched()));
    connect(objTwo, SIGNAL(stateSwitched()), this, SLOT(objTwoSwitched()));
    connect(objThree, SIGNAL(stateSwitched()), this, SLOT(objThreeSwitched()));
    connect(objFour, SIGNAL(stateSwitched()), this, SLOT(objFourSwitched()));

    objOne->setState(SISwitchButton::ON);

    formLayout->addItem(new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Minimum));

    SIButton *okButton = new SIButton(centralWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    okButton->setGeometry(0, 0, 340, 48);
    okButton->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    okButton->setNormalStatePix(":/images/res/formulario_boton_siguiente.png");
    okButton->setPressedStatePix(":/images/res/formulario_boton_siguiente_on.png");
    connect(okButton, SIGNAL(clicked()), this, SLOT(pressedOk()));
    formLayout->addWidget(okButton);

    m_instance = this;
}

FormObjectiveView::~FormObjectiveView()
{

}

void FormObjectiveView::showEvent(QShowEvent *)
{
    navigationController()->tabBar()->setUserInteractionEnabled(m_processOnlyForm);

    m_headerView->backButton().setHidden(false);
    m_headerView->homeButton().setHidden(true);
    m_headerView->setTitleImageFilename(":/images/res/header_titulo_miperfil.png");
    m_headerView->repaint();

    switch( GlobalDataObject::instance().userInfo().objectiveIndex() )
    {
    case 0: objOneSwitched(); break;
    case 1: objTwoSwitched(); break;
    case 2: objThreeSwitched(); break;
    case 3: objFourSwitched(); break;
    default:
        objOneSwitched(); break;
    }

}

void FormObjectiveView::objOneSwitched()
{
    //connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));
    //SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/Planes/plan0.mp3");

    objOne->setState(SISwitchButton::ON);
    objTwo->setState(SISwitchButton::OFF);
    objThree->setState(SISwitchButton::OFF);
    objFour->setState(SISwitchButton::OFF);

    objOne->repaint();
    objTwo->repaint();
    objThree->repaint();
    objFour->repaint();

}

void FormObjectiveView::objTwoSwitched()
{
    //connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));
    //SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/Planes/plan1.mp3");

    objOne->setState(SISwitchButton::OFF);
    objTwo->setState(SISwitchButton::ON);
    objThree->setState(SISwitchButton::OFF);
    objFour->setState(SISwitchButton::OFF);

    objOne->repaint();
    objTwo->repaint();
    objThree->repaint();
    objFour->repaint();

}

void FormObjectiveView::objThreeSwitched()
{
    //connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));
    //SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/Planes/plan2.mp3");

    objOne->setState(SISwitchButton::OFF);
    objTwo->setState(SISwitchButton::OFF);
    objThree->setState(SISwitchButton::ON);
    objFour->setState(SISwitchButton::OFF);

    objOne->repaint();
    objTwo->repaint();
    objThree->repaint();
    objFour->repaint();

}

void FormObjectiveView::objFourSwitched()
{
    //connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));
    //SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/Planes/plan3.mp3");

    objOne->setState(SISwitchButton::OFF);
    objTwo->setState(SISwitchButton::OFF);
    objThree->setState(SISwitchButton::OFF);
    objFour->setState(SISwitchButton::ON);

    objOne->repaint();
    objTwo->repaint();
    objThree->repaint();
    objFour->repaint();

}

void FormObjectiveView::reachedEndOfMedia()
{
    disconnect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(reachedEndOfMedia()));

    // Set up
    QString genre = GlobalDataObject::instance().userInfo().gender() == UserInfo::G_MALE ? "m" : "f";
    int plan = 0;
    if( objTwo->state() == SISwitchButton::ON ) plan = 1;
    else if( objThree->state() == SISwitchButton::ON ) plan = 2;
    else if( objFour->state() == SISwitchButton::ON ) plan = 3;
    int r = rand() % 2;
    if( plan == 0 && (genre.compare("f") == 0) )
        r = rand() % 3;

    // play
    SIMediaPlayer::instance().playAudioFile(QString("e:/Data/Others/PersonalTrainer/Planes/plan%1-%2%3.mp3").arg(plan).arg(genre).arg(r));

}

SISwitchButton *FormObjectiveView::addSwitchButton(QVBoxLayout *formLayout, const QString &buttonPixName, QWidget *parent)
{
    SISwitchButton *switchButton = new SISwitchButton(parent);
    switchButton->setObjectName(QString("okButton%1").arg(buttonPixName));
    switchButton->setNormalStatePix(QString(":/images/res/%1.png").arg(buttonPixName));
    switchButton->setPressedStatePix(QString(":/images/res/%1_on.png").arg(buttonPixName));
    switchButton->setGeometry(0, 0, 340, 48);
    switchButton->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    formLayout->addWidget(switchButton);

    return switchButton;

}

void FormObjectiveView::pressedOk()
{
    //GlobalDataObject::instance().userInfo().setCurrentRoutineNumber(0);

    if( objOne->state() == SISwitchButton::ON )
        GlobalDataObject::instance().userInfo().setObjectiveIndex(0);
    else if( objTwo->state() == SISwitchButton::ON )
        GlobalDataObject::instance().userInfo().setObjectiveIndex(1);
    else if( objThree->state() == SISwitchButton::ON )
        GlobalDataObject::instance().userInfo().setObjectiveIndex(2);
    else if( objFour->state() == SISwitchButton::ON )
        GlobalDataObject::instance().userInfo().setObjectiveIndex(3);

    if( m_processOnlyForm )
    {
        MainWindow::instanceA()->getTabBarView()->setUserInteractionEnabled(true);
        m_processOnlyForm = false;
        MainWindow::instanceA()->getTabBarView()->setSelectedIndex(4);

        GlobalDataObject::instance().saveApplicationSettings();
    }
    else
    {
        // push next view
        TestView *testView = new TestView();
        testView->setHeaderView(m_headerView);
        navigationController()->pushView(testView);
    }

}
