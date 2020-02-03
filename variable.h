#ifndef VARIABLE_H
#define VARIABLE_H
#include <QList>
#include <QDebug>
#include <QChar>

/*!
 * \brief Variable - Класс логических переменных
 */
class Variable
{
public:
    Variable(const QChar name);
    Variable(const QString &name);
    Variable(const QChar name, const QList<bool> *vars);
    Variable(QChar name, int numberVariables, int positionVariable);

    //Some logical operations cannot be easily converted to statements
    //Therefore, operators have replaced by basic functions
    Variable conjunction(const Variable &other) const; //Конъюнкция
    Variable disjunction(const Variable &other) const; //Дизъюнкция
    Variable implication(const Variable &other) const; //Импликация
    Variable converse(const Variable &other) const; //Обратная импликация
    Variable notAnd(const Variable &other) const; //Штрих Шеффера
    Variable notOr(const Variable &other) const; //Стрелка Пирса
    Variable exclusiveDisjunction(const Variable &other) const; //Исключающее ИЛИ
    Variable equivalent(const Variable &other) const; //Эквиваленция
    Variable negation(); //Отрицание самой переменной

    void setName(const QString &name); //Задает имя
    void setVars(const QList<bool> &vars); //Задает принимаемые значения
    void setVars(const int index, const int size); //Генерирует значения

    QString getName() const; //Отдает название переменной
    QList<bool> getVars() const; //Отдает значения переменной


    //Используется только для сортировки, не является логическим действием в понимании самого калькулятора!
    bool operator > (const Variable &other); //оператор больше
    bool operator < (const Variable &other); //оператор меньше

private:
    void debugVars(); //Выводит значения vars_ в консоль (Не используется)
    int pow2(const int power) const; //Возвращает степень числа два
    QString makeName(const QString &first, const QString &operation, const QString &second) const; //Создает строку из двух названий переменных и операции между ними
    QString name_; ///Имя логической переменной
    QList<bool> vars_; ///Принимаемые значения
};

#endif // VARIABLE_H
