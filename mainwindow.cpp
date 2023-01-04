#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->textEdit->setText("");
    flag=0;
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name= QFileDialog::getOpenFileName(this,"Open file");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        return;
    }
    file_path=file_name;
    QTextStream in(&file);
    QString text= in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    if(!flag) {on_actionSave_as_triggered();flag=1;return;}
    QFile file(file_path);
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name= QFileDialog::getSaveFileName(this,"Save file");
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        return;
    }
    file_path=file_name;
    QTextStream out(&file);
    QString text= ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString abt;
    abt="Author : Shyam \n";
    abt+="A simple notepad app to get familiar with qt environment \n";
    abt+= "@Copyright 2022-23";
    QMessageBox::about(this,"About Notepad",abt);
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->undo();
}

