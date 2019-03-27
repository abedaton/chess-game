#include "PlateauScene.hpp"

PlateauScene::PlateauScene(int size, std::string pool_name, QWidget *parent) : _size(size), pool(pool_name) , QGraphicsView(parent) {
    _scene = new QGraphicsScene;
    _ggbox = new QGraphicsGridLayout;
    //_boxes = new PlateauBox[_size][_size];
    _scene->setSceneRect(0, 0, 700, 700);

    setScene(_scene);

    
    setBoxes(0, 100, 520/_size);
    //setTrappistBoxes(0, 100, 17);
    
    int moves[] = {1, 2, 3, 4};

    //showMoves(moves);
}

void PlateauScene::setBoxes(int x, int y, int sideLenght) {
    int curr_x, curr_y = y;
    _boxes.resize(_size);
    for (int i = 0; i < _size; ++i) {
        _boxes[i].resize(_size);
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

    
    //setBlack();
    //setWhite();
    setHigh("W");
    setLow("B");

}


// void PlateauScene::setTrappistBoxes(int x, int y, int sideLenght) {
//     int curr_x, curr_y = y;

//     for (int i = 0; i < _size; ++i) {
//         curr_x = x;
//         for (int j = 0; j < _size; ++j) {
//             PlateauBox *box = new PlateauBox(curr_x, curr_y, sideLenght);
//             curr_x += sideLenght;

//             if ((i + j) % 2 == 0)
//                 box->setFirstColor(Qt::white);
//             else
//                 box->setFirstColor(Qt::darkGray);
//             box->setPosition(i, j);
//             box->_scene = this;
//             _Tboxes[i][j] = box;
//             _scene->addItem(box);
//         }
//         curr_y += sideLenght;
//     }

    
//     //setBlack();
//     //setWhite();

// }

void PlateauScene::showMoves(int *moves, int *cap) {
    int x, y;
    for (int i = 0; i < sizeof(moves)/sizeof(moves[0]); ++i) {
        x = moves[i]/_size;
        y = moves[i]%_size;

        _boxes[x][y]->setColor(Qt::red);
    }
    
    for (int i = 0; i < sizeof(cap)/sizeof(cap[0]); ++i) {
        x = cap[i]/_size;
        y = cap[i]%_size;

        _boxes[x][y]->setColor(Qt::green);
    }
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


void PlateauScene::addPiece(std::string pieceType,std::string suffix,int x, int y){
    ChessItem* pion = new ChessItem(pieceType,this->get_pool(),suffix, 520/_size); // de base "pool1" // plustard nouveau parametre color!
    _boxes[x][y]->setPiece(pion);
    _scene->addItem(pion);
}
void PlateauScene::setLow(std::string suffix){
    //Fou
    addPiece("fou",suffix,0,2);
    addPiece("fou",suffix,0,5);
    //Chevalier
    addPiece("chev",suffix,0,1);
    addPiece("chev",suffix,0,6);
    //Tour
    addPiece("tour",suffix,0,0);
    addPiece("tour",suffix,0,7);
    //Roi et reine
    addPiece("roi",suffix,0,3);
    addPiece("reine",suffix,0,4);

    for(int i = 0; i<_size; ++i)
        addPiece("pion",suffix,1,i);

}

void PlateauScene::setHigh(std::string suffix){
    //Fou
    addPiece("fou",suffix,7,2);
    addPiece("fou",suffix,7,5);
    //Chevalier
    addPiece("chev",suffix,7,1);
    addPiece("chev",suffix,7,6);
    //Tour
    addPiece("tour",suffix,7,0);
    addPiece("tour",suffix,7,7);
    //Roi et reine
    addPiece("roi",suffix,7,3);
    addPiece("reine",suffix,7,4);

    for(int i = 0; i<_size; ++i)
        addPiece("pion",suffix,6,i);
}

void PlateauScene::setBlackTrappist(){
    // TO DO
}

void PlateauScene::setWhiteTrappist(){
    // TO DO
}
std::string PlateauScene::get_pool() const {return this->pool;}
