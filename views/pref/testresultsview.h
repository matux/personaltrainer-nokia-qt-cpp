#ifndef TESTRESULTSVIEW_H
#define TESTRESULTSVIEW_H

#include <SIKit/SIKit.h>

class HeaderView;

class TestResultsView : public SIView
{
    Q_OBJECT
public:
    explicit TestResultsView(QWidget *parent = 0);
    virtual ~TestResultsView();

    inline void setHeaderView(HeaderView *headerView) { m_headerView = headerView; }

signals:

public slots:
    void okButtonPressed();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    HeaderView *m_headerView;

};

#endif // TESTRESULTSVIEW_H
