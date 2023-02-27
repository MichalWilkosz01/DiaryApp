#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QKeyEvent>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QMouseEvent>
#include "program.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Program;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program *app = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_deleteNote_clicked();

    void on_pushSort_clicked();

    void on_handleDoubleClickRight();

    void on_handleDoubleClickLeft();

    void on_sendNotes(QString prevNote, QString currNote, QString nextNote);

    void on_setEnableUsun();
    void on_loadBackUpButton_clicked();

    void on_saveBackUpButton_clicked();

    void on_everyFeelingBox_clicked();

    void on_neutralFeelingBox_clicked(bool checked);

    void on_happyFeelingBox_clicked(bool checked);

    void on_sadFeelingBox_clicked(bool checked);

signals:
    void doubleClickedLeft();
    void doubleClickedRight();

private:
    Ui::MainWindow *ui = nullptr;
    Program *mainApp = nullptr;

    void keyPressEvent(QKeyEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent *e) override;
};
#endif // MAINWINDOW_H
