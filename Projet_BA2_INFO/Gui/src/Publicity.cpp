#ifndef PUBLICITY_CPP
#define PUBLICITY_CPP
#include "Publicity.hpp"
#include <stdio.h>


Publicity::Publicity(QWidget *parent) : QWidget(parent) 
{	
	init();
}

void Publicity::init()
{
	_timer = new QTimer(this); 
	_pub_label = new QLabel(this);
    // _pub_label->setPixmap(QPixmap("./Gui/advertisements/achraf_pub2.png"));
    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_pub_label);
    setLayout(_vBoxLayout);
	setPubToRandomImage();
	
	connect(_timer, SIGNAL(timeout()), this, SLOT(setPubToRandomImage()));
	//_timer->start(2*60*1000); 
	_timer->start(10*1000); 
}

void Publicity::setPubToRandomImage()
{
	QDir directory("./Gui/advertisements");
	QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
	if(images.length() > 0 )
	{
		size_t image_idx = rand()%images.length();
		QString image_path = "./Gui/advertisements/" + images.at(image_idx);
		QPixmap pub_image(image_path);
	   
	  
	    if (!pub_image.isNull()) 
	    {
	    	_pub_label->setPixmap(pub_image);
	    }
	}
}


#endif