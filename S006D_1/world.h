#ifndef WORLD_H
#define WORLD_H

#include <QGLWidget>
#include <qprogressbar>
#include <qlcdnumber>
#include <qpushbutton>
#include <QTimer>
#include <qlabel>
#include <qpixmap>
#include <QString>

#include "mouth_Breather.h"
#include "mouth_Manager.h"
#include "messageDispatch.h"


class World : public QGLWidget
{
	Q_OBJECT
public:
	World(QWidget *parent = 0); ///< constructor that statrs a Qtimer and sets the interval to 1 sec, the Qtimer runs paintGL
	void initializeGL(); ///< initialize option for the gl window and sets the scene graph
	void paintGL(); ///< paints the picture on the openGL window
	void resizeGL(int width, int height);///< resize the gl window

	void speedUp(); ///< slows donwn the interval
	void speedDown(); ///< speeds ip the interval
	void speedStopGO(); ///< stops the qtimer or start it if its allready stopped

	void showInfoID(int ID); ///< calld when a Qpushbutton for the entitys have been pushed, edits the bars, label and LCDNumbers to show info for the shousen ID

	void reciveNumber(QLCDNumber *drink_number, QLCDNumber *money_number, QLCDNumber *hour_number, QLCDNumber *minute_number); ///< gets the LCDNumbers, calld from s006d_1 constructor
	void reciveBarLabel(QProgressBar *hunger_bar, QProgressBar *energy_bar,QProgressBar *sleep_bar, QLabel *label_backround, QLabel *label_Name); ///< gets the bars and labels, calld from s006d_1 constructor
	void reciveButton(QPushButton *dude0, QPushButton *dude1, QPushButton *dude2, QPushButton *dude3); ///< gets the buttons, calld from s006d_1 constructor

	void setBarAndNumber(int hunger, int energy, int drinks, int money, int sleep); ///< update the bars and numbers on the screen with new values
	void setClock(int time); ///< calculates the hour and minute from time, displays it on the screen, and change the backround depending on what time it is

private:
	Mouth_Breather *mouth_Breathers[10];

	QTimer timer;
	int timeSpeed;
	int lastSpeed;
	int time, minute, hour;
	int showInfo;

	QProgressBar *hunger_Bar;
	QProgressBar *energy_Bar;
	QProgressBar *sleep_Bar;
	QLCDNumber *drink_Number;
	QLCDNumber *money_Number;
	QLCDNumber *hour_Number;
	QLCDNumber *minute_Number;
	QPushButton *dude0_Button;
	QPushButton *dude1_Button;
	QPushButton *dude2_Button;
	QPushButton *dude3_Button;
	QLabel *name_label;
	QLabel *backround;
};

#endif