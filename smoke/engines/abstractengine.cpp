#include "abstractengine.h"

const float AbstractEngine::farClippingPlane = 1.0f;
const float AbstractEngine::nearClippingPlane = -1.0f;

AbstractEngine::AbstractEngine(QObject *parent) :
   QObject(parent),
   texture(0)
{
   modelViewMatrix.setToIdentity();
   this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
   this->textureCoordinateBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
   init();
}


AbstractEngine::~AbstractEngine()
{
   delete this->shaderProgram;
   delete this->texture;
   this->vertexBuffer->destroy();
   this->textureCoordinateBuffer->destroy();
   this->vao.destroy();
}


void AbstractEngine::init()
{
   initializeOpenGLFunctions();
   initBuffers();
   initializeShaders();
   initializeUniforms();
}


void AbstractEngine::initializeUniforms()
{
   setMVPMatrix();
   initializeColorMapInfo();
}


void AbstractEngine::initializeColorMapInfo()
{
   QImage image = *ColorMapFactory::get()->createColorMap(
    Settings::defaults::visualization::colormap::colormap,
    Settings::defaults::visualization::colormap::numColors,
    Settings::defaults::visualization::colormap::saturation);

   setTexture(image);

   setColorMapValueRange(Settings::defaults::simulation::valueRangeMin,
                        Settings::defaults::simulation::valueRangeMax);
   setColorMapClampRange(Settings::defaults::visualization::colormap::clampMin,
                        Settings::defaults::visualization::colormap::clampMax);
   setColorMapClampingTo(Settings::defaults::visualization::colormap::clampingOn);
}


void AbstractEngine::setProjectionMatrix(float width, float height)
{
   projectionMatrix.setToIdentity();
   projectionMatrix.ortho(0.0,
                         width,
                         0.0,
                         height,
                         nearClippingPlane,
                         farClippingPlane);
}


void AbstractEngine::setMVPMatrix()
{
   QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
   this->shaderProgram->release();
}


/** Slots **/
void AbstractEngine::onValueRangeChanged(float min, float max)
{
   setColorMapValueRange(min, max);
}


void AbstractEngine::onSetClamping(bool clampingOn)
{
   setColorMapClampingTo(clampingOn);
}


void AbstractEngine::onsetClampingRange(float minimum, float maximum)
{
   setColorMapClampRange(minimum, maximum);
}


void AbstractEngine::onColorMapChanged(AbstractColorMap colormap)
{
   setTexture(colormap);
}


void AbstractEngine::onForceChanged(float force)
{
   if (Settings::getVisualization().scalar ==
       Settings::visualization::ScalarVariable::fluidDensity)
   {
      setColorMapValueRange(0.0f, force);
   }
}


void AbstractEngine::onWindowChanged(int width, int height)
{
   setProjectionMatrix(width, height);
   setMVPMatrix();
}


/** Set functions **/
void AbstractEngine::setTexture(QImage image)
{
   // TODO isValid?
   if (!texture)
   {
      texture = new QOpenGLTexture(QOpenGLTexture::Target1D);
   }

   if (texture->isCreated())
   {
      texture->destroy();
   }
   texture->create();
   texture->setData(image.mirrored());
   texture->setMagnificationFilter(QOpenGLTexture::Nearest);
   texture->setWrapMode(QOpenGLTexture::ClampToEdge);
}


void AbstractEngine::setColorMapValueRange(float min, float max)
{
   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("colorMapInfo.minimum", min);
   this->shaderProgram->setUniformValue("colorMapInfo.maximum", max);
   this->shaderProgram->release();
}


void AbstractEngine::setColorMapClampRange(float startClamp, float endClamp)
{
   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("colorMapInfo.clampMin", startClamp);
   this->shaderProgram->setUniformValue("colorMapInfo.clampMax", endClamp);
   this->shaderProgram->release();
}


void AbstractEngine::setColorMapClampingTo(bool clampingOn)
{
   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("colorMapInfo.clampingOn", clampingOn);
   this->shaderProgram->release();
}


/** Buffers **/
void AbstractEngine::initBuffers()
{
   this->vao.create();
   this->vao.bind();

   this->vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
   this->vertexBuffer->create();
   this->vertexBuffer->bind();

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

   this->textureCoordinateBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
   this->textureCoordinateBuffer->create();
   this->textureCoordinateBuffer->bind();

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

   this->vao.release();
}


void AbstractEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
   buffer->bind();
   buffer->allocate(data.data(), data.size() * sizeof(data[0]));
   buffer->release();
}


void AbstractEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<float> data)
{
   buffer->bind();
   buffer->allocate(data.data(), data.size() * sizeof(data[0]));
   buffer->release();
}


void AbstractEngine::drawWithMode(int mode,
                                  int bufferLength)
{
   this->shaderProgram->bind();
   this->texture->bind();
   this->vao.bind();
   glDrawArrays(mode, 0, bufferLength);
   this->vao.release();
   this->texture->release();
   this->shaderProgram->release();
}


/** Shader Functions **/

void AbstractEngine::initializeShaders()
{
   this->shaderProgram = new QOpenGLShaderProgram();
   this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               ":/shaders/shaders/vertex.glsl");
   this->shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               ":/shaders/shaders/fragment.glsl");
   this->shaderProgram->link();
}
