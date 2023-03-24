#include "notes.h"

bool Notes::fromOldest = true;
bool Notes::isLastDeleted = false;
int Notes::currentIdx;
int Notes::currentFiltredIdx;

QList<Notes> Notes::listNotes;
QList<Notes> Notes::filtredNotes;

void Notes::addToList(Notes newNote) {
    for(QList<Notes>::Iterator it = listNotes.begin();it != listNotes.end(); ++it) {
        if(*it == newNote) {
            listNotes.replace(listNotes.indexOf(*it), newNote);
            return;
        }
    }
    listNotes.push_back(newNote);
    sortFunction();
    currentIdx = listNotes.indexOf(newNote);
}

QString Notes::pNote() {
    int prevIdx = currentIdx;
    prevIdx--;
    if(prevIdx >= 0) {
        return listNotes.at(prevIdx).getFullNote();
    }
    else
        return "<em> Brak poprzedniego wpisu </em>";
}

QString Notes::cNote() {
    if(currentIdx >= 0)
        return listNotes.at(currentIdx).getFullNote();
    else
        return "Brak aktualnego wspomnienia";
}

QString Notes::nNote() {
    int nextIdx = currentIdx;
    nextIdx++;
    if(nextIdx < listNotes.size()) {
        return listNotes.at(nextIdx).getFullNote();
    }
    else
        return "<em> Brak nastepnego wpisu </em>";
}

QString Notes::filtredcNote()
{
    if(currentFiltredIdx >= 0) {
        return filtredNotes.at(currentFiltredIdx).getFullNote();
    }
    else
        return "Brak aktualnego wspomnienia";
}

QString Notes::filtredpNote()
{
    int prevIdx = currentFiltredIdx;
    prevIdx--;
    if(prevIdx >= 0) {
        return filtredNotes.at(prevIdx--).getFullNote();
    }
    else
        return "<em> Brak poprzedniego wpisu </em>";
}

QString Notes::filtrednNote()
{
    int nextIdx = currentFiltredIdx;
    nextIdx++;
    if(nextIdx < filtredNotes.size()) {
        return filtredNotes.at(nextIdx++).getFullNote();
    }
    else
        return "<em> Brak nastepnego wpisu </em>";
}

void Notes::decrementIdx()
{
    currentIdx--;
    if(currentIdx <= 0) {
        currentIdx = 0;
        return;
    }
}

void Notes::incrementIdx()
{
    currentIdx++;
    if(currentIdx >= listNotes.size()) {
        currentIdx = listNotes.size() - 1;
        return;
    }
}

void Notes::deleteNote()
{
    if(listNotes.size() > 0 && currentIdx >= 0) {
        listNotes.removeAt(currentIdx);
         currentIdx--;
         if(currentIdx < 0) {
            currentIdx = 0;
            isLastDeleted = false;
         }
         if(listNotes.isEmpty()) {
             QFileInfo file(QDir::currentPath() + "/wspomnienia.txt");
             if(file.exists()) {
                 QFile fileToDelete = file.filePath();
                 fileToDelete.remove();
             }
             isLastDeleted = true;
         }
    }
}

void Notes::changeSortType()
{
    if(!listNotes.isEmpty()) {
        fromOldest = !fromOldest;
        sortFunction();
    }
}

bool Notes::fileExist()
{
    QFileInfo file(QDir::currentPath() + "/wspomnienia.txt");
    return file.exists();
}

void Notes::readFile(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString numNotes = stream.readLine();
        currentIdx = numNotes.toInt();
        QDateTime date;
        int idxOfFeeling;
        Feelings feeling;
        QString note;
        while(stream.atEnd() == false) {
            date = QDateTime::fromString(stream.readLine());
            idxOfFeeling = stream.readLine().toInt();
            feeling = static_cast<Feelings>(idxOfFeeling);
            note = stream.readLine();
            addToList(Notes(date, note, feeling));
        }
        file.close();
    }
}

void Notes::createFile(QString path)
{
    if(listNotes.size() > 0) {
        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << currentIdx;
            stream << "\n";
            for (int i = 0; i < listNotes.size(); i++) {
                stream << listNotes.at(i).getm_DateTime().toString();
                stream << "\n";
                stream << (int)listNotes.at(i).m_feeling;
                stream << "\n";
                stream << listNotes.at(i).getm_Note();
                stream << "\n";
            }
        }
        file.close();
    }
}

void Notes::addNeutralne()
{
    filtredNotes.clear();
    for(int i = 0; i < listNotes.size(); i++) {
        if(listNotes.at(i).m_feeling == Feelings::Neutral) {
            filtredNotes.push_back(listNotes.at(i));
        }
    }
    currentFiltredIdx = filtredNotes.size() - 1;
}

void Notes::filterList(Feelings feeling)
{
    for(int i = 0; i < listNotes.size(); i++) {
        if(listNotes.at(i).m_feeling == feeling) {
            filtredNotes.push_back(listNotes.at(i));
        }
    }
}

bool Notes::isFilteredListEmpty()
{
    return filtredNotes.empty();
}

void Notes::clearFilteredList()
{
    filtredNotes.clear();
}

void Notes::decrementFilteredIdx()
{
    currentFiltredIdx--;
    if(currentFiltredIdx <= 0) {
        currentFiltredIdx = 0;
        return;
    }
}

void Notes::incrementFilteredIdx()
{
    currentFiltredIdx++;
    if(currentFiltredIdx >= filtredNotes.size()) {
        currentFiltredIdx = filtredNotes.size() - 1;
        return;
    }
}

void Notes::sortFilteredNotes()
{
    sortFunction();
}

bool Notes::isThisFeeling(Feelings feeling)
{
    for(auto i : listNotes){
        if(i.m_feeling == feeling)
            return true;
    }
    return false;
}



void Notes::sortFunction() {
    if(!filtredNotes.empty()) {
        if(fromOldest)
            std::sort(filtredNotes.begin(), filtredNotes.end());
        else
            std::sort(filtredNotes.begin(), filtredNotes.end(), std::greater<Notes>());
        return;
    }
    if(fromOldest)
        std::sort(listNotes.begin(), listNotes.end());
    else
        std::sort(listNotes.begin(), listNotes.end(), std::greater<Notes>());
}

Notes::Notes(QDateTime dateTime, QString note, Feelings feeling)
    :m_DateTime(dateTime), m_note(note)
{
    m_feeling = feeling;
    std::array<QString,3> feelingArr;
    feelingArr[0] = "smutny";
    feelingArr[1] = "neutralny";
    feelingArr[2] = "radosny";
    m_noteAndDate = "<b>" + dateTime.toString() + "</b>" + "<br>" + "<i>" + feelingArr[(int)m_feeling] + "</i>" + "<br>" + note;
};

bool Notes::operator==(const Notes& rhs) const {
    if(this != &rhs) {
        return (this->m_DateTime == rhs.m_DateTime);
    }
    return true;
}
bool Notes::operator!=(const Notes& rhs) const {
    return !(*this == rhs);
}
bool Notes::operator>(const Notes& rhs) const {
    return (this->m_DateTime > rhs.m_DateTime);
}
bool Notes::operator<(const Notes& rhs) const {
    return (this->m_DateTime < rhs.m_DateTime);
}


