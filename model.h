#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject {
    Q_OBJECT

private:
    int a, b, c;

public:
    Model();

    int getA() const { return a; }
    int getB() const { return b; }
    int getC() const { return c; }

    void setA(int value);
    void setB(int value);
    void setC(int value);

    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);

signals:
    void dataChanged();
};

#endif
