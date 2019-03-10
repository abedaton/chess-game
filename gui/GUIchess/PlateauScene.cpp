#include "PlateauScene.h"

PlateauScene::PlateauScene(int size, QWidget* parent) : _size(size), QGraphicsView(parent){
    _scene = new QGraphicsScene;
    _ggbox = new QGraphicsGridLayout;
    //_boxes = new PlateauBox[_size][_size];
    _scene->setSceneRect(0,0,700,700);

    setScene(_scene);

    setBoxes(0,100,65);
}

void PlateauScene::setBoxes(int x, int y, int sideLenght){
    int curr_x,curr_y = y;

    for(int i = 0; i< _size ; ++i){
        curr_x = x;
        for(int j = 0; j < _size ; ++j){
            PlateauBox* box = new PlateauBox(curr_x,curr_y,sideLenght);
            curr_x+=sideLenght;

            if((i+j)%2 == 0)
                box->setFirstColor(Qt::white);
            else
                box->setFirstColor(Qt::black);

            _boxes[i][j] = box;
            _scene->addItem(box);
        }
        curr_y += sideLenght;
    }

}
