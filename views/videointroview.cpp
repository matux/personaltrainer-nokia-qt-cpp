#include "videointroview.h"

VideoIntroView::VideoIntroView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString::fromUtf8("legalView"));
    setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));

    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName(QString("LegalViewCentralWidget"));
    m_centralWidget->setGeometry(QRect(0, 0, QApplication::desktop()->width(), QApplication::desktop()->height()));
    //m_centralWidget->setStyleSheet(QString::fromUtf8("QWidget#LegalViewCentralWidget { background-image: url(:/images/res/legal_base.png); }"));

    // Connect the media player to us
    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(introVideoEnded()));

}

VideoIntroView::~VideoIntroView()
{

}

void VideoIntroView::introVideoEnded()
{
    // Keeping this connection could be dangerous
    disconnect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfMedia()), this, SLOT(introVideoEnded()));

    //emit videoFinishedPlaying();

}
