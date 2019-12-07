#ifndef EDITARDIALOG_H
#define EDITARDIALOG_H

#include <QDialog>
#include "ninho.h"

namespace Ui {
class EditarDialog;
}

class EditarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditarDialog(QWidget *parent = nullptr);
    ~EditarDialog();

    Ninho getObjeto();
    void setObjeto();
    bool novo;
    void setObjeto(Ninho a);

    bool getApagar() const;
    void setApagar(bool value);


private slots:
    void on_pushButton_2_clicked();

    void on_btn_salvar_clicked();

    void on_btn_excluir_clicked();

private:
    Ui::EditarDialog *ui;
    Ninho temp;
    bool apagar;

};

#endif // EDITARDIALOG_H
