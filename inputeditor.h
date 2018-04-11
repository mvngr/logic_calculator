#ifndef INPUTEDITOR_H
#define INPUTEDITOR_H
#include <QString>
#include <QStringList>
#include <QList>
#include <QLineEdit>
#include <mainwindow.h>
#include <QMessageBox>
#include <QMap>


class InputEditor
{
public:
    InputEditor(QLineEdit *input);

    QList<QString> AVIABLE_WORDS;
    QMap<QString,QString> AVIABLE_TRANSFORMATIONS;

    void PushBack(QString str);
    QString toString();
    bool parse(QString str);
    QList<QString> * getVars();

private:
    QLineEdit *input_;
    QList<QString> *v_;
    void updateInput();
    void fillConsts();
    bool isValidity();

};

#endif // INPUTEDITOR_H
