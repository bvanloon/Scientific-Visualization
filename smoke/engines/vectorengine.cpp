#include "vectorengine.h"

VectorEngine::VectorEngine(Settings *settings):
    settings(settings)
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
//    int idx;
//    for (int i = 0; i < this->settings->simulation->dimension; i++)
//      for (int j = 0; j < this->settings->simulation->dimension; j++)
//      {
//        idx = (j * this->settings->simulation->dimension) + i;
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(this->settings->grid->cellWidth + (fftw_real)i * this->settings->grid->cellWidth, this->settings->grid->cellHeight + (fftw_real)j * this->settings->grid->cellHeight);
//        glVertex2f((this->settings->grid->cellWidth + (fftw_real)i * this->settings->grid->cellWidth) + this->settings->visualization->vecScale * simulation->realization->vx[idx], (this->settings->grid->cellHeight + (fftw_real)j * this->settings->grid->cellHeight) + this->settings->visualization->vecScale * simulation->realization->vy[idx]);
//      }
    this->updateBuffers(simulation);

    this->vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    updateBuffer(this->vertexBuffer, simulation->getVertices());
}

void VectorEngine::updateBuffer(QOpenGLBuffer *buffer, QVector<QVector3D> data)
{
    buffer->bind();
    buffer->allocate(data.data(), data.size() * sizeof(data[0]));
    buffer->release();
}

