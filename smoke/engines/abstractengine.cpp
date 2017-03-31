#include "abstractengine.h"

const float AbstractEngine::farClippingPlane = 100000.0f;
const float AbstractEngine::nearClippingPlane = -10000.0f;

AbstractEngine::AbstractEngine(int lightModel,
                               Settings::engines::EnginesTypes engineType,
                               QObject *parent) :
   QObject(parent),
   normalBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
   me(engineType),
   engineLightModel(lightModel),
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
   this->normalBuffer->destroy();
   this->vao.destroy();
}

void AbstractEngine::init()
{
   initializeOpenGLFunctions();
   initBuffers();
   initializeShaders();
   initializeUniforms();
}

void AbstractEngine::connectToColorMap()
{}

void AbstractEngine::setColorMap(Settings::visualization::ColorMap *value)
{
   this->colorMap = value;

   QPair<float, float> range = Settings::simulation().getRange(colorMap->scalar);
   setColorMapValueRange(range.first, range.second);
   connectToColorMap();

   /*
    * Hacky solution to ensure that the changes in range due to changes in initial
    * scalars are solved. Correct solution is initializing the engines and colormaptab
    * based on the correct instance of the colormap settings object.
    */
   this->colorMap->onTextureVariableChanged(this->colorMap->scalar);
}

void AbstractEngine::initializeUniforms()
{
   setMVPMatrix();
   setLightModel();
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

void AbstractEngine::updateProjectionMatrix(float width, float height)
{
   projectionMatrix.setToIdentity();
   projectionMatrix.ortho(0.0, width, 0.0, height,
                         nearClippingPlane, farClippingPlane);

   setMVPMatrix();
}

void AbstractEngine::setMVPMatrix()
{
   QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("mvpMatrix", mvpMatrix);
   this->shaderProgram->release();

   setNormalMatrix();
}

void AbstractEngine::setLightModel()
{
   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("lightModel", engineLightModel);
   this->shaderProgram->release();
}

void AbstractEngine::setNormalMatrix()
{
   QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;

   this->shaderProgram->bind();
   this->shaderProgram->setUniformValue("normalMatrix", mvpMatrix.normalMatrix());
   this->shaderProgram->release();
}

/** Slots **/

void AbstractEngine::onValueRangeChanged(Settings::sim::Scalar scalar, float min, float max)
{
   if (this->colorMap->scalar == scalar) setColorMapValueRange(min, max);
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

void AbstractEngine::onWindowChanged(int width, int height)
{
   updateProjectionMatrix(width, height);
}

/** Set functions **/
void AbstractEngine::setTexture(QImage image)
{
   // TODO isValid?
   if (!texture) texture = new QOpenGLTexture(QOpenGLTexture::Target1D);
   if (texture->isCreated()) texture->destroy();
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

   this->normalBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
   this->normalBuffer->create();
   this->normalBuffer->bind();

   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, 0);

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

void AbstractEngine::updateBuffers(GPUData data)
{
   updateBuffer(this->vertexBuffer, data.getVertices());
   updateBuffer(this->normalBuffer, data.getNormals());
   updateBuffer(this->textureCoordinateBuffer, data.getTextureCoordinates());
}

void AbstractEngine::drawWithMode(int mode, int bufferLength)
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
