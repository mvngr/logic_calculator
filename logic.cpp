#include "logic.h"

Logic::Logic(QPlainTextEdit *output){
    v_ = new QList<QString>;
    vars_ = *new QList<Variable>;
    ce_ = new ContentEditor(output);
    map_ = * new QMap<QString, int>;
}
Logic::Logic(QList<QString> *v, QPlainTextEdit *output)
{
    vars_ = *new QList<Variable>;
    ce_ = new ContentEditor(output);
    map_ = * new QMap<QString, int>;
    setVars(v);
}
Logic::~Logic(){
    vars_.~QList();
    v_->~QList();
    map_.~QMap();
    AVIABLE_NAME_OF_VARS_.~QList();
}
void Logic::setVars(QList<QString> *v){
    v_ = v;
    fillOperations();
    fillVars();
    sortVars();
    fillMap();
    makeBoolArrays();
}
void Logic::fillOperations(){
    BINARY_OPERATIONS_["*"] = "conjunction";
    BINARY_OPERATIONS_["+"] = "disjunction";
    BINARY_OPERATIONS_["^"] = "exclusiveDisjunction";
    BINARY_OPERATIONS_["|"] = "notAnd";
    BINARY_OPERATIONS_["#"] = "notOr";
    BINARY_OPERATIONS_["->"] = "implication";
    BINARY_OPERATIONS_["<-"] = "converse";
    BINARY_OPERATIONS_["~"] = "equivalent";

    BINARY_OPERATIONS_TO_NUM_["conjunction"] = 1;
    BINARY_OPERATIONS_TO_NUM_["disjunction"] = 2;
    BINARY_OPERATIONS_TO_NUM_["implication"] = 3;
    BINARY_OPERATIONS_TO_NUM_["converse"] = 4;
    BINARY_OPERATIONS_TO_NUM_["equivalent"] = 5;
    BINARY_OPERATIONS_TO_NUM_["exclusiveDisjunction"] = 6;
    BINARY_OPERATIONS_TO_NUM_["notAnd"] = 7;
    BINARY_OPERATIONS_TO_NUM_["notOr"] = 8;

    AVIABLE_NAME_OF_VARS_ << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "X" << "Y" << "Z"
                          << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "x" << "y" << "z";
    return;
}
void Logic::compute(){
    computeLogicalAction(v_);
    ce_->printTruthTable(getVarsTitle(), getVarsData());
    return;
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
    return;
}
void Logic::negation(QList<QString> *v){
    for(int i = 0; i < v->length(); i++)
        if(v->at(i) == "!" && i + 1 != v->length() && map_.contains(v->at(i + 1))){
            Variable newVar = getVariable(v->at(i + 1)).negation();
            if(newVar.getName() != "NULL")
                insertWithReplace(v, newVar, i, i+1);
        }
    return;
}
void Logic::binaryOperation(QList<QString> *v, QString operation){
    for(int i = 0; i < v->length(); i++)
        if(v->at(i) == operation
                && i + 1 != v->length() && i - 1 != -1
                && map_.contains(v->at(i + 1)) && map_.contains(v->at(i - 1))){
            Variable newVar = * new Variable("NULL");
            switch (BINARY_OPERATIONS_TO_NUM_[BINARY_OPERATIONS_[operation]]) {
            case 1: newVar = getVariable(v->at(i - 1)).conjunction(getVariable(v->at(i + 1))); break;
            case 2: newVar = getVariable(v->at(i - 1)).disjunction(getVariable(v->at(i + 1))); break;
            case 3: newVar = getVariable(v->at(i - 1)).implication(getVariable(v->at(i + 1))); break;
            case 4: newVar = getVariable(v->at(i - 1)).converse(getVariable(v->at(i + 1))); break;
            case 5: newVar = getVariable(v->at(i - 1)).equivalent(getVariable(v->at(i + 1))); break;
            case 6: newVar = getVariable(v->at(i - 1)).exclusiveDisjunction(getVariable(v->at(i + 1))); break;
            case 7: newVar = getVariable(v->at(i - 1)).notAnd(getVariable(v->at(i + 1))); break;
            case 8: newVar = getVariable(v->at(i - 1)).notOr(getVariable(v->at(i + 1))); break;
            default: break;
            }
            if(newVar.getName() != "NULL")
                insertWithReplace(v, newVar, i-1, i+1);
            else
                showError(* new QString("бинарная операция"), * new QString("Ошибка в чтении бинарной операции" + operation));
            i--;
        }
    return;
}
void Logic::makeSKNF(){
    compute();
    if(vars_.length() != 0){
        QString ans = * new QString;
        int num = vars_[0].getVars().length();
        int degree = 0;
        while (num != 1){
            degree++;
            num /= 2;
        }
        QList<bool> truthTable = vars_.last().getVars();
        for(int i = 0; i < truthTable.length(); i++)
            if(truthTable[i] == false){
                ans += "( ";
                for(int j = 0; j < degree; j++)
                    ans += j + 1 != degree ? (vars_[j].getVars()[i] ? "! " + vars_[j].getName() : vars_[j].getName())  + " + "
                                           : (vars_[j].getVars()[i] ? "! " + vars_[j].getName() : vars_[j].getName());
                ans += " ) * ";
            }
        if(ans.length() != 0) // clear last " * "
            ans.remove(ans.length() - 3, 2);
        ce_->printSKNF(ans);
    }
    return;
}
void Logic::makeSDNF(){
    compute();
    if(vars_.length() != 0){
        QString ans = * new QString;
        int num = vars_[0].getVars().length();
        int degree = 0;
        while (num != 1){
            degree++;
            num /= 2;
        }
        QList<bool> truthTable = vars_.last().getVars();
        for(int i = 0; i < truthTable.length(); i++)
            if(truthTable[i] == true){
                ans += "( ";
                for(int j = 0; j < degree; j++)
                    ans += j + 1 != degree ? (vars_[j].getVars()[i] ? vars_[j].getName() : "! " + vars_[j].getName())  + " * "
                                           : (vars_[j].getVars()[i] ? vars_[j].getName() : "! " + vars_[j].getName());
                ans += " ) + ";
            }
        if(ans.length() != 0) // clear last " + "
            ans.remove(ans.length() - 3, 2);
        ce_->printSDNF(ans);
    }
    return;
}
void Logic::findBrackets(QList<QString> *v){
    QList<int> bracket_ind = * new QList<int>;
    for(int i = 0; i < v->length(); i++){
        if(v->at(i) == "(")
            bracket_ind.push_back(i);
        if(v->at(i) == ")"){
            QList<QString> *new_v = subString(v, bracket_ind.last() + 1, i - 1);
            computeLogicalAction(new_v);
            for(int n = bracket_ind.last(); n <= i; n++)
                v->removeAt(bracket_ind.last());
            QString new_name = * new QString("( " + new_v->at(0) + " )");
            v->insert(bracket_ind.last(), new_name);
            map_[new_name] = map_[new_v->at(0)];
            vars_[map_[new_name]].setName(new_name);
            i = bracket_ind.last() + 1;
            bracket_ind.removeLast();
        }
    }
    return;
}
QList<QString> * Logic::subString(QList<QString> *v, int begin, int end){
    QList<QString> * new_v = new QList<QString>;
    do
        new_v->push_back(v->at(begin));
    while(begin++ < end);
    return new_v;
}
void Logic::insertWithReplace(QList<QString> *v, Variable variable, int begin, int end){
    if(!map_.contains(variable.getName())){
        vars_.push_back(variable);
        map_[variable.getName()] = vars_.length() - 1;
    }
    for(int i = begin; i <= end; i++)
        v->removeAt(begin);
    v->insert(begin, variable.getName());
    return;
}
Variable Logic::getVariable(QString name){
    return map_.contains(name) ? vars_.at(map_[name]) : *new Variable("NULL");
}
void Logic::showError(QString logicOperation, QString error){
    QMessageBox::information(NULL, "Ош: " + logicOperation, error);
    return;
}
void Logic::fillVars(){
    vars_.clear();
    for(int i = 0; i < v_->length(); i++){
        QChar c = v_->at(i).at(0);
        if(AVIABLE_NAME_OF_VARS_.indexOf(v_->at(i)) != -1 && !isRepeat( &c )){
            if(vars_.length() < 16)
                vars_.append(*new Variable(v_->at(i).at(0)));
            else{
                showError(*new QString("добавление переменных"), *new QString("Увы, слишком много переменных. \nНекоторые введенные переменные будут удалены"));
                break;
            }
        }
    }
}
void Logic::fillMap(){
    map_.clear();
    for(int i = 0; i < vars_.length(); i++)
        map_.insert(vars_[i].getName(), i);
    return;
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
