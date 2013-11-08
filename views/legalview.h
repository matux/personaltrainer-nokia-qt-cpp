#ifndef LEGALVIEW_H
#define LEGALVIEW_H

#include <SIKit/SIKit.h>

class QLabel;
class QTextBrowser;
class SIMediaPlayer;

class LegalView : public QWidget
{
    Q_OBJECT
public:
    explicit LegalView(QWidget *parent = 0);
    virtual ~LegalView();

    inline SIButton const *okButton() const { return m_okButton; }

signals:
    void videoFinishedPlaying();

private slots:
    void okButtonPressed();
    void introVideoEnded();

private:
    QWidget *m_centralWidget;

    SIButton *m_okButton;
    QLabel *m_labelTitle;
    QTextBrowser *m_legalText;

};

#endif // LEGALVIEW_H
