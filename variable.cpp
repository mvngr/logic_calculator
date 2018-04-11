#include "variable.h"

Variable::Variable(QChar name){
    setName(name);
    vars_ = new QList<bool>;
}
Variable::Variable(QChar name, QList<bool> * vars){
    setName(name);
    setVars(vars);
}
Variable::Variable(QChar name, int numberVariables, int positionVariable){
    setName(name);
    setVars(numberVariables, positionVariable);
}
Variable & Variable::operator=(Variable & v)
{
    name_ = v.name_;
    vars_ = v.vars_;
    return *this;
}
void Variable::setName(QChar name){
    name_ = name;
    return;
}
void Variable::setVars(QList<bool> *vars){
    vars_ = vars;
    return;
}
void Variable::setVars(int index, int size){
    vars_ = new QList<bool>;
    int switcherCounter = 0;
    bool switcher = false;
    for(int i = 0; i < pow2(size); i++){
        if(switcherCounter < pow2(size - index - 1)) // swap 0 1 2 3 to 3 2 1 0 for easy calculations
            switcherCounter++;
        else{
            switcher = !switcher;
            switcherCounter = 1;
        }
        vars_->push_back(switcher);
    }
    return;
}
QChar Variable::getName(){
    return name_;
}
QList<bool> *Variable::getVars(){
    return vars_;
}
int Variable::pow2(int power){
    return 1 << power;
}
