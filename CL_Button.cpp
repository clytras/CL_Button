
/*
* Author: Christos Lytras <christos.lytras@gmail.com>
* Description: A monetary switch class to handle IO pins
* Version: 1.2
*/

#include "Arduino.h"
#include "CL_Button.h"


CL_Button::CL_Button() :
onKeyDown(NULL),
onKeyUp(NULL),
onKeyPress(NULL),
m_decouplingMillis(50)
{
	
}

void CL_Button::init(uint8_t pin, int state)
{
	this->pin = pin;
	this->state = state;
	checkState = state == HIGH ? LOW : HIGH;

	pinMode(pin, INPUT);
	digitalWrite(pin, state);
}

void CL_Button::update()
{
	update(false);
}

void CL_Button::update(bool untilRelease)
{
	//static unsigned long decouplingTimer;
	//if((millis() - decouplingTimer) < m_decouplingMillis)
	//	return;

	int state = digitalRead(pin);

	if (state == checkState)
	{
		if (currentState != state && onKeyPress && !untilRelease)
		{
			//decouplingTimer = millis();
			onKeyPress(this);
		}

		currentState = state;

		if (onKeyDown)
		{
			onKeyDown(this);
			delay(20);
		}

		if (untilRelease)
		{
			while (digitalRead(pin) == checkState)
			{
				if(onDoEventsCB)
					onDoEventsCB(onDoEventsArg);
			}
			//delay(20);
			//decouplingTimer = millis();

			if (onKeyUp) onKeyUp(this);
			if (onKeyPress) onKeyPress(this);
		}
	}
	else if (currentState != state)
	{
		currentState = state;
		if (onKeyUp) onKeyUp(this);
		//if (onKeyPress) onKeyPress(this);
	}
}

void CL_Button::onButtonDown(button_callback onBtnDown)
{
	onKeyDown = onBtnDown;
}

void CL_Button::onButtonUp(button_callback onBtnUp)
{
	onKeyDown = onBtnUp;
}

void CL_Button::onButtonPress(button_callback onBtnPress)
{
	onKeyPress = onBtnPress;
}

void CL_Button::onDoEvents(doevents_callback doEventsCB, void* arg)
{
	onDoEventsCB = doEventsCB;
	onDoEventsArg = arg;
}
