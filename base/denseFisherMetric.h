#ifndef _BETA_DENSEMETRIC_

#include <Eigen/Cholesky>

#include "dynamMetric.h"

///  \author Michael Betancourt
///
/// Abstract base class defining the interface
/// for a Hamiltonian defined on a Riemannian manifold
/// with a dense Fisher-Rao metric.

class denseFisherMetric: public dynamMetric
{
    
    public:
        
        explicit denseFisherMetric(int dim);
        virtual ~denseFisherMetric() {};
        
        //////////////////////////////////////////////////
        //                   Accessors                  //
        //////////////////////////////////////////////////
        
        double T();
        double tau();

        void bounceP(const VectorXd& normal);
    
        /// Return the Fisher-Rao metric
        MatrixXd& G() { return mG; }
    
        /// Return the Cholesky decompositio of the Fisher-Rao metric
        LLT<MatrixXd>& GL() { return mGL; }
        
        //////////////////////////////////////////////////
        //                   Mutators                   //
        //////////////////////////////////////////////////
        
        void sampleP(Random& random);
        
        //////////////////////////////////////////////////
        //              Auxiliary Functions             //
        //////////////////////////////////////////////////
        
        void checkEvolution(const double epsilon = 1e-6);
        
        void displayState();
        
        void prepareEvolution() { fComputeCholeskyG(); }
        
    protected:
    
        MatrixXd mG;          ///< denseFisher-Rao metric
        MatrixXd mGradG;      ///< Component of the gradient of the denseFisher-Rao metric
        LLT<MatrixXd> mGL;    ///< Cholesky decomposition of the denseFisher-Rao metric
        VectorXd mC;          ///< Additional auxiliary vector for efficient matrix computations

        void fComputeMetric() {  fComputeCholeskyG(); }
    
        /// Compute the Fisher-Rao metric
        virtual void fComputeG() = 0;
    
        /// Compute the ith component of the gradient of the Fisher-Rao metric
        virtual void fComputeGradG(int i) = 0;
    
        void fComputeCholeskyG();
    
        VectorXd& dTaudp();
        VectorXd& dTaudq();
        VectorXd& dPhidq();
    
};
 
#define _BETA_DENSEFISHERMETRIC_
#endif