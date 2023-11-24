#include "resistencia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Resistencia w;
    w.show();

    return a.exec();
}
