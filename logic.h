#ifndef LOGIC_H
#define LOGIC_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QMap>

#include "variable.h"
#include "contenteditor.h"

class Logic
{
public:
    Logic(QPlainTextEdit *output);
    Logic(QList<QString> *v, QPlainTextEdit *output);
    ~Logic();
    void setVars(QList<QString> *v);
    void compute();
    void computeLogicalAction(QList<QString> *v);
    QList<QString> getVarsTitle() const;
    QList<QList<bool>> getVarsData() const;
    void makeSKNF();
    void makeSDNF();

private:
    void negation(QList<QString> *v);
    void findBrackets(QList<QString> *v);
    QList<QString> * subString(QList<QString> *v, int begin, const int end);
    void binaryOperation(QList<QString> *v, const QString operation);

    void showError(const QString logicOperation, const QString error) const;
    void insertWithReplace(QList<QString> *v, const Variable variable, const int begin, const int end);
    Variable getVariable(const QString name) const;

    void fillVars();
    void fillMap();
    bool isRepeat(const QChar c) const;
    void sortVars();
    void makeBoolArrays();

    QList<Variable> vars_;
    QList<QString> *v_;
    QMap<QString, int> map_;
    ContentEditor *ce_;

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
    };
    const QMap<QString, int> BINARY_OPERATIONS_TO_NUM_ {
        {"conjunction", 1},
        {"disjunction", 2},
        {"implication", 3},
        {"converse", 4},
        {"equivalent", 5},
        {"exclusiveDisjunction", 6},
        {"notAnd", 7},
        {"notOr", 8}
    };
    const QList<QString> AVIABLE_NAME_OF_VARS_ {
        "A", "B", "C", "D", "E", "F", "G", "X", "Y", "Z",
        "a", "b", "c", "d", "e", "f", "g", "x", "y", "z"
    };
};

#endif // LOGIC_H
