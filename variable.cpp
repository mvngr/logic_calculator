#include "variable.h"

Variable::Variable(const QChar name){
    setName(name);
}
Variable::Variable(const QString &name){
    setName(name);
}
Variable::Variable(const QChar name, const QList<bool> * vars){
    setName(name);
    if(vars)
        setVars(*vars);
}
Variable::Variable(const QChar name, const int numberVariables, const int positionVariable){
    setName(name);
    setVars(numberVariables, positionVariable);
}
bool Variable::operator > (const Variable &other)
{
   return name_ > other.name_;
}
bool Variable::operator < (const Variable &other)
{
   return name_ < other.name_;
}

Variable Variable::conjunction(const Variable &other) const{
    Variable v(makeName(getName(), " * ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] && other.vars_[i]);
    v.setVars(temp);
    return v;
}
Variable Variable::disjunction(const Variable &other) const{
    Variable v(makeName(getName(), " + ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] || other.vars_[i]);
    v.setVars(temp);
    return v;
}
Variable Variable::implication(const Variable &other) const{
    Variable v(makeName(getName(), " -> ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == true && other.vars_[i] == false ) ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::converse(const Variable &other) const{
    Variable v(makeName(getName(), " <- ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == false && other.vars_[i] == true ) ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::notAnd(const Variable &other) const{
    Variable v(makeName(getName(), " | ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == true && other.vars_[i] == true ) ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::notOr(const Variable &other) const{
    Variable v(makeName(getName(), " # ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == false && other.vars_[i] == false);
    v.setVars(temp);
    return v;
}
Variable Variable::exclusiveDisjunction(const Variable &other) const{
    Variable v(makeName(getName(), " ^ ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.vars_[i] ? false : true);
    v.setVars(temp);
    return v;
}
Variable Variable::equivalent(const Variable &other) const{
    Variable v(makeName(getName(), " ~ ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.vars_[i] ? true : false);
    v.setVars(temp);
    return v;
}
Variable Variable::negation(){
    setName(QString("! " + getName()));
    for(int i = 0; i < vars_.size(); i++)
        vars_[i] = !vars_[i];
    return *this;
}

void Variable::setName(const QString &name){
    name_ = name;
}
void Variable::setVars(const QList<bool> &vars){
    vars_ = vars;
}
void Variable::setVars(const int index, const int size){
    vars_.clear();
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
}
QString Variable::getName() const{
    return name_;
}
QList<bool> Variable::getVars() const{
    return vars_;
}
QString Variable::makeName(const QString &first, const QString &operation, const QString &second) const{
    return first + operation + second;
}
int Variable::pow2(const int power) const{
    return 1 << power;
}
