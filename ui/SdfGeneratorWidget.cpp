#include "SdfGeneratorWidget.h"

SdfGeneratorWidget::SdfGeneratorWidget(QWidget* parent)
: QOpenGLWidget(parent)
{

}

SdfGeneratorWidget::~SdfGeneratorWidget() 
{
	makeCurrent();
}

void SdfGeneratorWidget::initializeGL() 
{
	initializeOpenGLFunctions();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	//TODO create and upload shaders
}

void SdfGeneratorWidget::paintGL() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SdfGeneratorWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);
}