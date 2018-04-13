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
    void printTruthTable(QList<QString> title, QList<QList<bool> > data);
private:
    QPlainTextEdit *pte_;
    QList<int> cellSize_;

    QList<int> getSize(QList<QString> title);
    QString makeString(char segment, int amount);
    QString makeLine();
    QString makeTitle(QList<QString> title);
    QString makeData(QList<QList<bool> > data);
    QString centerAlign(QString text, int cellSize);
};

#endif // CONTENTEDITOR_H
