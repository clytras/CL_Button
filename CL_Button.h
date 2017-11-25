
/*
* Author: Christos Lytras <christos.lytras@gmail.com>
* Description: A monetary switch class to handle IO pins
* Version: 1.2
*/

#ifndef __CL_BUTTON__
#define __CL_BUTTON__

class CL_Button
{
public:
	typedef void(*button_callback)(CL_Button*);
	typedef void(*doevents_callback)(void*);

	CL_Button();
	void init(uint8_t pin, int state /* HIGH | LOW */);
	void update();
	void update(bool untilRelease);

	void onButtonDown(button_callback onBtnDown);
	void onButtonUp(button_callback onBtnUp);
	void onButtonPress(button_callback onBtnPress);
	void onDoEvents(doevents_callback doEventsCB, void* arg);


private:
	uint8_t pin;
	int state;
	int checkState;
	int currentState;
	uint16_t m_decouplingMillis;

	button_callback onKeyDown;
	button_callback onKeyUp;
	button_callback onKeyPress;
	doevents_callback onDoEventsCB;
	void* onDoEventsArg;
};

#endif // __CL_BUTTON__
