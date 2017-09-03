#include "world.h"
#include "s006d_1.h"


World::World(QWidget* parent) : QGLWidget(parent)
{
	this->timeSpeed = 1000;
	this->timer.setInterval(timeSpeed);
	connect(&this->timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	this->timer.start();
}

void World::initializeGL()
{
	glClearColor(1,0,0,1);

	time = 0;
	showInfo = 0;

	Mouth_Breather* mb0 = new Mouth_Breather(0, dude0_Button, "Beni");
	Mouth_Breather* mb1 = new Mouth_Breather(1, dude1_Button, "Slagathor");
	Mouth_Breather* mb2 = new Mouth_Breather(2, dude2_Button, "Stormageddon");
	Mouth_Breather* mb3 = new Mouth_Breather(3, dude3_Button, "Kevin");
	mouth_Breathers[0] = mb0;
	mouth_Breathers[1] = mb1;
	mouth_Breathers[2] = mb2;
	mouth_Breathers[3] = mb3;
	Manager->registerMouth(mb0);
	Manager->registerMouth(mb1);
	Manager->registerMouth(mb2);
	Manager->registerMouth(mb3);
}

void World::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	time += 1;
	setClock(time);

	this->setBarAndNumber(mouth_Breathers[showInfo]->getHunger(), mouth_Breathers[showInfo]->getEnergy(), mouth_Breathers[showInfo]->getDrinks(), mouth_Breathers[showInfo]->getMoney(), mouth_Breathers[showInfo]->getSleep());

	for (int i = 0; i < 4; i++)
	{
		mouth_Breathers[i]->update(time);
	}

	Dispatch->dispatchDelayedMassage();
}

void World::resizeGL(int width, int height)
{}

void World::reciveBarLabel(QProgressBar *hunger_bar, QProgressBar *energy_bar, QProgressBar *sleep_bar, QLabel *label_backround, QLabel *label_Name)
{
	this->hunger_Bar = hunger_bar;
	this->energy_Bar = energy_bar;
	this->sleep_Bar = sleep_bar;
	this->backround = label_backround;
	this->name_label = label_Name;
}

void World::reciveNumber(QLCDNumber *drink_number, QLCDNumber *money_number, QLCDNumber *hour_number, QLCDNumber *minute_number)
{
	this->drink_Number = drink_number;
	this->money_Number = money_number;
	this->hour_Number = hour_number;
	this->minute_Number = minute_number;
}

void World::setBarAndNumber(int hunger, int energy, int drinks, int money, int sleep)
{
	this->hunger_Bar->setValue(hunger);
	this->energy_Bar->setValue(energy);
	this->drink_Number->display(drinks);
	this->money_Number->display(money);
	this->sleep_Bar->setValue(sleep);
}

void World::setClock(int time)
{
	hour = (time / 60) % 60;
	minute = time % 60;
	this->minute_Number->display(minute);
	if (hour > 24)
	{
		this->hour_Number->display(hour % 24);
	}
	else
	{
		this->hour_Number->display(hour);
	}

	if ((hour % 24) > 17 || (hour % 24) < 6)
	{
		this->backround->setPixmap(QPixmap("backround2.png"));
	}
	else
	{
		this->backround->setPixmap(QPixmap("backround.png"));
	}
}

void World::speedUp()
{
	this->timeSpeed /= 1.5;
	this->timer.setInterval(timeSpeed);
}
void World::speedDown()
{
	this->timeSpeed *= 1.5;
	this->timer.setInterval(timeSpeed);
}
void World::speedStopGO()
{
	if(this->timeSpeed == 0) //if already stopped time
	{
		timeSpeed = this->lastSpeed;
		this->timer.start();
	}
	else
	{
		this->lastSpeed = this->timeSpeed;
		timeSpeed = 0;
		this->timer.stop();
	}
}
void World::showInfoID(int ID)
{
	this->setBarAndNumber(mouth_Breathers[ID]->getHunger(), mouth_Breathers[ID]->getEnergy(), mouth_Breathers[ID]->getDrinks(), mouth_Breathers[ID]->getMoney(), mouth_Breathers[ID]->getSleep());

	string str = mouth_Breathers[ID]->getName();
	QString qstr(str.c_str());
	this->name_label->clear();
	this->name_label->setText(qstr);
	showInfo = ID;
}

void World::reciveButton(QPushButton *dude0, QPushButton *dude1, QPushButton *dude2, QPushButton *dude3)
{
	dude0_Button = dude0;
	dude1_Button = dude1;
	dude2_Button = dude2;
	dude3_Button = dude3;
}