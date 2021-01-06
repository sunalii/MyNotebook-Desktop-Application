#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "noteswriter.h"
#include "notesdoodle.h"
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Opnes MyNotesWriter Window
void MainWindow::on_pushButton_clicked()
{
    noteswriter = new NotesWriter(this);
    noteswriter->show();
}

// Opnes MyNotesWriter Window
void MainWindow::on_pushButton_2_clicked()
{
    notesdoodle = new NotesDoodle(this);
    notesdoodle->show();
}

// Opnes Google
void MainWindow::on_pushButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/"));
}

// Opening University of Plymouth website
void MainWindow::on_pushButton_4_clicked()
{
    QDesktopServices::openUrl(QUrl("https://dle.plymouth.ac.uk/"));
}

