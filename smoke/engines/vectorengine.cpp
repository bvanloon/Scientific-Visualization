#include "vectorengine.h"

VectorEngine::VectorEngine(Settings *settings)
{
    this->vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    initializeOpenGLFunctions();

    initBuffers();
}

VectorEngine::~VectorEngine()
{
    this->vertexBuffer->destroy();
    this->vao.destroy();
}

void VectorEngine::draw(Simulation *simulation)
{
    qDebug() << "void VectorEngine::draw(Simulation *simulation)";
    this->updateBuffers(simulation);

    this->vao.bind();
    glDrawArrays(GL_LINES, 0, 3);
    this->vao.release();
}

void VectorEngine::initBuffers()
{
    this->vao.create();
    this->vao.bind();

    this->vertexBuffer->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->vertexBuffer->create();
    this->vertexBuffer->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->vao.release();
}

void VectorEngine::updateBuffers(Simulation *simulation)
{
    qDebug() << "void VectorEngine::updateBuffers(Simulation *simulation)";
//    QVector<QVector3D> lines = QVector<QVector3D>();
//    lines.append(QVector3D(1.0f, 1.0f, 0.0f));
//    lines.append(QVector3D(100.0f, 100.0f, 0.0f));

    qDebug() << simulation->getGridV().at(0);
    updateBuffer(this->vertexBuffer, simulation->getGridV());
}

void VectorEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

