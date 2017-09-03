#include "s006d_1.h"


S006D_1::S006D_1(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	this->worldScreen = this->findChild<World*>("world");

	connect(ui.fast_time_button, SIGNAL(clicked()), this, SLOT(fasterTime()));
	connect(ui.slow_time_button, SIGNAL(clicked()), this, SLOT(slowerTime()));
	connect(ui.stop_time_button, SIGNAL(clicked()), this, SLOT(stopTime()));

	connect(ui.pushButton_dude1, SIGNAL(clicked()), this, SLOT(showInfo0()));
	connect(ui.pushButton_dude2, SIGNAL(clicked()), this, SLOT(showInfo1()));
	connect(ui.pushButton_dude3, SIGNAL(clicked()), this, SLOT(showInfo2()));
	connect(ui.pushButton_dude4, SIGNAL(clicked()), this, SLOT(showInfo3()));

	QProgressBar* hunger_bar  = this->findChild<QProgressBar*>("hunger_bar");
	QProgressBar* energy_bar  = this->findChild<QProgressBar*>("energy_bar");
	QProgressBar* sleep_bar  = this->findChild<QProgressBar*>("sleep_bar");

	QPushButton* pushButton_dude1 = this->findChild<QPushButton*>("pushButton_dude1");
	QPushButton* pushButton_dude2 = this->findChild<QPushButton*>("pushButton_dude2");
	QPushButton* pushButton_dude3 = this->findChild<QPushButton*>("pushButton_dude3");
	QPushButton* pushButton_dude4 = this->findChild<QPushButton*>("pushButton_dude4");

	QLabel* label_backround = this->findChild<QLabel*>("label_backround");
	QLabel* label_Name = this->findChild<QLabel*>("label_Name");

	QLCDNumber* money_number = this->findChild<QLCDNumber*>("money_number");
	QLCDNumber* drink_number = this->findChild<QLCDNumber*>("drink_number");

	QLCDNumber* hour_number = this->findChild<QLCDNumber*>("hour_number");
	QLCDNumber* minute_number = this->findChild<QLCDNumber*>("minute_number");

	this->worldScreen->reciveNumber(drink_number, money_number, hour_number, minute_number);
	this->worldScreen->reciveBarLabel(hunger_bar, energy_bar, sleep_bar, label_backround, label_Name);
	this->worldScreen->reciveButton(pushButton_dude1, pushButton_dude2, pushButton_dude3, pushButton_dude4);
}

S006D_1::~S006D_1()
{}

void S006D_1::fasterTime()
{
	this->worldScreen->speedUp();
}
void S006D_1::slowerTime()
{
	this->worldScreen->speedDown();
}
void S006D_1::stopTime()
{
	this->worldScreen->speedStopGO();
}

void S006D_1::showInfo0()
{
	this->worldScreen->showInfoID(0);
}
void S006D_1::showInfo1()
{
	this->worldScreen->showInfoID(1);
}
void S006D_1::showInfo2()
{
	this->worldScreen->showInfoID(2);
}
void S006D_1::showInfo3()
{
	this->worldScreen->showInfoID(3);
}