#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QList>

void writeCSV(QList<QStringList>& data)
{
    QFile file("zmienione_analiza_skasowań_kart.csv");
    QTextStream textStream(&file);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    for (int i = 0; i < data.size(); ++i){
        textStream << data.at(i).join(";") << endl;
    }

    file.close();
}

void readList(QList<QStringList>&data)
{
    QFile file("od28wrzesniado05pazdziern2021.csv");
    QTextStream textStream(&file);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    while(textStream.atEnd() == false){
        QString line = textStream.readLine();
        QStringList oldLine = line.split(";");

        if(!oldLine.at(10).startsWith("Pasażerska punktowa")){
            continue;
        }
        QStringList newLine;
        QString hour= oldLine.at(6);

        newLine.append(oldLine.at(0));
        newLine.append(oldLine.at(1));
        newLine.append(hour.mid(hour.indexOf("(")+1,5));
        newLine.append(oldLine.at(4));
        newLine.append(oldLine.at(3));
        newLine.append(oldLine.at(2));
        newLine.append(oldLine.at(7));
        newLine.append(oldLine.at(8));

        data.append(newLine);
    }
    writeCSV(data);
    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QStringList> daneList;
    readList(daneList);
    return a.exec();
}
