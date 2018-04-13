#include "logic.h"

Logic::Logic(QPlainTextEdit *output){
    v_ = new QList<QString>;
    vars_ = *new QList<Variable>;
    ce_ = new ContentEditor(output);
}
Logic::Logic(QList<QString> *v, QPlainTextEdit *output)
{
    vars_ = *new QList<Variable>;
    ce_ = new ContentEditor(output);
    setVars(v);
}
Logic::~Logic(){
    vars_.~QList();
    v_->~QList();
    AVIABLE_NAME_OF_VARS_.~QList();
}
void Logic::setVars(QList<QString> *v){
    v_ = v;
    fillVars();
    sortVars();
    makeBoolArrays();
}
void Logic::compute(){
    ce_->printTruthTable(getVarsTitle(), getVarsData());
    return;
}
void Logic::fillVars(){
    vars_.clear();
    AVIABLE_NAME_OF_VARS_ << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "X" << "Y" << "Z"
                          << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "x" << "y" << "z";
    for(int i = 0; i < v_->length(); i++){
        QChar c = v_->at(i).at(0);
        if(AVIABLE_NAME_OF_VARS_.indexOf(v_->at(i)) != -1 && !isRepeat( &c )){
            if(vars_.length() < 16)
                vars_.append(*new Variable(v_->at(i).at(0)));
            else{
                QMessageBox::information(NULL, "Ошибка", "Увы, слишком много переменных. \nНекоторые введенные переменные будут удалены");
                break;
            }
        }
    }
}
bool Logic::isRepeat(QChar *c){
    for(int i = 0; i < vars_.length(); i++)
        if(vars_[i].getName() == *c)
            return true;
    return false;
}
void Logic::sortVars(){
    for(int i = 0; i < vars_.length() - 1; i++)
        for( int j = i+1; j < vars_.length(); j++)
            if(QString::compare((QString)vars_[i].getName(), (QString)vars_[j].getName()) > 0)
            {
                QString c = vars_[i].getName();
                vars_[i].setName(vars_[j].getName());
                vars_[j].setName(c);
            }
    return;
}
void Logic::makeBoolArrays(){
    int length = vars_.length();
    for(int i = 0; i < length; i++)
        vars_[i].setVars(i, length);
    return;
}
QList<QString> Logic::getVarsTitle(){
    QList<QString> result = * new QList<QString>;
    for(int i = 0; i < vars_.length(); i++)
        result.push_back((QString)vars_[i].getName());
    return result;
}
QList<QList<bool>> Logic::getVarsData(){
    QList<QList<bool>> result = * new QList<QList<bool>>;
    for(int i = 0; i < vars_.length(); i++)
        result.push_back(vars_[i].getVars());
    return result;
}
