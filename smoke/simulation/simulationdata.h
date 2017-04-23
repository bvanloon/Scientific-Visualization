#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "rfftw.h"
#include <QVector2D>
#include <QVector>
#include <assert.h>
#include "utilities/range.h"

class SimulationData
{
   public:
      SimulationData(int dimension);
      SimulationData(const SimulationData& obj);
      SimulationData(SimulationData&& other);

      ~SimulationData();

      fftw_real *getVx();
      fftw_real getVxAt(int idx) const;

      fftw_real *getVy();
      fftw_real getVyAt(int idx) const;

      QVector2D getFluidVelocityAt(int idx) const;

      Range<double> getFluidVelocityMagnitudeRange();

      fftw_real *getFx();
      fftw_real getFxAt(int idx) const;

      fftw_real *getFy();
      fftw_real getFyAt(int idx) const;

      QVector2D getForceAt(int idx);

      Range<double> getForceMagnitudeRange();

      fftw_real *getRho();
      fftw_real getRhoAt(int idx) const;
      double getDensityAt(int idx) const;

      Range<double> getDensityRange();


      static SimulationData mean(QList<SimulationData> list);
      static SimulationData mean(QList<SimulationData *> list);


      SimulationData& operator+=(const SimulationData& rhs);

      SimulationData& operator/=(const double rhs);

      SimulationData& operator*=(const double rhs);

      SimulationData& operator=(SimulationData other);

      friend SimulationData operator+(SimulationData lhs, const SimulationData& rhs);

      friend SimulationData operator*(SimulationData lhs, const double rhs);

      friend SimulationData operator*(const double lhs, SimulationData rhs);

      friend SimulationData operator/(SimulationData lhs, const double rhs);

      friend QDebug operator<<(QDebug stream, const SimulationData& data);


   private:
      //Velocity field
      QVector<fftw_real> vx, vy;

      // Simulation forces
      QVector<fftw_real> fx, fy;

      // Smoke density
      QVector<fftw_real> rho;

      size_t velocitiesSize;
      size_t rhoSize;
      size_t forceSize;

      void allocateData();

      void allocateVelocityData(int length);

      void allocteForceData(int length);

      void allocateDensityData(int dimension);
};

#endif // SIMULATIONDATA_H
