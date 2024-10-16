#include <QApplication>
#include "colorGame.h"

int main(int argc, char* argv[]){
    srand(static_cast<unsigned int>(time(nullptr)));//random state


    QApplication app(argc, argv);
    ColorGame* game = new ColorGame;
    game->show();

    return app.exec();
}
