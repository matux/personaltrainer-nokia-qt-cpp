#include "trainerview.h"
#include "trainerdetailedview.h"

#include "model/exercises/exercise.h"
#include "model/exercises/exercisemanager.h"

TrainerView::TrainerView(QWidget *parent)
    :SIView(parent)
{
    setObjectName(QString().sprintf("TrainerView%p", parent));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString().sprintf("%p", centralWidget));

    resize(QApplication::desktop()->width(), 436);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumWidth(QApplication::desktop()->width());
    setMinimumHeight(436);

    centralWidget->setStyleSheet(QString("QWidget#%1 { background-image: url(:/images/res/fondo_base.png); }").arg(centralWidget->objectName()));
    centralWidget->resize(size());
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    centralWidget->setMinimumWidth(QApplication::desktop()->width());
    centralWidget->setMinimumHeight(436);

    // Create the List Widget
    QWidget *listContainer = new QWidget();
    listContainer->setObjectName(QString("exerciseListContainer"));
    listContainer->setGeometry(QRect(0, 0, 320, 2060));
    listContainer->setStyleSheet(QString("QWidget#exerciseListContainer { background-color: rgba(255, 0, 0, 0); }"));
    QListWidget *listWidget = new QListWidget(listContainer);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(15, 0, 310, 2060));
    listWidget->setFrameShape(QFrame::NoFrame);
    listWidget->setFrameShadow(QFrame::Plain);
    listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //listWidget->setProperty("showDropIndicator", QVariant(false));
    //listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listWidget->setSpacing(9);
    listWidget->setViewMode(QListView::ListMode);
    listWidget->setModelColumn(0);
    listWidget->setMovement(QListWidget::Static);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setStyleSheet(QString("QListWidget#listWidget { background-color: rgba(255, 0, 0, 0); selection-color: rgb(222, 222, 222); color: rgb(175, 175, 175); font: 75 18px \"AvantGardeMdITCTT\"; }"));
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(exerciseSelected(QListWidgetItem*)));

    // Create the Scrolling Area
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setObjectName(QString("trainerViewScrollArea"));
    scrollArea->setStyleSheet(QString("QScrollArea#trainerViewScrollArea { background-color: rgba(255, 0, 0, 0); }"));
    scrollArea->setWidgetResizable(false);
    scrollArea->setWidget(listContainer);
    scrollArea->setGeometry(QRect(0, 10, 350, 417));
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFont font(QString("AvantGardeMdITCTT"));
    font.setPixelSize(16);
    QFontMetrics fontMetrics(font);

    QPixmap sepImage(QString(":/images/res/ejercicios_linea_1.png"));
    int count = 0, magicNumber = 30;
    QList<Exercise *>::const_iterator exercise;
    for( exercise = ExerciseManager::instance().list().constBegin(); exercise != ExerciseManager::instance().list().constEnd(); ++exercise )
    {
        // Item
        new QListWidgetItem((*exercise)->name().toUpper(), listWidget);
        /*
        // Separator
        QWidget *sep = new QWidget(listContainer);
        sep->setObjectName(QString("exerciseSeparator%1").arg(count));
        if( (bool)(count & 0x1) )
            sep->setStyleSheet(QString("QWidget#%1 { background-color: rgba(255, 0, 0, 0); image: url(:/images/res/ejercicios_linea_2.png); }").arg(sep->objectName()));
        else
            sep->setStyleSheet(QString("QWidget#%1 { background-color: rgba(255, 0, 0, 0); image: url(:/images/res/ejercicios_linea_1.png); }").arg(sep->objectName()));
        int secretEquation = ((fontMetrics.height()+(magicNumber-fontMetrics.height()))+(listWidget->spacing()<<1));
        sep->setGeometry(36, (secretEquation - (secretEquation >> 3)) + (secretEquation * count), sepImage.width(), sepImage.height());
        */

        count++;

    }

    // A bug in QListWidgetItem? The last item will remain outside the scroll area
    new QListWidgetItem("", listWidget);

}

TrainerView::~TrainerView()
{

}

void TrainerView::initData()
{

}

void TrainerView::exerciseSelected(QListWidgetItem *item)
{
    navigationController()->removeViewAt(1);

    int row = item->listWidget()->row(item);
    Exercise *exercise = ExerciseManager::instance().list().at(row);
    navigationController()->pushView(new TrainerDetailedView(exercise, NULL));

}
