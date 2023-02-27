#ifndef NOTES_H
#define NOTES_H


#include "qdatetime.h"
#include <QList>
#include <algorithm>
#include <QFileInfo>
#include <QDir>


class Notes
{
private:
    QDateTime m_DateTime;
    QString m_note;
    QString m_noteAndDate;
    static void sortFunction();
    static bool fromOldest;
    static QList<Notes> listNotes;
    static int currentIdx;
    static bool isLastDeleted;
    static QList<Notes> filtredNotes;
    static int currendFiltredIdx;
    int m_uczucie = 1;

public:
    Notes(QDateTime dateTime, QString note, int uczucie);
    QDateTime getm_DateTime() const { return m_DateTime; }
    QString getm_Note() const { return m_note; }
    QString getFullNote() const { return m_noteAndDate; }
    bool operator==(const Notes& rhs) const;
    bool operator!=(const Notes& rhs) const;
    bool operator>(const Notes& rhs) const;
    bool operator<(const Notes& rhs) const;
    static bool isEmpty() { return listNotes.isEmpty(); }
    static bool getIsLastdeleted() { return isLastDeleted; }
    static void addToList(Notes newNote);
    static int getListSize() { return listNotes.size(); }
    static int getCurrentIndex() { return currentIdx; }
    static QString cNote();
    static QString pNote();
    static QString nNote();
    static QString filtredcNote();
    static QString filtredpNote();
    static QString filtrednNote();
    static void decrementIdx();
    static void incrementIdx();
    static void deleteNote();
    static void changeSortType();
    static bool fileExist();
    static void readFile(QString path);
    static void createFile(QString path);
    static void addNeutralne();
};

#endif // NOTES_H
