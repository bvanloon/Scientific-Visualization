#ifndef ABSTRACTENGINE_H
#define ABSTRACTENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QObject>
#include <QOpenGLWidget>
#include <QMatrix4x4>

#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"

class AbstractEngine : protected QOpenGLFunctions
{
public:
    AbstractEngine();
    virtual ~AbstractEngine();
    virtual void draw(Simulation* Simulation) = 0;

    void setProjectionMatrix(float width, float height, float nearClippingPlane, float farClippingplane);
    void setMVPMatrix();

    void setTexture(QImage image);
    void setColorMapValueRange(float min, float max);
    void setColorMapClampRange(float startClamp, float endClamp);
    void setColorMapClampingTo(bool clampingOn);


protected:
    //Shaders
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLTexture *texture;


    //Buffers
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer* vertexBuffer;
    QOpenGLBuffer* textureCoordinateBuffer;


    void init();

    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);
    void drawWithMode(Simulation* Simulation, int mode, int bufferLength);



private:
    // OpenGL initialization
    void initializeUniforms();
    void initializeColorMapInfo();

    void initializeShaders();
    void initBuffers();

    //Uniforms
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 projectionMatrix;


};

#endif // ABSTRACTENGINE_H
