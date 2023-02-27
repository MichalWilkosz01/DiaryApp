#include "program.h"

Program::Program(QObject *parent)
    : QObject{parent}
{

}

void Program::createWindow()
{
    winNote = new AddingNotes(nullptr);
    winNote->exec();
    if(winNote->getIsEmpty()) {
        delete winNote;
        return;
    }
    Notes n1(winNote->getDate(), winNote->getNote(), (int)winNote->getUczucie());
    Notes::addToList(n1);
    delete winNote;
    displayNotes();
    if(!Notes::isEmpty())
        emit setEnableUsun();
}

void Program::decrementIdx()
{
    if(!Notes::isEmpty()) {
        Notes::decrementIdx();
        displayNotes();
    }
}

void Program::incrementIdx()
{
    if(!Notes::isEmpty()) {
        Notes::incrementIdx();
        displayNotes();
    }
}

void Program::deleteNote()
{
    Notes::deleteNote();
    if(Notes::getListSize() != 0)
       displayNotes();
    if(Notes::isEmpty()) {
       QString prevNote = "";
       QString currNote = "Usunieto ostatni wpis";
       QString nextNote = "";
       emit sendNotes(prevNote, currNote, nextNote);
    }
}

void Program::displayNotes()
{
    QString prevNote = Notes::pNote();
    QString currNote = Notes::cNote();
    QString nextNote = Notes::nNote();
    emit sendNotes(prevNote, currNote, nextNote);
}

void Program::choseFile(QString path)
{
    Notes::readFile(path);
}

void Program::changeSortType()
{
    if(!Notes::isEmpty()) {
        Notes::changeSortType();
        displayNotes();
    }
}

void Program::checkFile()
{
    if(Notes::fileExist()) {
        choseFile(QDir::currentPath() + "/wspomnienia.txt");
        displayNotes();
        emit setEnableUsun();
    }
}

void Program::saveFile()
{
    Notes::createFile(QDir::currentPath() + "/wspomnienia.txt");
}

void Program::loadBackUp(QString filePath)
{
    Notes::readFile(filePath);
    displayNotes();
    emit setEnableUsun();
}

void Program::saveBackUp(QString filePath)
{
    Notes::createFile(filePath);
}

void Program::filtrNeutralne()
{
    Notes::addNeutralne();
    displayFiltred();

}

void Program::displayFiltred()
{
    QString prevNote = Notes::pNote();
    QString currNote = Notes::filtredcNote();
    QString nextNote = Notes::nNote();
    emit sendNotes(prevNote, currNote, nextNote);
}


