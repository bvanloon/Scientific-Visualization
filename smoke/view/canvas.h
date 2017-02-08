#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Canvas(QWidget* parent);
    ~Canvas();

public slots:

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    //Shaders
    QOpenGLShaderProgram *shaderProgram;

    //Buffers
    QOpenGLBuffer *vertexBuffer;
    QOpenGLBuffer *colorBuffer;
    QOpenGLBuffer *indexBuffer;
    QOpenGLVertexArrayObject vao;

    bool isAllocated(QOpenGLBuffer *buffer);

    // OpenGL initialization
    void initializeShaders();
    void initializeBuffers();
    void initializeVertexBuffer(QOpenGLBuffer *buffer, GLint layoutPosition, GLint elementDimension, GLenum elementType);
    void initializeIndexBuffer(QOpenGLBuffer* buffer);

    // OpenGL update
    int numIndices;
    int numVertices;
    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

    // Transformation variables;
    QMatrix4x4 mvpMatrix;
    QMatrix3x3 normalMatrix;
    QVector3D rotationAngles;
    float zoomingFactor;
    void constructModelViewProjectionMatrix();
    void updateTransformationMatrix();

    //Uniforms
    void setUniforms();

    //Temporary, model
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
};

#endif // CANVAS_H
