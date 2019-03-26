#include "PlateauScene.hpp"

PlateauScene::PlateauScene(int size, QWidget *parent,std::string pool_name) : _size(size), pool(pool_name) , QGraphicsView(parent) {
    _scene = new QGraphicsScene;
    _ggbox = new QGraphicsGridLayout;
    //_boxes = new PlateauBox[_size][_size];
    _scene->setSceneRect(0, 0, 700, 700);

    setScene(_scene);

    setClassicBoxes(0, 100, 65);
    int moves[] = {1, 2, 3, 4};

    //showMoves(moves);
}

void PlateauScene::setClassicBoxes(int x, int y, int sideLenght) {
    int curr_x, curr_y = y;

    for (int i = 0; i < _size; ++i) {
        curr_x = x;
        for (int j = 0; j < _size; ++j) {
            PlateauBox *box = new PlateauBox(curr_x, curr_y, sideLenght);
            curr_x += sideLenght;

            if ((i + j) % 2 == 0)
                box->setFirstColor(Qt::white);
            else
                box->setFirstColor(Qt::darkGray);
            box->setPosition(i, j);
            box->_scene = this;
            _boxes[i][j] = box;
            _scene->addItem(box);
        }
        curr_y += sideLenght;
    }

    //addPiece("pionB", 4,5);
    //addPiece("pionW", 6,6);
    setBlack();
    setWhite();

}

void PlateauScene::showMoves(int *moves, int *cap) {
    int x, y;
    for (int i = 0; i < 3; ++i) {
        x = moves[i];
        y = moves[i];

        _boxes[x][y]->setColor(Qt::red);
    }

    _boxes[cap[0]][cap[0]]->setColor(Qt::green);
}

PlateauBox* PlateauScene::getPriorityBox() const{
    return _priorityBox;
}

void PlateauScene::setPriorityBox(PlateauBox* box){
    _priorityBox = box;
}

void PlateauScene::resetAllColors(){
    for(int i = 0 ;i<_size;++i){
        for(int j = 0 ;j<_size;++j){
            _boxes[i][j]->resetColor();
        }
    }
}

void PlateauScene::addPiece(std::string pieceType,int x, int y){
    ChessItem* pion = new ChessItem(pieceType,this->get_pool()); // de base "pool1" // plustard nouveau parametre color!
    _boxes[x][y]->setPiece(pion);
    _scene->addItem(pion);
}

void PlateauScene::setBlack(){
    //Fou
    addPiece("fouB",0,2);
    addPiece("fouB",0,5);
    //Chevalier
    addPiece("chevB",0,1);
    addPiece("chevB",0,6);
    //Tour
    addPiece("tourB",0,0);
    addPiece("tourB",0,7);
    //Roi et reine
    addPiece("roiB",0,3);
    addPiece("reineB",0,4);

    for(int i = 0; i<8; ++i)
        addPiece("pionB",1,i);

}

void PlateauScene::setWhite(){
    //Fou
    addPiece("fouW",7,2);
    addPiece("fouW",7,5);
    //Chevalier
    addPiece("chevW",7,1);
    addPiece("chevW",7,6);
    //Tour
    addPiece("tourW",7,0);
    addPiece("tourW",7,7);
    //Roi et reine
    addPiece("roiW",7,3);
    addPiece("reineW",7,4);

    for(int i = 0; i<8; ++i)
        addPiece("pionW",6,i);

}

std::string get_pool() const {return this->pool;}
