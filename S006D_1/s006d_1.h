#ifndef S006D_1_H
#define S006D_1_H

#include <QtGui/QMainWindow>
#include "ui_s006d_1.h"
#include "world.h"

class S006D_1 : public QMainWindow
{
	Q_OBJECT

public:
	S006D_1(QWidget *parent = 0, Qt::WFlags flags = 0); ///< constructor that connects all qt elements, and sends them to world so they can be used there 
	~S006D_1();



private:
	Ui::S006D_1Class ui;
	World *worldScreen;

public slots:
	void fasterTime(); ///< calls worlds function speedUp
	void slowerTime(); ///< calls the world function speedDown
	void stopTime(); ///< calls the  world function speedStopGo

	void showInfo0(); ///< calls the world function showInfoID for id 0
	void showInfo1(); ///< calls the world function showInfoID for id 1
	void showInfo2(); ///< calls the world function showInfoID for id 2
	void showInfo3(); ///< calls the world function showInfoID for id 3
	
};

#endif // S006D_1_H
