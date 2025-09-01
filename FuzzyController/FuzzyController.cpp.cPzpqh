#include "FuzzyController.h"
#include "xyplatform.h"
#include <algorithm>
#include <QThread>
#include <iostream>
#include <qdebug.h>

FuzzyController::FuzzyController(ProbabilityProvider* probProv, QObject* parent)
    : QThread(parent), probProvider(probProv), platform(XyPlatform::getInstance()) {
    // Initialize membership functions
     ot_mfs[0] = {-1.0, -0.7, -0.4}; // NL
     ot_mfs[1] = {-0.6, -0.3, 0.0};  // NS
     ot_mfs[2] = {-0.2, 0.0, 0.2};   // ZE
     ot_mfs[3] = {0.0, 0.3, 0.6};    // PS
     ot_mfs[4] = {0.4, 0.7, 1.0};    // PL
     dt_mfs = ot_mfs;
     cs_mfs[0] = {-1.0, -0.7, -0.4}; // NL (Adjusted)
     cs_mfs[1] = {-0.6, -0.3, 0.0};  // NS
     cs_mfs[2] = {-0.2, 0.0, 0.2};   // ZE
     cs_mfs[3] = {0.0, 0.3, 0.6};    // PS
     cs_mfs[4] = {0.4, 0.7, 1.0};    // PL

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
    {
        QMutexLocker locker(&mutex);
        IsRunning = true;
    }
    while (!QThread::currentThread()->isInterruptionRequested()) {
        Probabilities probs;
        bool success = probProvider->getProbabilities(probs);
        if (!success) {
            QThread::msleep(500); // Short sleep when no probabilities
            continue;
        }

        // Calculate offset tendency
        double ot = probs.left - probs.right;
        otHistory.push_back(ot);
        if (otHistory.size() > windowSize) {
            otHistory.pop_front();
        }

        // Compute window metrics
        double sum = 0.0;
        for (double ot : otHistory) {
            sum += ot;
        }
        double OT_window = otHistory.empty() ? 0.0 : sum / otHistory.size();
        double delta_ot_window = hasPreviousWindow ? OT_window - previousOTWindow : 0.0;
        previousOTWindow = OT_window;
        hasPreviousWindow = true;

        // Apply correction only if significant offset
        if (std::abs(OT_window) > threshold) {
            float correction = static_cast<float>(computeCorrection(OT_window, delta_ot_window));
            qDebug()<< "Correction: " << correction << endl;
            // platform->QuickCorrectionRelatively(correction);//暂时弃用
            emit SendCorrectionRelatively(correction);
        }

        QThread::msleep(500); // Control loop frequency
    }
    {
        QMutexLocker locker(&mutex);
        IsRunning = false;
    }
}

void FuzzyController::stop() {
    QMutexLocker locker(&mutex);
    IsRunning = false;
    mutex.unlock();
    wait();
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

double FuzzyController::computeCorrection(double ot_window, double delta_ot_window) {
    auto mem_ot = fuzzify(ot_window, ot_mfs);
    auto mem_dt = fuzzify(delta_ot_window, dt_mfs);
    std::vector<double> agg_membership(num_cs_points, 0.0);

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

    double numerator = 0.0, denominator = 0.0;
    for (int k = 0; k < num_cs_points; ++k) {
        double x_cs = cs_min + k * cs_step;
        numerator += x_cs * agg_membership[k];
        denominator += agg_membership[k];
    }
    return denominator > 0.0 ? numerator / denominator : 0.0;
}

bool FuzzyController::GetRunningStatus() const {
    QMutexLocker locker(&mutex);
    return IsRunning;
}
