#ifndef NOTESWRITER_H
#define NOTESWRITER_H

#include <QMainWindow>
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

namespace Ui {
class NotesWriter;
}

class NotesWriter : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesWriter(QWidget *parent = nullptr);
    ~NotesWriter();

protected:
    void closeEvent(QCloseEvent *event)override;

private slots:
    void on_actionGo_to_University_of_Plymouth_triggered();

    void on_actionNew_Writer_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionPrint_triggered();

    void on_actionClose_Writer_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSelect_Font_triggered();

    void on_actionSelect_Font_Color_triggered();

    void on_actionSelect_Font_Highlighter_Color_triggered();

    void on_actionChange_Writer_Background_Color_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_Writer_triggered();

    void on_actionAbout_QT_triggered();

    void on_actionGo_to_Google_triggered();


private:
    Ui::NotesWriter *ui;
    QString filePath = ""; //Holds the current path of the file
};

#endif // NOTESWRITER_H
