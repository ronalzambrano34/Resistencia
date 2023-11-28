#include "resistencia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("WindowsVista");
    Resistencia w;
    w.show();

    return a.exec();
}
