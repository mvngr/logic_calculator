#ifndef INPUTEDITOR_H
#define INPUTEDITOR_H

#include <QStringList>
#include <QLineEdit>
#include <QMessageBox>
#include <QMap>

/*!
 * \brief InputEditor - Класс отвечает за обработку данных, вводимых в поле ввода данных
 */
class InputEditor
{
public:
    InputEditor(QLineEdit *input);
    ~InputEditor();

    const QList<QString> AVIABLE_WORDS {
        "*" , "+" , "!" , "^" , "->" , "<-" , "~" , "|" , "#",
        "A" , "B" , "C" , "D" , "E" , "F" , "G" , "X" , "Y" , "Z",
        "a" , "b" , "c" , "d" , "e" , "f" , "g" , "x" , "y" , "z",
        "(" , ")"
    }; ///Словарь доступных символов
    const QMap<QString,QString> AVIABLE_TRANSFORMATIONS {
        {"conjunction", "*"},
        {"disjunction", "+"},
        {"exclusive_disjunction", "^"},
        {"not_and", "|"},
        {"not_or", "#"},
        {"implication", "->"},
        {"converse", "<-"},
        {"equivalent", "~"},
        {"negation", "!"}
    }; ///словарь доступных действий

    void pushBack(const QString &str); //Добавляет определенные данные в конец внутреннего массива
    QString toString() const; //Преобразует внутренний массив в строку
    bool parse(const QString &str); //Парсит введенную строку
    QList<QString> *getVars(); //Выдает указатель на внутренний массив данных

private:
    QLineEdit *input_; ///Используется для управления полем ввода данных
    QList<QString> *v_; ///Внутренний массив для хранения данных из поля ввода данных
    void updateInput(); //Обновляет поле для ввода данных
    bool isValidity() const;

};

#endif // INPUTEDITOR_H
