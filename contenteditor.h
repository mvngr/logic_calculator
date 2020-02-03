#ifndef CONTENTEDITOR_H
#define CONTENTEDITOR_H

#include <QList>
#include <QString>
#include <QPlainTextEdit>

/*!
 * \brief ContentEditor - Класс отвечает за корректный и удобный вывод чего-либо в поле для вывода
 */
class ContentEditor
{
public:
    ContentEditor(QPlainTextEdit *plainTextEdit);
    void printTruthTable(const QList<QString> &title, const QList<QList<bool>> &data); //Инициирует вывод таблицы истинности
    void printSKNF(const QString &sknf) const; //выводит Совершенную Конъюнктивную Нормальную Форму
    void printSDNF(const QString &sdnf) const; //выводит Совершенную Дизъюнктивную Нормальную Форму

    const int minimumColumnCharSize = 5; ///Минимальный размер столбца в символах
private:
    QPlainTextEdit *pte_; ///Управление полем вывода
    QList<int> cellSize_; ///Размеры ячеек в таблице истинности

    QList<int> getSize(const QList<QString> &title) const; //Заполняет значения размеров ячеек в таблице истинности cellSize_
    QString makeString(char segment, int amount) const; //Создает строку из повторяющихся amount раз символов segment
    QString makeLine() const; //Создает линию под заголовком
    QString makeTitle(const QList<QString> &title) const; //Создает заголовок
    QString makeData(const QList<QList<bool> > &data) const; //Создает двумерный массив данных <0/1>
    QString centerAlign(const QString &text, const int cellSize) const; //выравнивает все элементы по центру своей ячейки
};

#endif // CONTENTEDITOR_H
