

#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Line.h"
#include <vector>
#include "Point2D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
signals:
    void shapeUpdate();
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();


private:
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    QVector<QVector2D> mPixelVertices;
    std::vector<float> baC;
    std::vector<float> heC;
    QVector<GLfloat> curveVertices;
    QVector<GLfloat> curveColors;

public:
    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;
    int gridSize;
    void bezierCurve(std::vector<Point2D> v);
    void hermiteCurve(std::vector<Point2D> v);
};