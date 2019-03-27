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
    explicit PlateauScene(int size, std::string pool_name = "pool1", QWidget *parent = nullptr );
    
    void setBoxes(int x, int y, int sideLenght);
    //void setTrappistBoxes(int x, int y, int sideLenght);

    void showMoves(int *moves = nullptr, int* cap = nullptr);
    PlateauBox* getPriorityBox() const;
    void setPriorityBox(PlateauBox* box);
    void resetAllColors();

    void setBlackTrappist();
    void setWhiteTrappist();
    void addPiece(std::string pieceType,std::string suffix, int x, int y);

    //void setBlack();
    //void setWhite();
    
    void setHigh(std::string suffix);
    void setLow(std::string suffix);

    private:
    const int _size;
    PlateauBox* _priorityBox;
    std::string pool;

    QGraphicsScene *_scene;
    std::vector<std::vector<PlateauBox*>> _boxes;
    //PlateauBox *_boxes[8][8];
    //PlateauBox *_Tboxes[24][24];
    QGraphicsGridLayout *_ggbox;
    std::string get_pool() const;
};

#endif // PLATEAUSCENE_HPP
