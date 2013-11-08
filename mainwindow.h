#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SIKit/SIKit.h>

namespace Ui {
    class MainWindow;
}

class LegalView;
class HeaderView;
class RutinaView;
class MainMenuView;
class GPSLegalView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow *instanceA();

    QWidget *centralWidget;
    inline SITabBar *getTabBarView() { return tabBarView; }
    inline MainMenuView *getMainMenuView() { return mainMenuView; }
    inline HeaderView *headerViewAt(int i) { return headerViews[i]; }

public slots:
    void homeButtonPressed();

    void gpsAcquired();
    void gpsAcquisitionTimedout();

private slots:
    void introViewAppeared();
    void tabBarSelectionChanged(int);
    void mainMenuButtonPressed(int);
    void introTimerTimeout();
    void introVideoFinished();

    void aboutToQuit();

    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *);

protected:
    void paintEvent(QPaintEvent *paintEvent);

private:
    void initApp();

    Ui::MainWindow *ui;

    SIView *introView;
    LegalView *legalView;

    // Actual Views
    HeaderView *headerViews[6];
    MainMenuView *mainMenuView;
    RutinaView *rutinaView;
    GPSLegalView *gpsLegalView;

    // Shared
    SITabBar *tabBarView;

    QTimer *genericTimer;
    QTimer *introTimer;

    bool m_appInitialized;
};

#endif // MAINWINDOW_H
