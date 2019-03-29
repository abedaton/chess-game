#ifndef PLATEAUSCENE_HPP
#define PLATEAUSCENE_HPP
#include "PlateauBox.hpp"
#include "FenPrincipale.hpp"
#include <QGraphicsGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <iostream>

class PlateauBox;
class FenPrincipale;

class PlateauScene : public QGraphicsView {
    public:
    explicit PlateauScene(std::string game_type , std::string pool_name = "pool1", FenPrincipale* mainWindow = nullptr ,QWidget *parent = nullptr );
    
    void setBoxes(int x, int y, int sideLenght);
    //void setTrappistBoxes(int x, int y, int sideLenght);

    void showMoves(int *moves = nullptr, int* cap = nullptr);
    void showMoves(std::vector<std::pair<int,int> > deplacement);
    PlateauBox* getPriorityBox() const;
    void setPriorityBox(PlateauBox* box);
    void resetAllColors();

    void addPiece(std::string pieceType,std::string suffix, int x, int y);

    //void setBlack();
    //void setWhite();
    
    void setHigh(std::string suffix);
    void setLow(std::string suffix);
    void setHighTrappist(std::string suffix);
    void setLowTrappist(std::string suffix);

    void setFog(std::vector<std::vector<int> >* fog);

    //AbstractClient* getClient() const;
    void sendPosition(std::string pos);

    private:
    int _size;
    PlateauBox* _priorityBox;
    FenPrincipale* _mainWindow;
    std::string _game_type;
    std::string _pool;

    QGraphicsScene *_scene;
    std::vector<std::vector<PlateauBox*>> _boxes;
    //PlateauBox *_boxes[8][8];
    //PlateauBox *_Tboxes[24][24];
    QGraphicsGridLayout *_ggbox;
    std::string get_pool() const;
    std::string get_game_type() const;
    void set_size(int taille);
};

#endif // PLATEAUSCENE_HPP
