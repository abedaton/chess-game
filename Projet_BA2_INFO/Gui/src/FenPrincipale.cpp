#include "FenPrincipale.hpp"

// TODO link list d'amis
// TODO link chat
// TODO link le jeu
// TODO dark chess brouillard
// TODO leaderboard
// TODO timer
// TODO fenetre d'attend matchmaking

FenPrincipale::FenPrincipale(AbstractClient* client) : _client(client) {
    init_window();
    init_stack();
    init_dock();
    init_connect();

    setTheme("pool0");

    setCentralWidget(_stack);
    goToLogIn();
}

void FenPrincipale::init_window() {
    setWindowTitle("On Veut Pas D'Échec");
    setWindowIcon(QIcon("./Gui/img/logo_compl_v1.png"));
    // setStyleSheet("background-image:url(img/retro_space.png)");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
    _statusBar = new QStatusBar(this);
    setStatusBar(_statusBar);
    MenuBar();
}

void FenPrincipale::init_stack() {
    _register = new Register(this);
    _login = new Login(this);
    _gameWindow = new GameWindow(this);
    _menu = new Menu(this);
    _stack = new QStackedWidget(this);
    _statWindow = new StatWindow(this);
    _stack->addWidget(_login);
    _stack->addWidget(_register);
    _stack->addWidget(_menu);
    _stack->addWidget(_gameWindow);
    _stack->addWidget(_statWindow);
}

void FenPrincipale::init_connect() {
    connect(_login->getSI(), SIGNAL(clicked()), this, SLOT(checkSignIn()));
    connect(_login, SIGNAL(enterPressed()), this, SLOT(checkSignIn()));
    connect(_login->getRegister(), SIGNAL(clicked()), this, SLOT(goToRegister()));

    connect(_register->getCancel(), SIGNAL(clicked()), this, SLOT(goToLogIn()));
    connect(_register, SIGNAL(escapePressed()), this, SLOT(goToLogIn()));
    connect(_register->getOK(), SIGNAL(clicked()), this, SLOT(checkRegister()));
    connect(_register, SIGNAL(enterPressed()), this, SLOT(checkRegister()));

    connect(_gameWindow->getClassicButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    connect(_gameWindow->getDarkButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    connect(_gameWindow->getTrapistButton(), SIGNAL(clicked()), this, SLOT(goToTrappist()));
    connect(_gameWindow->getAntiButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
    
    connect(_menu->getNewGame(), SIGNAL(clicked()), this, SLOT(goToGame()));
    connect(_menu->getExit(), SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(_menu->getStat(), SIGNAL(clicked()), this, SLOT(goToStat()));
    connect(_friendList->getPushButtonAddFriend(), SIGNAL(clicked()), this, SLOT(addFriend()));
    connect(_friendList->getPushButtonRemoveFriend(), SIGNAL(clicked()), this, SLOT(removeFriend()));
    connect(_friendList->getListWidgetFriendList(), SIGNAL(itemClicked(QListWidgetItem *)),this, SLOT(showFriend(QListWidgetItem *)));

    //connect(_statWindow,SIGNAL(enterPressed()), this, SLOT(fonctionjsp qui appelle StatWindow::getPlayerStats ))


}

void FenPrincipale::init_dock() {
    _chat = new Chat(this);
    _dockChat = new QDockWidget(this);
    _dockChat->setWidget(_chat);
    addDockWidget(Qt::RightDockWidgetArea, _dockChat);

    _timer = new Timer(this);
    _dockTimer = new QDockWidget(this);
    _dockTimer->setWidget(_timer);
    addDockWidget(Qt::LeftDockWidgetArea, _dockTimer);
    
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
    _dockTimer->hide();
    _dockFriendList->hide();
    _dockPublicity->hide();
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
    if (_register->isTextEmpty()) {
        QMessageBox::critical(this, "Incorrect Register", "Missing elements");
        _statusBar->showMessage("Missing elements");
    } else if (!_register->isSamePassword()) {
        QMessageBox::critical(this, "Incorrect Register", "Passwords do not match");
        _statusBar->showMessage("Passwords do not match");
    } else {
        std::string* text = _register->getLinesEditText();
        if(_client->letsRegister(text[0], text[2], text[3], text[1])){
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

void FenPrincipale::goToClassic() {
    //std::string pool = "pool2";
 
    _classicWindow = new PlateauScene("classic", _pool);
    
    _stack->addWidget(_classicWindow);
    _stack->setCurrentWidget(_classicWindow);
    //_client->waitForMatch(1);
    
}

void FenPrincipale::goToTrappist(){
    _classicWindow = new PlateauScene("trappist", _pool);
    _stack->addWidget(_classicWindow);
    _stack->setCurrentWidget(_classicWindow);
}

void FenPrincipale::goToMenu() {
    setFriendMenu();
    setThemeMenu();
    _stack->setCurrentWidget(_menu);
}

void FenPrincipale::sendMessage() {
    _chat->getTextEdit()->insertPlainText(_chat->getLineEdit()->text());
}

void FenPrincipale::addFriend() {
    _friendList->getListWidgetFriendList()->addItems(QStringList("un nouvel ami"));
}

void FenPrincipale::removeFriend() {

}

/*
void FenPrincipale::gameStart(std::string opponent){
    //_client->waitForMatch(1); TO DO
    goToClassic();
}
*/
void FenPrincipale::showFriendList(){
    _dockFriendList->show();
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

void FenPrincipale::showFriend(QListWidgetItem *item){
    QCursor cursor;
    QPoint point = this->mapFromGlobal(cursor.pos());
    QMenu menu;
    menu.addAction("Chat");
    menu.addAction("profile");
    menu.addAction("Chat");
    menu.addAction("Chat");
    menu.addAction("Chat");
    menu.exec(point);
}