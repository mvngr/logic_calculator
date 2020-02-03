#ifndef LOGIC_H
#define LOGIC_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QMap>

#include "variable.h"
#include "contenteditor.h"

/*!
 * \brief Logic - Класс отвечает за логику выполнения действий
 */
class Logic
{
public:
    Logic(QPlainTextEdit *output);
    ~Logic();
    void setVars(QList<QString> *v); //Добавляет массив логических переменных в внутренний массив
    void compute(); //Инициирует вычисления
    void computeLogicalAction(QList<QString> *v); //Инициирует вычисление таблицы истинности
    QList<QString> getVarsTitle() const; //Отдает массив имен логических переменных
    QList<QList<bool>> getVarsData() const; //Отдает массив всех данных из логических переменных
    void makeSKNF(); //создает Совершенную Конъюнктивную Нормальную Форму
    void makeSDNF(); //создает Совершенную Дизъюнктивную Нормальную Форму

private:
    void negation(QList<QString> *v); //Используется для выполнения отрицания у всей входной строки
    void findBrackets(QList<QString> *v); //Находит выражения в скобках и высчитывает их
    QList<QString> * subString(QList<QString> *v, int begin, const int end); //Возвращает подстроку из строки
    void binaryOperation(QList<QString> *v, const QString &operation); //Используется для выполнения входной операции у всей входной строки

    void showError(const QString &logicOperation, const QString &error) const; //Выводит в пользовательский интерфейс сообщения с ошибками
    void insertWithReplace(QList<QString> *v, const Variable &variable, const int begin, const int end); //Выполняет внедрение логической операции в внутренние массивы взамен переменным(ой) и оператора
    Variable getVariable(const QString &name) const;

    void fillVars(); //Добавляет логические переменные в vars_ из строк v_
    void fillMap(); //Заполняет карту map_
    bool isRepeat(const QChar c) const; //Проверяет на повторение названия имен в vars_
    void sortVars(); //Сортирует массив vars_ по названиям
    void makeBoolArrays(); //Создает массив начальных данных у переменных

    QList<Variable> vars_; ///Массив логических переменных
    QList<QString> *v_; ///Массив строк, разделенных при помощи пробела. Пример: {"A", "*", "B", "+", "!", "C"}
    QMap<QString, int> map_; ///Используется для сопоставления строковых переменных и их аналогов из vars_. <Название переменной> => <Индекс в массиве объекта>
    ContentEditor *ce_; ///Используется для управление полем вывода

public:
    const QMap<QString, QString> BINARY_OPERATIONS_ {
        {"*", "conjunction"},
        {"+", "disjunction"},
        {"^", "exclusiveDisjunction"},
        {"|", "notAnd"},
        {"#", "notOr"},
        {"->", "implication"},
        {"<-", "converse"},
        {"~", "equivalent"}
    }; ///Словарь бинарных операций

    const QMap<QString, int> BINARY_OPERATIONS_TO_NUM_ {
        {"conjunction", 1},
        {"disjunction", 2},
        {"implication", 3},
        {"converse", 4},
        {"equivalent", 5},
        {"exclusiveDisjunction", 6},
        {"notAnd", 7},
        {"notOr", 8}
    }; ///Сопоставление бинарной операции с её внутренним номером (нужно для удобства)

    const QList<QString> AVIABLE_NAME_OF_VARS_ {
        "A", "B", "C", "D", "E", "F", "G", "X", "Y", "Z",
        "a", "b", "c", "d", "e", "f", "g", "x", "y", "z"
    }; ///Словарь разрешенных имен для логических переменных

};

#endif // LOGIC_H
