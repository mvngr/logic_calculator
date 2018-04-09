#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <inputeditor.h>
#include <contenteditor.h>
#include <variable.h>

namespace Ui {
class MainWindow;
}
class InputEditor;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:
    void inputPressed();
    void onClicked();
    void bindConnect();

private:
    void connectQss();
    InputEditor *ie_;
    ContentEditor *ce_;
};

#endif // MAINWINDOW_H
