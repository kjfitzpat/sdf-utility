#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "svgview.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), 
  mUi(new Ui::MainWindow() ) 
{
    mUi->setupUi(this);
	mView = new SvgView();
	//mUi->mRenderParent->layout()->addWidget(mView);
    //hook up load button click to open function
    //connect(mUi->mActionLoadGraphic, SIGNAL(triggered(bool)), this, SLOT(openLoadClick()));
}

MainWindow::~MainWindow() 
{
    delete mUi;
}

void MainWindow::openLoadClick() 
{
    QString str = QFileDialog::getOpenFileName(this, "Open SVG", "C://", "SVG (*.svg)");
	if(str.isEmpty()){
		QMessageBox::warning(this, "File error", "No file selected.");
	} else {
		if(mView->openFile(str)) {
			return;
		} else {
			QMessageBox::warning(this, "File error", "Could not load SVG.");
		}
	}
}
