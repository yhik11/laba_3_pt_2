#include "model.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>

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

void Model::saveToFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << a << " " << b << " " << c;
        file.close();
    }
}

void Model::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> a >> b >> c;
        file.close();

        a = std::max(0, std::min(a, 100));
        b = std::max(0, std::min(b, 100));
        c = std::max(0, std::min(c, 100));

        if (a > b) std::swap(a, b);
        if (b > c) std::swap(b, c);
        if (a > b) std::swap(a, b);

        emit dataChanged();
    }
}
