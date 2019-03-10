#ifndef PLATEAUSCENE_H
#define PLATEAUSCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include "PlateauBox.h"
#include <QList>

class PlateauScene : public QGraphicsView {
public:
    explicit PlateauScene(int size = 8, QWidget* parent = nullptr);
    void setBoxes(int x=0, int y=0);
private:
    int _size;

    QGraphicsScene* _scene;
    QList<PlateauBox*> _boxes;
    QGraphicsGridLayout* _ggbox;
};

#endif // PLATEAUSCENE_H
