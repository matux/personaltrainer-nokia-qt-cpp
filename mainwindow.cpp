#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "views/legalview.h"
#include "views/headerview.h"
#include "views/rutina/rutinaview.h"
#include "views/trainer/trainerview.h"
#include "views/agenda/agendaview.h"
#include "views/musica/musicaview.h"
#include "views/pref/prefview.h"
#include "views/pref/formview.h"
#include "views/mainmenuview.h"
#include "views/gpslegalview.h"
#include "model/globaldataobject.h"
#include "model/network/network.h"
#include "model/routines/routinemanager.h"
#include "model/exercises/exercisemanager.h"
#include "model/location/geodistancecalc.h"
#include "model/network/network.h"
#include "constants.h"

#include <iostream>
#include <QtGui>
#include <QTimer>

static MainWindow *m_mainWindowInstance = NULL;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    m_appInitialized = false;

    m_mainWindowInstance = this;

    if( objectName().isEmpty() )
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(QApplication::desktop()->width(), QApplication::desktop()->height());

    // Central Widget
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString("centralWidget"));

    // Intro
    introView = new SIView(centralWidget);
    introView->setBackgroundImage(QString(":/images/res/intro.png"));
    connect(introView, SIGNAL(viewWillAppear()), this, SLOT(introViewAppeared()));

    setCentralWidget(centralWidget);

    qDebug("MainWindow::Done setting up");

    introTimer = new QTimer();
    introTimer->setInterval(5000);
    introTimer->setSingleShot(true);
    introTimer->start();
    connect(introTimer, SIGNAL(timeout()), this, SLOT(introTimerTimeout()));

    qDebug("MainWindow::Intro Timer created");
    qDebug("MainWindow::Screen = %d, %d", QApplication::desktop()->width(), QApplication::desktop()->height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initApp()
{
    m_appInitialized = true;

    // load our settings
    GlobalDataObject::instance().setForceReset(false);
    GlobalDataObject::instance().loadApplicationSettings();
    //GlobalDataObject::instance().setFirstTimeRun(true);
    connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));

    // Start GPS
    GeoDistanceCalc::instance();
    connect(&GeoDistanceCalc::instance(), SIGNAL(acquisitionTimedout()), this, SLOT(gpsAcquisitionTimedout()));
    connect(&GeoDistanceCalc::instance(), SIGNAL(gpsAcquired()), this, SLOT(gpsAcquired()));
    //Network::instanceA().initialize();

    // Load Exercises
    ExerciseManager::instance().load();

    // Load Routines
    RoutineManager::instance().load();

    legalView = new LegalView(centralWidget);
    legalView->hide();

    qDebug("MainWindow::Legal View created");

    tabBarView = new SITabBar(centralWidget);
    tabBarView->setBackgroundImage(":/images/res/barra_inferior_base.png");
    tabBarView->setBarItemSize(QSize(70, 74));
    tabBarView->setUserInteractionEnabled(true);
    tabBarView->layout()->setContentsMargins(0, 17, 0, 0);
    tabBarView->setDefaultHeaderImage(":/images/res/header.png");
    connect(tabBarView, SIGNAL(selectionChanged(int)), this, SLOT(tabBarSelectionChanged(int)));
    tabBarView->hide();

    qDebug("MainWindow::Tab Bar View created");

    // Add Tab Bar buttons
    // First Tab
    SITabBarItem &b0 = tabBarView->addTabBarButton();
    b0.setIcon(":/images/res/barra_inferior_rutina.png");
    b0.setIconSelected(":/images/res/barra_inferior_rutina_on.png");
    headerViews[0] = new HeaderView(QString(":/images/res/header_titulo_rutina.png"), b0.associatedNavigationController()->navigationBarPtr());
    headerViews[0]->setNavigationController(b0.associatedNavigationController());
    connect(headerViews[0], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    // Second Tab
    SITabBarItem &b1 = tabBarView->addTabBarButton();
    b1.setIcon(":/images/res/barra_inferior_trainer.png");
    b1.setIconSelected(":/images/res/barra_inferior_trainer_on.png");
    // Attach our own header view to the navigation bar
    headerViews[1] = new HeaderView(QString(":/images/res/header_titulo_trainer.png"), b1.associatedNavigationController()->navigationBarPtr());
    headerViews[1]->setNavigationController(b1.associatedNavigationController());
    connect(headerViews[1], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    // Third Tab
    SITabBarItem &b2 = tabBarView->addTabBarButton();
    b2.setIcon(":/images/res/barra_inferior_agenda.png");
    b2.setIconSelected(":/images/res/barra_inferior_agenda_on.png");
    // Attach our own header view to the navigation bar
    headerViews[2] = new HeaderView(QString(":/images/res/header_titulo_agenda.png"), b2.associatedNavigationController()->navigationBarPtr());
    headerViews[2]->setNavigationController(b2.associatedNavigationController());
    connect(headerViews[2], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    // Fourth Tab
    SITabBarItem &b3 = tabBarView->addTabBarButton();
    b3.setIcon(":/images/res/barra_inferior_musica.png");
    b3.setIconSelected(":/images/res/barra_inferior_musica_on.png");
    // Attach our own header view to the navigation bar
    headerViews[3] = new HeaderView(QString(":/images/res/header_titulo_musica.png"), b3.associatedNavigationController()->navigationBarPtr());
    headerViews[3]->setNavigationController(b3.associatedNavigationController());
    connect(headerViews[3], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    // Fifth Tab
    SITabBarItem &b4 = tabBarView->addTabBarButton();
    b4.setIcon(":/images/res/barra_inferior_pref.png");
    b4.setIconSelected(":/images/res/barra_inferior_pref_on.png");
    // Attach our own header view to the navigation bar
    headerViews[4] = new HeaderView(QString(":/images/res/header_titulo_pref.png"), b4.associatedNavigationController()->navigationBarPtr());
    headerViews[4]->setNavigationController(b4.associatedNavigationController());
    connect(headerViews[4], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    // Sixth Tab (HIDDEN)
    SITabBarItem *b5 = &tabBarView->addTabBarButton(true);
    // Attach our own header view to the navigation bar
    headerViews[5] = new HeaderView(QString(":/images/res/header_titulo_miperfil.png"), b5->associatedNavigationController()->navigationBarPtr());
    headerViews[5]->setNavigationController(b5->associatedNavigationController());
    connect(headerViews[5], SIGNAL(homePressed()), this, SLOT(homeButtonPressed()));

    FormView *formView = new FormView();
    formView->setHeaderView(headerViews[5]);
    b5->associatedNavigationController()->pushView(formView);

    // Create the Root views
    RutinaView *rutinaView = new RutinaView();
    b0.associatedNavigationController()->addView(rutinaView);
    TrainerView *trainerView = new TrainerView();
    b1.associatedNavigationController()->addView(trainerView);
    AgendaView *agendaView = new AgendaView();
    b2.associatedNavigationController()->addView(agendaView);
    MusicaView *musicaView = new MusicaView();
    b3.associatedNavigationController()->addView(musicaView);
    PrefView *prefView = new PrefView();
    b4.associatedNavigationController()->addView(prefView);

    // Create the Main Menu
    mainMenuView = new MainMenuView(centralWidget);
    connect(mainMenuView, SIGNAL(menuButtonPressed(int)), this, SLOT(mainMenuButtonPressed(int)));
    mainMenuView->hide();

    // Create GPS legal
    gpsLegalView = new GPSLegalView(centralWidget);
    gpsLegalView->hide();

}

void MainWindow::introViewAppeared()
{
    if( !m_appInitialized )
        initApp();
}

void MainWindow::introTimerTimeout()
{
    qDebug("MainWindow::introTimerTimeout");
    //introTimer->stop();
    delete introTimer;
    introView->setParent(NULL);
    delete introView;
    qDebug("MainWindow::introTimerTimeout ... done");

    legalView->show();
    connect(legalView, SIGNAL(videoFinishedPlaying()), this, SLOT(introVideoFinished()));

}

void MainWindow::introVideoFinished()
{
    qDebug("MainWindow::introVideoFinished()");

    delete legalView;

    if( GlobalDataObject::instance().firstTimeRun() )
    {
        MainWindow::instanceA()->headerViewAt(5)->homeButton().setHidden(true);
        tabBarView->setSelectedIndex(5);
        tabBarView->show();
    }
    else
    {
        // Start
        homeButtonPressed();
    }

}

void MainWindow::homeButtonPressed()
{
    qDebug("MainWindow::homeButtonPressed()");
    /*if( tabBarView->selectedIndex() == 5 )
    {
        mainMenuButtonPressed(4);
    }
    else
    {*/
        tabBarView->hide();
        mainMenuView->show();
    //}
}

void MainWindow::mainMenuButtonPressed(int i)
{
    qDebug("MainWindow:mainMenuButtonPressed(%d)", i);
    mainMenuView->hide();
    tabBarView->setSelectedIndex(i);
    tabBarView->show();

}

void MainWindow::tabBarSelectionChanged(int i)
{
    if( i != 0 )
        tabBarView->navigationControllerAtTab(i)->showViewAtIndex(0);
}

void MainWindow::paintEvent(QPaintEvent *paintEvent)
{

}

void MainWindow::hideEvent(QHideEvent *event)
{
    qDebug("MainWindow::hideEvent!!!!!!!");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug("MainWindow::closeEvent");
    event->accept();

}

bool MainWindow::event(QEvent *event)
{
    QWindowStateChangeEvent *windowEvent = dynamic_cast<QWindowStateChangeEvent *>(event);
    if( windowEvent )
    {
        qDebug("MainWindow::QWindowStateChangeEvent");
        event->ignore();
        return QMainWindow::event(event);
    }
    else
    {
        event->ignore();
        return QMainWindow::event(event);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug("Key pressed: %d, %d, %d, %d", event->key(), event->nativeModifiers(), event->nativeScanCode(), event->nativeVirtualKey());

    event->ignore();
    QMainWindow::keyPressEvent(event);

}

void MainWindow::aboutToQuit()
{
    qDebug("MainWindow::aboutToQuit");

    GlobalDataObject::instance().saveApplicationSettings();
    SIMediaPlayer::instance().stopAll();
    GeoDistanceCalc::instance().stop();

    delete &SIMediaPlayer::instance();
    delete &Network::instanceA();

    close();

    QCoreApplication::quit();
}

void MainWindow::gpsAcquired()
{
    qDebug("void MainWindow::gpsAcquired()");
    gpsLegalView->hide();
}

void MainWindow::gpsAcquisitionTimedout()
{
    qDebug("void MainWindow::gpsAcquisitionTimedout()");
    gpsLegalView->show();
}

MainWindow *MainWindow::instanceA()
{
    return m_mainWindowInstance;
}

