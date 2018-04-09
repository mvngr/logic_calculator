#include "variable.h"

Variable::Variable(char name){
    setName(name);
    vars_ = new QList<bool>;
}
Variable::Variable(char name, QList<bool> * vars){
    setName(name);
    setVars(vars);
}
Variable::Variable(char name, int numberVariables, int positionVariable){
    setName(name);
    setVars(numberVariables, positionVariable);
}
void Variable::setName(char name){
    name_ = name;
    return;
}
void Variable::setVars(QList<bool> *vars){
    vars_ = vars;
    return;
}
void Variable::setVars(int numberVariables, int positionVariable){
    vars_ = new QList<bool>;
    int switcherCounter = 0;
    bool switcher = false;
    for(int i = 0; i < pow2(numberVariables); i++){
        if(switcherCounter < pow2(numberVariables - positionVariable - 1)) // swap 0 1 2 3 to 3 2 1 0 for easy calculations
            switcherCounter++;
        else{
            switcher = !switcher;
            switcherCounter = 1;
        }
        vars_->push_back(switcher);
    }
    return;
}
char Variable::getName(){
    return name_;
}
QList<bool> *Variable::getVars(){
    return vars_;
}
int Variable::pow2(int power){
    return 1 << power;
}
