#ifndef TFUNCTIONCALC_H
#define TFUNCTIONCALC_H

#include <QList>
#include <QString>
#include <QVector>
#include <complex>

class TFunctionCalc
{
public:
    TFunctionCalc(double damping = 0.1, double H = 10, double Vs = 500);
    ~TFunctionCalc();

    QVector<double> abssoilTF();
    void calcSoilTf(QVector<std::complex<double>>& tf);
    void calculate();
    void calculateRS();

    void setFreq(int length = 100);
    void setDamping(double damping);
    void setHs(double H);
    void setVs(double Vs);
    void accelRecord();

    QVector<double> getSoilTF();
    QVector<double> getFreq();
    QVector<double> getAccel();
    QVector<double> getTime();
protected:

    QVector<double> m_acc;
    // QVector<double> m_accT;
    QVector<double> m_time;
    QVector<double> m_freq;
    // QVector<double> m_absaccB;
    // QVector<double> m_absaccT;
    QVector<double> m_SoilTF;
    QVector<double> m_absSoilTF;


    // Damping , height, and Shear wave velocity
    double m_dt;
    double m_damping;
    double m_H;
    double m_Vs;
};

#endif // TFUNCTIONCALC_H
