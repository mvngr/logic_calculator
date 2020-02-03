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

/*!
 * \brief MainWindow - Класс отвечает за взаимодействие с пользовательским интерфейсом
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
private slots:
    void inputPressed(); //Обработчик для поля ввода данных, вызывается при нажатии на enter
    void onClicked(); //Обработчик на кнопки логических операций. Добавляет в поле ввода данных соответствующий символ
    void bindConnect() const; //Создаёт связи между обработчиком события onClicked и нажатой кнопкой

    void on_compute_clicked(); //Обработчик нажатия на кнопку Вычислить

    void on_f5_clicked(); //Обработчик для кнопки СКНФ

    void on_f4_clicked(); //Обработчик для кнопки СДНФ

private:
    void connectQss(); //Отвечает за подключение стилей
    InputEditor *ie_; ///отвечает за обработку данных, вводимых в поле ввода данных
    Logic *logic_; ///отвечает за логику выполнения действий
};

#endif // MAINWINDOW_H
