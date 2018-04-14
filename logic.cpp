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
    sortVars();
    fillVars();
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
    return;
}
void Logic::compute(){
    computeLogicalAction();
    ce_->printTruthTable(getVarsTitle(), getVarsData());
    return;
}
void Logic::computeLogicalAction(){
    negation(v_);
    binaryOperation(v_, "*");
    binaryOperation(v_, "+");
    binaryOperation(v_, "|");
    binaryOperation(v_, "#");
    binaryOperation(v_, "->");
    binaryOperation(v_, "^");
    binaryOperation(v_, "<-");
    binaryOperation(v_, "~");
    /*implication();
    equivalent();
    notAnd();
    notOr();
    exclusiveDisjunction();
    negationFunc();*/
    return;
}
void Logic::negation(QList<QString> *v){
    for(int i = 0; i < v_->length(); i++)
        if(v->at(i) == "!" && i + 1 != v->length() && map_.contains(v->at(i + 1))){
            Variable newVar = getVariable(v->at(i + 1)).negation();
            if(newVar.getName() != "NULL")
                insertWithReplace(newVar, i, i+1);
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
                insertWithReplace(newVar, i-1, i+1);
            else
                showError(* new QString("бинарная операция"), * new QString("Ошибка в чтении бинарной операции" + operation));
            i--;
        }
    return;
}
void Logic::insertWithReplace(Variable v, int begin, int end){
    if(!map_.contains(v.getName())){
        vars_.push_back(v);
        map_[v.getName()] = vars_.length() - 1;
    }
    for(int i = begin; i <= end; i++)
        v_->removeAt(begin);
    v_->insert(begin, v.getName());
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
    AVIABLE_NAME_OF_VARS_ << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "X" << "Y" << "Z"
                          << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "x" << "y" << "z";
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
