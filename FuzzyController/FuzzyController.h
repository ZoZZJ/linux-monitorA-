#ifndef FUZZYCONTROLLER_H
#define FUZZYCONTROLLER_H

#include <QThread>
#include <QMutex>
#include <array>
#include <vector>
#include <deque>
#include "ProbabilityProvider.h"

struct TriangularMF {
    double a, b, c;
};

class XyPlatform;

class FuzzyController : public QThread {
    Q_OBJECT
public:
    explicit FuzzyController(ProbabilityProvider* probProv, QObject* parent = nullptr);
    void run() override;
    void stop();
    bool GetRunningStatus() const;

signals:
    void SendCorrectionRelatively(float correction);

private:
    mutable QMutex mutex;
    bool IsRunning = false;
    ProbabilityProvider* probProvider;
    XyPlatform& platform;
    double previous_ot = 0.0;
    std::deque<double> otHistory; // Sliding window for 20 OT values
    double previousOTWindow = 0.0;
    bool hasPreviousWindow = false;
    const double threshold = 0.2; // Correction threshold
    const size_t windowSize = 20; // Sliding window size

    std::array<TriangularMF, 5> ot_mfs;
       std::array<TriangularMF, 5> dt_mfs;
       std::array<TriangularMF, 5> cs_mfs;

       struct Rule {
           int ante1;
           int ante2;
           int cons;
       };
       std::vector<Rule> rules;

       const double cs_min = -1.0;  // Adjusted
       const double cs_max = 1.0;   // Adjusted
       const double cs_step = 0.001;// Adjusted
       int num_cs_points = static_cast<int>((cs_max - cs_min) / cs_step) + 1;

       double triangularMembership(double x, const TriangularMF& mf) const;
       std::array<double, 5> fuzzify(double x, const std::array<TriangularMF, 5>& mfs) const;
       double computeCorrection(double ot_window, double delta_ot_window);
};

#endif // FUZZYCONTROLLER_H
