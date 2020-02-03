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

/*!
 * \brief Variable::operator > оператор больше
 * \param other другая переменная
 * \return больше ли данная перменная
 *
 * \warning Используется только для сортировки, не является логическим действием в понимании самого калькулятора!
 */
bool Variable::operator > (const Variable &other)
{
   return name_ > other.name_;
}

/*!
 * \brief Variable::operator < оператор меньше
 * \param other другая переменная
 * \return меньше ли данная перменная
 *
 * \warning Используется только для сортировки, не является логическим действием в понимании самого калькулятора!
 */
bool Variable::operator < (const Variable &other)
{
   return name_ < other.name_;
}

/*!
 * \brief Variable::conjunction Конъюнкция
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::conjunction(const Variable &other) const{
    Variable v(makeName(getName(), " * ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] && other.vars_[i]);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::disjunction Дизъюнкция
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::disjunction(const Variable &other) const{
    Variable v(makeName(getName(), " + ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] || other.vars_[i]);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::implication Импликация
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::implication(const Variable &other) const{
    Variable v(makeName(getName(), " -> ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == true && other.vars_[i] == false ) ? false : true);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::converse Обратная импликация
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::converse(const Variable &other) const{
    Variable v(makeName(getName(), " <- ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == false && other.vars_[i] == true ) ? false : true);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::notAnd Штрих Шеффера
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::notAnd(const Variable &other) const{
    Variable v(makeName(getName(), " | ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(( vars_[i] == true && other.vars_[i] == true ) ? false : true);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::notOr Стрелка Пирса
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::notOr(const Variable &other) const{
    Variable v(makeName(getName(), " # ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == false && other.vars_[i] == false);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::exclusiveDisjunction Исключающее ИЛИ
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::exclusiveDisjunction(const Variable &other) const{
    Variable v(makeName(getName(), " ^ ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.vars_[i] ? false : true);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::equivalent Эквиваленция
 * \param other с данной переменной
 * \return Получившееся значение
 */
Variable Variable::equivalent(const Variable &other) const{
    Variable v(makeName(getName(), " ~ ", other.getName()));
    QList<bool> temp;
    for(int i = 0; i < vars_.size(); i++)
        temp.push_back(vars_[i] == other.vars_[i] ? true : false);
    v.setVars(temp);
    return v;
}

/*!
 * \brief Variable::negation Отрицание самой переменной
 * \return получившееся значение
 */
Variable Variable::negation(){
    setName(QString("! " + getName()));
    for(int i = 0; i < vars_.size(); i++)
        vars_[i] = !vars_[i];
    return *this;
}

/*!
 * \brief Variable::setName Задает имя
 * \param name задаваемое имя
 */
void Variable::setName(const QString &name){
    name_ = name;
}

/*!
 * \brief Variable::setVars Задает принимаемые значения
 * \param vars задаваемые значения
 */
void Variable::setVars(const QList<bool> &vars){
    vars_ = vars;
}

/*!
 * \brief Variable::setVars Генерирует значения
 * \param index индекс элемента
 * \param size количество элементов
 */
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

/*!
 * \brief Variable::getName Отдает название
 * \return название переменной
 */
QString Variable::getName() const{
    return name_;
}

/*!
 * \brief Variable::getVars Отдает значения переменной
 * \return Значения переменной
 */
QList<bool> Variable::getVars() const{
    return vars_;
}

/*!
 * \brief Variable::makeName Создает строку из двух названий переменных и операции между ними
 * \param first Первое значение
 * \param operation Операция между этими значениями
 * \param second Второе значение
 * \return Получившаяся строка
 */
QString Variable::makeName(const QString &first, const QString &operation, const QString &second) const{
    return first + operation + second;
}

/*!
 * \brief Variable::pow2 Возвращает степень числа два
 * \param power степень
 * \return полученное число
 */
int Variable::pow2(const int power) const{
    return 1 << power;
}
