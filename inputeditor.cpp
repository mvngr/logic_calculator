#include "inputeditor.h"

InputEditor::InputEditor(QLineEdit *input) : input_(input), v_(new QList<QString>){}
InputEditor::~InputEditor(){
    //delete v_; в соседнем классе чистится v_ (эх, костылики)
}
void InputEditor::pushBack(const QString &str){
    if(!isValidity())
        parse(input_->text());
    v_->push_back(str);
    updateInput();
}
//эх... исправить бы этот метод на более безопасный вариант
QList<QString> *InputEditor::getVars(){
    return v_;
}
void InputEditor::updateInput(){
    input_->setText(toString());
}
QString InputEditor::toString() const {
    return v_->join(" ");
}
bool InputEditor::isValidity() const {
    return input_->text() == toString();
}
bool InputEditor::parse(const QString &str){
    bool res = true;
    QList<int> errors;
    QStringList sl = str.trimmed().split(" ");
    for(int i = 0; i < sl.count(); i++)
        if(AVIABLE_WORDS.indexOf(sl[i]) == -1)
        {
            errors.push_back(i);
        }
    if(errors.length() == 0){
        delete v_;
        v_ = new QList<QString>(sl);
    }
    else{
        QString msg("Неправильный синтаксис: ");
        for(const int &error : errors)
            msg.append("\" ").append(sl[error]).append(" \", ");
        QMessageBox::warning(nullptr, "Ошибка", msg);
        res = false;
    }
    return res;
}
