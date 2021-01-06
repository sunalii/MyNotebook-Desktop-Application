#ifndef NOTESDOODLE_H
#define NOTESDOODLE_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QImage>
#include <QCloseEvent>

namespace Ui {
class NotesDoodle;
}

class NotesDoodle : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesDoodle(QWidget *parent = 0);
    ~NotesDoodle();

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void paintEvent(QPaintEvent *event)override;
    virtual void resizeEvent(QResizeEvent *event)override;

protected:
    void closeEvent(QCloseEvent *event)override;

private slots:

    void on_actionSave_triggered();

    void on_actionClear_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_action2px_triggered();

    void on_action5px_triggered();

    void on_action10px_triggered();

    void on_action12px_triggered();

    void on_actionBlack_triggered();

    void on_actionWhite_triggered();

    void on_actionRed_triggered();

    void on_actionGreen_triggered();

    void on_actionBlue_triggered();

    void on_actionEraser_triggered();

    void on_actionEraser_20px_triggered();

    void on_actionPen_triggered();

    void on_actionPencil_triggered();

    void on_actionAbout_MyNotebookDoodle_triggered();

    void on_actionAbout_QT_triggered();

    void on_actionGo_to_Google_triggered();

    void on_actionGo_to_Plymouth_triggered();

private:
    Ui::NotesDoodle *ui;
    QImage image;
    bool drawing;
    QPoint lastPoint;
    int brushSize;
    QColor brushColor;
    void resizeImage(QImage *image, const QSize &newSize);
};

#endif // NOTESDOODLE_H
