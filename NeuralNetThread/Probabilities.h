// Probabilities.h
#ifndef PROBABILITIES_H
#define PROBABILITIES_H

#include <QMetaType>

struct Probabilities {
    double left;
    double none;
    double right;
};

Q_DECLARE_METATYPE(Probabilities)

#endif // PROBABILITIES_H
