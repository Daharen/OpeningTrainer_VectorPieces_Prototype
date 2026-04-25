#include "PreviewWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    otpvp::PreviewWindow window;
    window.show();

    return app.exec();
}
