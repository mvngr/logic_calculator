#include "inputeditor.h"

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
    bool res = true;
    QList<int> errors;
    QStringList sl = str.trimmed().split(" ");
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
