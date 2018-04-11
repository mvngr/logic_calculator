#ifndef LOGIC_H
#define LOGIC_H
#include <QList>
#include <QDebug>
#include <QString>
#include <QChar>
#include <variable.h>
#include <contenteditor.h>

class Logic
{
public:
    Logic(QPlainTextEdit *output);
    Logic(QList<QString> *v, QPlainTextEdit *output);
    void setVars(QList<QString> *v);
    QList<QString> * getVarsTitle();
    QList<bool> * getVarsData();
private:
    void fillVars();
    QList<Variable *> *vars_;
    QList<QString> *v_;
    ContentEditor *ce_;
    QList<QString> AVIABLE_NAME_OF_VARS_;
    bool isRepeat(QChar *c);
    void sortVars();
    void makeBoolArrays();
};

#endif // LOGIC_H
