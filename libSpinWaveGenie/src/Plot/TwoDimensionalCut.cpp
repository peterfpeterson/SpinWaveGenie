//
//  TwoDimensionalCut.cpp
//  spin_wave_genie
//
//  Created by Hahn, Steven E. on 1/16/14.
//
//
#include <fstream>
#include <Eigen/Dense>
#include "SpinWaveGenie/Plot/TwoDimensionalCut.h"
#include "SpinWaveGenie/Plot/EnergyResolutionFunction.h"
#include "SpinWaveGenie/Containers/Energies.h"
#include "External/ezRateProgressBar.hpp"
#include <unistd.h>
#include <boost/thread/thread.hpp>
#ifdef USE_THREADS
#include "tbb/tbb.h"
using namespace tbb;
#else

#ifdef HAVE_ATOMIC_H
#include <atomic>
#else
#include <cstdatomic>
#endif

#endif

using namespace std;

namespace SpinWaveGenie
{
    class TwoDimensionalCut::CutImpl
    {
    public:
        std::string Filename;
#ifdef USE_THREADS
        tbb::atomic<int> counter;
#else
        atomic_int counter;
#endif
        Eigen::MatrixXd mat;
        unique_ptr<SpinWaveGenie::SpinWavePlot> cut;
        SpinWaveGenie::ThreeVectors<double> points;
        CutImpl() { counter = 0;};
        CutImpl(unique_ptr<SpinWaveGenie::SpinWavePlot> inCut, SpinWaveGenie::ThreeVectors<double> inPoints): cut(move(inCut)), points(inPoints) { counter = 0;};
    
        void progressBar(int numberPoints)
        {
            ez::ezRateProgressBar<int> p(numberPoints);
            p.units = "Q-points";
            p.start();
            while( counter < numberPoints)
            {
                p.update(counter);
                sleep(1);
            }
            p.update(numberPoints);
        }
    
        void partialCut(size_t begin,size_t end)
        {
            unique_ptr<SpinWaveGenie::SpinWavePlot> cutclone = cut->clone();
            for(size_t m=begin;m<end;m++)
            {
                auto it = points.begin()+m;
                vector<double> val = cutclone->getCut(it->get<0>(),it->get<1>(),it->get<2>());
                for(int n=0;n<val.size();n++)
                {
                    mat(n,m) = val[n];
                }
                counter++;
            }
        }
#ifdef USE_THREADS
        Eigen::MatrixXd generateMatrix()
        {
            mat.resize(cut->getEnergies().size(),points.size());
            TbbExecutor tbbExec(this);
            boost::thread myThread(bind(&CutImpl::progressBar,this,points.size() ));
            tbb::parallel_for(tbb::blocked_range<size_t>(0,points.size()),tbbExec);
            myThread.join();
           return mat;
        }
        struct TbbExecutor
        {
        public:
            TbbExecutor(CutImpl* w) : w_(w) {}
            void operator() (const tbb::blocked_range<size_t> r) const
            {
                w_->partialCut(r.begin(),r.end());
            }
        
        private:
            CutImpl* w_;
        };
#else
        Eigen::MatrixXd generateMatrix()
        {
            mat.resize(cut->getEnergies().size(),points.size());
            boost::thread pbar(bind(&CutImpl::progressBar,this,points.size() ));
            partialCut(0,points.size());
            pbar.join();
            return mat;
        }
#endif
    };

    TwoDimensionalCut::TwoDimensionalCut() : m_p{ new CutImpl{} } {};
    TwoDimensionalCut::~TwoDimensionalCut() {};

    void TwoDimensionalCut::setFilename(string name)
    {
        m_p->Filename = name;
    }
    
    void TwoDimensionalCut::setPlotObject(unique_ptr<SpinWavePlot> object)
    {
        m_p->cut = move(object);
    }

    void TwoDimensionalCut::setPoints(ThreeVectors<double> pts)
    {
        m_p->points = pts;
    }

    void TwoDimensionalCut::setEnergyPoints(double min, double max, size_t points)
    {
        m_p->cut->setEnergies(Energies(min, max, points));
    }

    Eigen::MatrixXd TwoDimensionalCut::getMatrix()
    {
        return m_p->generateMatrix();
    }

    void TwoDimensionalCut::save()
    {
        Eigen::MatrixXd figure = getMatrix();
        std::ofstream file(m_p->Filename+".mat");
        if (file.is_open())
        {
            file << figure << endl;
        }
        file.close();
        
        file.open(m_p->Filename+".x");
        if (file.is_open())
        {
            ThreeVectors<double> pts = m_p->points;
            for (auto it = pts.begin();it!=pts.end();++it)
                file << it->get<0>() << "\t" <<  it->get<1>() << "\t" << it->get<2>() << endl;
        }
        
        file.close();
        file.open(m_p->Filename+".y");
        if (file.is_open())
        {
            Energies energies = m_p->cut->getEnergies();
            for (auto it = energies.begin();it!=energies.end();++it)
                file << (*it) << endl;
        }
        file.close();
        
    }
}