#include "logic.h"

Logic::Logic(QPlainTextEdit *output){
    v_ = new QList<QString>;
    vars_ = new QList<Variable *>;
    ce_ = new ContentEditor(output);
}
Logic::Logic(QList<QString> *v, QPlainTextEdit *output)
{
    vars_ = new QList<Variable *>;
    setVars(v);
    ce_ = new ContentEditor(output);
}
void Logic::setVars(QList<QString> *v){
    v_ = v;
    fillVars();
    sortVars();
    makeBoolArrays();
    QList<QString>  str = *getVarsTitle();
    QList<bool> blist = *getVarsData();
    //ce_->printTruthTable(*str, *blist);
}
void Logic::fillVars(){
    AVIABLE_NAME_OF_VARS_ << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "X" << "Y" << "Z"
                          << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "x" << "y" << "z";
    for(int i = 0; i < v_->length(); i++){
        QChar c = v_->at(i).at(0);
        if(AVIABLE_NAME_OF_VARS_.indexOf(v_->at(i)) != -1 && !isRepeat( &c )){
            Variable *temp = new Variable(v_->at(i).at(0));
            vars_->append( temp );
        }
    }
}
bool Logic::isRepeat(QChar *c){
    for(int i = 0; i < vars_->length(); i++)
        if(vars_->at(i)->getName() == *c)
            return true;
    return false;
}
void Logic::sortVars(){
    for(int i = 0; i < vars_->length() - 1; i++)
            for( int j = i+1; j < vars_->length(); j++)
                if(QString::compare((QString)vars_->at(i)->getName(), (QString)vars_->at(j)->getName()) > 0)
                {
                    QChar c = vars_->at(i)->getName();
                    vars_->at(i)->setName(vars_->at(j)->getName());
                    vars_->at(j)->setName(c);
                }
    return;
}
void Logic::makeBoolArrays(){
    int length = vars_->length();
    for(int i = 0; i < length; i++)
        vars_->at(i)->setVars(i, length);
    return;
}
QList<QString> * Logic::getVarsTitle(){
    QList<QString> *result;
    for(int i = 0; i < vars_->length(); i++)
        result->push_back((QString)vars_->at(i)->getName());
    return result;
}
QList<bool> * Logic::getVarsData(){
    QList<bool> * result;
    for(int i = 0; i < vars_->length(); i++)
        result->push_back(vars_->at(i)->getVars());
    return result;
}
