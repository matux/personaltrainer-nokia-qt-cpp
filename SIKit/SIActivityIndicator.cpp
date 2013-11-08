#include "SIActivityIndicator.h"

#include <QVBoxLayout>

SIActivityIndicator::SIActivityIndicator(const QString &animationPath, QWidget *parent)
    :SIView(parent)
{
    init(animationPath, QSize());
}

SIActivityIndicator::SIActivityIndicator(const QString &animationPath, QSize size, QWidget *parent)
    :SIView(parent)
{
    init(animationPath, size);
}


SIActivityIndicator::~SIActivityIndicator()
{
    m_container->deleteLater();
    m_animation->deleteLater();
}

void SIActivityIndicator::init(const QString &animationPath, const QSize &size)
{
    // We'll create the QMovie for the animation
    m_animation = new QMovie(animationPath);
    QSize s = size;
    // If the size is empty we'll try to detect it.
    if( s.isEmpty() )
    {
        // Go to the first frame
        m_animation->jumpToNextFrame();
        // Take the size from there
        s = m_animation->currentPixmap().size();
        // Go back to the beginning
        m_animation->jumpToFrame(0);
    }
    // We're not automatically shown, so lets hide.
    setHidden(true);
    // We need a container for the QMovie, let's use QLabel
    m_container = new QLabel(this);

    // We'll set a fixed size to the QLabel
    // because we don't want to be resized

    m_container->setFixedSize(s);
    // To get the movie displayed on the QLabel
    m_container->setMovie(m_animation);
    // To get the QLabel displayed we'll use a layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    // Remove the all the extra space.
    layout->setSpacing(0);
    layout->setMargin(0);
    // Add the movie container to the layout
    layout->addWidget(m_container);
    // Set the layout as our layout
    setLayout(layout);
    // Set our size fixed.
    setFixedSize(s);

}

void SIActivityIndicator::start()
{
    // Let's check if the movie can be started.
    if( !m_animation.isNull() &&
        (m_animation->state() == QMovie::NotRunning ||
         m_animation->state() == QMovie::Paused))
    {
        // It can so we'll start the animation...
        m_animation->start();
        // ...and reveal ourself
        setHidden(false);
    }

}

void SIActivityIndicator::stop()
{
    // Check if the animation can be stopped.
    if( !m_animation.isNull() )
    {
        if( m_animation->state() == QMovie::Running )
        {
            // It can so we'll stop the animation...
            m_animation->stop();
            // ...and hide.
            setHidden(true);
        }

    }

}
