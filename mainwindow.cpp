#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    model.loadFromFile("model_data.txt");

    setupConnections();
    updateUI();
    qDebug() << "Приложение запущено, загружены значения из файла";
}

MainWindow::~MainWindow() {
    model.saveToFile("model_data.txt");
    qDebug() << "Приложение закрыто, значения сохранены в файл";
    delete ui;
}

void MainWindow::setupConnections() {
    // Подключаем сигнал модели к слоту
    connect(&model, &Model::dataChanged, this, &MainWindow::on_Model_dataChanged);
}

void MainWindow::updateUI() {
    // Блокируем сигналы чтобы избежать рекурсии
    ui->spinBoxA->blockSignals(true);
    ui->spinBoxB->blockSignals(true);
    ui->spinBoxC->blockSignals(true);

    ui->SliderA->blockSignals(true);
    ui->SliderB->blockSignals(true);
    ui->SliderC->blockSignals(true);

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

    // Отладочный вывод
    static int updateCount = 0;
    updateCount++;
    qDebug() << "updateUI вызван" << updateCount << "раз. Значения: A="
             << model.getA() << "B=" << model.getB() << "C=" << model.getC();
}

void MainWindow::on_Model_dataChanged() {
    updateUI();
}

void MainWindow::on_spinBoxA_valueChanged(int value) {
    model.setA(value);
}

void MainWindow::on_spinBoxB_valueChanged(int arg1) {
    model.setB(arg1);
}

void MainWindow::on_spinBoxC_valueChanged(int arg1) {
    model.setC(arg1);
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
