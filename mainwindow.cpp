#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, Program *app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mainApp(app)
{
    app->setGUI(this);
    ui->setupUi(this);

    connect(mainApp,SIGNAL(sendNotes(QString,QString,QString)),this,SLOT(on_sendNotes(QString,QString,QString)));
    connect(this,SIGNAL(doubleClickedRight()),this,SLOT(on_handleDoubleClickRight()));
    connect(this,SIGNAL(doubleClickedLeft()),this,SLOT(on_handleDoubleClickLeft()));
    connect(mainApp,SIGNAL(setEnableUsun()),this,SLOT(on_setEnableUsun()));

    mainApp->checkFile();
    ui->everyFeelingBox->setChecked(true);
}

MainWindow::~MainWindow()
{
    mainApp->saveFile();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mainApp->createWindow();
}

void MainWindow::on_downButton_clicked()
{
    mainApp->incrementIdx();
}

void MainWindow::on_upButton_clicked()
{
    mainApp->decrementIdx();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Up) {
        on_upButton_clicked();
    }
    if(event->key() == Qt::Key_Down) {
        on_downButton_clicked();
    }

}

void MainWindow::on_handleDoubleClickRight()
{
    on_deleteNote_clicked();
}

void MainWindow::on_handleDoubleClickLeft()
{
    on_pushButton_clicked();
}

void MainWindow::on_sendNotes(QString prevNote, QString currNote, QString nextNote)
{
    ui->previousNote->setText(prevNote);
    ui->currentNote->setText(currNote);
    ui->nextNote->setText(nextNote);
}

void MainWindow::on_setEnableUsun()
{
    ui->deleteNote->setEnabled(true);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(ui->deleteNote->isEnabled()) {
        if(e->button() == Qt::LeftButton) {
            emit doubleClickedLeft();
        }
        if(e->button() == Qt::RightButton) {
            emit doubleClickedRight();
        }
    }
}


void MainWindow::on_deleteNote_clicked()
{
    mainApp->deleteNote();
}


void MainWindow::on_pushSort_clicked()
{
    mainApp->changeSortType();
}


void MainWindow::on_loadBackUpButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Otworz plik .txt","","Pliki tekstowe (*.txt)");
    mainApp->loadBackUp(path);
}


void MainWindow::on_saveBackUpButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"Wybierz lokalizacje zapisu pliku","","Pliki tekstowe (*.txt)");
    mainApp->saveBackUp(path);
}


void MainWindow::on_everyFeelingBox_clicked()
{
    mainApp->displayNotes();
    ui->neutralFeelingBox->setChecked(false);
    ui->sadFeelingBox->setChecked(false);
    ui->happyFeelingBox->setChecked(false);
}


void MainWindow::on_neutralFeelingBox_clicked(bool checked)
{
    if(checked)
        ui->everyFeelingBox->setChecked(false);
}


void MainWindow::on_happyFeelingBox_clicked(bool checked)
{
    if(checked)
        ui->everyFeelingBox->setChecked(false);
}


void MainWindow::on_sadFeelingBox_clicked(bool checked)
{
    if(checked)
        ui->everyFeelingBox->setChecked(false);
}

