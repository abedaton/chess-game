#ifndef PLATEAUSCENE_HPP
#define PLATEAUSCENE_HPP
#include "PlateauBox.hpp"
#include <QGraphicsGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <iostream>

class PlateauBox;
class PlateauScene : public QGraphicsView {
    public:
    explicit PlateauScene(int size = 8, QWidget *parent = nullptr);
    void setBoxes(int x, int y, int sideLenght);
    void showMoves(int *moves = nullptr, int* cap = nullptr);
    PlateauBox* getPriorityBox() const;
    void setPriorityBox(PlateauBox* box);
    void resetAllColors();

    void addPiece(std::string pieceType, int x, int y);

    private:
    const int _size;
    PlateauBox* _priorityBox;

    QGraphicsScene *_scene;
    PlateauBox *_boxes[8][8];
    QGraphicsGridLayout *_ggbox;
};

#endif // PLATEAUSCENE_HPP
