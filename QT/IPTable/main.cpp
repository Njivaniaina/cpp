#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QFile file("../IPTable/style.css");
//    file.open(QFile::ReadOnly);
//    QString style = QLatin1String(file.readAll());
//    a.setStyleSheet(style);

    w.show();
    return a.exec();
}
