#include "simulationdata.h"
#include <QDebug>
#include <algorithm>
#include <limits>

SimulationData::SimulationData(int dimension) :
   velocitiesSize(dimension * 2 * (dimension / 2 + 1)),
   rhoSize(dimension * dimension),
   forceSize(dimension * dimension)
{
   allocateData();
}

SimulationData::SimulationData(const SimulationData& obj) :
   velocitiesSize(obj.velocitiesSize),
   rhoSize(obj.rhoSize),
   forceSize(obj.forceSize)
{
   allocateData();

   std::copy(std::begin(obj.vx), std::end(obj.vx), std::begin(this->vx));
   std::copy(std::begin(obj.vy), std::end(obj.vy), std::begin(this->vy));

   std::copy(std::begin(obj.fx), std::end(obj.fx), std::begin(this->fx));
   std::copy(std::begin(obj.fy), std::end(obj.fy), std::begin(this->fy));

   std::copy(std::begin(obj.rho), std::end(obj.rho), std::begin(this->rho));
}

SimulationData::SimulationData(SimulationData&& other) :
   velocitiesSize(other.velocitiesSize),
   rhoSize(other.rhoSize),
   forceSize(other.forceSize)
{
   vx = other.vx;
   vy = other.vy;

   fx = other.fx;
   fy = other.fy;

   rho = other.rho;

   other.velocitiesSize = 0;
   other.rhoSize = 0;
   other.forceSize = 0;
}

void SimulationData::allocateData()
{
   allocateVelocityData(velocitiesSize);
   allocteForceData(forceSize);
   allocateDensityData(rhoSize);
}

SimulationData::~SimulationData()
{
   vx.clear();
   vy.clear();

   fx.clear();
   fy.clear();

   rho.clear();
}

fftw_real *SimulationData::getVx()
{
   return this->vx.data();
}

fftw_real SimulationData::getVxAt(int idx) const
{
   return vx[idx];
}

fftw_real *SimulationData::getVy()
{
   return this->vy.data();
}

fftw_real SimulationData::getVyAt(int idx) const
{
   return vy[idx];
}

QVector2D SimulationData::getFluidVelocityAt(int idx) const
{
   return QVector2D(getVxAt(idx),
                    getVyAt(idx));
}

Range<double> SimulationData::getFluidVelocityMagnitudeRange()
{
   double minimum = std::numeric_limits<double>::max();
   double maximum = std::numeric_limits<double>::min();
   double currentMagnitude;
   for (size_t i = 0; i < velocitiesSize; i++)
   {
      currentMagnitude = getFluidVelocityAt(i).length();
      minimum = qMin(currentMagnitude, minimum);
      maximum = qMax(currentMagnitude, maximum);
   }
   return Range<double>(minimum, maximum);
}

fftw_real *SimulationData::getFx()
{
   return fx.data();
}

fftw_real SimulationData::getFxAt(int idx) const
{
   return fx[idx];
}

fftw_real *SimulationData::getFy()
{
   return fy.data();
}

fftw_real SimulationData::getFyAt(int idx) const
{
   return fy[idx];
}

QVector2D SimulationData::getForceAt(int idx)
{
   return QVector2D(getFxAt(idx),
                    getFyAt(idx));
}

Range<double> SimulationData::getForceMagnitudeRange()
{
   double minimum = std::numeric_limits<double>::max();
   double maximum = std::numeric_limits<double>::min();
   double currentMagnitude;
   for (size_t i = 0; i < forceSize; i++)
   {
      currentMagnitude = getForceAt(i).length();
      minimum = qMin(currentMagnitude, minimum);
      maximum = qMax(currentMagnitude, maximum);
   }
   return Range<double>(minimum, maximum);
}

fftw_real *SimulationData::getRho()
{
   return rho.data();
}

fftw_real SimulationData::getRhoAt(int idx) const
{
   return rho[idx];
}

double SimulationData::getDensityAt(int idx) const
{
   return this->getRhoAt(idx);
}

Range<double> SimulationData::getDensityRange()
{
   fftw_real minimum = *std::min_element(rho.constBegin(), rho.constEnd());
   fftw_real maximum = *std::max_element(rho.constBegin(), rho.constEnd());
   return Range<double>(minimum, maximum);
}

SimulationData SimulationData::mean(QList<SimulationData> list)
{
   QList<SimulationData>::const_iterator it = list.cbegin();

   SimulationData sum = *it++;

   while (it != list.cend()) sum += *it++;

   sum /= list.length();
   return sum;
}

SimulationData SimulationData::mean(QList<SimulationData *> list)
{
   QList<SimulationData *>::const_iterator it = list.cbegin();

   SimulationData sum = *(*it++);

   while (it != list.cend()) sum += *(*it++);

   sum /= list.length();
   return sum;
}

void SimulationData::allocateVelocityData(int length)
{
   vx.resize(length);
   vy.resize(length);
}

void SimulationData::allocteForceData(int length)
{
   fx.resize(length);
   fy.resize(length);
}

void SimulationData::allocateDensityData(int length)
{
   rho.resize(length);
}

SimulationData& SimulationData::operator+=(const SimulationData& rhs)
{
   assert(this->fx.size() == rhs.fx.size());
   for (int i = 0; i < this->fx.size(); i++) this->fx[i] = this->fx[i] + rhs.fx[i];
   for (int i = 0; i < this->fy.size(); i++) this->fy[i] = this->fy[i] + rhs.fy[i];

   for (int i = 0; i < this->rho.size(); i++) this->rho[i] = this->rho[i] + rhs.rho[i];

   for (int i = 0; i < this->vx.size(); i++) this->vx[i] = this->vx[i] + rhs.vx[i];
   for (int i = 0; i < this->vy.size(); i++) this->vy[i] = this->vy[i] + rhs.vy[i];

   return *this;
}

SimulationData& SimulationData::operator/=(const double rhs)
{
   for (int i = 0; i < this->fx.size(); i++) this->fx[i] = this->fx[i] / rhs;
   for (int i = 0; i < this->fy.size(); i++) this->fy[i] = this->fy[i] / rhs;

   for (int i = 0; i < this->rho.size(); i++) this->rho[i] = this->rho[i] / rhs;

   for (int i = 0; i < this->vx.size(); i++) this->vx[i] = this->vx[i] / rhs;
   for (int i = 0; i < this->vy.size(); i++) this->vy[i] = this->vy[i] / rhs;

   return *this;
}

SimulationData& SimulationData::operator*=(const double rhs)
{
   for (int i = 0; i < this->fx.size(); i++) this->fx[i] = this->fx[i] * rhs;
   for (int i = 0; i < this->fy.size(); i++) this->fy[i] = this->fy[i] * rhs;

   for (int i = 0; i < this->rho.size(); i++) this->rho[i] = this->rho[i] * rhs;

   for (int i = 0; i < this->vx.size(); i++) this->vx[i] = this->vx[i] * rhs;
   for (int i = 0; i < this->vy.size(); i++) this->vy[i] = this->vy[i] * rhs;

   return *this;
}

SimulationData& SimulationData::operator=(SimulationData other)
{
   std::swap(vx, other.vx);
   std::swap(vy, other.vy);

   std::swap(fx, other.fx);
   std::swap(fy, other.fy);

   std::swap(rho, other.rho);

   std::swap(velocitiesSize, other.velocitiesSize);
   std::swap(rhoSize, other.rhoSize);
   std::swap(forceSize, other.forceSize);
   return *this;
}

SimulationData operator/(SimulationData lhs, const double rhs)
{
   lhs /= rhs;
   return lhs;
}

SimulationData operator*(const double lhs, SimulationData rhs)
{
   rhs *= lhs;
   return rhs;
}

SimulationData operator*(SimulationData lhs, const double rhs)
{
   lhs *= rhs;
   return lhs;
}

SimulationData operator+(SimulationData lhs, const SimulationData& rhs)
{
   lhs += rhs;
   return lhs;
}

QDebug operator<<(QDebug stream, const SimulationData& data)
{
   stream << "fx:  " << data.fx << endl
          << "fy:  " << data.fy << endl
          << "rho: " << data.rho << endl
          << "vx:  " << data.vx << endl
          << "vy:  " << data.vy << endl;
   return stream;
}
