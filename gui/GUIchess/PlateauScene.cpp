#include "PlateauScene.h"

PlateauScene::PlateauScene(int size, QWidget* parent) : _size(size), QGraphicsView(parent){
    _scene = new QGraphicsScene;
    _ggbox = new QGraphicsGridLayout;
    _scene->setSceneRect(0,0,700,700);

    //setFixedSize(700,700);
    setScene(_scene);
    setBoxes();

}

void PlateauScene::setBoxes(int x, int y){
    PlateauBox* box = new PlateauBox(x,y,65);
    box->setFirstColor(Qt::white);
    //QGraphicsLayoutItem* item = box;
    _scene->addItem(box);
    //_ggbox->addItem(item,2,2);

}
