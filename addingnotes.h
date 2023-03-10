#ifndef ADDINGNOTES_H
#define ADDINGNOTES_H

#include "qdatetime.h"
#include <QDialog>
#include "myenums.h"

namespace Ui {
class AddingNotes;
}



class AddingNotes : public QDialog
{
    Q_OBJECT

public:
    explicit AddingNotes(QWidget *parent = nullptr);
    //Notes* getNote();
    bool getIsEmpty();
    QDateTime getDate();
    QString getNote();
    ~AddingNotes();
    Feelings getUczucie() {return feeling; }

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_checkBoxSmutny_clicked();

    void on_checkBoxNeutralny_clicked();

    void on_checkBoxRadosny_clicked();

private:
    Feelings feeling = Feelings::Neutral;
    Ui::AddingNotes *ui;
    QString note;
    QDateTime date;
    bool isEmpty;
};

#endif // ADDINGNOTES_H
