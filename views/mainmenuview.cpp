#include "mainmenuview.h"

#include <QtCore>
#include <QtGui>
#include <QUrl>

MainMenuView::MainMenuView(QWidget *parent)
    :QWidget(parent)
{
    setObjectName(QString::fromUtf8("mainMenu"));
    setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString("MainMenuCentralWidget"));
    centralWidget->setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));
    centralWidget->setStyleSheet(QString::fromUtf8("QWidget#MainMenuCentralWidget { background-image: url(:/images/res/menu_base_2.png); }"));

    // Rutina button
    m_rutinaButton = new SIButton(centralWidget);
    m_rutinaButton->setObjectName(QString::fromUtf8("rutinaButton"));
    m_rutinaButton->setGeometry(QRect(0, 295, geometry().width(), 33));
    m_rutinaButton->setNormalStatePix(":/images/res/menu_rutina.png");
    m_rutinaButton->setPressedStatePix(":/images/res/menu_rutina_on.png");
    m_rutinaButton->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    QObject::connect(m_rutinaButton, SIGNAL(clicked()), this, SLOT(rutinaButtonPressedSlot()));

    // Ejercicio button
    m_ejercicioButton = new SIButton(centralWidget);
    m_ejercicioButton->setObjectName(QString::fromUtf8("ejercicioButton"));
    m_ejercicioButton->setGeometry(QRect(0, 347, geometry().width(), 36));
    m_ejercicioButton->setNormalStatePix(":/images/res/menu_ejercicio.png");
    m_ejercicioButton->setPressedStatePix(":/images/res/menu_ejercicio_on.png");
    m_ejercicioButton->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    QObject::connect(m_ejercicioButton, SIGNAL(clicked()), this, SLOT(ejercicioButtonPressedSlot()));

    // Agenda button
    m_agendaButton = new SIButton(centralWidget);
    m_agendaButton->setObjectName(QString::fromUtf8("agendaButton"));
    m_agendaButton->setGeometry(QRect(0, 401, geometry().width(), 37));
    m_agendaButton->setNormalStatePix(":/images/res/menu_agenda.png");
    m_agendaButton->setPressedStatePix(":/images/res/menu_agenda_on.png");
    m_agendaButton->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    QObject::connect(m_agendaButton, SIGNAL(clicked()), this, SLOT(agendaButtonPressedSlot()));

    // Musica button
    m_musicaButton = new SIButton(centralWidget);
    m_musicaButton->setObjectName(QString::fromUtf8("musicaButton"));
    m_musicaButton->setGeometry(QRect(0, 455, geometry().width(), 36));
    m_musicaButton->setNormalStatePix(":/images/res/menu_musica.png");
    m_musicaButton->setPressedStatePix(":/images/res/menu_musica_on.png");
    m_musicaButton->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    QObject::connect(m_musicaButton, SIGNAL(clicked()), this, SLOT(musicaButtonPressedSlot()));

    // Preferencias button
    m_prefButton = new SIButton(centralWidget);
    m_prefButton->setObjectName(QString::fromUtf8("prefButton"));
    m_prefButton->setGeometry(QRect(0, 508, geometry().width(), 37));
    m_prefButton->setNormalStatePix(":/images/res/menu_preferencias.png");
    m_prefButton->setPressedStatePix(":/images/res/menu_preferencias_on.png");
    m_prefButton->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    QObject::connect(m_prefButton, SIGNAL(clicked()), this, SLOT(prefButtonPressedSlot()));

    didPlayIntro = false;

}

MainMenuView::~MainMenuView()
{

}

void MainMenuView::showEvent(QShowEvent *showEvent)
{
    qDebug("MainMenuView::showEvent");
    //if( !didPlayIntro ) {
    //    SIMediaPlayer::instance().playAudioFile("e:/Data/Others/PersonalTrainer/sfx_hola.mp3");
    //    didPlayIntro = true;
    //}

}

void MainMenuView::hideEvent(QHideEvent *hideEvent)
{

}

void MainMenuView::rutinaButtonPressedSlot()
{
    emit menuButtonPressed(0);
}

void MainMenuView::ejercicioButtonPressedSlot()
{
    emit menuButtonPressed(1);
}

void MainMenuView::agendaButtonPressedSlot()
{
    emit menuButtonPressed(2);
}

void MainMenuView::musicaButtonPressedSlot()
{
    emit menuButtonPressed(3);
}

void MainMenuView::prefButtonPressedSlot()
{
    emit menuButtonPressed(4);
}
