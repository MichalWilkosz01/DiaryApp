#include "program.h"
#include "notes.h"

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
    Notes::addToList(Notes(winNote->getDate(), winNote->getNote(), winNote->getUczucie()));
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
       QString currNote = "Usunieto ostatni wpis!";
       QString nextNote = "";
       emit sendNotes(prevNote, currNote, nextNote);
    }
}

void Program::displayNotes()
{
    if(!Notes::isEmpty()) {
        if(!Notes::isFilteredListEmpty())
            Notes::clearFilteredList();
        isFiltered = false;
        QString prevNote = Notes::pNote();
        QString currNote = Notes::cNote();
        QString nextNote = Notes::nNote();
        emit sendNotes(prevNote, currNote, nextNote);
    }
}

void Program::displayFilteredNotes(Feelings feeling)
{
    if(!Notes::isEmpty()) {
        if(Notes::isThisFeeling(feeling)) {
            isFiltered = true;
            Notes::filterList(feeling);
            Notes::sortFilteredNotes();

            QString prevNote = Notes::filtredpNote();
            QString currNote = Notes::filtredcNote();
            QString nextNote = Notes::filtrednNote();
            emit sendNotes(prevNote, currNote, nextNote);
        }
        else {
            if(Notes::isFilteredListEmpty()) {
                emit sendNotes("", "Brak wspomnien", "");
            }
        }
    }
}

bool Program::checkIsFiltered()
{
    return isFiltered;
}

void Program::decrementFilteredIdx()
{
    if(!Notes::isFilteredListEmpty()) {
        Notes::decrementFilteredIdx();
        displayFiltered();
    }
}

void Program::incrementFilteredIdx()
{
    if(!Notes::isFilteredListEmpty()) {
        Notes::incrementFilteredIdx();
        displayFiltered();
    }
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
    displayFiltered();

}

void Program::displayFiltered()
{
    QString prevNote = Notes::filtredpNote();
    QString currNote = Notes::filtredcNote();
    QString nextNote = Notes::filtrednNote();
    emit sendNotes(prevNote, currNote, nextNote);
}


