#pragma once
//#include "stdafx.h"
//#include "NSDirectives.h"
#include <string>


class  CNSTextHeight//_declspec(dllexport)
{
public:
	CNSTextHeight(void);
	virtual ~CNSTextHeight(void);
public:
	double getHeight();
	double getXPosition();
	double getYPosition();
	void setHeight(double dHeight);
	void setXPosition(double dXPosition);
	void setYPosition(double dYPosition);
private:
	double m_dHeight;
	double m_dXPosition;
	double m_dYPosition;
};