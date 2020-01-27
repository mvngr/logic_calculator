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
void MainWindow::inputPressed(){
    on_compute_clicked();
}
void MainWindow::connectQss(){
    QFile styleF;
    styleF.setFileName(":/qss/qss/style.css");
    styleF.open(QFile::ReadOnly);
    qApp->setStyleSheet(styleF.readAll());
}
void MainWindow::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender()); //get sender button
    if(pButton)
        ie_->pushBack(ie_->AVIABLE_TRANSFORMATIONS[pButton->objectName()]);
}
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

void MainWindow::on_compute_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->compute();
    }
}

void MainWindow::on_f5_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->makeSKNF();
    }
}

void MainWindow::on_f4_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->makeSDNF();
    }
}
