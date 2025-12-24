#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Устанавливаем начальные диапазоны
    ui->spinBoxA->setRange(0, 100);
    ui->spinBoxB->setRange(0, 100);
    ui->spinBoxC->setRange(0, 100);

    ui->SliderA->setRange(0, 100);
    ui->SliderB->setRange(0, 100);
    ui->SliderC->setRange(0, 100);

    // Загружаем данные из файла
    model.loadFromFile("model_data.txt");

    setupConnections();

    // Принудительно обновляем UI сразу после загрузки
    updateUI();

    qDebug() << "Application started";
    qDebug() << "Initial values: A=" << model.getA()
             << "B=" << model.getB()
             << "C=" << model.getC() << "\n";
}

MainWindow::~MainWindow() {
    // Сохраняем данные при закрытии
    model.saveToFile("model_data.txt");
    qDebug() << "Application closed, values saved to model_data.txt";
    delete ui;
}

void MainWindow::setupConnections() {
    // Подключаем сигнал модели к обновлению UI
    connect(&model, &Model::dataChanged, this, &MainWindow::updateUI);

    // Подключаем UI элементы к модели
    connect(ui->spinBoxA, QOverload<int>::of(&QSpinBox::valueChanged),
            &model, &Model::setA);
    connect(ui->spinBoxB, QOverload<int>::of(&QSpinBox::valueChanged),
            &model, &Model::setB);
    connect(ui->spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged),
            &model, &Model::setC);

    connect(ui->SliderA, &QSlider::valueChanged,
            &model, &Model::setA);
    connect(ui->SliderB, &QSlider::valueChanged,
            &model, &Model::setB);
    connect(ui->SliderC, &QSlider::valueChanged,
            &model, &Model::setC);
}

void MainWindow::updateUI() {
    // Блокируем сигналы чтобы избежать рекурсии
    ui->spinBoxA->blockSignals(true);
    ui->spinBoxB->blockSignals(true);
    ui->spinBoxC->blockSignals(true);

    ui->SliderA->blockSignals(true);
    ui->SliderB->blockSignals(true);
    ui->SliderC->blockSignals(true);

    // Обновляем диапазон слайдера B в зависимости от A и C
    ui->SliderB->setMinimum(model.getA());
    ui->SliderB->setMaximum(model.getC());
    ui->spinBoxB->setMinimum(model.getA());
    ui->spinBoxB->setMaximum(model.getC());

    // Устанавливаем значения из модели
    ui->spinBoxA->setValue(model.getA());
    ui->spinBoxB->setValue(model.getB());
    ui->spinBoxC->setValue(model.getC());

    ui->SliderA->setValue(model.getA());
    ui->SliderB->setValue(model.getB());
    ui->SliderC->setValue(model.getC());

    // Разблокируем сигналы
    ui->spinBoxA->blockSignals(false);
    ui->spinBoxB->blockSignals(false);
    ui->spinBoxC->blockSignals(false);

    ui->SliderA->blockSignals(false);
    ui->SliderB->blockSignals(false);
    ui->SliderC->blockSignals(false);

    static int updateCount = 0;
    updateCount++;
    qDebug() << "UI Update #" << updateCount
             << ": A=" << model.getA()
             << "B=" << model.getB()
             << "C=" << model.getC();
}

// Слоты для ручного подключения (если используешь auto-connect)
void MainWindow::on_spinBoxA_valueChanged(int value) {
    model.setA(value);
}

void MainWindow::on_spinBoxB_valueChanged(int value) {
    model.setB(value);
}

void MainWindow::on_spinBoxC_valueChanged(int value) {
    model.setC(value);
}

void MainWindow::on_SliderA_valueChanged(int value) {
    model.setA(value);
}

void MainWindow::on_SliderB_valueChanged(int value) {
    model.setB(value);
}

void MainWindow::on_SliderC_valueChanged(int value) {
    model.setC(value);
}
