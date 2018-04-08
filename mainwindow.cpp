#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connectQss();
    ui->setupUi(this);
    ie = new InputEditor(ui->input);
    ui->input->setFocus();
    bindConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::inputPressed(){
    ie->parse(ui->input->text());
}
void MainWindow::connectQss(){
    QFile styleF;

    styleF.setFileName("C:/Users/Mike/Documents/Qt/LogicCalc/qss/style.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    qApp->setStyleSheet(qssStr);
    return;
}
void MainWindow::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender()); //get sender button
    ie->PushBack(ie->AVIABLE_TRANSFORMATIONS[pButton->objectName()]);
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
