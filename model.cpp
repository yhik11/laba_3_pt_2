#include "model.h"
#include <algorithm>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QDir>

Model::Model() : a(25), b(50), c(75) {
    qDebug() << "Model constructor: default A=" << a << "B=" << b << "C=" << c;
}

void Model::loadFromFile(const QString& filename) {
    qDebug() << "\n=== LOADING FROM FILE ===";
    qDebug() << "File:" << filename;

    QFile file(filename);

    if (!file.exists()) {
        qDebug() << "File doesn't exist. Creating with defaults.";
        a = 25; b = 50; c = 75;
        saveToFile(filename);
        emit dataChanged();
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ERROR: Cannot open file for reading!";
        return;
    }

    QTextStream in(&file);
    int valA, valB, valC;
    in >> valA >> valB >> valC;
    file.close();

    qDebug() << "Raw values from file:" << valA << valB << valC;

    if (in.status() != QTextStream::Ok) {
        qDebug() << "ERROR: Failed to read numbers! Using defaults.";
        a = 25; b = 50; c = 75;
        saveToFile(filename);
        emit dataChanged();
        return;
    }

    // Ограничиваем 0..100
    valA = std::max(0, std::min(valA, 100));
    valB = std::max(0, std::min(valB, 100));
    valC = std::max(0, std::min(valC, 100));

    // Упорядочиваем: A <= B <= C
    if (valA > valB) std::swap(valA, valB);
    if (valB > valC) std::swap(valB, valC);
    if (valA > valB) std::swap(valA, valB);

    a = valA;
    b = valB;
    c = valC;

    qDebug() << "Successfully loaded: A=" << a << "B=" << b << "C=" << c;
    qDebug() << "=== END LOADING ===\n";

    emit dataChanged();
}

void Model::saveToFile(const QString& filename) {
    qDebug() << "\n=== SAVING TO FILE ===";
    qDebug() << "File:" << filename;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "ERROR: Cannot open file for writing!";
        return;
    }

    QTextStream out(&file);
    out << a << " " << b << " " << c;
    file.close();

    qDebug() << "Saved: A=" << a << "B=" << b << "C=" << c;
    qDebug() << "=== END SAVING ===\n";
}

void Model::setA(int value) {
    if (value == a) return;

    int newA = std::max(0, std::min(value, 100));

    // A не может быть больше C! Упираемся в C
    if (newA > c) {
        newA = c; // Ограничиваем A сверху значением C
    }

    // Сохраняем A
    a = newA;

    // Если A > B, то поднимаем B до A
    if (a > b) {
        b = a;
    }
    // C НЕ МЕНЯЕТСЯ!

    qDebug() << "Model changed (setA): A=" << a << "B=" << b << "C=" << c;
    emit dataChanged();
}

void Model::setC(int value) {
    if (value == c) return;

    int newC = std::max(0, std::min(value, 100));

    // C не может быть меньше A! Упираемся в A
    if (newC < a) {
        newC = a; // Ограничиваем C снизу значением A
    }

    // Сохраняем C
    c = newC;

    // Если C < B, то опускаем B до C
    if (c < b) {
        b = c;
    }
    // A НЕ МЕНЯЕТСЯ!

    qDebug() << "Model changed (setC): A=" << a << "B=" << b << "C=" << c;
    emit dataChanged();
}

void Model::setB(int value) {
    if (value == b) return;

    int newB = std::max(0, std::min(value, 100));

    // ЗАПРЕЩАЮЩЕЕ поведение: если B вне [A, C] - не меняем
    if (newB < a || newB > c) {
        qDebug() << "Model rejected (setB):" << value << "not in [" << a << "," << c << "]";
        return;
    }

    b = newB;
    qDebug() << "Model changed (setB): A=" << a << "B=" << b << "C=" << c;
    emit dataChanged();
}
