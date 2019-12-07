#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    id = 0;
    ui->Tabela->setColumnWidth(0,120);
    ui->Tabela->setColumnWidth(1,120);

    QHeaderView *header = ui->Tabela->horizontalHeader();
    header->setSortIndicator(1, Qt::DescendingOrder);
    connect(header, SIGNAL(sectionClicked(int)), ui->Tabela, SLOT (sortByColumn(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_1_clicked()
{
    Ninho temp;
    QString temp_praia = ui->cB_1->currentText();
    int temp_sinal = ui->cB_2->currentIndex();
    QDate tempo;

    tempo = ui->data_1->date();

    temp.setPraia(temp_praia);

    temp.setDia(ui->data_1->DaySection);
    temp.setMes(ui->data_1->MonthSection);
    temp.setAno(ui->data_1->YearSection);

    switch(temp_sinal){

    case 0:
        temp.setSinal(false);break;

    case 1:
        temp.setSinal(true);break;
    }

    QString mat = "";

    QString ano = QString::number(ui->data_1->date().year());

    QString semestre;
        if(ui->data_1->date().month() <= 6)
            semestre = "1";
        else
            semestre = "2";

     mat += ano;
     mat += semestre;
     mat += QString::number(++id);

     temp.setMat(mat);

    temp.setDesova(tempo);

    ninhos.push_back(temp);

    inserirNaTabela(temp);

    ui->quantNinhos->setText(QString::number(ninhos.size()));

    ContNinhos();
}

void MainWindow::inserirNaTabela(Ninho a)
{
    int linha = ui->Tabela->rowCount();

    ui->Tabela->insertRow(linha);
    ui->Tabela->setRowHeight(linha, 40);

    ui->Tabela->setItem(linha,0, new QTableWidgetItem(a.getMat()));
    ui->Tabela->setItem(linha,1, new QTableWidgetItem(a.getPraia()));
    ui->Tabela->setItem(linha,2, new QTableWidgetItem(a.getDesova().toString(Qt::RFC2822Date))); // qt::RFC2822Date converte a data no patrao printado na tabela
    ui->Tabela->setItem(linha,3, new QTableWidgetItem(a.getSinal()));
    ui->Tabela->setItem(linha,4, new QTableWidgetItem(a.nascimento()));

}


void MainWindow::on_Tabela_cellDoubleClicked(int row, int column)
{
    EditarDialog edit;
    edit.setObjeto(ninhos[row]);
    edit.setWindowTitle("Editar ninho");
    edit.setModal(true);
    edit.exec();

    column = 0;
    qDebug() << row;
    if(edit.getApagar()){ ninhos.erase(ninhos.begin()+row); atualizarTabela();
}
    if(edit.novo){
        ninhos[row]=edit.getObjeto();
        atualizarTabela();
    }
}

void MainWindow::atualizarTabela()
{
    ui->Tabela->setRowCount(0);

    for(auto show : ninhos){

        int linha = ui->Tabela->rowCount();

        ui->Tabela->insertRow(linha);
        ui->Tabela->setRowHeight(linha, 40);

        ui->Tabela->setItem(linha,0, new QTableWidgetItem(show.getMat()));
        ui->Tabela->setItem(linha,1, new QTableWidgetItem(show.getPraia()));
        ui->Tabela->setItem(linha,2, new QTableWidgetItem(show.getDesova().toString(Qt::RFC2822Date)));
        ui->Tabela->setItem(linha,3, new QTableWidgetItem(show.getSinal()));
        ui->Tabela->setItem(linha,4, new QTableWidgetItem(show.nascimento()));


    }
}

void MainWindow::ordenarPorPraia()
{
    std::sort(ninhos.begin(),ninhos.end(),[](Ninho a, Ninho b){
        return a.getPraia()<b.getPraia();
    });

}

void MainWindow::on_btn_2_clicked()
{
    ordenarPorPraia();
    atualizarTabela();

}

void MainWindow::on_actionSALVAR_triggered()
{
    QString arquivo;
    arquivo = QFileDialog::getSaveFileName(this,"Salvar Arquivo", "","*.csv");
    if(salvarDados(arquivo)){
        QMessageBox::information(this, "SALVAR ARQUIVO", "SALVO COM SUCESSO");
    }else{
        QMessageBox::critical(this, "ERRO","NÃO FOI POSSÍVEL SALVAR O ARQUIVO");
    }

}

bool MainWindow::salvarDados(QString arquivo)
{
    QFile file(arquivo + ".csv");
    file.open(QIODevice:: WriteOnly);

    if(file.isOpen()){
        for(auto elemento : ninhos){
            QString linha = elemento.getMat() + "," + elemento.getPraia() + "," + elemento.getDesova().toString() + "," + elemento.getSinal() + "\n";
            file.write(linha.toLocal8Bit());
        }
        file.close();
        return true;
    }else{
        return false;
    }
}

bool MainWindow::carregarDados(QString arquivo)
{
   QFile file(arquivo);
   if(file.isOpen()){
        return true;
   }else{
       file.open(QIODevice::ReadOnly);

       QString linha;
       QStringList dados;

       while(!file.atEnd()){
           Ninho temp;
           QDate temp1;

           linha = file.readLine();
           dados = linha.split(",");

           temp.setPraia(dados[0]);

           temp.setDesova(temp1.fromString(dados[1]));
           if(dados[2]== "FINALIZADO"){
               temp.setSinal(true);
           }else{
               temp.setSinal(false);
           }
       }
       file.close();
       return false;
   }
}

void MainWindow::on_actionCARREGAR_triggered()
{
    ninhos.erase(ninhos.begin(),ninhos.end());
    ui->Tabela->setRowCount(0);

    QString arquivo;

    arquivo = QFileDialog::getOpenFileName(this,"CARREGAR ARQUIVO","*csv");

    QFile file(arquivo);
        if(file.isOpen())
        {
            QMessageBox::critical(this,"Erro","Arquivo já carregado");

        }else{

            file.open(QIODevice::ReadOnly);

                    QString linha;
                    QStringList dados;

                    while(!file.atEnd()){
                        Ninho temp;
                        QDate temp1;

                        linha = file.readLine();
                        dados = linha.split(",");

                        temp.setMat(dados[0]);
                        temp.setPraia(dados[1]);
                        temp.setDesova(temp1.fromString(dados[2]));

                        if(dados[3] == "FINALIZADO") temp.setSinal(true);
                        else temp.setSinal(false);

                        ninhos.push_back(temp);
                    }
        }
            file.close();
            atualizarTabela();
}

void MainWindow::ContNinhos()
{
    QMap<QString, int> npp;

    for(auto n : ninhos){

        ++npp[n.getPraia()];
    }

    ui->txt_QuantNinhosBessa->setText(QString::number(npp["BESSA"]));
    ui->txt_QuantNinhosManaira->setText(QString::number(npp["MANAÍRA"]));
    ui->txt_QuantNinhosCaboBranco->setText(QString::number(npp["CABO BRANCO"]));
    ui->txt_QuantNinhosTambau->setText(QString::number(npp["TAMBAÚ"]));
    ui->txt_QuantNinhosSeixas->setText(QString::number(npp["SEIXAS"]));
    ui->txt_QuantNinhosPenha->setText(QString::number(npp["PENHA"]));

}

