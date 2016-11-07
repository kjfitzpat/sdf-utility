#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsPixmapItem;
class SdfGeneratorWidget;
class QVBoxLayout;

namespace Ui {
    class MainWindow; 
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *mUi;
    QPixmap mSourceImagePixmap;
    QGraphicsScene* mSourceImageScene;
    QGraphicsPixmapItem* mSourceImagePixmapItem;
    SdfGeneratorWidget* mSdfGeneratorWidget;

private slots:
    void mNewCommand();
    void mSaveCommand();
    void mGenerateCommand();
    void mExitCommand();
};

#endif // MAINWINDOW_H
