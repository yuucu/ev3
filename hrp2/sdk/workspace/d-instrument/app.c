/**
 * This sample program shows how to create and control periodic tasks in EV3RT
 */

#include "app.h"
#include <stdlib.h>

static int32_t fontw, fonth;

// a cyclic handler to activate a task
void task_activator(intptr_t tskid) {
	ER ercd = act_tsk(tskid);
	assert(ercd == E_OK);
}

// a periodic task
void periodic_task_1(intptr_t unused) {
}

uint16_t doremi(int d) {

	uint16_t freq = 0;
	if(d < 5)
		freq = 0;
	else if(d < 10)
		freq = NOTE_C4;
	else if(d < 15)
		freq = NOTE_D4;
	else if(d < 20)
		freq = NOTE_E4;
	else if(d < 25)
		freq = NOTE_F4;
	else if(d < 30)
		freq = NOTE_G4;
	else if(d < 35)
		freq = NOTE_A4;
	else if(d < 40)
		freq = NOTE_B4;
	else if(d < 45)
		freq = NOTE_C5;
	else
		freq = 0;

	return freq;
}

// a periodic task
void periodic_task_2(intptr_t unused) {

	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	ev3_font_get_size(EV3_FONT_MEDIUM, &fontw, &fonth);

	uint16_t freq;
	int16_t  distance;
	intptr_t data;
	PRI dpri;
	//bool_t start_prd_tsk_2 = false;

	while(1) {
		rcv_pdq(DTQ_1, &data, &dpri);
		distance = data;
		//start_prd_tsk_2 = ev3_button_is_pressed(ENTER_BUTTON);
		freq = doremi(distance);

		//if (start_prd_tsk_2) {
		//	if(freq ==0)
		//		ev3_speaker_stop();
		//	else
		//}
		ev3_speaker_play_tone(freq,100);

		char buf[100];
		sprintf(buf, "Distance: %-3d cm", distance);
		ev3_lcd_draw_string(buf,0, fonth * 5);

		tslp_tsk(100);
	}
}

void main_task(intptr_t unused) {
	int16_t distance = 0;
	intptr_t data = 0;

	ev3_sensor_config(EV3_PORT_1, ULTRASONIC_SENSOR);
//	ev3_sta_cyc(CYC_PRD_TSK_1);
//	ev3_sta_cyc(CYC_PRD_TSK_2);

	act_tsk(PRD_TSK_2);
	while(1) {
		distance = ev3_ultrasonic_sensor_get_distance(EV3_PORT_1);
		data = distance;
		snd_pdq(DTQ_1, data, TMAX_DPRI);

		tslp_tsk(250);
	}
}

