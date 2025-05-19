#ifndef FUZZYLOGICCONTROLLER_H
#define FUZZYLOGICCONTROLLER_H

#include <QThread>
#include <QMutex>
#include <array>
#include <vector>
#include "FuzzyController/ProbabilityProvider.h"
#include "xyplatform.h"
#include "NeuralNetThread/Probabilities.h"

struct TriangularMF {
    double a, b, c;
};

class FuzzyController : public QThread {
    Q_OBJECT
public:
    FuzzyController(ProbabilityProvider* probProvider,  QObject* parent = nullptr);
    void run() override;
    void stop();

private:
    QMutex mutex;
    bool isRunning = false;
    double previous_ot = 0.0;
    ProbabilityProvider* probProvider;
    XyPlatform* platform;

    std::array<TriangularMF, 5> ot_mfs;
    std::array<TriangularMF, 5> dt_mfs;
    std::array<TriangularMF, 5> cs_mfs;

    struct Rule {
        int ante1;
        int ante2;
        int cons;
    };
    std::vector<Rule> rules;

    const double cs_min = -10.0;
    const double cs_max = 10.0;
    const double cs_step = 0.01;
    int num_cs_points = static_cast<int>((cs_max - cs_min) / cs_step) + 1;

    double triangularMembership(double x, const TriangularMF& mf) const;
    std::array<double, 5> fuzzify(double x, const std::array<TriangularMF, 5>& mfs) const;
    double defuzzify(const std::vector<double>& agg_membership) const;

    double computeCorrection(double offset_tendency, double delta_tendency);
};

#endif // FUZZYLOGICCONTROLLER_H
