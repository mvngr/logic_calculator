#ifndef LOGIC_H
#define LOGIC_H
#include <QList>
#include <QDebug>
#include <QString>
#include <QChar>
#include <variable.h>
#include <contenteditor.h>
#include <QMessageBox>
#include <QMap>

class Logic
{
public:
    Logic(QPlainTextEdit *output);
    Logic(QList<QString> *v, QPlainTextEdit *output);
    ~Logic();
    void setVars(QList<QString> *v);
    void compute();
    void computeLogicalAction(QList<QString> *v);
    QList<QString> getVarsTitle();
    QList<QList<bool>> getVarsData();

private:
    void negation(QList<QString> *v);
    void findBrackets(QList<QString> *v);
    QList<QString> * subString(QList<QString> *v, int begin, int end);
    void binaryOperation(QList<QString> *v, QString operation);
    void fillOperations();
    QMap<QString, QString> BINARY_OPERATIONS_;
    QMap<QString, int> BINARY_OPERATIONS_TO_NUM_;

    void showError(QString logicOperation, QString error);
    void insertWithReplace(QList<QString> *v, Variable variable, int begin, int end);
    Variable getVariable(QString name);

    void fillVars();
    void fillMap();
    QList<Variable> vars_;
    QList<QString> *v_;
    QMap<QString, int> map_;
    ContentEditor *ce_;
    QList<QString> AVIABLE_NAME_OF_VARS_;
    bool isRepeat(QChar *c);
    void sortVars();
    void makeBoolArrays();
};

#endif // LOGIC_H
