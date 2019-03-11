#ifndef PLATEAUSCENE_H
#define PLATEAUSCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include "PlateauBox.h"
#include <iostream>
#include <QList>

class PlateauScene : public QGraphicsView {
public:
    explicit PlateauScene(int size = 8, QWidget* parent = nullptr);
    void setBoxes(int x, int y, int sideLenght);
    void showMoves(int *moves = nullptr);
private:
    const int _size;

    QGraphicsScene* _scene;
    PlateauBox* _boxes[8][8];
    QGraphicsGridLayout* _ggbox;

};

#endif // PLATEAUSCENE_H
