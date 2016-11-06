#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SvgView; //forward declare

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
	SvgView* mView;

private slots:
    void openLoadClick();
};

#endif // MAINWINDOW_H
