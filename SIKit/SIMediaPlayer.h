//
//  SIMediaPlayer.h
//  SIMediaPlayer
//
//  Copyright 2010 Silicon Illusions. All rights reserved.
//

#ifndef SIMEDIAPLAYER_H
#define SIMEDIAPLAYER_H

#include "SIMediaKeyObserver.h"

#include <QObject>
#include <QLayout>
#include <QMutex>
#include <QMediaPlayer>

class QVideoWidget;

class SIMediaPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_currentMediaFile READ currentMediaFile WRITE setCurrentMediaFile FINAL)
    Q_PROPERTY(QString m_currentBackgroundMediaFile READ currentBackgroundMediaFile WRITE setCurrentBackgroundMediaFile FINAL)

public:
    static SIMediaPlayer &instance();
    virtual ~SIMediaPlayer();

    bool playAudioFileOnBackground(const QString &audioFile);
    bool playAudioFile(const QString &audioFile);
    bool playVideoFile(const QString &videoFile, bool fullScreen, QObject *layoutOrWidget = NULL);

    void stop();
    void stopAll();

    inline QString const &currentMediaFile() const { return m_currentMediaFile; }
    inline QString const &currentBackgroundMediaFile() const { return m_currentBackgroundMediaFile; }

    static bool videoIsPlaying;

    static QString errorToString(const int e);
    static QString statusToString(const int s);
    static QString stateToString(const int s);

signals:
    void reachedEndOfMedia();
    void reachedEndOfBackgroundMedia();

public slots:
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void mediaStateChanged(QMediaPlayer::State state);
    void mediaError(QMediaPlayer::Error error);
    void backgroundMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void backgroundMediaStateChanged(QMediaPlayer::State state);
    void backgroundMediaError(QMediaPlayer::Error error);

    void handleMediaKeyEvent(SIMediaKeyObserver::MediaKeys key);
    void handleAudioOutputChangedSignal(const QString &);

protected:
    inline void setCurrentMediaFile(const QString &mediaFile) { m_currentMediaFile = mediaFile; }
    inline void setCurrentBackgroundMediaFile(const QString &mediaFile) { m_currentBackgroundMediaFile = mediaFile; }

private:
    SIMediaPlayer();
    SIMediaPlayer(SIMediaPlayer const &) {}
    SIMediaPlayer &operator =(SIMediaPlayer const &);

    SIMediaKeyObserver *m_mediaKeysObserver;

    void resetVideoWidget();

    QMediaPlayer *m_mediaBackgroundPlayer;
    QMediaPlayer *m_mediaPlayer;
    QVideoWidget *m_videoWidget;

    QString m_currentBackgroundMediaFile;
    QString m_currentMediaFile;

    bool previousFullScreenState;

    QMutex mutex;

};

#endif // SIMEDIAPLAYER_H
