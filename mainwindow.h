#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPushButton>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_toggled(bool checked);

    void on_horizontalSlider_valueChanged(int);

    void on_reset_clicked();

    void on_close_clicked();

    void on_restart_clicked();

    void on_four_1_clicked();

    void on_four_2_clicked();

    void on_four_3_clicked();

    void on_four_4_clicked();

    void on_four_5_clicked();

    void on_four_6_clicked();

    void on_four_7_clicked();

    void on_four_8_clicked();

    void on_four_9_clicked();

    void on_four_10_clicked();

    void on_four_11_clicked();

    void on_four_12_clicked();

    void on_four_13_clicked();

    void on_four_14_clicked();

    void on_four_15_clicked();

    void on_four_16_clicked();

    void on_pushButton_15_clicked();

    void on_restart_2_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
