#include "vectorengine.h"

VectorEngine::VectorEngine()
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
//    glBegin(GL_LINES);				//draw velocities
//    for (int i = 0; i < DIM; i++)
//      for (int j = 0; j < DIM; j++)
//      {
//        idx = (j * DIM) + i;
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(wn + (fftw_real)i * wn, hn + (fftw_real)j * hn);
//        glVertex2f((wn + (fftw_real)i * wn) + vec_scale * vx[idx], (hn + (fftw_real)j * hn) + vec_scale * vy[idx]);
//      }
//    glEnd();
//    this->updateBuffers(simulation);

//    this->vao.bind();
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    this->vao.release();
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

