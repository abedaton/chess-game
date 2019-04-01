#ifndef FENPRINCIPALE_CPP
#define FENPRINCIPALE_CPP

#include "FenPrincipale.hpp"
#include <thread>
#include <chrono>

// TODO link list d'amis
// TODO link chat
// TODO link le jeu
// TODO leaderboard
// TODO timer
// TODO fenetre d'attend matchmaking

FenPrincipale::FenPrincipale(AbstractClient* client) : _client(client) {
    _client->setInterface(this);
    
    _thread = new QThread;
    //moveToThread(_thread);

    
    init_window();
    init_stack();
    init_dock();
    init_menu();
    init_connect();


    setTheme("pool0");


    setCentralWidget(_stack);
    goToLogIn();
}

void FenPrincipale::init_window() {
    setWindowTitle("On Veut Pas D'Échec");
    setWindowIcon(QIcon("./Gui/img/logo_compl_v1.png"));
    // setStyleSheet("background-image:url(img/retro_space.png)");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    _statusBar = new QStatusBar(this);
    setStatusBar(_statusBar);
    MenuBar();
}

void FenPrincipale::init_stack() {
    _register = new Register(this);
    _login = new Login(this);
    _gameWindow = new GameWindow(this);
    _menu = new Menu(this);
    _stack = new QStackedWidget;
    _statWindow = new StatWindow(_client);
    _stack->addWidget(_login);
    _stack->addWidget(_register);
    _stack->addWidget(_menu);
    _stack->addWidget(_gameWindow);
    _stack->addWidget(_statWindow);
}

void FenPrincipale::init_connect() {
    qRegisterMetaType< QVector<int> >("QVector<int>");
    connect(_login->getSI(), SIGNAL(clicked()), this, SLOT(checkSignIn()));
    connect(_login, SIGNAL(enterPressed()), this, SLOT(checkSignIn()));
    connect(_login->getRegister(), SIGNAL(clicked()), this, SLOT(goToRegister()));

    connect(_register->getCancel(), SIGNAL(clicked()), this, SLOT(goToLogIn()));
    connect(_register, SIGNAL(escapePressed()), this, SLOT(goToLogIn()));
    connect(_register->getOK(), SIGNAL(clicked()), this, SLOT(checkRegister()));
    connect(_register, SIGNAL(enterPressed()), this, SLOT(checkRegister()));

    connect(_gameWindow->getClassicButton(), SIGNAL(clicked()), this, SLOT(goToMatchmaking()));
    connect(_gameWindow->getDarkButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    connect(_gameWindow->getTrapistButton(), SIGNAL(clicked()), this, SLOT(goToTrappist()));
    connect(_gameWindow->getAntiButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    connect(_gameWindow->getExitButton(), SIGNAL(clicked()), this,SLOT(goToMenu()));    

    connect(_menu->getNewGame(), SIGNAL(clicked()), this, SLOT(goToGame()));
    connect(_menu->getExit(), SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_menu->getStat(), SIGNAL(clicked()), this, SLOT(goToStat()));
    connect(_friendList->getPushButtonAddFriend(), SIGNAL(clicked()), this, SLOT(addFriend()));
    connect(_friendList->getPushButtonRemoveFriend(), SIGNAL(clicked()), this, SLOT(removeFriend()));
    connect(_friendList->getListWidgetFriendList(), SIGNAL(itemClicked(QListWidgetItem *)),this, SLOT(getFriendListItem(QListWidgetItem *)));
    connect(_friendList->getListWidgetFriendRequestList(), SIGNAL(itemClicked(QListWidgetItem *)),this, SLOT(getFriendRequestListItem(QListWidgetItem *)));
    connect(_chat->getLineEdit(), SIGNAL(returnPressed()), this, SLOT(sendMessage()));

    //connect(_statWindow,SIGNAL(enterPressed()), this, SLOT(fonctionjsp qui appelle StatWindow::getPlayerStats ))
    connect(_statWindow->getExitButton(), SIGNAL(clicked()), this, SLOT(goToMenu()));
    connect(_menuFriendList, SIGNAL(triggered(QAction *)), this, SLOT(getMenuFriendListAction(QAction *)));


}

void FenPrincipale::init_dock() {
    _chat = new Chat(this);
    _dockChat = new QDockWidget(this);
    _dockChat->setWidget(_chat);
    addDockWidget(Qt::RightDockWidgetArea, _dockChat);
    // _timer = new Timer(this);
    // _dockTimer = new QDockWidget(this);
    // _dockTimer->setWidget(_timer);
    // addDockWidget(Qt::LeftDockWidgetArea, _dockTimer);
    
    _friendList = new FriendList(this);
    _dockFriendList = new QDockWidget(this);
    _dockFriendList->setWidget(_friendList);
    addDockWidget(Qt::LeftDockWidgetArea, _dockFriendList);
    _dockFriendList->setFloating(true);
    _dockFriendList->setAllowedAreas(Qt::NoDockWidgetArea);
    
    _publicity = new Publicity(this);
    _dockPublicity = new QDockWidget(this);
    _dockPublicity->setWidget(_publicity);
    addDockWidget(Qt::BottomDockWidgetArea, _dockPublicity);
    _dockPublicity->setFloating(true);
    _dockPublicity->setAllowedAreas(Qt::NoDockWidgetArea);

    _dockChat->hide();
    //_dockTimer->hide();
    _dockFriendList->hide();
    _dockPublicity->hide();
}

void FenPrincipale::init_menu(){
    _menuFriendList = new QMenu(this);
    QAction *actionChat = new QAction("chat",this);
    connect(actionChat, SIGNAL(triggered()), this, SLOT(showChat()));
    QAction *actionRemove = new QAction("remove",this);
    connect(actionRemove, SIGNAL(triggered()), this, SLOT(removeFriend()));
    _menuFriendList->addAction(actionChat);
    _menuFriendList->addAction(actionRemove);
    _menuFriendRequestList = new QMenu(this);
    QAction *actionAccept = new QAction("accept",this);
    connect(actionAccept, SIGNAL(triggered()), this, SLOT(acceptFriend()));
    QAction *actionRefuse = new QAction("refuse",this);
    connect(actionRefuse, SIGNAL(triggered()), this, SLOT(refuseFriend()));
    _menuFriendRequestList->addAction(actionAccept);
    _menuFriendRequestList->addAction(actionRefuse);
}

void FenPrincipale::MenuBar() {
    _menuReglages = menuBar()->addMenu("&Réglages");
    QAction *actionLangues = new QAction("&Langues", this);
    _menuReglages->addAction(actionLangues);
    
}

void FenPrincipale::checkSignIn() {
    std::string nom = _login->getUsername().toStdString();
    std::string mdp = _login->getPassword().toStdString();

    /*result = client->login(username, password)
     * if (username dont exist in dataBase)
     * Qmessage:: username invalide please register
     *
     */

    if (_client->login(nom,mdp)) {
        goToMenu();
        //_statusBar->showMessage("Welcome " + nom + " !", 5000);

    } else {
        _statusBar->showMessage("Username or password is incorrect", 5000);
        QMessageBox::critical(this, "Incorrect SignIn", "Username and Password do not match");
    }
}

void FenPrincipale::checkRegister() {
    std::string* text = _register->getLinesEditText();
    std::regex regEmail("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\\])");
    if (_register->isTextEmpty()) {
        QMessageBox::critical(this, "Incorrect Register", "Missing elements");
        _statusBar->showMessage("Missing elements");
    } else if (!_register->isSamePassword()) {
        QMessageBox::critical(this, "Incorrect Register", "Passwords do not match");
        _statusBar->showMessage("Passwords do not match");
    } else if (! std::regex_match(text[1].begin(), text[1].end(), regEmail)){
        QMessageBox::critical(this, "Incorrect Register", "Incorrect E-Mail");
        _statusBar->showMessage("E-Mail not valid");
        
    } else {
        
        if(_client->letsRegister(text[0], text[2], text[3], text[1])){ //email = text[1]
            goToMenu();
            _statusBar->showMessage("Welcome new user !", 5000);
        }
    }
}

void FenPrincipale::goToRegister() {
    _stack->setCurrentWidget(_register);
}

void FenPrincipale::goToLogIn() {
    _stack->setCurrentWidget(_login);
}

void FenPrincipale::goToGame() {
    _stack->setCurrentWidget(_gameWindow);
}

void FenPrincipale::goToStat(){
    _stack->setCurrentWidget(_statWindow);
}

int FenPrincipale::getWichMatchmaking(std::string variante){
    int tmp;
    if(variante == "classic")
        tmp = 0;
    else if(variante == "dark")
        tmp = 1;
    else if(variante == "trapist")
        tmp = 2;
    else
        tmp = 3;
    

    return tmp + (4 * _gameWindow->getCurrentGameMode());

}
void FenPrincipale::updateMov(std::string text){
    
    std::vector<std::pair<int,int> > res;

    int mid = text.find(";");
    std::string coord1 = text.substr(0, mid);
    std::string coord2 = text.substr(mid+1, text.size());
    
    std::string tmp(coord1.begin()+1, coord1.end());
    res.push_back(std::make_pair<int,int>(static_cast<int>(coord1[0])-65, std::stoi(tmp)-1));
    std::string tmp2(coord2.begin()+1, coord2.end());
    res.push_back(std::make_pair<int,int>(static_cast<int>(coord2[0])-65, std::stoi(tmp2)-1));

    //TO DO
    _classicWindow->updateMov(res);

}

void FenPrincipale::cancelMatchmaking(){
    _client->exitQueue();
    
}

void FenPrincipale::goToMatchmaking() {
    _mdial = new MatchmakingDialog(this);
    connect(_mdial->getOkButton(),SIGNAL(clicked()), _mdial, SLOT(deleteDialog()));
    connect(_mdial->getCancelButton(),SIGNAL(clicked()), this, SLOT(cancelMatchmaking()));
    connect(_mdial->getCancelButton(),SIGNAL(clicked()), _mdial, SLOT(deleteDialog()));
    
    //connect(_mdial->getOkButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    int gamemode = getWichMatchmaking("classic");
    _client->waitForMatch(gamemode);
}

void FenPrincipale::goToClassic() {
    //std::string pool = "pool2" 
    _classicWindow = new PlateauScene("classic", _pool,this, this);
    //QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
    
    _stack->addWidget(_classicWindow);
    _stack->setCurrentWidget(_classicWindow);
    //int gamemode = getWichMatchmaking("classic");
    //std::cout << "GAMEMODE : " << gamemode << std::endl;
    //_client->waitForMatch(gamemode);
    // int tmp = this->_chessMod + (4 * (std::stoi(gameMod)-1));
    // while (gameMod != "1" && gameMod != "2" && gameMod != "3" && gameMod != "4"){
    //  std::cout << "Enter 1 for Tour Par tour, 2 for Chrono, 3 for Temps Reel, 4 for return to the menu: ";
}

void FenPrincipale::goToTrappist(){
    _classicWindow = new PlateauScene("trappist", _pool,this);
    
    
    
    _stack->addWidget(_classicWindow);
    _stack->setCurrentWidget(_classicWindow);

    // std::cout << "GAMEMODE : " << gamemode << std::endl;

    //_client->waitForMatch(gamemode);
}
void FenPrincipale::goToMenu() {
    setFriendMenu();
    setThemeMenu();
    _stack->setCurrentWidget(_menu);
}

void FenPrincipale::sendMessage() {
    if (!_chat->getLineEdit()->text().isEmpty()){
        _client->sendMessage(_chat->getFriendName().toStdString(), _chat->getLineEdit()->text().toStdString());
        _chat->getTextEdit()->insertPlainText(_chat->getLineEdit()->text()+"\n");
        _chat->getLineEdit()->clear();
        _chat->getLineEdit()->setFocus();
    }
}

void FenPrincipale::addFriend() {
    QString textFriend = _friendList->getLineEditFriend()->text();
    if (!textFriend.isEmpty()){
        std::cout<<"demande envoyer a : "<<textFriend.toStdString()<<std::endl;
        _client->addFriend(textFriend.toStdString());
        _friendList->getLineEditFriend()->clear();
    }
    _client->getFriendList();
    _client->getFriendRequests();
    // _friendList->getListWidgetFriendList()->addItems(QStringList("un nouvel ami"));
}

void FenPrincipale::acceptFriend(){
    std::cout<<"accept friend : "<<_friendList->getSelectFriend().toStdString()<<std::endl;
    _client->acceptFriend(_friendList->getSelectFriend().toStdString(), true);
    _client->getFriendList();
    _client->getFriendRequests();
}

void FenPrincipale::refuseFriend(){
    std::cout<<"refuse friend : "<<_friendList->getSelectFriend().toStdString()<<std::endl;
    _client->acceptFriend(_friendList->getSelectFriend().toStdString(), false);
    _client->getFriendList();
    _client->getFriendRequests();
}

void FenPrincipale::removeFriend() {
    std::cout<<"amis supprimer : "<<_friendList->getSelectFriend().toStdString()<<std::endl;
    _client->removeFriend(_friendList->getSelectFriend().toStdString());
    _client->getFriendList();
    _client->getFriendRequests();
}


void FenPrincipale::gameStart(std::string opponent){
	this->_ennemyName = opponent;
    _mdial->fondOpponent(_ennemyName);
    //_client->waitForMatch(1); TO DO
    //delete _mdial;
    this->moveToThread(_thread);
    connect(_thread, SIGNAL(started()), this, SLOT(goToClassic()));
    _thread->start();
   
    //goToStat();
}

void FenPrincipale::movPossibleUpdate(std::vector<std::pair<int,int> >* listMov){
    _classicWindow->showMoves(*listMov);
}

void FenPrincipale::showFriendList(){
    QApplication::processEvents();
    _client->getFriendList();
    _client->getFriendRequests();
    _dockFriendList->show();
}

void FenPrincipale::showChat(){
    _chat->setFriendName(_friendList->getSelectFriend());
    _dockChat->show();
}

void FenPrincipale::setTheme(std::string pool){
    _pool = pool;
}

void FenPrincipale::setFriendMenu(){
    _menuAmis = menuBar()->addMenu("&Ami(s)");
    QAction *actionAmis = new QAction("&Voir ses amis", this);
    _menuAmis->addAction(actionAmis);
    connect(actionAmis,&QAction::triggered,this,&FenPrincipale::showFriendList);
}

void FenPrincipale::setThemeMenu(){
    _menuThemes = menuBar()->addMenu("&Thème");
    QAction* pool0 = new QAction("&Classic",this);
    _menuThemes->addAction(pool0);
    connect(pool0,&QAction::triggered,this,&FenPrincipale::setPool0);
    
    QAction* pool1 = new QAction("&Trappist",this);
    _menuThemes->addAction(pool1);
    connect(pool1,&QAction::triggered,this,&FenPrincipale::setPool1);
    
    QAction* pool2 = new QAction("&Donald Trump :)",this);
    _menuThemes->addAction(pool2);
    connect(pool2,&QAction::triggered,this,&FenPrincipale::setPool2);
    
    QAction* pool3 = new QAction("&Is that us ???",this);
    _menuThemes->addAction(pool3);
    connect(pool3,&QAction::triggered,this,&FenPrincipale::setPool3);

    QAction* pool4 = new QAction("&Named Piece",this);
    _menuThemes->addAction(pool4);
    connect(pool4,&QAction::triggered,this,&FenPrincipale::setPool4);
}

void FenPrincipale::setPool0(){
    setTheme("pool0");
}
void FenPrincipale::setPool1(){
    setTheme("pool1");
}
void FenPrincipale::setPool2(){
    setTheme("pool2");
}
void FenPrincipale::setPool3(){
    setTheme("pool3");
}
void FenPrincipale::setPool4(){
    setTheme("pool4");
}

void FenPrincipale::getFriendListItem(QListWidgetItem *item){
    QCursor cursor;
    QPoint point = this->mapFromGlobal(cursor.pos());
    _friendList->setSelectFriend(item->text());
    _menuFriendList->exec(point);
}

void FenPrincipale::getFriendRequestListItem(QListWidgetItem *item){
    QCursor cursor;
    QPoint point = this->mapFromGlobal(cursor.pos());
    _friendList->setSelectFriend(item->text());
    _menuFriendRequestList->exec(point);
}

AbstractClient* FenPrincipale::getTest(){
    return this->_client;
}
void FenPrincipale::sendPosition(std::string pos){
    //quand on lance le jeu
    // A6
    // if(this->getTest()){
    //     std::cout << "WSH" << std::endl;
    // } else {
    //     std::cout << "CLIENT IS NULLPTR" << std::endl;
    // }
        _client->click(pos);
}

void FenPrincipale::getMenuFriendListAction(QAction *action){
    Q_UNUSED(action);

    _dockChat->show();
}

void FenPrincipale::recvFriendList(std::vector<std::pair<std::string,bool> > friendList){
    _friendList->setFriendList(friendList);
}

void FenPrincipale::recvFriendRequestsList(std::vector<std::string> friendRequestsList){
    _friendList->setFriendRequestsList(friendRequestsList);
}

void FenPrincipale::recvInfo(std::string username, int nbrgames, int win, int elo)
{
    std::cout << "recFInfo was called " << std::endl;
}

void FenPrincipale::feedback(int info, std::string message)
{
    std::cout << "FenPrincipale::feedback: " << info << "  "<< message << std::endl;
    //if(message == "")
}

void FenPrincipale::recvMessage(std::string name, std::string message){
    this->moveToThread(_thread);
    std::cout << message << std::endl;
    _chat->setFriendName(QString::fromStdString(name));
    _chat->getTextEdit()->insertPlainText(QString::fromStdString(message+"\n"));
    _dockChat->show();
}
#endif
