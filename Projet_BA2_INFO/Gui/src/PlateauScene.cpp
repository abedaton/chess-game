#ifndef PLATEAUSCENE_CPP
#define PLATEAUSCENE_CPP
#include "PlateauScene.hpp"

PlateauScene::PlateauScene(std::string game_type , std::string pool_name, FenPrincipale *mainWindow, QWidget *parent) : QGraphicsView(parent), _size(0), _game_type(game_type) , _pool(pool_name), _mainWindow(mainWindow){
    
    if (this->get_game_type() == "classic" or this->get_game_type() == "anti" or this->get_game_type() == "dark"){
		this->set_size(8);
        if(_game_type == "dark"){

        }
	}
	else if (this->get_game_type() == "trappist") {
		this->set_size(24);
	}
	else{throw std::invalid_argument("mode de jeu inconnu");}
    
    _scene = new QGraphicsScene;
    _ggbox = new QGraphicsGridLayout;
    //_boxes = new PlateauBox[_size][_size];
    _scene->setSceneRect(0, 0, 700, 700);

    setScene(_scene);

    
    setBoxes(0, 100, 520/_size);
    //setTrappistBoxes(0, 100, 17);
    
    //int moves[] = {1, 2, 3, 4}; ------------------------------------------------- !!! enleve le warning

    //showMoves(moves);
}

void PlateauScene::make_box_line(int begin_x,int y_pos, int sideLenght,int i){
	
	int curr_x = begin_x;
	for (int j = 0; j < this->_size; ++j) {
		PlateauBox *box = new PlateauBox(curr_x, y_pos, sideLenght);
		curr_x += sideLenght;

		if ((i + j) % 2 == 0)
			box->setFirstColor(Qt::white);
		else
			box->setFirstColor(Qt::darkGray);
		
		box->setPosition(i, j);
		box->_scene = this;
		
		_boxes[i][j] = box;
		_scene->addItem(box);
		
		// setPosText(-50,125, "wsh");
		// setPosText(-50,125+sideLenght, "wsh");
		// setPosText(sideLenght/2 - 13 ,50, "wsh");
		// setPosText(sideLenght/2 - 13 + sideLenght ,50, "wsh");
		
	}
}

void PlateauScene::make_char_lines(int curr_x,int y_pos,int sideLenght){
	
	for (int i = 0; i < this->_size; ++i) {
		char chr = 65 + i;//wsh
        std::string str(1,chr);
        setPosText(curr_x,y_pos, str);
        
        curr_x += sideLenght;
	}
}

void PlateauScene::setPieces(){
	
	//setBlack();
    //setWhite();
    if (this->get_game_type() == "classic" or this->get_game_type() == "anti" or this->get_game_type() == "dark"){
		setHigh("W");
		setLow("B");
        //addPiece("fog","", 7,1);
        //addFog(7,1);
        //removeFog(7,1);
	}
	else if (this->get_game_type() == "trappist") {
		setHighTrappist("W");
		setLowTrappist("B");
	}
	else{throw std::invalid_argument("mode de jeu inconnu");}

}

void PlateauScene::setBoxes(int x, int y, int sideLenght) {
    int curr_x = x, curr_y = y;

    int char_height = 10;
    int char_widht = 10;
    
    int char_hor_spacing = (sideLenght/2 - char_widht/2);
    int char_ver_spacing = (sideLenght/2 - char_height/2);
    
    int plat_size = sideLenght*this->_size;
    
    _boxes.resize(_size);
    
    this->make_char_lines((curr_x+char_hor_spacing),y - sideLenght,sideLenght); // !!! bizzarie y-char_ver_spacing ne suffit pas (y bizarre) // - char_ver_spacing
    
    std::string str;
    for (int i = 0; i < this->_size; ++i) {
        _boxes[i].resize(this->_size);

        str = std::to_string(this->_size-i);
        setPosText(curr_x-sideLenght, curr_y+char_ver_spacing, str); //curr_x-char_hor_spacing ne suffit pas ???
        
		this->make_box_line(curr_x,curr_y,sideLenght,i);
		
		setPosText(curr_x + plat_size + char_hor_spacing,curr_y+char_ver_spacing, str);
		
        curr_y += sideLenght;
    }
	
	this->make_char_lines((curr_x+char_hor_spacing),(y + plat_size + char_ver_spacing),sideLenght);
    
    this->setPieces();
}

void PlateauScene::setPosText(int x, int y, std::string pos){
    QGraphicsTextItem * coor = new QGraphicsTextItem(QString::fromStdString(pos));
    coor->setPos(x,y);
    //coor->setPlainText(QString::fromStdString(pos));

    _scene->addItem(coor);
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

void PlateauScene::showMoves(std::vector<std::pair<int,int> > deplacement){
    int x, y;
    const int size = deplacement.size();
    for(int i = 0; i < size ; ++i){
        x = std::get<0>(deplacement[i]);
        y = std::get<1>(deplacement[i]);
        
        if(_boxes[x][y]->getPiece() == nullptr)
            _boxes[x][y]->setColor(Qt::green);
        else 
            _boxes[x][y]->setColor(Qt::red);
    }
}

void PlateauScene::showMoves(int *moves, int *cap) {
    
    int x, y;
    for (unsigned i = 0; i < sizeof(moves)/sizeof(moves[0]); ++i) {
        x = moves[i]/_size;
        y = moves[i]%_size;

        _boxes[x][y]->setColor(Qt::red);
    }
    
    for (unsigned i = 0; i < sizeof(cap)/sizeof(cap[0]); ++i) {
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

void PlateauScene::addFog(int x, int y){
    ChessItem* fog = new ChessItem("fog",this->get_pool(),"", 520/_size); // de base "pool1" // plustard nouveau parametre color!
    _boxes[x][y]->setFog(fog);
    _scene->addItem(fog);

    if(_boxes[x][y]->getPiece() != nullptr)
        _scene->removeItem(_boxes[x][y]->getPiece());
}

void PlateauScene::removeFog(int x, int y){
    _boxes[x][y]->removeFog();
    if(_boxes[x][y]->getPiece() != nullptr)
        _scene->addItem(_boxes[x][y]->getPiece());
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

void PlateauScene::setHighTrappist(std::string suffix){
	
	//ligne 24
	addPiece("pion",suffix,23,1);
    addPiece("fauc",suffix,23,3);
    addPiece("pion",suffix,23,5);
    addPiece("pion",suffix,23,18);
    addPiece("fauc",suffix,23,20);
    addPiece("pion",suffix,23,22);
    
    //ligne 23
	addPiece("pion",suffix,22,2);
    addPiece("pion",suffix,22,4);
    addPiece("pion",suffix,22,19);
    addPiece("pion",suffix,22,21);
    
    //ligne 22
    addPiece("pion",suffix,21,3);
    addPiece("pion",suffix,21,20);
    
    //ligne 17
	addPiece("pion",suffix,16,4);
	addPiece("fonc",suffix,16,5);
	addPiece("chev",suffix,16,10);
	addPiece("fou",suffix,16,11);
	addPiece("fou",suffix,16,12);
	addPiece("chev",suffix,16,13);
	addPiece("fonc",suffix,16,18);
	addPiece("pion",suffix,16,19);
	
	// ligne 16
	addPiece("pion",suffix,15,5);
	addPiece("tour",suffix,15,6);
	addPiece("chan",suffix,15,7);
	addPiece("gard",suffix,15,8);
	addPiece("chev",suffix,15,9);
	addPiece("fou",suffix,15,10);
	addPiece("reine",suffix,15,11);
	addPiece("roi",suffix,15,12);
	addPiece("fou",suffix,15,13);
	addPiece("chev",suffix,15,14);
	addPiece("gard",suffix,15,15);
	addPiece("chan",suffix,15,16);
	addPiece("tour",suffix,15,17);
	addPiece("pion",suffix,15,18);
	
	// ligne 15
	addPiece("pion",suffix,14,6);
	addPiece("pion",suffix,14,7);
	addPiece("pion",suffix,14,8);
	addPiece("pion",suffix,14,9);
	addPiece("pion",suffix,14,10);
	addPiece("pion",suffix,14,11);
	addPiece("pion",suffix,14,12);
	addPiece("pion",suffix,14,13);
	addPiece("pion",suffix,14,14);
	addPiece("pion",suffix,14,15);
	addPiece("pion",suffix,14,16);
	addPiece("pion",suffix,14,17);
	
}

void PlateauScene::setLowTrappist(std::string suffix){
	
	// ligne 10
	addPiece("pion",suffix,9,6);
	addPiece("pion",suffix,9,7);
	addPiece("pion",suffix,9,8);
	addPiece("pion",suffix,9,9);
	addPiece("pion",suffix,9,10);
	addPiece("pion",suffix,9,11);
	addPiece("pion",suffix,9,12);
	addPiece("pion",suffix,9,13);
	addPiece("pion",suffix,9,14);
	addPiece("pion",suffix,9,15);
	addPiece("pion",suffix,9,16);
	addPiece("pion",suffix,9,17);
	
	// ligne 9
	addPiece("pion",suffix,8,5);
	addPiece("tour",suffix,8,6);
	addPiece("chan",suffix,8,7);
	addPiece("gard",suffix,8,8);
	addPiece("chev",suffix,8,9);
	addPiece("fou",suffix,8,10);
	addPiece("reine",suffix,8,11);
    
	addPiece("roi",suffix,8,12);
	addPiece("fou",suffix,8,13);
	addPiece("chev",suffix,8,14);
    
	addPiece("gard",suffix,8,15);
    
	addPiece("chan",suffix,8,16);
    
	addPiece("tour",suffix,8,17);
	addPiece("pion",suffix,8,18);
    
    //ligne 8
	addPiece("pion",suffix,7,4);
	addPiece("fonc",suffix,7,5);
	addPiece("chev",suffix,7,10);
	addPiece("fou",suffix,7,11);
	addPiece("fou",suffix,7,12);
	addPiece("chev",suffix,7,13);
	addPiece("fonc",suffix,7,18);
	addPiece("pion",suffix,7,19);
    
    //ligne 3
    addPiece("pion",suffix,2,3);
    addPiece("pion",suffix,2,20);
    
  
    
    //ligne 1
    addPiece("pion",suffix,0,1);
    addPiece("fauc",suffix,0,3);
    addPiece("pion",suffix,0,5);
    addPiece("pion",suffix,0,18);
    addPiece("fauc",suffix,0,20);
    addPiece("pion",suffix,0,22);
   
}


void PlateauScene::setFog(std::vector<std::vector<int> > *fog){

    for(int i = 0 ; i < 8 ; ++i){
        for(int j = 0; j < 8 ; ++j){
            if(fog->at(i).at(j) == 1)
                addFog(i,j);
            else
                removeFog(i,j);  
        }
    }
}


void PlateauScene::sendPosition(std::string pos){
    _mainWindow->sendPosition(pos);
}

std::string PlateauScene::get_pool() const {return this->_pool;}
std::string PlateauScene::get_game_type() const {return this->_game_type;}
void PlateauScene::set_size(int taille){this->_size = taille;}
#endif
