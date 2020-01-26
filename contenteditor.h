#ifndef CONTENTEDITOR_H
#define CONTENTEDITOR_H

#include <QList>
#include <QString>
#include <QPlainTextEdit>

class ContentEditor
{
public:
    ContentEditor(QPlainTextEdit *plainTextEdit);
    void printTruthTable(const QList<QString> &title, const QList<QList<bool>> &data);
    void printSKNF(QString sknf) const;
    void printSDNF(QString sdnf) const;

    const int minimumColumnCharSize = 5;
private:
    QPlainTextEdit *pte_;
    QList<int> cellSize_;

    QList<int> getSize(const QList<QString> &title) const;
    QString makeString(char segment, int amount) const;
    QString makeLine() const;
    QString makeTitle(const QList<QString> &title) const;
    QString makeData(const QList<QList<bool> > &data) const;
    QString centerAlign(QString text, const int cellSize) const;
};

#endif // CONTENTEDITOR_H
