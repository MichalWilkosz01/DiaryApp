#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <QFileDialog>
#include "addingnotes.h"
#include "notes.h"

class MainWindow;

class Program : public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr) { GUI = ui; }
    void createWindow();
    void decrementIdx();
    void incrementIdx();
    void deleteNote();
    void changeSortType();
    void checkFile();
    void saveFile();
    void loadBackUp(QString filePath);
    void saveBackUp(QString filePath);
    void filtrNeutralne();
    void displayFiltred();
    void displayNotes();
signals:
    void sendNotes(QString pNote, QString cNote, QString nNote);
    void setEnableUsun();
private:
    MainWindow *GUI = nullptr;
    AddingNotes* winNote;  
    void choseFile(QString path);

};

#endif // PROGRAM_H
