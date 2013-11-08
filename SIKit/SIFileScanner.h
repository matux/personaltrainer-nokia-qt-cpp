#ifndef SIFILESCANNER_H
#define SIFILESCANNER_H

#include <QtCore>
#include <SIKit/SILock.h>

class SIFileScanner : public QThread
{
    Q_OBJECT
public:
    explicit SIFileScanner(const QString &path, const QStringList &nameFilters, const QStringList &exceptionDirs, QObject *parent = NULL);

    void run();

    QStringList const &fileList();
    bool isScanning();

signals:
    void fileCountChanged(int);
    void finishedScanning(int);

public slots:
    void stop() { m_stopped = true; }

private:
    QDirIterator m_iterator;
    QStringList m_fileList;
    QStringList m_exceptionDir;
    bool m_scanning;
    bool m_stopped;

    QMutex m_mutex;
};

#endif // SIFILESCANNER_H
