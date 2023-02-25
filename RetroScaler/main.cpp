#include "RetroScaler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RetroScaler w;
    w.show();
    return a.exec();
}
