#include "model.h"
#include <algorithm>

Model::Model() : a(25), b(50), c(75) {
}

void Model::setA(int value) {
    if (value == a) return;

    int newA = std::max(0, std::min(value, 100));

    if (newA > b) {
        b = newA;
        if (b > c) c = b;
    }

    a = newA;
    emit dataChanged();
}

void Model::setB(int value) {
    if (value == b) return;

    int newB = std::max(0, std::min(value, 100));

    if (newB < a || newB > c) {
        return;
    }

    b = newB;
    emit dataChanged();
}

void Model::setC(int value) {
    if (value == c) return;

    int newC = std::max(0, std::min(value, 100));

    if (newC < b) {
        b = newC;
        if (b < a) a = b;
    }

    c = newC;
    emit dataChanged();
}
