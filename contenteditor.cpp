#include "contenteditor.h"

ContentEditor::ContentEditor(QPlainTextEdit *plainTextEdit)
{
    pte_ = plainTextEdit;
}
void ContentEditor::printTruthTable(QList<QString> title, QList<QList<bool>> data){
    cellSize_ = getSize(title);
    QString output = * new QString;
    output.append(makeTitle(title));
    output.append(makeLine());
    output.append(makeData(data));
    pte_->setPlainText(output);

    return;
}
QString ContentEditor::makeString(char segment, int amount){
    QString res;
    while (amount-- != 0)
        res.append(segment);
    return res;
}
QList<int> ContentEditor::getSize(QList<QString> title){
    QList<int> size = * new QList<int>;
    foreach (QString temp, title)
        size.append(temp.length() > 5 ? temp.length() : 5);
    return size;
}
QString ContentEditor::centerAlign(QString text, int cellSize){
    QString result = * new QString;
    int spaceCount = text.length() > cellSize ? 0 : cellSize - text.length();
    result.append(makeString(' ', spaceCount / 2));
    result.append(text);
    result.append(makeString(' ', spaceCount % 2 == 0 ? spaceCount / 2 : spaceCount / 2 + 1));
    return result;
}
QString ContentEditor::makeTitle(QList<QString> title){
    QString output = * new QString;
    for(int i = 0; i < title.length(); i++){
        output.append(centerAlign(title.at(i), cellSize_.at(i)));
        if(i + 1 != title.length()){
            output.append("|");
        }
    }
    return output;
}
QString ContentEditor::makeLine(){
    QString result = * new QString;
    result.append('\n');
    for(int i = 0; i < cellSize_.length(); i++){
        result.append(makeString('-', cellSize_[i]));
        if(i + 1 != cellSize_.length())
            result.append('+');
    }
    return result;
}
QString ContentEditor::makeData(QList<QList<bool>> data){
    QString result = * new QString;
    if(data.length() == 0)
        return result;
    for(int i = 0; i < data[0].length(); i++){
        result.append('\n');
        for(int j = 0; j < data.length(); j++){
            result.append(centerAlign(data[j][i] ? "1" : "0", cellSize_.at(j)));
            if(j + 1 != data.length() )
                result.append('|');
        }
    }
    return result;
}
void ContentEditor::printSKNF(QString sknf){
    pte_->setPlainText(pte_->toPlainText() + "\n\nСКНФ: " + sknf);
    return;
}
void ContentEditor::printSDNF(QString sdnf){
    pte_->setPlainText(pte_->toPlainText() + "\n\nСДНФ: " + sdnf);
    return;
}
