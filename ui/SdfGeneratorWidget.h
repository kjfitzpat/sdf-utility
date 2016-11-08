#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class QOpenGLShaderProgram;
class QOpenGLTexture;

class SdfGeneratorWidget : 	public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit SdfGeneratorWidget(QWidget* parent = 0);
	~SdfGeneratorWidget();
	void setTexture(QPixmap* source);

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

private:
		QOpenGLShaderProgram *mSdfGenerateShader;
		QOpenGLTexture *mSourceOpenGLTexture;
		QOpenGLBuffer mVertexBuffer;
};

