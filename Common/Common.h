#pragma once

#include "User.h"


class Common
{
public:
	// return "yyyy-MM-dd hh:mm:ss"
	static QString Get_currentTime() {
		QDateTime currentDateTime = QDateTime::currentDateTime();
		QString currentDateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
		return currentDateTimeString;
	}
};