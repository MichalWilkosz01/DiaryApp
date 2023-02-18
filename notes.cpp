#include "notes.h"

bool Notes::fromOldest = true;
bool Notes::isLastDeleted = false;
int Notes::currentIdx;
int Notes::currendFiltredIdx;

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
    if(currentIdx >= 0)
        return listNotes.at(currendFiltredIdx).getFullNote();
    else
        return "Brak aktualnego wspomnienia";
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
        int ucz;
        QString note;
        while(stream.atEnd() == false) {
            date = QDateTime::fromString(stream.readLine());
            ucz = stream.readLine().toInt();
            note = stream.readLine();
            addToList(Notes(date, note, ucz));
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
                stream << listNotes.at(i).m_uczucie;
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
        if(listNotes.at(i).m_uczucie == 1) {
            filtredNotes.push_back(listNotes.at(i));
        }
    }
    currendFiltredIdx = filtredNotes.size() - 1;
}



void Notes::sortFunction() {
    if(fromOldest)
        std::sort(listNotes.begin(), listNotes.end());
    else
        std::sort(listNotes.begin(), listNotes.end(), std::greater<Notes>());
}

Notes::Notes(QDateTime dateTime, QString note, int uczucie)
    :m_DateTime(dateTime), m_note(note)
{
    m_uczucie = uczucie;
    std::array<QString,3> feelingArr;
    feelingArr[0] = "smutny";
    feelingArr[1] = "neutralny";
    feelingArr[2] = "radosny";
    m_noteAndDate = "<b>" + dateTime.toString() + "</b>" + "<br>" + "<i>" + feelingArr[m_uczucie] + "</i>" + "<br>" + note;
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

