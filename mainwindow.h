#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <inputeditor.h>
#include <variable.h>
#include <logic.h>

namespace Ui {
class MainWindow;
}
class InputEditor;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:
    void inputPressed();
    void onClicked();
    void bindConnect() const;

    void on_compute_clicked();

    void on_f5_clicked();

    void on_f4_clicked();

private:
    void connectQss();
    InputEditor *ie_;
    Logic *logic_;
};

#endif // MAINWINDOW_H
