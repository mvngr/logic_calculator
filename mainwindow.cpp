#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connectQss();
    ui->setupUi(this);
    QList<bool> tempList = * new QList<bool>{true, true, false, false};
    QList<bool> tempList2 = * new QList<bool>{true, false, true, false};
    QChar c = 'a', c2 = 'b';
    Variable v = * new Variable(c, &tempList);
    Variable v2 = * new Variable(c2, &tempList2);
    Variable v3 = v.disjunction(v2);

    ie_ = new InputEditor(ui->input);
    logic_ = new Logic(ui->result);
    ui->input->setFocus();
    bindConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::inputPressed(){
    on_compute_clicked();
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

void MainWindow::on_compute_clicked()
{
    bool isCorrect = ie_->parse(ui->input->text());
    if(isCorrect){
        logic_->setVars(ie_->getVars());
        logic_->compute();
    }
    return;
}
