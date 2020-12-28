#include "inputeditor.h"

#include <QString>

InputEditor::InputEditor(QLineEdit *input) : input_(input), v_(new QList<QString>){}
InputEditor::~InputEditor(){
    //delete v_; в соседнем классе чистится v_ (эх, костылики)
}

/*!
 * \brief InputEditor::pushBack Добавляет определенные данные в конец внутреннего массива
 * \param str данные
 */
void InputEditor::pushBack(const QString &str){
    if(!isValidity())
        parse(input_->text());
    v_->push_back(str);
    updateInput();
}

/*!
 * \brief InputEditor::getVars Выдает указатель на внутренний массив данных
 * \return Указатель на внутренний массив данных
 */
QList<QString> *InputEditor::getVars(){
    //эх... исправить бы этот метод на более безопасный вариант
    return v_;
}

/*!
 * \brief InputEditor::updateInput Обновляет поле для ввода данных
 */
void InputEditor::updateInput(){
    input_->setText(toString());
}
/*!
 * \brief InputEditor::toString Преобразует внутренний массив в строку
 * \return сгенерированная строка
 */
QString InputEditor::toString() const {
    return v_->join(" ");
}
bool InputEditor::isValidity() const {
    return input_->text() == toString();
}

/*!
 * \brief InputEditor::parse Парсит введенную строку
 * \param str строка для парсинга
 * \return смогло ли произойти чтение
 */
bool InputEditor::parse(const QString &str){
    QString prettyString = normalizeString(str); //приводим строку с виду пробел значение пробел значение
    bool res = true;
    QList<int> errors;
    QStringList sl = prettyString.trimmed().split(" ");
    for(int i = 0; i < sl.count(); i++)
        if(AVIABLE_WORDS.indexOf(sl[i]) == -1)
        {
            errors.push_back(i);
        }
    if(errors.length() == 0){
        delete v_;
        v_ = new QList<QString>(sl);
    }
    else{
        QString msg("Неправильный синтаксис: ");
        for(const int &error : errors)
            msg.append("\" ").append(sl[error]).append(" \", ");
        QMessageBox::warning(nullptr, "Ошибка", msg);
        res = false;
    }
    return res;
}

/*!
 * \brief InputEditor::normalizeString приводит входную строку в вид значение пробел значение пробел
 * \param input входная строка
 * \return Отформатированная строка
 *
 * \example
 * Вход: A*B+    C
 * Выход: A * B + C
 */
QString InputEditor::normalizeString(const QString &input) const
{
    QString res; //результирующая строка
    QString inStr = input; //копируем входную строку
    inStr.remove(" ");

    for(int i = 0; i < inStr.size(); i++)
    {
        auto foundIterator = std::find_if(AVIABLE_WORDS.cbegin(), AVIABLE_WORDS.cend(), [&inStr, &i](const QString &value){ return inStr[i] == value.at(0); }); //ищем совпадение с допустимыми словами

        if(foundIterator == AVIABLE_WORDS.cend())
        {
            //res.push_back(' '); //если ничего не нашли то добавляем пробел
        }
        else
        {
            res.push_back((*foundIterator) + ' '); //Добавляем доступное слово и пробел
            i += (*foundIterator).size() - 1; //Добавляем к i сколько надо, если длина доступного слова больше 1
        }
    }

    return res;
}
