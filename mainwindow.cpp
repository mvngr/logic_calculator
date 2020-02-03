#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connectQss();
    ui->setupUi(this);

    ie_ = new InputEditor(ui->input);
    logic_ = new Logic(ui->result);
    ui->input->setFocus();
    bindConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete logic_;
    delete ie_;
}

/*!
 * \brief MainWindow::inputPressed Обработчик для поля ввода данных, вызывается при нажатии на enter
 */
void MainWindow::inputPressed(){
    on_compute_clicked();
}

/*!
 * \brief MainWindow::connectQss Отвечает за подключение стилей
 */
void MainWindow::connectQss(){
    QFile styleF;
    styleF.setFileName(":/qss/qss/style.css");
    styleF.open(QFile::ReadOnly);
    qApp->setStyleSheet(styleF.readAll());
}

/*!
 * \brief MainWindow::onClicked Обработчик на кнопки логических операций. Добавляет в поле ввода данных соответствующий символ
 */
void MainWindow::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender()); //get sender button
    if(pButton)
        ie_->pushBack(ie_->AVIABLE_TRANSFORMATIONS[pButton->objectName()]);
}

/*!
 * \brief MainWindow::bindConnect Создаёт связи между обработчиком события onClicked и нажатой кнопкой
 */
void MainWindow::bindConnect() const{
    connect(ui->input, &QLineEdit::returnPressed, this, &MainWindow::inputPressed);
    connect(ui->conjunction, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->disjunction, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->exclusive_disjunction, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->not_and, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->not_or, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->implication, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->converse, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->equivalent, &QPushButton::clicked, this, &MainWindow::onClicked);
    connect(ui->negation, &QPushButton::clicked, this, &MainWindow::onClicked);
}

/*!
 * \brief MainWindow::on_compute_clicked Обработчик нажатия на кнопку Вычислить
 */
void MainWindow::on_compute_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->compute();
    }
}

/*!
 * \brief MainWindow::on_f5_clicked Обработчик для кнопки СКНФ
 */
void MainWindow::on_f5_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->makeSKNF();
    }
}

/*!
 * \brief MainWindow::on_f4_clicked Обработчик для кнопки СДНФ
 */
void MainWindow::on_f4_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->makeSDNF();
    }
}
