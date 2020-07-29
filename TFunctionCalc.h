#ifndef TFUNCTIONCALC_H
#define TFUNCTIONCALC_H

#include <QList>
#include <QString>
#include <QVector>
#include <QJsonArray>
#include <complex>

class TFunctionCalc
{
public:
    TFunctionCalc(double damping = 0.1, double H = 10, double Vs = 500);
    ~TFunctionCalc();

    void calcSoilTf(QVector<std::complex<double>>& tf);
    void fft(QVector<double> ts, QVector<std::complex<double> >& fas);
    void ifft(QVector<std::complex<double>> fas, QVector<double>& ts);
    void calculate();
    void calculateRS();

    void setFreq(double maxFreq = 25.0);
    void setTime();
    void setDamping(double damping);
    void setHs(double H);
    void setVs(double Vs);
    void earthquakeRecord();
    void sinRecord(double frequency = 5.0);
    void sweepRecord();
    void readGM(QJsonArray accTH, double dT, double accUnit);

    QVector<double> getSoilTF();
    QVector<double> getFreq();
    QVector<double> getAccel();
    QVector<double> getAccelT();
    QVector<double> getTime();
    QVector<double> getFft();
    QVector<double> getIFft();
protected:

    QVector<double> m_acc;
    QVector<double> m_accT;
    QVector<double> m_time;
    QVector<double> m_freq;
    QVector<double> m_absFft;
    QVector<double> m_absIFft;
    QVector<double> m_SoilTF;
    QVector<double> m_absSoilTF;


    // Damping , height, and Shear wave velocity
    double m_dt;
    double m_damping;
    double m_H;
    double m_Vs;
};

#endif // TFUNCTIONCALC_H
