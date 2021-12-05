#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName(QStringLiteral("Colored Map App"));
    QCoreApplication::setOrganizationName(QStringLiteral("QtQuickSoft"));

    MainWindow w;
    w.show();

    return a.exec();
}
