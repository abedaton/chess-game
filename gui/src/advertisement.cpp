#include "Advertisement .hpp"


#include <stdio.h>

Publicite::Publicite(QWidget *parent) : QWidget(parent) 
{	
	init();
}

void Publicite::init()
{
	_timer = new QTimer(this); 
	_pub_label = new QLabel(this);
	setPubToRandomImage();
	


	connect(_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	_timer->start(5*60*1000); 
}

void Publicite::setPubToRandomImage()
{
	QDir directory("advertisements");
	QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
	size_t image_idx = rand()%images.length();
	
	QString image_path = "advertisements/" + images.at(image_idx);
	QPixmap pub_image(image_path);
    if (!pub_image.isNull()) 
    {
    	_pub_label->setPixmap(pub_image);
    }
   /* else
    	std::cout << "c" << std::endl;*/

	
}

void Publicite::on_timer_timeout() {
    setPubToRandomImage();
}

