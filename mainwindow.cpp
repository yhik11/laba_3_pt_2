#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

    model.loadFromFile("model_data.txt");

    setupConnections();
    // updateUI(); // УДАЛЕНО - вызовется автоматически через on_Model_dataChanged()

    qDebug() << "The application is running";
}

MainWindow::~MainWindow() {
    model.saveToFile("model_data.txt");
    qDebug() << "The application is closed, the values are saved to a file.";
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

    // ВАЖНО: Обновляем диапазон слайдера B в зависимости от A и C!
    ui->SliderB->setMinimum(model.getA());  // B не может быть меньше A
    ui->SliderB->setMaximum(model.getC());  // B не может быть больше C

    // Также обновляем spinBoxB диапазон
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

    // Отладочный вывод
    static int updateCount = 0;
    updateCount++;
    qDebug() << "UI Update #" << updateCount
             << ": A =" << model.getA()
             << "B =" << model.getB()
             << "C =" << model.getC()
             << "(B range: [" << model.getA() << "-" << model.getC() << "])";
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
