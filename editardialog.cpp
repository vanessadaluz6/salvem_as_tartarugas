#include "editardialog.h"
#include "ui_editardialog.h"
#include <QDebug>

EditarDialog::EditarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditarDialog)
{
    ui->setupUi(this);
    novo = false;
    apagar=false;
}

EditarDialog::~EditarDialog()
{
    delete ui;

}

Ninho EditarDialog::getObjeto()
{
    return temp;
}

void EditarDialog::setObjeto()
{

    QDate tempo;

    tempo = ui->data_1->date();

    temp.setPraia(ui->cB_1->currentText());

    temp.setDia(ui->data_1->DaySection);

    temp.setMes(ui->data_1->MonthSection);

    temp.setAno(ui->data_1->YearSection);


    switch(ui->cB_2->currentIndex()){

    case 0:
        temp.setSinal(false);break;

    case 1:
        temp.setSinal(true);break;
    }
    temp.setDesova(tempo);


}

void EditarDialog::setObjeto(Ninho a)
{
    temp = a;
    QString p = "PENDENTE";
    QString f = "FINALIZADO";

    ui->cB_1->setCurrentText(a.getPraia());
    ui->data_1->setDate(a.getDesova());

    ui->cB_2->setCurrentText(a.getSinal());

}


void EditarDialog::on_pushButton_2_clicked()
{
    close();
}

void EditarDialog::on_btn_salvar_clicked()
{
    setObjeto();
    novo = true;

    close();

}

void EditarDialog::on_btn_excluir_clicked()
{
    setApagar(true);
    close();
}

bool EditarDialog::getApagar() const
{
    return apagar;
}

void EditarDialog::setApagar(bool value)
{
    apagar = value;
}
