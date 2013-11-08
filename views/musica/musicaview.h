#ifndef MUSICAVIEW_H
#define MUSICAVIEW_H

#include <SIKit/SIKit.h>

class MusicaView : public SIView
{
    Q_OBJECT
public:
    explicit MusicaView(QWidget *parent = 0);
    virtual ~MusicaView();

signals:

public slots:
    void songSelected(QListWidgetItem *);
    void fileCountChanged(int);
    void finishedScanning(int);

private slots:
    void reachedEndOfMedia();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    void lookForAudioFiles();

    int m_currentSongRow;
    SIFileScanner *m_fileScanner;
    bool m_searching;
    QListWidget *m_listWidget;
    QLabel *m_fileFound;

};

#endif // MUSICAVIEW_H
