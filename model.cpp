#include "model.h"
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Model::Model() : a(25), b(50), c(75) {
    qDebug() << "Model created: A =" << a << "B =" << b << "C =" << c;
}

void Model::setA(int value) {
    if (value == a) return;

    int newA = std::max(0, std::min(value, 100));

    // Сохраняем A
    a = newA;

    // Если A > B, то ПОДНИМАЕМ B до A
    if (a > b) {
        b = a;
        // Если B стал больше C - это ОК по "разрешающему" поведению
    }

    qDebug() << "Model changed (setA): A =" << a << "B =" << b << "C =" << c;
    qDebug() << "  New range for B: [" << a << "-" << c << "]";
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
    qDebug() << "Model changed (setB): A =" << a << "B =" << b << "C =" << c;
    emit dataChanged();
}

void Model::setC(int value) {
    if (value == c) return;

    int newC = std::max(0, std::min(value, 100));

    // Сохраняем C
    c = newC;

    // Если C < B, то ОПУСКАЕМ B до C
    if (c < b) {
        b = c;
        // Если B стал меньше A - это ОК по "разрешающему" поведению
    }

    qDebug() << "Model changed (setC): A =" << a << "B =" << b << "C =" << c;
    qDebug() << "  New range for B: [" << a << "-" << c << "]";
    emit dataChanged();
}

void Model::saveToFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << a << " " << b << " " << c;
        file.close();
        qDebug() << "Model saved to" << filename << ": A =" << a << "B =" << b << "C =" << c;
    }
}

void Model::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> a >> b >> c;
        file.close();

        // Корректируем значения 0..100
        a = std::max(0, std::min(a, 100));
        b = std::max(0, std::min(b, 100));
        c = std::max(0, std::min(c, 100));

        // ВАЖНО: при загрузке нужно обеспечить A <= B <= C
        // Потому что файл мог быть сохранен в "нарушенном" состоянии
        if (a > b) b = a;  // Поднимаем B до A
        if (b > c) c = b;  // Поднимаем C до B

        qDebug() << "Model loaded from" << filename << ": A =" << a << "B =" << b << "C =" << c;
        emit dataChanged();
    } else {
        qDebug() << "File not found, using default values";
    }
}
