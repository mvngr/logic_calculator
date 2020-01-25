#include "contenteditor.h"

ContentEditor::ContentEditor(QPlainTextEdit *plainTextEdit)
{
    pte_ = plainTextEdit;
}
void ContentEditor::printTruthTable(const QList<QString> &title, const QList<QList<bool>> &data){
    cellSize_ = getSize(title);
    QString output;
    output.append(makeTitle(title));
    output.append(makeLine());
    output.append(makeData(data));
    pte_->setPlainText(output);
}
QString ContentEditor::makeString(char segment, int amount) const {
    QString res;
    while (amount-- != 0)
        res.append(segment);
    return res;
}
QList<int> ContentEditor::getSize(const QList<QString> &title) const {
    QList<int> size;
    for(const QString &temp : title)
        size.append(temp.length() > minimumColumnCharSize ? temp.length() : minimumColumnCharSize);
    return size;
}
QString ContentEditor::centerAlign(const QString text, const int cellSize) const {
    QString result;
    int spaceCount = text.length() > cellSize ? 0 : cellSize - text.length();
    result.append(makeString(' ', spaceCount / 2));
    result.append(text);
    result.append(makeString(' ', spaceCount % 2 == 0 ? spaceCount / 2 : spaceCount / 2 + 1));
    return result;
}
QString ContentEditor::makeTitle(const QList<QString> &title) const {
    QString output;
    for(int i = 0; i < title.length(); i++){
        output.append(centerAlign(title.at(i), cellSize_.at(i)));
        if(i + 1 != title.length()){
            output.append("|");
        }
    }
    return output;
}
QString ContentEditor::makeLine() const {
    QString result;
    result.append('\n');
    for(int i = 0; i < cellSize_.length(); i++){
        result.append(makeString('-', cellSize_[i]));
        if(i + 1 != cellSize_.length())
            result.append('+');
    }
    return result;
}
QString ContentEditor::makeData(const QList<QList<bool>> &data) const {
    QString result;
    if(data.length() == 0) //тут мы проходимся по вдумерному массиву, если он существует
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
void ContentEditor::printSKNF(QString sknf) const {
    pte_->setPlainText(pte_->toPlainText() + "\n\nСКНФ: " + sknf);
}
void ContentEditor::printSDNF(QString sdnf) const {
    pte_->setPlainText(pte_->toPlainText() + "\n\nСДНФ: " + sdnf);
}
