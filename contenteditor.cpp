#include "contenteditor.h"

ContentEditor::ContentEditor(QPlainTextEdit *plainTextEdit)
{
    pte_ = plainTextEdit;
}
void ContentEditor::printTruthTable(QList<QString> *title, QList<QList<bool>> *data){
    QList<int> *size = new QList<int>;
    QString *output;
    fillSize(size, title);
    for(int i = 0; i < size->length(); i++){
        output->append(makeString('-', size->at(i)));
        output->append("+");
    }
    return;
}
void ContentEditor::fillSize(QList<int> *size, QList<QString> *title){
    for(int i = 0; i < title->size(); i++)
        size->push_back(title[i].length() + 2);
    return;
}
QString ContentEditor::makeString(char segment, int amount){
    QString res;
    while (amount-- != 0)
        res.append(segment);
    return res;
}
