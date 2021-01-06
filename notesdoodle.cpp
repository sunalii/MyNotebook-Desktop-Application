#include "notesdoodle.h"
#include "ui_notesdoodle.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QUrl>

//// NotesDoodle Constructor ////

NotesDoodle::NotesDoodle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesDoodle)
{
    ui->setupUi(this);
    setWindowTitle(tr("Doodle")); // Window title
    image = QImage(this->size(), QImage::Format_RGB32); // Doodle area
    image.fill(Qt::white); // Setting default background
    drawing = false; // Clear screen
    brushColor = Qt::black; // Setting default Brush Color
    brushSize = 2; // Setting default Brush Color
}

NotesDoodle::~NotesDoodle()
{
    delete ui;
}

//// Event Handling ////

void NotesDoodle::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) // Allowing user to draw when the Left Mouse button is pressed
  {
    drawing = true;
    lastPoint = event->pos();
  }
}

void NotesDoodle::mouseMoveEvent(QMouseEvent *event)
{
  if ((event->buttons() & Qt::LeftButton) && drawing) // Allowing user to draw when the Left Mouse button is moving
  {
    QPainter painter(&image);
    painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, event->pos());

    lastPoint = event->pos();
    this->update();
  }
}

void NotesDoodle::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) // Drawing stops with the relase of the Left Mouse button click
  {
    drawing = false;
  }
}

void NotesDoodle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // Interacting with the available printer
    QRect scribbleRect = event->rect();
    painter.drawImage(scribbleRect,image,scribbleRect); // Printing the screen
}

void NotesDoodle::resizeEvent(QResizeEvent *event) // Not working
{
    if (width() > image.width() || height() > image.height()) {
      // int newWidth = qMax(width() + 128, image.width());
       // int newHeight = qMax(height() + 128, image.height());
        //resizeImage(&image, QSize(newWidth, newHeight));
        resize(1920,1080);
        update();
    }
    QWidget::resizeEvent(event);
}

void NotesDoodle::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton answer = QMessageBox::warning(this,"Unsaved file",
                                                              "Unsaved doodle found. Do you want to close the doodle?",
                                                              QMessageBox::Save | QMessageBox::Yes | QMessageBox::No); // Warning the user about an unsaved file

    if(answer == QMessageBox::Yes){
        QWidget::closeEvent(event); // Closes the window
    }
    else if(answer == QMessageBox::Save){
        QString filePath = QFileDialog::getSaveFileName(this,"Save Doodle", "", "PNG (*.png);;jpeg(*.jpg *.jpeg);;All files (*.*)"); // Triggering the Save action function to save the Doodle
        image.save(filePath);
        event->ignore();
    }
    else if(answer == QMessageBox::No){
        event->ignore(); // Returning back to the Doodle
    }
}

//// End of Event Handling ////

//// Buttons ////

void NotesDoodle::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Save Doodle", "", "PNG (*.png);;jpeg(*.jpg *.jpeg);;All files (*.*)");

    if(filePath == ""){
        return;
    }

    image.save(filePath);
}

void NotesDoodle::on_actionClear_triggered()
{
    image.fill(Qt::white); // Clearing the background
    this->update();
}

void NotesDoodle::on_actionPrint_triggered()
{
    QPrinter printer(QPrinter::HighResolution); // Can be used to print

    QPrintDialog printDialog(&printer, this); // Open printer dialog and print if asked
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
}

void NotesDoodle::on_actionExit_triggered()
{
    NotesDoodle::close(); // Exiting from the current window
}

void NotesDoodle::on_action2px_triggered()
{
    brushSize = 2;
    brushColor = Qt::black;
}

void NotesDoodle::on_action5px_triggered()
{
    brushSize = 5;
    brushColor = Qt::black;
}

void NotesDoodle::on_action10px_triggered()
{
    brushSize = 10;
    brushColor = Qt::black;
}

void NotesDoodle::on_action12px_triggered()
{
    brushSize = 20;
    brushColor = Qt::black;
}

void NotesDoodle::on_actionBlack_triggered()
{
    brushColor = Qt::black;
}

void NotesDoodle::on_actionWhite_triggered()
{
    brushColor = Qt::white;
}

void NotesDoodle::on_actionRed_triggered()
{
    brushColor = Qt::red;
}

void NotesDoodle::on_actionGreen_triggered()
{
    brushColor = Qt::green;
}

void NotesDoodle::on_actionBlue_triggered()
{
    brushColor = Qt::blue;
}

void NotesDoodle::on_actionEraser_triggered()
{
    brushSize = 5;
    brushColor = Qt::white;
}

void NotesDoodle::on_actionEraser_20px_triggered()
{
    brushSize = 20;
    brushColor = Qt::white;
}

void NotesDoodle::on_actionPen_triggered()
{
    brushSize = 5;
    brushColor = Qt::blue;
}

void NotesDoodle::on_actionPencil_triggered()
{
    brushSize = 2;
    brushColor = Qt::black;
}

void NotesDoodle::on_actionAbout_MyNotebookDoodle_triggered()
{
    QString aboutDoodle = "MyNotebook Doodle is a simple painting playground for the anyone to "
                          "quickly get started with scribbling any patterns and designs. "
                          "MyNotebook Doodle will provide the facilities simply from drawing patterns to printing it.\n\nEnjoy!";
    QMessageBox::about(this,"About MyNotebook Doodle", aboutDoodle);
}

void NotesDoodle::on_actionAbout_QT_triggered()
{
     QMessageBox::aboutQt(this);
}

void NotesDoodle::on_actionGo_to_Google_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.google.com/"));  // Opening Google webpage
}

void NotesDoodle::on_actionGo_to_Plymouth_triggered()
{
    QDesktopServices::openUrl(QUrl("https://dle.plymouth.ac.uk/")); // Opening University of Plymouth website
}

//// End of Buttons ////
//// End ////
