#include<algorithm>

#include "logic.h"

Logic::Logic(QPlainTextEdit *output) : v_(new QList<QString>), ce_(new ContentEditor(output)){}
Logic::~Logic(){
    delete v_;
    delete ce_;
}
void Logic::setVars(QList<QString> *v){
    v_ = v;
    fillVars();
    sortVars();
    fillMap();
    makeBoolArrays();
}
void Logic::compute(){
    computeLogicalAction(v_);
    ce_->printTruthTable(getVarsTitle(), getVarsData());
}
void Logic::computeLogicalAction(QList<QString> *v){
    findBrackets(v);
    negation(v);
    binaryOperation(v, "*");
    binaryOperation(v, "+");
    binaryOperation(v, "|");
    binaryOperation(v, "#");
    binaryOperation(v, "->");
    binaryOperation(v, "^");
    binaryOperation(v, "<-");
    binaryOperation(v, "~");
}
void Logic::negation(QList<QString> *v){
    for(int i = 0; i < v->length(); i++)
        if(v->at(i) == "!" && i + 1 != v->length() && map_.contains(v->at(i + 1))){
            Variable newVar(getVariable(v->at(i + 1)).negation());
            if(newVar.getName() != "NULL")
                insertWithReplace(v, newVar, i, i+1);
        }
}
void Logic::binaryOperation(QList<QString> *v, const QString &operation){
    for(int i = 0; i < v->length(); i++)
        if(v->at(i) == operation
                && i + 1 != v->length() && i - 1 != -1
                && map_.contains(v->at(i + 1)) && map_.contains(v->at(i - 1)))
        {
            Variable newVar("NULL");
            switch (BINARY_OPERATIONS_TO_NUM_[BINARY_OPERATIONS_[operation]]) {
            case 1: newVar = getVariable(v->at(i - 1)).conjunction(getVariable(v->at(i + 1)));          break;
            case 2: newVar = getVariable(v->at(i - 1)).disjunction(getVariable(v->at(i + 1)));          break;
            case 3: newVar = getVariable(v->at(i - 1)).implication(getVariable(v->at(i + 1)));          break;
            case 4: newVar = getVariable(v->at(i - 1)).converse(getVariable(v->at(i + 1)));             break;
            case 5: newVar = getVariable(v->at(i - 1)).equivalent(getVariable(v->at(i + 1)));           break;
            case 6: newVar = getVariable(v->at(i - 1)).exclusiveDisjunction(getVariable(v->at(i + 1))); break;
            case 7: newVar = getVariable(v->at(i - 1)).notAnd(getVariable(v->at(i + 1)));               break;
            case 8: newVar = getVariable(v->at(i - 1)).notOr(getVariable(v->at(i + 1)));                break;
            default: break;
            }
            if(newVar.getName() != "NULL")
                insertWithReplace(v, newVar, i-1, i+1);
            else
                showError(QString("бинарная операция"), QString("Ошибка в чтении бинарной операции: " + operation));
            i--;
        }
}
void Logic::makeSKNF(){
    compute();
    if(vars_.length() != 0){
        QString ans;
        int num = vars_[0].getVars().length();
        int degree = 0;
        while (num != 1){
            degree++;
            num /= 2;
        }
        QList<bool> truthTable = vars_.last().getVars();
        for(int i = 0; i < truthTable.length(); i++)
            if(!truthTable[i]){
                ans += "( ";
                for(int j = 0; j < degree; j++)
                {
                    ans += j + 1 != degree ? (vars_[j].getVars()[i] ? "! " + vars_[j].getName() : vars_[j].getName())  + " + "
                                           : (vars_[j].getVars()[i] ? "! " + vars_[j].getName() : vars_[j].getName());
                }
                ans += " ) * ";
            }
        if(ans.length() != 0) // clear last " * "
            ans.remove(ans.length() - 3, 2);
        ce_->printSKNF(ans);
    }
}
void Logic::makeSDNF(){
    compute();
    if(vars_.length() != 0){
        QString ans;
        int num = vars_[0].getVars().length();
        int degree = 0;
        while (num != 1){
            degree++;
            num /= 2;
        }
        QList<bool> truthTable(vars_.last().getVars());
        for(int i = 0; i < truthTable.length(); i++)
            if(truthTable[i]){
                ans += "( ";
                for(int j = 0; j < degree; j++)
                {
                    ans += j + 1 != degree ? (vars_[j].getVars()[i] ? vars_[j].getName() : "! " + vars_[j].getName())  + " * "
                                           : (vars_[j].getVars()[i] ? vars_[j].getName() : "! " + vars_[j].getName());
                }
                ans += " ) + ";
            }
        if(ans.length() != 0) // clear last " + "
            ans.remove(ans.length() - 3, 2);
        ce_->printSDNF(ans);
    }
}
void Logic::findBrackets(QList<QString> *v){
    QList<int> bracket_ind;
    for(int i = 0; i < v->length(); i++){
        if(v->at(i) == "(")
            bracket_ind.push_back(i);
        if(v->at(i) == ")" && bracket_ind.length() > 0){
            QList<QString> *new_v = subString(v, bracket_ind.last() + 1, i - 1);
            computeLogicalAction(new_v);
            for(int n = bracket_ind.last(); n <= i; n++)
                v->removeAt(bracket_ind.last());
            QString new_name("( " + new_v->at(0) + " )");
            v->insert(bracket_ind.last(), new_name);
            map_[new_name] = map_[new_v->at(0)];
            vars_[map_[new_name]].setName(new_name);
            i = bracket_ind.last();
            bracket_ind.removeLast();
        }
    }
}
QList<QString> * Logic::subString(QList<QString> *v, int begin, const int end){
    QList<QString> * new_v = new QList<QString>;
    do
        new_v->push_back(v->at(begin));
    while(begin++ < end);
    return new_v;
}
void Logic::insertWithReplace(QList<QString> *v, const Variable &variable, const int begin, const int end){
    if(!map_.contains(variable.getName())){
        vars_.push_back(variable);
        map_[variable.getName()] = vars_.length() - 1;
    }
    for(int i = begin; i <= end; i++)
        v->removeAt(begin);
    v->insert(begin, variable.getName());
}
Variable Logic::getVariable(const QString &name) const{
    return map_.contains(name) ? vars_.at(map_[name]) : Variable("NULL");
}
void Logic::showError(const QString &logicOperation, const QString &error) const{
    QMessageBox::information(nullptr, "Ошибка: " + logicOperation, error);
}
void Logic::fillVars(){
    vars_.clear();
    if(!v_)
        return;
    for(int i = 0; i < v_->length(); i++){
        QChar c = v_->at(i).at(0);
        if(AVIABLE_NAME_OF_VARS_.indexOf(v_->at(i)) != -1 && !isRepeat( c )){
            if(vars_.length() < 16)
                vars_.append(Variable(v_->at(i).at(0)));
            else{
                //TODO узнать почему 16...
                showError("добавление переменных", "Увы, слишком много переменных. \nНекоторые введенные переменные будут удалены");
                break;
            }
        }
    }
}
void Logic::fillMap(){
    map_.clear();
    for(int i = 0; i < vars_.length(); i++)
        map_.insert(vars_[i].getName(), i);
}
bool Logic::isRepeat(const QChar c) const{
    bool res = false;
    for(int i = 0; i < vars_.length(); i++)
        if(vars_[i].getName() == c)
        {
            res = true;
            break;
        }
    return res;
}
void Logic::sortVars(){
    std::sort(vars_.begin(), vars_.end());
}
void Logic::makeBoolArrays(){
    int length = vars_.length();
    for(int i = 0; i < length; i++)
        vars_[i].setVars(i, length);
}
QList<QString> Logic::getVarsTitle() const{
    QList<QString> result;
    for(const Variable &item : vars_)
        result.push_back(item.getName());
    return result;
}
QList<QList<bool>> Logic::getVarsData() const{
    QList<QList<bool>> result;
    for(const Variable &item : vars_)
        result.push_back(item.getVars());
    return result;
}
