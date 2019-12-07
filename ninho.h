#ifndef NINHO_H
#define NINHO_H

#include <QString>
#include <QDate>
#

class Ninho
{
private:

    int dia;
    int mes;
    int ano;
    QString mat;
    QString praia;
    bool sinal;
    QDate desova;


public:


    Ninho();

    int getDia() const;
    void setDia(int value);

    int getMes() const;
    void setMes(int value);

    int getAno() const;
    void setAno(int value);

    QString getMat() const;
    void setMat(const QString &value);

    QString getPraia() const;
    void setPraia(const QString &value);

    QString getSinal() const;
    void setSinal(bool value);

    QDate getDesova() const;
    void setDesova(const QDate &value);

    QString nascimento();

    QDate dateDesova();

  };

#endif // NINHO_H
