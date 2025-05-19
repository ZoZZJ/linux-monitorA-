#include "control_interface.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    control_interface w;
    //w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);

    a.setWindowIcon(QIcon("qrc:/photos/icon1.png"));
    w.setWindowTitle("激光加工实时校正平台");

   // w.showFullScreen();
    w.show();
    return a.exec();
}
