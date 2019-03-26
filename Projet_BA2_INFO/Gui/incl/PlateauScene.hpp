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
    explicit PlateauScene(int size, QWidget *parent = nullptr);
    
    void setClassicBoxes(int x, int y, int sideLenght);
    void setTrappistBoxes(int x, int y, int sideLenght);

    void showMoves(int *moves = nullptr, int* cap = nullptr);
    PlateauBox* getPriorityBox() const;
    void setPriorityBox(PlateauBox* box);
    void resetAllColors();

    void addPiece(std::string pieceType, int x, int y);

    void setBlack();
    void setWhite();


    private:
    const int _size;
    PlateauBox* _priorityBox;

    QGraphicsScene *_scene;
    PlateauBox *_boxes[8][8];
    PlateauBox *_Tboxes[24][24];
    QGraphicsGridLayout *_ggbox;
};

#endif // PLATEAUSCENE_HPP
