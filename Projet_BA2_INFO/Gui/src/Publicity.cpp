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
	setPubToRandomImage();
	
	connect(_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	//_timer->start(2*60*1000); 
	_timer->start(30*1000); 
}

void Publicity::setPubToRandomImage()
{
	QDir directory("advertisements");
	QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
	if(images.length() > 0 )
	{
		size_t image_idx = rand()%images.length();
		QString image_path = "advertisements/" + images.at(image_idx);
		QPixmap pub_image(image_path);
	   
	  
	    if (!pub_image.isNull()) 
	    {
	    	_pub_label->setPixmap(pub_image.scaled(600, 222));
	    }
	}
}

void Publicity::on_timer_timeout() {
    setPubToRandomImage();
}

