#include "noteswriter.h"
#include "ui_noteswriter.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QPrinter>
#include <QPrintDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QCloseEvent>

//// NotesWriter constructor ////
NotesWriter::NotesWriter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesWriter)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle(tr("Writer")); // Window title
}

NotesWriter::~NotesWriter()
{
    delete ui;
}

//// Event Handling ////

void NotesWriter::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton answer = QMessageBox::warning(this,"Unsaved file",
                                                              "Unsaved document found. Do you want to close this document?",
                                                              QMessageBox::Save | QMessageBox::Yes | QMessageBox::No); // Warning the user about an unsaved file

    if(answer == QMessageBox::Yes){
        QWidget::closeEvent(event);
    }
    else if(answer == QMessageBox::Save){
        QString fileName = QFileDialog::getSaveFileName(this,"Document Save As..." ,"", "txt (*.txt);;All files (*.*)"); // Opening the path to save the document
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            event->ignore();
        }

        filePath = fileName;
        setWindowTitle(fileName); // Setting the file path to window title
        QTextStream out(&file); // Interface to do the reading
        QString text = ui->textEdit->toPlainText();
        out << text; // Output to file
        file.flush();
        file.close();
    }
    else if(answer == QMessageBox::No){
         event->ignore(); // Returning back to the Text Editor
    }
}

//// End of Event Handling ////

//// Buttons ////

void NotesWriter::on_actionNew_Writer_triggered()
{
    filePath = ""; // Global referencing the current file
    ui->textEdit->setText(""); // Clearing the textEdit widget
}

void NotesWriter::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open a Document", QDir::homePath(),"Text documents (*.txt)"); // Allowing user to open a file using the home directory of the computer
    QFile file(fileName); // Getting the name of a file
    filePath = fileName; // Saving the current document

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    setWindowTitle(fileName); // Setting the file path to window title
    QTextStream in(&file); // Interface to do the reading
    QString text = in.readAll(); // Copying text
    ui->textEdit->setText(text);
    file.close();
}

void NotesWriter::on_actionSave_triggered()
{
    QFile file(filePath); // Getting the path of a file

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error!","You have not saved this Document anywhere. Click OK to return back.");
        return;
    }

    setWindowTitle(filePath); // Setting the file path to window title
    QTextStream out(&file); // Interface to do the reading
    QString text = ui->textEdit->toPlainText();
    out << text; // Output to file
    file.flush();
    file.close();
}

void NotesWriter::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Document Save As...", "", "PDF (*.pdf);;txt(*.txt);;All files (*.*)"); // Opening the path to save the document
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error!","You have not saved this Document.  Click OK to return back.");
        return;
    }

    filePath = fileName;
    setWindowTitle(fileName); // Setting the file path to window title
    QTextStream out(&file); // Interface to do the reading
    QString text = ui->textEdit->toPlainText();
    out << text; // Output to file
    file.flush();
    file.close();
}

void NotesWriter::on_actionPrint_triggered()
{
    /*QPrinter printer;
    printer.setPrinterName("Printer Name: "); //This is name of the printer
    QPrintDialog printDialog(&printer, this); //Allowing the user to select the Printer to print the document

    if(printDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Error!", "Printing the Document is not set. Click OK to return back.");
        return;
    }

    ui->textEdit->print(&printer); //Sending texts to the printer*/ // Not working

    QPrinter printer; // Interacting with the available printer
    QPrintDialog dialog(&printer,this);
    dialog.setWindowTitle("Print document");
    if(ui->textEdit->textCursor().hasSelection()){
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection); // Allowing the user to select the Printer to print the document
    }
    if(dialog.exec() != QDialog::Accepted)
        return;
}

void NotesWriter::on_actionClose_Writer_triggered()
{
    NotesWriter::close(); // Exiting from the current window
}

void NotesWriter::on_actionCut_triggered()
{
    ui->textEdit->cut(); // Allowing the text editor to cut text
}

void NotesWriter::on_actionCopy_triggered()
{
    ui->textEdit->copy(); // Allowing the text editor to copy text
}

void NotesWriter::on_actionPaste_triggered()
{
    ui->textEdit->paste(); // Allowing the text editor to paste text
}

void NotesWriter::on_actionSelect_Font_triggered()
{
    bool selectFont;
    QFont editFont = QFontDialog::getFont(&selectFont, this); // Allowing the user to select font

    if(selectFont){
        ui->textEdit->setFont(editFont);
    }
    else
        return;
}

void NotesWriter::on_actionSelect_Font_Color_triggered()
{
    QColor fontColor = QColorDialog::getColor(Qt::white,this,"Select a color to your font..."); // White color is set to dafault font color

    if(fontColor.isValid()){
        ui->textEdit->setTextColor(fontColor);
    }
}

void NotesWriter::on_actionSelect_Font_Highlighter_Color_triggered()
{
    QColor fontHightlight = QColorDialog::getColor(Qt::white,this,"Select a color to highlight your font..."); // White color is set to dafault font hightlight color

    if(fontHightlight.isValid()){
        ui->textEdit->setTextBackgroundColor(fontHightlight);
    }
}

void NotesWriter::on_actionChange_Writer_Background_Color_triggered()
{
    QColor bgColor = QColorDialog::getColor(Qt::white,this,"Change background color..."); // White color is set to dafault font hightlight color

    if(bgColor.isValid()){
        ui->textEdit->setPalette(QPalette(bgColor)); // Currently only black color background is visible
    }
}

void NotesWriter::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void NotesWriter::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void NotesWriter::on_actionAbout_Writer_triggered()
{
    QString aboutWriter = "MyNotebook Writer is a simple text editor for the anyone to "
                          "quickly get started with writing text documents. "
                          "MyNotebook Writer will provide the facilities simply from writing documents to printing it.\n\nEnjoy!";
    QMessageBox::about(this,"About MyNotebook Writer", aboutWriter);
}

void NotesWriter::on_actionAbout_QT_triggered()
{
    QMessageBox::aboutQt(this);
}

void NotesWriter::on_actionGo_to_Google_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/")); // Opening Google webpage
}

void NotesWriter::on_actionGo_to_University_of_Plymouth_triggered()
{
    QDesktopServices::openUrl(QUrl("https://dle.plymouth.ac.uk/")); // Opening University of Plymouth website
}

//// End of Buttons ////
//// End ////
