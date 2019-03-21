#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.show();

    return app.exec();
}
