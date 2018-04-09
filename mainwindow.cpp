#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connectQss();
    ui->setupUi(this);
    ie_ = new InputEditor(ui->input);
    ce_ = new ContentEditor(ui->result);
    ui->input->setFocus();
    bindConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::inputPressed(){
    ie_->parse(ui->input->text());
    return;
}
void MainWindow::connectQss(){
    QFile styleF;
    styleF.setFileName("C:/Users/Mike/Documents/Qt/LogicCalc/qss/style.css");
    styleF.open(QFile::ReadOnly);
    qApp->setStyleSheet(styleF.readAll());
    return;
}
void MainWindow::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender()); //get sender button
    ie_->PushBack(ie_->AVIABLE_TRANSFORMATIONS[pButton->objectName()]);
    return;
}
void MainWindow::bindConnect(){
    connect(ui->input, SIGNAL(returnPressed()), this, SLOT(inputPressed()));
    connect(ui->conjunction, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->disjunction, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->exclusive_disjunction, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->not_and, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->not_or, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->implication, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->converse, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->equivalent, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(ui->negation, SIGNAL(clicked()), this, SLOT(onClicked()));
    return;
}