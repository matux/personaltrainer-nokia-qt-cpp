//
//  SIMediaPlayer.cpp
//  SIMediaPlayer
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#include "SIMediaPlayer.h"

#include "SILock.h"

#include <QtCore>
#include <QtGui>
#include <QVideoWidget>
#include <qmediaservice.h>
#include <qmediaplaylist.h>
#include <qaudioendpointselector.h>

static SIMediaPlayer *theInstance = NULL;
bool SIMediaPlayer::videoIsPlaying = false;

SIMediaPlayer &SIMediaPlayer::instance()
{
    if( !theInstance )
        theInstance = new SIMediaPlayer();
    return *theInstance;
}

SIMediaPlayer::SIMediaPlayer()
    :QObject(NULL)
{
    // Create our player
    m_mediaPlayer = new QMediaPlayer(this, 0, QMediaServiceProvider::defaultServiceProvider());
    m_mediaBackgroundPlayer = new QMediaPlayer(this, 0, QMediaServiceProvider::defaultServiceProvider());

    // Connect the signals to our slots
    connect(m_mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(m_mediaPlayer, SIGNAL(stateChanged      (QMediaPlayer::State)),       this, SLOT(mediaStateChanged (QMediaPlayer::State)));
    connect(m_mediaPlayer, SIGNAL(error             (QMediaPlayer::Error)),       this, SLOT(mediaError        (QMediaPlayer::Error)));
    connect(m_mediaBackgroundPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(backgroundMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(m_mediaBackgroundPlayer, SIGNAL(stateChanged      (QMediaPlayer::State)),       this, SLOT(backgroundMediaStateChanged (QMediaPlayer::State)));
    connect(m_mediaBackgroundPlayer, SIGNAL(error             (QMediaPlayer::Error)),       this, SLOT(backgroundMediaError        (QMediaPlayer::Error)));

    // Set some defaults
    m_mediaPlayer->setVolume(80);
    m_mediaPlayer->setMuted(false);
    m_mediaBackgroundPlayer->setVolume(80);
    m_mediaBackgroundPlayer->setMuted(false);
/*
    QMediaService *service = m_mediaPlayer->service();
    if( service )
    {
        QMediaControl *control = service->requestControl(QAudioEndpointSelector_iid);
        if( control )
        {
            audioEndpointSelector = qobject_cast<QAudioEndpointSelector*>(control);
            if( audioEndpointSelector )
            {
                connect(audioEndpointSelector, SIGNAL(activeEndpointChanged(const QString&)),
                        this, SLOT(handleAudioOutputChangedSignal(const QString&)));
            }
            else
            {
                service->releaseControl(control);
            }
        }
    }
*/
    m_mediaKeysObserver = new SIMediaKeyObserver(this);
    connect(m_mediaKeysObserver, SIGNAL(mediaKeyPressed(SIMediaKeyObserver::MediaKeys)), this, SLOT(handleMediaKeyEvent(SIMediaKeyObserver::MediaKeys)));

    // Create Video Widget
    m_videoWidget = new QVideoWidget();
    m_videoWidget->setObjectName("SIMediaPlayervideoWidget");
    m_videoWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_videoWidget->setAttribute(Qt::WA_OpaquePaintEvent);
    m_videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    //m_videoWidget->setFullScreen(false);

    // Assign our Video Widget to our Media Player
    m_mediaPlayer->setVideoOutput(m_videoWidget);

    videoIsPlaying = false;

}

SIMediaPlayer::~SIMediaPlayer()
{
    qDebug("Destroying SIMediaPlayer");

    stopAll();

    if( !m_videoWidget->parent() )
        delete m_videoWidget;

}

void SIMediaPlayer::stopAll()
{
    m_mediaBackgroundPlayer->stop();
    m_mediaPlayer->stop();

}

bool SIMediaPlayer::playAudioFileOnBackground(const QString &audioFile)
{
    qDebug("SIMediaPlayer::playAudioFileOnBackground(): %s", audioFile.toAscii().constData());
    bool ret = true;
    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::playAudioFileOnBackground(): %s - MUTEX LOCKED", audioFile.toAscii().constData());

        m_mediaPlayer->stop();
        if( m_mediaBackgroundPlayer->mediaStatus() == QMediaPlayer::LoadingMedia )
        {
            qDebug("Another media file is being loaded, aborting");
            ret = false;
        }
        else
        {
            if( QFile(audioFile).exists() )
            {
                if( audioFile.compare(currentBackgroundMediaFile()) == 0 && m_mediaBackgroundPlayer->state() == QMediaPlayer::PlayingState )
                    m_mediaBackgroundPlayer->stop();
                else
                {
                    setProperty("m_currentBackgroundMediaFile", QFile(audioFile).fileName());
                    // Load the Audio
                    m_mediaBackgroundPlayer->setMedia(QUrl::fromLocalFile(audioFile));
                    if( m_mediaBackgroundPlayer->mediaStatus() == QMediaPlayer::LoadedMedia ||
                        m_mediaBackgroundPlayer->mediaStatus() == QMediaPlayer::BufferedMedia ||
                        m_mediaBackgroundPlayer->mediaStatus() == QMediaPlayer::EndOfMedia )
                            m_mediaPlayer->play();
                }

                ret = true;
            }
            else
            {
                qDebug("SIMediaPlayer::playAudioFileOnBackground(): %s - ERROR: File does not exists.", audioFile.toAscii().constData());
                emit reachedEndOfMedia();
                ret = false;
            }
        }

        //qDebug("SIMediaPlayer::playAudioFileOnBackground(): %s - MUTEX UNLOCKED", audioFile.toAscii().constData());
    //}

    return ret;

}

bool SIMediaPlayer::playAudioFile(const QString &audioFile)
{
    qDebug("SIMediaPlayer::playAudioFile(): %s", audioFile.toAscii().constData());
    bool ret = true;
    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::playAudioFile(): %s - MUTEX LOCKED", audioFile.toAscii().constData());
        m_mediaPlayer->stop();
        if( m_mediaPlayer->mediaStatus() == QMediaPlayer::LoadingMedia )
        {
            qDebug("Another media file is being loaded, aborting");
            ret = false;
        }
        else
        {
            if( QFile(audioFile).exists() )
            {
                setProperty("m_currentMediaFile", QFile(audioFile).fileName());
                // Load the Audio
                m_mediaPlayer->setMedia(QUrl::fromLocalFile(audioFile));
                ret = true;
            }
            else
            {
                qDebug("SIMediaPlayer::playAudioFile(): %s - ERROR: File does not exists.", audioFile.toAscii().constData());
                emit reachedEndOfMedia();
                ret = false;
            }
        }

        //qDebug("SIMediaPlayer::playAudioFile(): %s - MUTEX UNLOCKED", audioFile.toAscii().constData());
    //}

    return ret;

}

bool SIMediaPlayer::playVideoFile(const QString &videoFile, bool fullScreen, QObject *layoutOrWidget)
{
    qDebug("SIMediaPlayer::playVideoFile(): %s", videoFile.toAscii().constData());
    bool ret = true;
    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::playVideoFile(): %s - MUTEX LOCKED", videoFile.toAscii().constData());

        //m_mediaPlayer->stop();
        if( m_mediaPlayer->mediaStatus() == QMediaPlayer::LoadingMedia )
        {
            qDebug("Another media file is being loaded, aborting");
            ret = false;
        }
        else
        {
            if( QFile(videoFile).exists() )
            {
                setProperty("m_currentMediaFile", QFile(videoFile).fileName());

                // Configure the video Widget
                if( layoutOrWidget )
                {
                    if( QLayout *layout = dynamic_cast<QLayout *>(layoutOrWidget) )
                    {
                        qDebug("SIMediaPlayer::playVideoFile():88 QObject is QLayout");
                        layout->addWidget(m_videoWidget);
                    }
                    else
                    {
                        qDebug("SIMediaPlayer::playVideoFile():93 QObject is QWidget");
                        m_videoWidget->setParent(dynamic_cast<QWidget *>(layoutOrWidget));
                    }
                }
                else
                {
                    qDebug("SIMediaPlayer::playVideoFile():99 QObject is NULL");
                    m_videoWidget->setParent(QApplication::activeWindow());
                }

                m_videoWidget->setFullScreen(fullScreen);
                m_videoWidget->show();

                // Load the video
                m_mediaPlayer->setMedia(QUrl::fromLocalFile(videoFile));

                ret = true;
            }
            else
            {
                qDebug("SIMediaPlayer::playVideoFile(): %s - ERROR: File does not exists.", videoFile.toAscii().constData());
                //resetVideoWidget();
                //emit reachedEndOfMedia();
                ret =  false;
            }
        }

        //qDebug("SIMediaPlayer::playVideoFile(): %s - MUTEX UNLOCKED", videoFile.toAscii().constData());
    //}

    return ret;

}

void SIMediaPlayer::stop()
{
    m_mediaPlayer->stop();
    resetVideoWidget();
}

void SIMediaPlayer::resetVideoWidget()
{
    qDebug("SIMediaPlayer::resetVideoWidget() - %s", currentMediaFile().toAscii().constData());

    videoIsPlaying = false;

    //m_videoWidget->setFullScreen(previousFullScreenState);
    setProperty("m_currentMediaFile", "");
    m_mediaPlayer->setMedia(QMediaContent());
    m_videoWidget->hide();
    m_videoWidget->setParent(NULL);
    delete m_videoWidget;

    // Recreate our video widget
    m_videoWidget = new QVideoWidget();
    m_videoWidget->setObjectName("SIMediaPlayervideoWidget");
    m_videoWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_videoWidget->setAttribute(Qt::WA_OpaquePaintEvent);
    m_videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    //m_videoWidget->setFullScreen(false);

    // Assign our Video Widget to our Media Player
    m_mediaPlayer->setVideoOutput(m_videoWidget);


}

/**
 * Slots
 *
 */
void SIMediaPlayer::mediaError(QMediaPlayer::Error error)
{
    qWarning("SIMediaPlayer::mediaError: %s (%s) - %s", m_mediaPlayer->errorString().toAscii().constData(), errorToString(m_mediaPlayer->error()).toAscii().constData(), currentMediaFile().toAscii().constData());
    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::mediaError(): %s - MUTEX LOCKED", currentMediaFile().toAscii().constData());

        if( error != QMediaPlayer::NoError )
        {
            // Reset our media widget
            resetVideoWidget();

            emit reachedEndOfMedia();
        }

        //qDebug("SIMediaPlayer::mediaError(): %s - MUTEX UNLOCKED", currentMediaFile().toAscii().constData());
    //}

}

void SIMediaPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug("%d SIMediaPlayer::mediaStatusChanged: %s", QThread::currentThreadId(), currentMediaFile().toAscii().constData());

    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::mediaStatusChanged(): %s - MUTEX LOCKED", currentMediaFile().toAscii().constData());

        switch( status )
        {
            case QMediaPlayer::LoadedMedia:
                qDebug("SIMediaPlayer::mediaStatusChanged: LoadedMedia! Playing... - %s", currentMediaFile().toAscii().constData());
                m_mediaPlayer->play();
                break;
            case QMediaPlayer::EndOfMedia:
                qDebug("SIMediaPlayer::mediaStatusChanged: EndOfMedia - %s", currentMediaFile().toAscii().constData());
                videoIsPlaying = false;
                emit reachedEndOfMedia();
                break;
            default:
                qDebug("SIMediaPlayer::mediaStatusChanged: %d (%s) - %s", status, statusToString(status).toAscii().constData(), currentMediaFile().toAscii().constData());
                break;

        }

        //qDebug("SIMediaPlayer::mediaStatusChanged(): %s - MUTEX UNLOCKED", currentMediaFile().toAscii().constData());
    //}

}

void SIMediaPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    qDebug("SIMediaPlayer::mediaStateChanged: %d (%s) - %s", state, stateToString(state).toAscii().constData(), currentMediaFile().toAscii().constData());

    //synchronized(mutex)
    //{
        //qDebug("SIMediaPlayer::mediaStateChanged(): %s - MUTEX LOCKED", currentMediaFile().toAscii().constData());

        if( state == QMediaPlayer::StoppedState )
            // Reset our media widget
            resetVideoWidget();
        else if( state == QMediaPlayer::PlayingState )
        {
            if( currentMediaFile().contains("intro.mp4") )
                videoIsPlaying = true;
        }

        //qDebug("SIMediaPlayer::mediaStateChanged(): %s - MUTEX UNLOCKED", currentMediaFile().toAscii().constData());
    //}
}

void SIMediaPlayer::backgroundMediaError(QMediaPlayer::Error error)
{
    //synchronized(mutex)
    //{
        Q_UNUSED(error);
        qWarning("SIMediaPlayer::backgroundMediaError: %s (%s) - %s", m_mediaBackgroundPlayer->errorString().toAscii().constData(), errorToString(m_mediaBackgroundPlayer->error()).toAscii().constData(), currentBackgroundMediaFile().toAscii().constData());
    //}
}

void SIMediaPlayer::backgroundMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    //synchronized(mutex)
    //{
        switch( status )
        {
            case QMediaPlayer::LoadedMedia:
                qDebug("SIMediaPlayer::backgroundMediaStatusChanged: LoadedMedia! Playing... - %s", currentBackgroundMediaFile().toAscii().constData());
                m_mediaBackgroundPlayer->play();
                break;
            case QMediaPlayer::EndOfMedia:
                qDebug("SIMediaPlayer::backgroundMediaStatusChanged: EndOfMedia - %s", currentBackgroundMediaFile().toAscii().constData());
                emit reachedEndOfBackgroundMedia();
                break;
            default:
                qDebug("SIMediaPlayer::backgroundMediaStatusChanged: %d (%s) - %s", status, statusToString(status).toAscii().constData(), currentBackgroundMediaFile().toAscii().constData());
                break;

        }
    //}
}

void SIMediaPlayer::backgroundMediaStateChanged(QMediaPlayer::State state)
{
    //synchronized(mutex)
    //{
        qDebug("SIMediaPlayer::backgroundMediaStateChanged: %d (%s) - %s", state, stateToString(state).toAscii().constData(), currentBackgroundMediaFile().toAscii().constData());
    //}
}

void SIMediaPlayer::handleAudioOutputChangedSignal(const QString&)
{
   /*QMessageBox msgBox;
   msgBox.setText("Output changed: " + audioEndpointSelector->activeEndpoint());
   msgBox.exec();*/
}

void SIMediaPlayer::handleMediaKeyEvent(SIMediaKeyObserver::MediaKeys key)
{
    switch( key )
    {
        case SIMediaKeyObserver::EVolIncKey:
            m_mediaBackgroundPlayer->setVolume(m_mediaBackgroundPlayer->volume() + 10);
            m_mediaPlayer->setVolume(m_mediaPlayer->volume() + 10);
            break;
        case SIMediaKeyObserver::EVolDecKey:
            m_mediaBackgroundPlayer->setVolume(m_mediaBackgroundPlayer->volume() - 10);
            m_mediaPlayer->setVolume(m_mediaPlayer->volume() + 10);
            break;
        default:
        break;
    }

}

/**
 * Helpers
 *
 */
QString SIMediaPlayer::errorToString(const int e)
{
    switch( e )
    {
    case 0: return "NoError";
    case 1: return "ResourceError";
    case 2: return "FormatError";
    case 3: return "NetworkError";
    case 4: return "AccessDeniedError";
    case 5: return "ServiceMissingError";
    default: return "UnknownError != 0";
    }

}

QString SIMediaPlayer::statusToString(const int s)
{
    switch( s )
    {
    case 0: return "UnknownMediaStatus";
    case 1: return "NoMedia";
    case 2: return "LoadingMedia";
    case 3: return "LoadedMedia";
    case 4: return "StalledMedia";
    case 5: return "BufferingMedia";
    case 6: return "BufferedMedia";
    case 7: return "EndOfMedia";
    case 8: return "InvalidMedia";
    default: return "UnknownMediaStatus != 0";
    }

}

QString SIMediaPlayer::stateToString(const int s)
{
    switch( s )
    {
    case 0: return "StoppedState";
    case 1: return "PlayingState";
    case 2: return "PausedState";
    default: return "Unknown != 0";
    }

}
