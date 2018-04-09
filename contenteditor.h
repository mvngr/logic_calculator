#ifndef CONTENTEDITOR_H
#define CONTENTEDITOR_H
#include <QList>
#include <QString>
#include <QPlainTextEdit>
#include <QDebug>

class ContentEditor
{
public:
    ContentEditor(QPlainTextEdit *plainTextEdit);
    void printTruthTable(QList<QString> *title, QList<QList<bool>> *data);
private:
    QPlainTextEdit *pte_;
    void fillSize(QList<int> *size, QList<QString> *title);
    QString makeString(char segment, int amount);
};

#endif // CONTENTEDITOR_H
