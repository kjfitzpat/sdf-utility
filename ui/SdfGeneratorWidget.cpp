#include "SdfGeneratorWidget.h"

#include<qopenglshaderprogram>
#include<qopengltexture>
SdfGeneratorWidget::SdfGeneratorWidget(QWidget* parent)
: QOpenGLWidget(parent),
  mSdfGenerateShader(0)
{

}

SdfGeneratorWidget::~SdfGeneratorWidget() 
{
	makeCurrent();
	mVertexBuffer.destroy();
	delete mSdfGenerateShader;
	doneCurrent();
}

void SdfGeneratorWidget::setTexture(QPixmap* source) 
{
	if (!source) {
		return;
	}
	if (mSourceOpenGLTexture) {
		delete mSourceOpenGLTexture;
	}
	mSourceOpenGLTexture = new QOpenGLTexture(source->toImage().mirrored());
}

void SdfGeneratorWidget::initializeGL() 
{
	initializeOpenGLFunctions();

	static const int mVertexCoords[4][3] = {
		{ +1, -1, -1 },{ -1, -1, -1 },{ -1, +1, -1 },{ +1, +1, -1 }
	};

	QVector<GLfloat> vertexData;
	for (int i = 0; i < 4; i++) {
		vertexData.append(mVertexCoords[i][0]);
		vertexData.append(mVertexCoords[i][1]);
		vertexData.append(mVertexCoords[i][2]);

		vertexData.append(i == 0 || i == 3);
		vertexData.append(i == 0 || i == 1);
	}
	mVertexBuffer = QOpenGLBuffer();
	mVertexBuffer.create();
	mVertexBuffer.bind();
	mVertexBuffer.allocate(vertexData.constData(), vertexData.count() * sizeof(GLfloat));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute highp vec4 vertex;\n"
		"attribute mediump vec4 texCoord;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = matrix * vertex;\n"
		"    texc = texCoord;\n"
		"}\n";
	vertexShader->compileSourceCode(vsrc);

	QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		"uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture, texc.st);\n"
		"}\n";
	fragmentShader->compileSourceCode(fsrc);
	
	mSdfGenerateShader = new QOpenGLShaderProgram();
	mSdfGenerateShader->addShader(vertexShader);
	mSdfGenerateShader->addShader(fragmentShader);
	mSdfGenerateShader->bindAttributeLocation("vertex", 0);
	mSdfGenerateShader->bindAttributeLocation("texCoord", 1);
	mSdfGenerateShader->link();
	mSdfGenerateShader->bind();
	mSdfGenerateShader->setUniformValue("texture", 0);


}

void SdfGeneratorWidget::paintGL() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	QMatrix4x4 m;
	m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 0.1f, 15.0f);
	m.translate(0.0f, 0.0f, -10.0f);

	mSdfGenerateShader->setUniformValue("matrix", m);
	mSdfGenerateShader->enableAttributeArray(0);
	mSdfGenerateShader->enableAttributeArray(1);
	mSdfGenerateShader->setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
	mSdfGenerateShader->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

	if (mSourceOpenGLTexture) {
		mSourceOpenGLTexture->bind();
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void SdfGeneratorWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);
}