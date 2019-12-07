#include "ninho.h"


int Ninho::getDia() const
{
    return dia;
}

void Ninho::setDia(int value)
{
    dia = value;
}

int Ninho::getMes() const
{
    return mes;
}

void Ninho::setMes(int value)
{
    mes = value;
}

int Ninho::getAno() const
{
    return ano;
}

void Ninho::setAno(int value)
{
    ano = value;
}

QString Ninho::getMat() const
{
    return mat;
}

void Ninho::setMat(const QString &value)
{
    mat = value;
}

QString Ninho::getPraia() const
{
    return praia;
}

void Ninho::setPraia(const QString &value)
{
    praia = value;
}

QString Ninho::getSinal() const
{
    if(sinal) return "FINALIZADO";
    return "PENDENTE";
}

void Ninho::setSinal(bool value)
{
    sinal = value;
}

QDate Ninho::getDesova() const
{
    return desova;
}

void Ninho::setDesova(const QDate &value)
{
    desova = value;
}

QString Ninho::nascimento()
{
    QString minDias = desova.addDays(45).toString(Qt::RFC2822Date);
    QString maxDias = desova.addDays(60).toString(Qt::RFC2822Date);

    return "Data mínima: " + minDias + "\nData máxima: " + maxDias;
}

QDate Ninho::dateDesova()
{
    return desova;
}


Ninho::Ninho()
{
    dia = 0;
    mes = 0;
    ano = 0;
}
