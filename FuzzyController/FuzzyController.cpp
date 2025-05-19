#include "FuzzyController/FuzzyController.h"
#include "FuzzyController/ProbabilityProvider.h"
#include "xyplatform.h"
#include <algorithm>
#include <QThread>

FuzzyController::FuzzyController(ProbabilityProvider* probProv, QObject* parent)
    : probProvider(probProv), platform(&XyPlatform::getInstance()) {
    // Initialize membership functions
    ot_mfs[0] = {-1.0, -0.7, -0.4}; // NL
    ot_mfs[1] = {-0.6, -0.3,  0.0}; // NSc
    ot_mfs[2] = {-0.2,  0.0,  0.2}; // ZE
    ot_mfs[3] = { 0.0,  0.3,  0.6}; // PS
    ot_mfs[4] = { 0.4,  0.7,  1.0}; // PL
    dt_mfs = ot_mfs; // Same as ot_mfs
    cs_mfs[0] = {-10.0, -7.0, -4.0}; // NL
    cs_mfs[1] = { -6.0, -3.0,  0.0}; // NS
    cs_mfs[2] = { -2.0,  0.0,  2.0}; // ZE
    cs_mfs[3] = {  0.0,  3.0,  6.0}; // PS
    cs_mfs[4] = {  4.0,  7.0, 10.0}; // PL

    // Initialize rules
    rules = {
        {4, 0, 0}, {4, 1, 0}, {4, 2, 0}, {4, 3, 1}, {4, 4, 2},
        {3, 0, 0}, {3, 1, 1}, {3, 2, 1}, {3, 3, 2}, {3, 4, 3},
        {2, 0, 3}, {2, 1, 2}, {2, 2, 2}, {2, 3, 2}, {2, 4, 1},
        {1, 0, 3}, {1, 1, 2}, {1, 2, 1}, {1, 3, 1}, {1, 4, 0},
        {0, 0, 2}, {0, 1, 3}, {0, 2, 4}, {0, 3, 4}, {0, 4, 4}
    };
}

void FuzzyController::run() {
    mutex.lock();
    isRunning = true;
    mutex.unlock();

    while (true) {
        mutex.lock();
        if (!isRunning) {
            mutex.unlock();
            break;
        }
        mutex.unlock();
        Probabilities probs;
        bool success = probProvider->getProbabilities(probs);

        if (!success) {
            QThread::msleep(40);
            continue;
        }
        double current_ot = probs.left - probs.right;
        double dt = current_ot - previous_ot;
        previous_ot = current_ot;

        double correction = computeCorrection(current_ot, dt);

        //platform->applyCorrection(correction);

        QThread::msleep(40);
    }
}


void FuzzyController::stop() {
    mutex.lock();
    isRunning = false;
    mutex.unlock();
    wait(); // Wait for thread to finish
}

double FuzzyController::triangularMembership(double x, const TriangularMF& mf) const {
    if (x < mf.a || x > mf.c) return 0.0;
    if (x <= mf.b) return (x - mf.a) / (mf.b - mf.a);
    else return (mf.c - x) / (mf.c - mf.b);
}

std::array<double, 5> FuzzyController::fuzzify(double x, const std::array<TriangularMF, 5>& mfs) const {
    std::array<double, 5> memberships;
    for (int i = 0; i < 5; ++i) {
        memberships[i] = triangularMembership(x, mfs[i]);
    }
    return memberships;
}

double FuzzyController::computeCorrection(double offset_tendency, double delta_tendency) {
    // Fuzzify inputs
    auto mem_ot = fuzzify(offset_tendency, ot_mfs);
    auto mem_dt = fuzzify(delta_tendency, dt_mfs);

    // Initialize aggregated membership function
    std::vector<double> agg_membership(num_cs_points, 0.0);

    // Evaluate rules
    for (const auto& rule : rules) {
        double firing_strength = std::min(mem_ot[rule.ante1], mem_dt[rule.ante2]);
        const auto& cons_mf = cs_mfs[rule.cons];
        for (int k = 0; k < num_cs_points; ++k) {
            double x_cs = cs_min + k * cs_step;
            double mem_cons = triangularMembership(x_cs, cons_mf);
            double clipped_mem = std::min(mem_cons, firing_strength);
            agg_membership[k] = std::max(agg_membership[k], clipped_mem);
        }
    }

    // Defuzzify using centroid method
    double numerator = 0.0;
    double denominator = 0.0;
    for (int k = 0; k < num_cs_points; ++k) {
        double x_cs = cs_min + k * cs_step;
        numerator += x_cs * agg_membership[k];
        denominator += agg_membership[k];
    }
    if (denominator > 0.0) {
        return numerator / denominator;
    } else {
        return 0.0; // No correction if no rules fire
    }
}
