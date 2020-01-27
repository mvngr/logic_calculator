#ifndef INPUTEDITOR_H
#define INPUTEDITOR_H

#include <QStringList>
#include <QLineEdit>
#include <QMessageBox>
#include <QMap>

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
    };
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
    };

    void pushBack(const QString &str);
    QString toString() const;
    bool parse(const QString &str);
    QList<QString> *getVars();

private:
    QLineEdit *input_;
    QList<QString> *v_;
    void updateInput();
    bool isValidity() const;

};

#endif // INPUTEDITOR_H
