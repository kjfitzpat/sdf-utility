#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SdfGeneratorWidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), 
  mUi(new Ui::MainWindow()) 
{
	mUi->setupUi(this);

	//initialize QGraphicsView instance for source image
	mSourceImageScene = new QGraphicsScene(this);
	mSourceImagePixmapItem = new QGraphicsPixmapItem();
	mSourceImageScene->addItem(mSourceImagePixmapItem);
	mUi->mSourceGraphicsView->setScene(mSourceImageScene);

	//initialize SdfGeneratorWidget
	mSdfGeneratorWidget = new SdfGeneratorWidget(this);
	mUi->mGeneratorContainer->layout()->addWidget(mSdfGeneratorWidget);

	//connect actions and buttons
	connect(mUi->mNewAction, &QAction::triggered, this, &MainWindow::mNewCommand);
	connect(mUi->mSaveAction, &QAction::triggered, this, &MainWindow::mSaveCommand);
	connect(mUi->mExitAction, &QAction::triggered, this, &MainWindow::mExitCommand);
	connect(mUi->mGenerateButton, &QAbstractButton::released, this, &MainWindow::mGenerateCommand);
}

MainWindow::~MainWindow() 
{
	delete mUi;
}

void MainWindow::mNewCommand() 
{
	QString str = QFileDialog::getOpenFileName(this, "Open Image", "C://", "Image File (*.jpg *.png)");
	
	if(str.isEmpty() || str.isNull()) {
		QMessageBox::warning(this, "File Error", "No file selected.");
		return;
	}

	if (!mSourceImagePixmap.load(str)) {
		QMessageBox::warning(this, "File Error", "Failed to load image.");
		return;
	}
	
	mSourceImagePixmapItem->setPixmap(mSourceImagePixmap);
	mUi->mSourceGraphicsView->fitInView(mSourceImagePixmapItem, Qt::AspectRatioMode::KeepAspectRatio);
	mSourceImageScene->setSceneRect(mSourceImageScene->itemsBoundingRect());
	mSdfGeneratorWidget->setTexture(&mSourceImagePixmap);
}

void MainWindow::mSaveCommand() {
	QMessageBox::warning(this, "SAVE", "Save");
}

void MainWindow::mGenerateCommand() {
	QMessageBox::warning(this, "GEN", "Generate");
}

void MainWindow::mExitCommand() {
	QMessageBox::warning(this, "EXIT", "Exit");
}