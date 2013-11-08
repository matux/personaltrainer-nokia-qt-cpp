#include "SIFileScanner.h"

SIFileScanner::SIFileScanner(const QString &path, const QStringList &nameFilters, const QStringList &exceptionDirs, QObject *parent)
    :QThread(parent),
    m_iterator(path,
                nameFilters,
                QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks,
                QDirIterator::Subdirectories),
    m_exceptionDir(exceptionDirs),
    m_stopped(false)
{

}

void SIFileScanner::run()
{
    qDebug("SIFileScanner::run()");

    m_scanning = true;

    while( !m_stopped && m_iterator.hasNext() )
    {
        bool skip = false;
        QString entry(m_iterator.next());
        for( int i = 0; i < m_exceptionDir.count(); ++i )
        {
            if( entry.contains(m_exceptionDir.at(i)) )
            {
                skip = true;
                break;
            }
        }
        if( !skip )
        {
            m_fileList << entry;
            emit fileCountChanged(m_fileList.count());
        }

    }

    if( !m_stopped )
        emit finishedScanning(m_fileList.count());

    m_scanning = false;

    qDebug("SIFileScanner::run() DONE");
}

QStringList const &SIFileScanner::fileList()
{
    synchronize(m_mutex);
    return m_fileList;

}

bool SIFileScanner::isScanning()
{
    synchronize(m_mutex);
    return m_scanning;

}
