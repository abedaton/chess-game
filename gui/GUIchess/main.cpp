#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameWindow fenetre;
    fenetre.show();

    return app.exec();
}
