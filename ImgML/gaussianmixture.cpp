#include "ImgML/gaussianmixture.hpp"
#include "ImgML/eigenutils.hpp"


GaussianMixture::GaussianMixture()
{
    index=0;
}



void GaussianMixture::setnmix(int n)
{
    _nmix=n;
    _components.resize(_nmix);
    _weights.resize(_nmix);
}

void GaussianMixture::setGaussian(Gaussian a,float prior)
{
    _components[index]=a;
    _weights[index]=std::log(prior);
    index=index+1;
}


void GaussianMixture::clearModel()
{
    index=0;
    _nmix=0;
    _components.clear();
    _weights.clear();
}


/**
 * @brief ProbMix:method returns the probability that
 *        vector X belongs to each of mixture gaussian
 * @param X : input vector X
 * @return  :output vector of probabilities
 */
vector<float> GaussianMixture::ProbMix(Mat X)
{
    vector<float> res;
    res.resize(_nmix);
    for(int i=0;i<_nmix;i++)
    {
    //    cerr << _weights[i] << endl;
        res[i]=(_components[i].Prob(X));
    }
    return res;

}


/**
 * @brief Prob : method computes the probability that vector X
 *               is drawn from the gaussian mixture model
 * @param X     : input vector X
 * @return
 */
float GaussianMixture::Prob(Mat X)
{


    //double res=0;
    vector<float> res;

    res.resize(_nmix);
   // #pragma omp parallel for
    for(int i=0;i<_nmix;i++)
    {
        res[i]=(_weights[i]+_components[i].Prob(X));
    }


    float r=EigenUtils::logsumexp(res);

    return r;
}



