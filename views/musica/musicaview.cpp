#include "musicaview.h"

MusicaView::MusicaView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("MusicaView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { image: url(:/images/res/musica_base.png); background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    m_listWidget = new QListWidget(centralWidget);
    m_listWidget->setObjectName("listWidget");
    m_listWidget->setGeometry(QRect(25, 80, 310, 346));
    m_listWidget->setFrameShape(QFrame::NoFrame);
    m_listWidget->setFrameShadow(QFrame::Plain);
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listWidget->setProperty("showDropIndicator", QVariant(false));
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWidget->setStyleSheet(QString("QListWidget#listWidget { color: rgb(222, 222, 222); font: 75 19px \"AvantGardeMdITCTT\"; }"));
    m_listWidget->setSpacing(3);
    connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(songSelected(QListWidgetItem *)));

    m_fileFound = new QLabel(centralWidget);
    m_fileFound->setObjectName(QString().sprintf("m_fileFound%p", m_fileFound));
    m_fileFound->setGeometry(0, 223, 360, 24);
    m_fileFound->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_fileFound->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_fileFound->setText("Buscando Canciones...");
    m_fileFound->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    m_fileFound->setStyleSheet(QString("QLabel#%1 { background-color: rgba(255,0,0,0); color: rgb(222, 222, 222); font: 75 18px \"AvantGardeMdITCTT\"; }").arg(m_fileFound->objectName()));

    m_fileScanner = new SIFileScanner("e:/", QStringList() << "*.mp3" << "*.wav" << "*.aac" << "*.wma" << "*.ac3", QStringList() << "PersonalTrainer", this);
    //m_fileScanner = new SIFileScanner("e:/Music", QStringList("*"), this);
    connect(m_fileScanner, SIGNAL(fileCountChanged(int)), this, SLOT(fileCountChanged(int)));
    connect(m_fileScanner, SIGNAL(finishedScanning(int)), this, SLOT(finishedScanning(int)));

    m_currentSongRow = 0;
    connect(&SIMediaPlayer::instance(), SIGNAL(reachedEndOfBackgroundMedia()), this, SLOT(reachedEndOfMedia()));

}

MusicaView::~MusicaView()
{

}

void MusicaView::showEvent(QShowEvent *)
{
    m_listWidget->clear();
    if( !m_fileScanner->isScanning() )
        m_fileScanner->start();

}

void MusicaView::hideEvent(QHideEvent *)
{

}

void MusicaView::songSelected(QListWidgetItem *pItem)
{
    m_currentSongRow = m_listWidget->currentRow();
    const QString &fileName = m_fileScanner->fileList().at(m_currentSongRow);

    SIMediaPlayer::instance().playAudioFileOnBackground(fileName);

    qDebug("%d - %s", m_currentSongRow, fileName.toAscii().constData());

}

void MusicaView::fileCountChanged(int c)
{
    m_fileFound->setText(QString().sprintf("%d canciones encontradas.", c));
}

void MusicaView::finishedScanning(int c)
{
    m_fileFound->hide();
    QStringListIterator it(m_fileScanner->fileList());
    while( it.hasNext() )
    {
        QListWidgetItem *newItem = new QListWidgetItem(m_listWidget);
        newItem->setText(QFileInfo(it.next()).baseName());
        m_listWidget->addItem(newItem);
    }

}

void MusicaView::reachedEndOfMedia()
{
    m_currentSongRow++;
    if( m_currentSongRow >= m_fileScanner->fileList().count() )
        m_currentSongRow = 0;

    const QString &fileName = m_fileScanner->fileList().at(m_currentSongRow);
    SIMediaPlayer::instance().playAudioFileOnBackground(fileName);

    qDebug("%d - %s", m_currentSongRow, fileName.toAscii().constData());

}
