#ifndef ABSTRACTENGINE_H
#define ABSTRACTENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QObject>
#include <QMatrix4x4>

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "utilities/gpudata.h"
#include "simulation/simulation.h"
#include "settings/settings.h"
#include "settings/visualizationsettings.h"

class AbstractEngine :  public QObject, protected QOpenGLFunctions
{
   Q_OBJECT
   public:
      explicit AbstractEngine(int engineLightModel, Settings::engines::EnginesTypes me, QObject *parent = 0);
      virtual ~AbstractEngine();
      virtual void draw() = 0;

      void setColorMap(Settings::visualization::ColorMap *value);

   public slots:

      void onValueRangeChanged(Settings::sim::Scalar scalar, float min, float max);

      void onSetClamping(bool clampingOn);

      void onsetClampingRange(float minimum, float maximum);

      void onColorMapChanged(AbstractColorMap colormap);

      void onWindowChanged(int width, int height);

   protected:
      QOpenGLBuffer *vertexBuffer;
      QOpenGLBuffer *textureCoordinateBuffer;
      QOpenGLBuffer *normalBuffer;
      QOpenGLBuffer *alphaBuffer;

      Settings::visualization::ColorMap *colorMap;

      Settings::engines::EnginesTypes me;

      enum lightModel { noLight = 0, phongLight = 1 };

      void updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data);

      void updateBuffer(QOpenGLBuffer *buffer, QVector<float> data);

      void updateBuffers(GPUData data);

      void updateBuffersAndDraw(GPUData data);

      void draw(GPUData data);

      void drawWithMode(int mode, int bufferLength);

      void setMVPMatrix();

      void setModelViewMatrix(const QMatrix4x4& value);

      void setProjectionMatrix(const QMatrix4x4& value);

      void setGlobalAlpha();
      void setGlobalAlpha(float alpha);

      virtual void connectToColorMap();

   private:
      void init();

      QMatrix4x4 modelViewMatrix;
      QMatrix4x4 projectionMatrix;

      int engineLightModel;

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

      void updateProjectionMatrix(float width, float height);

      //Uniforms
      void setColorMapClampingTo(bool clampingOn);

      void setColorMapValueRange(float min, float max);

      void setTexture(QImage image);

      void setColorMapClampRange(float startClamp, float endClamp);

      void setLightModel();

      void setNormalMatrix();

      static const float nearClippingPlane;
      static const float farClippingPlane;
};

#endif // ABSTRACTENGINE_H
