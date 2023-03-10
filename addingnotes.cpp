#include "addingnotes.h"
#include "qpushbutton.h"
#include "ui_addingnotes.h"

AddingNotes::AddingNotes(QWidget *parent) :    
    QDialog(parent),
    ui(new Ui::AddingNotes)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Dodaj");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Anuluj");
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->checkBoxNeutralny->click();
    ui->checkBoxNeutralny->setChecked(true);
}

bool AddingNotes::getIsEmpty()
{
    return isEmpty;
}

QDateTime AddingNotes::getDate()
{
    return date;
}

QString AddingNotes::getNote()
{
    return note;
}

AddingNotes::~AddingNotes()
{
    delete ui;
}

void AddingNotes::on_buttonBox_accepted()
{
    if(ui->enterNote->toPlainText().isEmpty()) {
        isEmpty = true;
        return;
    }
    isEmpty = false;
    this->note = ui->enterNote->toPlainText();
    this->date = ui->dateTimeEdit->dateTime();
}


void AddingNotes::on_buttonBox_rejected()
{
    isEmpty = true;
}

void AddingNotes::on_checkBoxSmutny_clicked()
{
    feeling = Feelings::Sad;
    ui->checkBoxSmutny->setEnabled(false);
    ui->checkBoxNeutralny->setEnabled(true);
    ui->checkBoxRadosny->setEnabled(true);


    ui->checkBoxNeutralny->setChecked(false);
    ui->checkBoxRadosny->setChecked(false);
}

void AddingNotes::on_checkBoxNeutralny_clicked()
{
    feeling = Feelings::Neutral;
    ui->checkBoxSmutny->setEnabled(true);
    ui->checkBoxNeutralny->setEnabled(false);
    ui->checkBoxRadosny->setEnabled(true);


    ui->checkBoxSmutny->setChecked(false);
    ui->checkBoxRadosny->setChecked(false);
}


void AddingNotes::on_checkBoxRadosny_clicked()
{
    feeling = Feelings::Happy;
    ui->checkBoxSmutny->setEnabled(true);
    ui->checkBoxNeutralny->setEnabled(true);
    ui->checkBoxRadosny->setEnabled(false);


    ui->checkBoxNeutralny->setChecked(false);
    ui->checkBoxSmutny->setChecked(false);
}

