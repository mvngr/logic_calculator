#include "contenteditor.h"

ContentEditor::ContentEditor(QPlainTextEdit *plainTextEdit)
{
    pte_ = plainTextEdit;
}

/*!
 * \brief ContentEditor::printTruthTable Инициирует вывод таблицы истинности
 * \param title заголовок таблицы истинности
 * \param data данные таблицы истинности
 */
void ContentEditor::printTruthTable(const QList<QString> &title, const QList<QList<bool>> &data){
    cellSize_ = getSize(title);
    QString output;
    output.append(makeTitle(title));
    output.append(makeLine());
    output.append(makeData(data));
    pte_->setPlainText(output);
}

/*!
 * \brief ContentEditor::makeString Создает строку из повторяющихся amount раз символов segment
 * \param segment повторяющийся символ
 * \param amount сколько раз повторять символ
 * \return получившаяся строка
 */
QString ContentEditor::makeString(char segment, int amount) const {
    QString res;
    while (amount-- != 0)
        res.append(segment);
    return res;
}

/*!
 * \brief ContentEditor::getSize Заполняет значения размеров ячеек в таблице истинности cellSize_
 * \param title список заголовков
 * \return размер, необходимый для каждого из столбцов
 */
QList<int> ContentEditor::getSize(const QList<QString> &title) const {
    QList<int> size;
    for(const QString &temp : title)
        size.append(temp.length() > minimumColumnCharSize ? temp.length() : minimumColumnCharSize);
    return size;
}

/*!
 * \brief ContentEditor::centerAlign выравнивает все элементы по центру своей ячейки
 * \param text Текст, который необходимо выравнять по центру
 * \param cellSize размер столбца (в символах)
 * \return выровненный текст по центру
 */
QString ContentEditor::centerAlign(const QString &text, const int cellSize) const {
    QString result;
    int spaceCount = text.length() > cellSize ? 0 : cellSize - text.length();
    result.append(makeString(' ', spaceCount / 2));
    result.append(text);
    result.append(makeString(' ', spaceCount % 2 == 0 ? spaceCount / 2 : spaceCount / 2 + 1));
    return result;
}

/*!
 * \brief ContentEditor::makeTitle Создает заголовок
 * \param title текст, который нужно вставить в каждую из колонок заголовка
 * \return получившаяся строка
 */
QString ContentEditor::makeTitle(const QList<QString> &title) const {
    QString output;
    for(int i = 0; i < title.length(); i++){
        output.append(centerAlign(title.at(i), cellSize_.at(i)));
        if(i + 1 != title.length()){
            output.append("|");
        }
    }
    return output;
}

/*!
 * \brief ContentEditor::makeLine Создает линию под заголовком
 * \return получившаяся линия
 */
QString ContentEditor::makeLine() const {
    QString result;
    result.append('\n');
    for(int i = 0; i < cellSize_.length(); i++){
        result.append(makeString('-', cellSize_[i]));
        if(i + 1 != cellSize_.length())
        {
            result.append('+');
        }
    }
    return result;
}

/*!
 * \brief ContentEditor::makeData Создает двумерный массив данных <0/1>
 * \param data данные, которые необходимо вывести
 * \return итоговая строка с данными
 */
QString ContentEditor::makeData(const QList<QList<bool>> &data) const {
    QString result;
    if(data.length() == 0) //тут мы проходимся по вдумерному массиву, если он существует
        return result;
    for(int i = 0; i < data[0].length(); i++){
        result.append('\n');
        for(int j = 0; j < data.length(); j++){
            result.append(centerAlign(QString(data[j][i] ? "1" : "0"), cellSize_.at(j)));
            if(j + 1 != data.length() )
                result.append('|');
        }
    }
    return result;
}

/*!
 * \brief ContentEditor::printSKNF выводит Совершенную Конъюнктивную Нормальную Форму
 * \param sknf Строка СКНФ
 */
void ContentEditor::printSKNF(const QString &sknf) const {
    pte_->setPlainText(pte_->toPlainText() + "\n\nСКНФ: " + sknf);
}

/*!
 * \brief ContentEditor::printSDNF выводит Совершенную Дизъюнктивную Нормальную Форму
 * \param sdnf Строка СДНФ
 */
void ContentEditor::printSDNF(const QString &sdnf) const {
    pte_->setPlainText(pte_->toPlainText() + "\n\nСДНФ: " + sdnf);
}
