#include "inputeditor.h"

InputEditor::InputEditor(QLineEdit *input)
{
    input_ = input;
    v_ = new QList<QString>();
    fillConsts();
}
void InputEditor::PushBack(QString str){
    if(!isValidity())
        parse(input_->text());
    v_->push_back(str);
    updateInput();
    return;
}
void InputEditor::fillConsts(){
    AVIABLE_WORDS << "*" << "+" << "!" << "^" << "->" << "<-" << "~" << "|" << "#"
                  << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "X" << "Y" << "Z"
                  << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "x" << "y" << "z"
                  << "(" << ")";
    AVIABLE_TRANSFORMATIONS["conjunction"] = "*";
    AVIABLE_TRANSFORMATIONS["disjunction"] = "+";
    AVIABLE_TRANSFORMATIONS["exclusive_disjunction"] = "^";
    AVIABLE_TRANSFORMATIONS["not_and"] = "|";
    AVIABLE_TRANSFORMATIONS["not_or"] = "#";
    AVIABLE_TRANSFORMATIONS["implication"] = "->";
    AVIABLE_TRANSFORMATIONS["converse"] = "<-";
    AVIABLE_TRANSFORMATIONS["equivalent"] = "~";
    AVIABLE_TRANSFORMATIONS["negation"] = "!";
    return;
}
QList<QString> * InputEditor::getVars(){
    return v_;
}
void InputEditor::updateInput(){
    input_->setText(toString());
    return;
}
QString InputEditor::toString(){
    QString res;
    for(int i = 0; i < v_->length(); i++)
        res.append(v_->at(i)).append(" ");
    return res;
}
bool InputEditor::isValidity(){
    return input_->text() == toString();
}
bool InputEditor::parse(QString str){
    QList<int> *errors = new QList<int>;
    QStringList sl = str.trimmed().split(QRegExp("\\s"));
    for(int i = 0; i < sl.count(); i++)
        if(AVIABLE_WORDS.indexOf(sl[i]) == -1)
            errors->push_back(i);
    if(errors->length() == 0){
        v_->clear();
        for(int i = 0; i < sl.length(); i++)
            v_->append(sl[i]);
    }
    else{
        QString msg;
        msg.append("Неправильный синтаксис: ");
        for(int i = 0; i < errors->length(); i++)
            msg.append("\" ").append(sl[errors->at(i)]).append(" \", ");
        QMessageBox::information(NULL, "Ошибка", msg);
        return false;
    }
    return true;
}
