#include "legalview.h"
#include "model/globaldataobject.h"

#include <QtCore>
#include <QtGui>

#include <qvideowidget.h>

// Needed Symbian specific headers
#ifdef Q_OS_SYMBIAN
#include <eikenv.h>
#include <eikappui.h>
#include <aknenv.h>
#include <aknappui.h>
#endif

LegalView::LegalView(QWidget *parent) :
    QWidget(parent)
{
    setObjectName(QString::fromUtf8("legalView"));
    setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));

    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName(QString("LegalViewCentralWidget"));
    m_centralWidget->setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));
    m_centralWidget->setStyleSheet(QString::fromUtf8("QWidget#LegalViewCentralWidget { background-image: url(:/images/res/legal_base.png); }"));

    m_okButton = new SIButton(m_centralWidget);
    m_okButton->setObjectName(QString::fromUtf8("okButton"));
    m_okButton->setGeometry(QRect(118, 565, 126, 48));
    m_okButton->setText(QString::fromUtf8("ACEPTAR"));
    m_okButton->setNormalStatePix(":/images/res/legal_bot_aceptar.png");
    m_okButton->setPressedStatePix(":/images/res/legal_bot_aceptar_pressed.png");
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(okButtonPressed()));

    // Connect the media player to us
    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(introVideoEnded()));

}

LegalView::~LegalView()
{

}

void LegalView::okButtonPressed()
{
    if( GlobalDataObject::instance().firstTimeRun() )
    {
        m_centralWidget->hide();
#ifdef Q_OS_SYMBIAN
        CAknAppUi *appUi = dynamic_cast<CAknAppUi *>(CEikonEnv::Static()->AppUi());
        appUi->SetOrientationL(CAknAppUi::EAppUiOrientationLandscape);
#endif

        if( !SIMediaPlayer::instance().playVideoFile("e:/Data/Others/PersonalTrainer/intro.mp4", true, NULL) )
            introVideoEnded();
    }
    else
        introVideoEnded();

}

void LegalView::introVideoEnded()
{
    // Keeping this connection could be dangerous
    disconnect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(introVideoEnded()));

#ifdef Q_OS_SYMBIAN
    CAknAppUi *appUi = dynamic_cast<CAknAppUi *>(CEikonEnv::Static()->AppUi());
    appUi->SetOrientationL(CAknAppUi::EAppUiOrientationPortrait);
#endif

    emit videoFinishedPlaying();

}
