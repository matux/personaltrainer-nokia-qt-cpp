#ifndef TRAINERVIEW_H
#define TRAINERVIEW_H

#include <SIKit/SIKit.h>

class TrainerView : public SIView
{
    Q_OBJECT
public:
    explicit TrainerView(QWidget *parent = 0);
    virtual ~TrainerView();

signals:

private slots:
    void exerciseSelected(QListWidgetItem *);

protected:
    virtual void initData();

private:

};

#endif // TRAINERVIEW_H
