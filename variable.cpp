#include "variable.h"

Variable::Variable(QChar name){
    setName(name);
    vars_ = * new QList<bool>;
}
Variable::Variable(QString name){
    setName(name);
    vars_ = * new QList<bool>;
}
Variable::Variable(QChar name, QList<bool> * vars){
    setName(name);
    setVars(*vars);
}
Variable::Variable(QChar name, int numberVariables, int positionVariable){
    setName(name);
    setVars(numberVariables, positionVariable);
}
Variable Variable::conjunction(Variable other){
    Variable v = * new Variable(makeName(getName(), " * ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] * other.getVars()[i]);
    v.setVars(temp);
    return v;
}
Variable Variable::disjunction(Variable other){
    Variable v = * new Variable(makeName(getName(), " + ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] + other.getVars()[i]);
    v.setVars(temp);
    return v;
}
Variable Variable::implication(Variable other){
    Variable v = * new Variable(makeName(getName(), " -> ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == 1 && other.getVars()[i] == 0 ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::converse(Variable other){
    Variable v = * new Variable(makeName(getName(), " <- ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == 0 && other.getVars()[i] == 1 ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::notAnd(Variable other){
    Variable v = * new Variable(makeName(getName(), " | ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == 1 && other.getVars()[i] == 1 ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::notOr(Variable other){
    Variable v = * new Variable(makeName(getName(), " # ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == 0 && other.getVars()[i] == 0 ? true : false);
    v.setVars(temp);
    return v;
}
Variable Variable::exclusiveDisjunction(Variable other){
    Variable v = * new Variable(makeName(getName(), " # ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.getVars()[i] ? true : false);
    v.setVars(temp);
    return v;
}
Variable Variable::equivalent(Variable other){
    Variable v = * new Variable(makeName(getName(), " # ", other.getName()));
    QList<bool> temp = * new QList<bool>;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.getVars()[i] ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::negation(){
    for(int i = 0; i < vars_.size(); i++)
        vars_[i] = !vars_[i];
    return *this;
}

void Variable::setName(QString name){
    name_ = name;
    return;
}
void Variable::setVars(QList<bool> vars){
    vars_ = vars;
    return;
}
void Variable::setVars(int index, int size){
    vars_ = * new QList<bool>;
    int switcherCounter = 0;
    bool switcher = false;
    for(int i = 0; i < pow2(size); i++){
        if(switcherCounter < pow2(size - index - 1)) // swap 0 1 2 3 to 3 2 1 0
            switcherCounter++;
        else{
            switcher = !switcher;
            switcherCounter = 1;
        }
        vars_.push_back(switcher);
    }
    return;
}
QString Variable::getName(){
    return name_;
}
QList<bool> Variable::getVars(){
    return vars_;
}
QString Variable::makeName(QString first, QString operation, QString second){
    return first + operation + second;
}
int Variable::pow2(int power){
    return 1 << power;
}
