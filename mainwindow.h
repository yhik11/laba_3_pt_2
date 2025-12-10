#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Model_dataChanged();

    void on_spinBoxA_valueChanged(int value);


    void on_spinBoxB_valueChanged(int arg1);

    void on_spinBoxC_valueChanged(int arg1);

    void on_SliderA_valueChanged(int value);

    void on_SliderB_valueChanged(int value);

    void on_SliderC_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Model model;

    void updateUI();
    void setupConnections();
};

#endif // MAINWINDOW_H
