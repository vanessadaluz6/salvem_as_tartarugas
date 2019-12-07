#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QDate>
#include <QDateEdit>
#include <algorithm>
#include "ninho.h"
#include "editardialog.h"
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_1_clicked();

    void inserirNaTabela(Ninho a);

    void on_Tabela_cellDoubleClicked(int row, int column);

    void atualizarTabela();

    void ordenarPorPraia();

    void on_btn_2_clicked();

    void on_actionSALVAR_triggered();

    bool salvarDados(QString arquivo);

    bool carregarDados(QString arquivo);

    void on_actionCARREGAR_triggered();

    void ContNinhos();

private:
    Ui::MainWindow *ui;
    QVector <Ninho> ninhos;
    int id;


};
#endif // MAINWINDOW_H
