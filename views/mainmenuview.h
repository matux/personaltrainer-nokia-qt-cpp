#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QWidget>
#include <SIKit/SIKit.h>

#include <qmediaplayer.h>
#include <qmediaplaylist.h>

class MainMenuView : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuView(QWidget *parent = 0);
    virtual ~MainMenuView();

signals:
    void menuButtonPressed(int);

private slots:
    void rutinaButtonPressedSlot();
    void ejercicioButtonPressedSlot();
    void agendaButtonPressedSlot();
    void musicaButtonPressedSlot();
    void prefButtonPressedSlot();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    bool didPlayIntro;

    SIButton *m_rutinaButton;
    SIButton *m_ejercicioButton;
    SIButton *m_agendaButton;
    SIButton *m_musicaButton;
    SIButton *m_prefButton;

};

#endif // MAINMENUVIEW_H
