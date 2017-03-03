#ifndef ABSTRACTENGINE_H
#define ABSTRACTENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QObject>
#include <QMatrix4x4>

#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"

class AbstractEngine :  public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit AbstractEngine(QObject *parent = 0);
    virtual ~AbstractEngine();
    virtual void draw(Simulation* Simulation) = 0;

    void setProjectionMatrix(float width, float height);
    void setMVPMatrix();




public slots:
    void onValueRangeChanged(float min, float max);
    void onSetClamping(bool clampingOn);
    void onsetClampingRange(float minimum, float maximum);
    void onColorMapChanged(AbstractColorMap colormap);
    void onForceChanged(float force);

protected:
    QOpenGLBuffer* vertexBuffer;
    QOpenGLBuffer* textureCoordinateBuffer;

    void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);
    void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);

    void drawWithMode(Simulation* Simulation, int mode, int bufferLength);

private:
    void init();

    //Shaders
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLTexture *texture;


    //Buffers
    QOpenGLVertexArrayObject vao;

    // OpenGL initialization
    void initializeUniforms();
    void initializeColorMapInfo();

    void initializeShaders();
    void initBuffers();

    //Uniforms
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 projectionMatrix;

    void setColorMapClampingTo(bool clampingOn);
    void setColorMapValueRange(float min, float max);
    void setTexture(QImage image);

    void setColorMapClampRange(float startClamp, float endClamp);

    static const float nearClippingPlane;
    static const  float farClippingPlane;



};

#endif // ABSTRACTENGINE_H
