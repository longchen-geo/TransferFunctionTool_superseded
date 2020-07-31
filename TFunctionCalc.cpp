#include "TFunctionCalc.h"
#include <mkl_dfti.h>

#define PI 3.141592653590

TFunctionCalc::TFunctionCalc(double damping, double H, double Vs)
{
    //Define soil layer parameters
    m_damping = damping / 100.0;
    m_H = H;
    m_Vs = Vs;
}

TFunctionCalc::~TFunctionCalc()
{

}

// Calculate soil transfer function and surface soil response
void TFunctionCalc::calculate()
{

    QVector<std::complex<double> > SoilTF(m_freq.size());
    QVector<double> absSoilTF(m_freq.size());

    // Compute the Fourier amplitude spectrum
    QVector<std::complex<double>> fas(m_freq.size());
    fft(m_acc, fas);
    QVector<double> absfas(fas.size());
    for ( int i = 0; i < fas.size(); i++ ) {
        absfas[i] = abs(fas[i]);
    }
    m_absFft = absfas;

    // Compute transfer function
    calcSoilTf(SoilTF);
    for ( int i = 0; i < m_freq.size(); i++ ) {
        absSoilTF[i] = abs(SoilTF[i]);
    }
    m_absSoilTF = absSoilTF;

    // Compute surface soil response
    QVector<std::complex<double>> ifas(m_freq.size());
    QVector<double> absfas2(ifas.size());
    for (int i = 0; i < m_freq.size(); i++) {
        ifas[i] = fas[i] * SoilTF[i];
        absfas2[i] = abs(ifas[i]);
    }
    m_absIFft = absfas2;
    QVector<double> accT(m_acc.size());
    ifft(ifas, accT);
    m_accT = accT;
}


void TFunctionCalc::calcSoilTf(QVector<std::complex<double>>& tf)
{
    std::complex<double> kstar;
    std::complex<double> Vsstar;

    for ( int i = 0; i < m_freq.size(); i++ )
    {
        /*
         * The uniform damped soil on rigid rock transfer function
         *
         *                             1
         *  H = -------------------------------------------------
         *       cos ( 2* PI * freq * H / (Vs(1+ i*damping))
         *
         */
         kstar = std::complex<double>(2.0*PI*m_freq[i]/m_Vs, -m_damping*2.0*PI*m_freq[i]/m_Vs);
         Vsstar = std::complex<double>(m_Vs, m_damping * m_Vs);
         //tf[i] = 1.0/cos(kstar*H);
         tf[i] = 1.0/cos(2.0*PI*m_freq[i]*m_H/Vsstar);
    }
}


void TFunctionCalc::fft(QVector<double> ts, QVector<std::complex<double>>& fas)
{

    DFTI_DESCRIPTOR_HANDLE descriptor;
    MKL_LONG status;

    status = DftiCreateDescriptor(&descriptor, DFTI_DOUBLE, DFTI_REAL, 1, ts.size()); //Specify size and precision
    status = DftiSetValue(descriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
    status = DftiSetValue(descriptor, DFTI_CONJUGATE_EVEN_STORAGE, DFTI_COMPLEX_COMPLEX);
    status = DftiCommitDescriptor(descriptor); //Finalize the descriptor
    status = DftiComputeForward(descriptor, ts.data(), fas.data()); //Compute the Forward FFT
    status = DftiFreeDescriptor(&descriptor); //Free the descriptor
}

void TFunctionCalc::ifft(QVector<std::complex<double>> fas, QVector<double>& ts)
{
    DFTI_DESCRIPTOR_HANDLE descriptor;
    MKL_LONG status;

    status = DftiCreateDescriptor(&descriptor, DFTI_DOUBLE, DFTI_REAL, 1, (fas.size() - 1) * 2); //Specify size and precision
    status = DftiSetValue(descriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
    status = DftiSetValue(descriptor, DFTI_CONJUGATE_EVEN_STORAGE, DFTI_COMPLEX_COMPLEX);
    status = DftiSetValue(descriptor, DFTI_BACKWARD_SCALE, 1.0f / fas.size()); //Scale down the output
    status = DftiCommitDescriptor(descriptor); //Finalize the descriptor
    status = DftiComputeBackward(descriptor, fas.data(), ts.data()); //Compute the Forward FFT
    status = DftiFreeDescriptor(&descriptor); //Free the descriptor
}


void TFunctionCalc::setFreq(double maxFreq)
{
    QVector<double> freq(m_acc.size()/2+1);
    // double dfreq = 1 / ( 2 * m_dt * (freq.size() - 1 ) );
    double dfreq = maxFreq / freq.size();
    for (int i = 0; i < freq.size(); i++ ) {
        freq[i] = i * dfreq;
    }
    m_freq = freq;
}

void TFunctionCalc::setTime()
{
    //Define time QVector
    m_time.resize(m_acc.size());
    for (int i=0; i<m_time.size();i++){
        m_time[i]=  i * m_dt;
    }

}

void TFunctionCalc::setDamping(double damping)
{
    m_damping = damping/100.0;
}

void TFunctionCalc::setHs(double H)
{
    m_H = H;
}

void TFunctionCalc::setVs(double Vs)
{
    m_Vs = Vs;
}

QVector<double> TFunctionCalc::getSoilTF()
{
    return m_absSoilTF;
}

QVector<double> TFunctionCalc::getFreq() {
    return m_freq;
}

QVector<double> TFunctionCalc::getAccel()
{
    return m_acc;
}

QVector<double> TFunctionCalc::getAccelT()
{
    return m_accT;
}

QVector<double> TFunctionCalc::getTime()
{
    return m_time;
}

QVector<double> TFunctionCalc::getFft()
{
    return m_absFft;
}

QVector<double> TFunctionCalc::getIFft()
{
    return m_absIFft;
}

void TFunctionCalc::sinRecord(double f)
{
    int nPoints = 2000;
    m_dt = 0.002;
    m_acc.resize(nPoints);
    QVector<double> accel;

    for (double s=0.;s<=nPoints * m_dt; s+=m_dt)
    {
        accel.append(0.4 * sin(2 * f * PI * s));
    }
    m_acc = accel;
    setTime();
    setFreq();
    calculate();
}

void TFunctionCalc::sweepRecord()
{
    int nPoints = 8000;
    double time;
    m_dt = 0.005;
    m_acc.resize(nPoints);
    m_time.resize(nPoints);

    for (int i=0; i<m_time.size();i++){
        time = i * m_dt;
        m_time[i]= time;
        m_acc[i] = sin(50.0 * time + 500.0 * (time * time / 2.0) / 40.0);
    }

    setFreq(10.0);
    calculate();
}

void TFunctionCalc::readGM(QJsonArray accTH, double dT, double accUnit)
{
    int nPoints = accTH.size();
    m_dt = dT;
    m_acc.clear();
    for (int ii = 0; ii < nPoints; ii++){
        m_acc.append(accTH[ii].toDouble() * accUnit);
    }
    if (nPoints % 2 == 0) m_acc.append(0.0);
    setTime();
    setFreq();
    calculate();
};

