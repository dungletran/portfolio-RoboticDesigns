/*******************************************************************************
* FILE NAME: user_routines.c <EDU VERSION>
*
* DESCRIPTION:
*  This file contains the default mappings of inputs  
*  (like switches, joysticks, and buttons) to outputs on the EDU RC.  
*
* USAGE:
*  You can either modify this file to fit your needs, or remove it from your 
*  project and replace it with a modified copy. 
*
*******************************************************************************/

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
#include "printf_lib.h"
#include "delays.h"


/*******************************************************************************
* FUNCTION PROTOTYPES
*******************************************************************************/

int check_boundary (void);
int avoid_boundary (int refl_set);
int compass_reading(void);
int turn_to(int left_turn, int right_turn, int pos);
void maneuvering(int left, int right);
int check_basket(void);
void ball_to_basket(void);
int back_home (void);
int ball_release(void);
int check_scoop(void);
int check_ball(void);
int catch_ball(int side);
int check_enemy(void);
int avoid_enemy(void);
void timeout(int index);
int turn_to1(int pos, int direction);
int turn_to_with_back(int pos, int direction);
void time_delays(int sec);
int orient_home (void);
int conv(int a, int b, int c);

/*** DEFINE USER VARIABLES AND INITIALIZE THEM HERE ***/

//compass
int oran[8] = {0x0E, 0x0C, 0x0D, 0x09, 0x0B, 0x03, 0x07, 0x06};

//pwm for DC motor
int left_wheel_backward_catch_ball = 79; 
int right_wheel_backward_catch_ball = 186; 
int left_wheel_turn_left_catch_ball = 80; 
int right_wheel_turn_left_catch_ball = 80; 
int left_wheel_turn_right_catch_ball = 173; 
int right_wheel_turn_right_catch_ball = 173; 

//car forward	
int left_wheel_forward = 186;     
int right_wheel_forward = 81;     

//car backward
int left_wheel_backward = 79;     
int right_wheel_backward = 186; 	

//car stop
int left_wheel_stop = 127;       
int right_wheel_stop = 127;  		

//car turn right
int left_wheel_turn_right = 163;    
int right_wheel_turn_right = 163; 		

//car turn right slow
int left_wheel_turn_right_slow = 153;    
int right_wheel_turn_right_slow = 153; 	

//car turn left
int left_wheel_turn_left = 101;  
int right_wheel_turn_left = 101; 

//turn left slow 
int left_wheel_turn_left_slow = 109;    
int right_wheel_turn_left_slow = 109; 	

	
//side sharp sensors
int side_sharp_max = 550;	
int left_sharp_min = 250;
int right_sharp_min = 230;

//detecting ball sharp sensor
int front_sharp_max = 300;	
int front_sharp_min = 250;	

//servor motor1, rotating the tray
int first_pos_servor1 = 255; 	// first position of tray
int sec_pos_servor1 = 0; 	//second position of tray

//servor motor2, rotating the basket
int first_pos_servor2 = 255; 	//first position of basket
int sec_pos_servor2 = 50; 		//second position of basket

//reflective threshole for detecting boundary
int back_ref_thr = 200 ; 
int right_ref_thr = 250; 
int left_ref_thr = 400; 

//enemy_count & threshold
int enm_thr = 50;

/*******************************************************************************
* FUNCTION NAME: check_boundary
* PURPOSE:       checking boundaries and return different actions
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-error; all refelective sensors are active
				 1-detected by back reflective sensor
				 2-detected by right reflective sensor, 3-detected by back and right reflective sensors
				 4-detected by left reflective sensor, 5-detected by back and left reflective sensors
				 6-detected by back and right reflective sensors
				 7-no boundary
*******************************************************************************/
int check_boundary (void) {
	static int l=0, k=0;
	int refl_set, i, j, init_pos, curr_cmps, curr_cmps_index, index1, index2, index3 ;
	int oran_index;
	int counter_back_time = 250;
	int counter_forward_time = 250;
	int stop_time=300;
	int forward_time=50;
	int back_error_time =150;
	int dig_in04, dig_in05, dig_in06;

	Getdata(&rxdata);
	if ((int)Get_Analog_Value(rc_ana_in04) < left_ref_thr)
		dig_in04 = 0;
	else
		dig_in04 = 1;
	
	if ((int)Get_Analog_Value(rc_ana_in05) < right_ref_thr)
		dig_in05= 0;
	else
		dig_in05 = 1;

	if ((int)Get_Analog_Value(rc_ana_in06) < back_ref_thr)
		dig_in06 = 0;
	else
		dig_in06 = 1;
	
	refl_set = conv(dig_in04, dig_in05, dig_in06);

	curr_cmps = compass_reading();	
	
	return refl_set;
}
/*******************************************************************************
* FUNCTION NAME: avoid_boundary
* PURPOSE:       avoid boundary
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     refl_set: indicate which reflective sensors are activated
* RETURNS:       1-successful; 0 fail to avoid
*******************************************************************************/	
int avoid_boundary (int refl_set) {
	static int l=0, k=0;
	int i, j, init_pos, curr_cmps, curr_cmps_index, index1, index2, index3 ;
	int oran_index;
	int counter_back_time = 250;
	int counter_forward_time = 250;
	int stop_time=300;
	int forward_time=50;
	int back_error_time =150;
	int dig_in04, dig_in05, dig_in06;	
	
	//back detech something
	if (refl_set == 6) {
		printf("\t\t back, forward car\n");
		for (i=0; i<counter_forward_time;i++){
			maneuvering (255, 0); //
			Delay1KTCYx (10);
		}
		printf("\t\t back, stop car\n");
		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}

		curr_cmps = compass_reading();
		printf("curr cmps:%d\n", curr_cmps);

		if (curr_cmps == oran[2] || curr_cmps == oran[3]){
			if (turn_to_with_back(5,1)==0){
				if (turn_to1( 5, 1) == 0){
					return 0;
				}
			}				
		}
		else if (curr_cmps == oran[6] || curr_cmps == oran[7]){	
			if (turn_to_with_back(1,1)==0){
				if (turn_to1(1, 1) == 0){
					return 0;
				}
			}
		}

		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}
		
		return 1;
	}
	
	//right detect something
	else if (refl_set == 5){
		//stop car
		for (i=0; i<counter_back_time;i++){
			maneuvering (0, 255); //
			Delay1KTCYx (10);
		}
	
		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}
		
		curr_cmps = compass_reading();

		if (curr_cmps == oran[5] || curr_cmps == oran[6]){
	
			if (turn_to_with_back(4,0)==0){
				if (turn_to1(4, 0) == 0){
					return 0;
				}
			}

		}
		else if (curr_cmps == oran[3] || curr_cmps == oran[4]){
			if (turn_to_with_back(2,0)==0){
				if (turn_to1(2, 0) == 0){
					return 0;
				}
			}

		}
		else if (curr_cmps == oran[1] || curr_cmps == oran[2]){
			if (turn_to_with_back(0,0)==0){
				if (turn_to1(0, 0) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[7] || curr_cmps == oran[0]){
			if (turn_to_with_back(6,0)==0){
				if (turn_to1(6, 0) == 0){
					return 0;
				}
			}
		}
		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}
		return 1;
	}
	
	//right and back detect something
	else if  (refl_set == 4){
		//stop car
		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}
		
		curr_cmps = compass_reading();

		if (curr_cmps == oran[5] ){
			printf("turn left, case 1\n");
			if (turn_to_with_back(4, 0)==0){
				if (turn_to1(4, 0) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[3] ){
			if (turn_to_with_back(2, 0)==0){
				if (turn_to1(2, 0) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[1]){
			if (turn_to_with_back(0, 0)==0){
				if (turn_to1(0, 0) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[7]){
			if (turn_to_with_back(6, 0)==0){
				if (turn_to1(6, 0) == 0){
					return 0;
				}
			}
		}

		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}
		return 1;	
	}
	
	//left detect something
	else if (refl_set == 3){
		//stop car

		for (i=0; i<counter_back_time;i++){
			maneuvering (0, 255); //
			Delay1KTCYx (10);
		}

		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}
		
		curr_cmps = compass_reading();

		if (curr_cmps == oran[0] || curr_cmps == oran[7]){
			if (turn_to_with_back(1, 1)==0){
				if (turn_to1(1, 1) == 0){
					return 0;
				}
			}		
		}
		else if (curr_cmps == oran[5] || curr_cmps == oran[6]){
			if (turn_to_with_back(7, 1)==0){
				if (turn_to1(7, 1) == 0){
					return 0;
				}
			}		
		}
		else if (curr_cmps == oran[3] || curr_cmps == oran[4]){
			if (turn_to_with_back(5, 1)==0){
				if (turn_to1(5, 1) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[1] || curr_cmps == oran[2]){
			if (turn_to_with_back(3, 1)==0){
				if (turn_to1(3, 1) == 0){
					return 0;
				}
			}
		}

		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}
		return 1;
	}
	
	//left and back detect something
	else if  (refl_set == 2){
		//stop car
		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}
		
		curr_cmps = compass_reading();

		if (curr_cmps == oran[2]){
			if (turn_to_with_back(3, 1)==0){
				if (turn_to1(3, 1) == 0){
					return 0;
				}
			}		
		}
		else if (curr_cmps == oran[0]){
			if (turn_to_with_back(1, 1)==0){
				if (turn_to1(1, 1) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[6]){
			if (turn_to_with_back(7, 1)==0){
				if (turn_to1(7, 1) == 0){
					return 0;
				}
			}
		}
		else if (curr_cmps == oran[4]){
			if (turn_to_with_back(5, 1)==0){
				if (turn_to1(5, 1) == 0){
					return 0;
				}
			}
		}

		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}	
		return 1;	
	
	}
	
	//left and right detect something
	else if (refl_set == 1) {
		//stop the car
		
		for (i=0; i<counter_back_time;i++){
			maneuvering (0, 255); //
			Delay1KTCYx (10);
		}
		
		for (i=0; i<stop_time;i++){
			maneuvering (left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (10);
		}
		
		curr_cmps = compass_reading();

		if ( curr_cmps == oran[6] || curr_cmps == oran[7]){
			if (turn_to_with_back(4, 0)==0){
				if (turn_to1(4, 0) == 0){
					return 0;
				}
			}
		}
		else if ( curr_cmps == oran[4] || curr_cmps == oran[5]){
			if (turn_to_with_back(2, 0)==0){
				if (turn_to1(2, 0) == 0){
					return 0;
				}
			}
		}
		else if ( curr_cmps == oran[2] || curr_cmps == oran[3]){
			if (turn_to_with_back(0, 0)==0){
				if (turn_to1(0, 0) == 0){
					return 0;
				}
			}
		}
		else if ( curr_cmps == oran[0] || curr_cmps == oran[1]){
			if (turn_to_with_back(6, 0)==0){
				if (turn_to1(6, 0) == 0){
					return 0;
				}
			}
		}
		for (i=0; i<forward_time;i++){
			maneuvering (left_wheel_forward, right_wheel_forward);
			Delay1KTCYx (10);
		}
		
		return 1;
	}
	else if (refl_set == 0){
		for (i=0;i<back_error_time;i++){
			maneuvering (0,255);
			Delay1KTCYx(30);
		}
		return 0;
	} 
}

/*******************************************************************************
* FUNCTION NAME: catch_ball
* PURPOSE:       finding the ball on the field
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     
* RETURNS:       0-fail to catch ball (terminate after certain time)
*				 1-successful to catch ball
*******************************************************************************/
int catch_ball(int side){  
	int back_index;
	int i, k, curr_cmps;
	int dist;
	int time_back= 150, time_stop = 300, rot_time_left = 180,rot_time_right = 250, timeout1 = 300;
	
	curr_cmps = compass_reading();
	if (curr_cmps == oran[7] || curr_cmps == oran[0] || curr_cmps == oran[1] || curr_cmps == oran[2]){
		back_index=0;
	}else{
		back_index=4;
	}
	
	if (side == 2){
		
		i=0;
	
		while (i<(time_back*2)){
			maneuvering(left_wheel_backward_catch_ball, right_wheel_backward_catch_ball); //need to be calibrated
			Delay1KTCYx (30);
			i++;
		}
		
		i=0;
		while (i<time_stop){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (30);
			i++;
		}
		
		for (i = 0; i < (rot_time_left/2); i++){
			maneuvering(left_wheel_turn_left_catch_ball, right_wheel_turn_left_catch_ball); 
			Delay1KTCYx (30);
		}
		
	}		
	
	else if (side == 1){
		
		i=0;
		while (i<(2*time_back)){
			maneuvering(left_wheel_backward_catch_ball, right_wheel_backward_catch_ball); //need to be calibrated
			Delay1KTCYx (30);
			i++;
		}
	
		i=0;
		while (i<time_stop){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay1KTCYx (30);
			i++;
		}
				
		for (i = 0; i < (rot_time_right/2); i++){
			maneuvering(left_wheel_turn_right_catch_ball, right_wheel_turn_right_catch_ball); 
			Delay1KTCYx (30);
		}
	}

	for (i = 0; i < timeout1; i++){
		maneuvering (left_wheel_forward, right_wheel_forward);
		Delay1KTCYx (30);
		
		if (check_scoop() == 1){
			maneuvering(left_wheel_forward+30,right_wheel_forward-30);
			Delay10KTCYx(30);
			ball_to_basket();
			return 1;
		}
		else{
			Getdata(&rxdata); 
			
			if (((int)Get_Analog_Value(rc_ana_in04) > left_ref_thr) && ((int)Get_Analog_Value(rc_ana_in05) > right_ref_thr)){
				continue;
			}
			
			else {
				timeout(back_index);
				return 0;
			}
		} 
	}
	
	timeout(back_index);
	return 0;

}

/*******************************************************************************
* FUNCTION NAME: timeout
* PURPOSE:       time out function for catch_ball
* CALLED FROM:   catch_ball
* ARGUMENTS:     
* RETURNS:       void
*******************************************************************************/

void timeout(int index){
	int i=0;	
	int time_back=150; 
	printf("TIMEOUT"); //
	while (i++<time_back){
		maneuvering(left_wheel_backward_catch_ball, right_wheel_backward_catch_ball);
		Delay1KTCYx (30);
	}
	turn_to1(index, 0);
}



/*******************************************************************************
* FUNCTION NAME: check_basket
* PURPOSE:       checking basket see whether there is any ball
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-error, 1-successful to check, go back home and release ball
*******************************************************************************/
int check_basket(void){

	Getdata(&rxdata); 
	if (rc_dig_in12 == 0){
		return 1;
	}
	else{
		return 0;
	}
}


/*******************************************************************************
* FUNCTION NAME: back_home
* PURPOSE:       going back home after getting the ball
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-fail to go back home, 1- sucessful to go back home
*******************************************************************************/
int back_home (void){

	int i=0, time_out = 1000;								//main loop
	int h=0, time_ref=3000;
	int k=0, time_away_home=200, time_away_ene = 200;		//home position
	int count1=0, time_out_back = 3000;						//home position while loop
	int m=0, counter_back_time = 100, stop_time = 300;		//BC
	
	
// orientate to home position
	if (orient_home() == 0){				// stuck - return 0
		for (i=0; i<200; i++){				// moving back
			maneuvering (0, 255);
			Delay1KTCYx (30);
		}
		
		for (i=0; i<100; i++){
			maneuvering(left_wheel_stop, right_wheel_stop);			//stop the car
			Delay1KTCYx (30);	
		}
		
		Getdata(&rxdata);		
		if ((((int)Get_Analog_Value(rc_ana_in06) < back_ref_thr) && (int)rc_dig_in08 == 0) || (((int)Get_Analog_Value(rc_ana_in06) < back_ref_thr) && (int)rc_dig_in09 == 0)){ // check if it is home position
			return 1;
		}

		else {
			for (i=0; i<100; i++){			//get out of the situation by moving forward
				maneuvering (255, 0);
				Delay1KTCYx (30);
			}
			return 0;
		}
	}

//go back to home position
	for (i=0; i<time_out; i++) {
		maneuvering (left_wheel_forward, right_wheel_forward);				// move car forward
		Delay1KTCYx (30);
		
		Getdata(&rxdata);				// get fresh data
		
		if ((int)rc_dig_in10 == CLOSED || (int)rc_dig_in11 == CLOSED){		//check if the front bar is activated
			for (h=0; h<time_ref; h++){
				Getdata(&rxdata);		// get fresh data				
				if ((int)Get_Analog_Value(rc_ana_in04) < left_ref_thr || (int)Get_Analog_Value(rc_ana_in05) < right_ref_thr){	// check if the front reflective == 0

					k=0;					
					while (k < time_away_home){								// move backwards away from home
						maneuvering(left_wheel_backward, right_wheel_backward);
						Delay1KTCYx (30);
						k++;
					}
					
					maneuvering(left_wheel_stop, right_wheel_stop);			//stop the car
					Delay1KTCYx (30);
					
					if (turn_to1(0, 0) == 0){								//180 turning, impt to make sure no blockage happen
						if (turn_to_with_back(1,1) == 0){
							return 0;
						}
					}
					
					count1=0;						
					while ((((int)Get_Analog_Value(rc_ana_in06) > back_ref_thr) || (int)rc_dig_in08 != 0) && (((int)Get_Analog_Value(rc_ana_in06) > back_ref_thr) || (int)rc_dig_in09 != 0)){ 	//6-ref, 8-back_limit1, 9-back_limit2
						Getdata(&rxdata);
						maneuvering (left_wheel_backward, right_wheel_backward);
						count1++;
						if (count1 > time_out_back){
							return 0;
						}
					}
					return 1;
				}
			}	
								
			k=0;
			while (k < time_away_ene){					// move backwards max
				maneuvering(0, 255);
				Delay1KTCYx (30);
				k++;
			}
			
			if (orient_home() == 0){				// stuck - return 0
				return 0;
			}
		}

		else {	// check BC
			if ((int)Get_Analog_Value(rc_ana_in04) < left_ref_thr && (int)Get_Analog_Value(rc_ana_in05) < right_ref_thr){	//left right sense smtg, pushed by enermy
				for (m=0; m<2*counter_back_time; m++){	//counter by moving back
					maneuvering (0, 255);
					Delay1KTCYx (30);
				}

				for (m=0; m<stop_time; m++){
					maneuvering (left_wheel_stop, right_wheel_stop);
					Delay1KTCYx (10);
				}
	
				if (orient_home() == 0){
					return 0;
				}
			}

			else if ((int)Get_Analog_Value(rc_ana_in04) < left_ref_thr){	//left sense smtg
				for (m=0; m<counter_back_time;m++){			//counter by moving back
					maneuvering (0, 255);
					Delay1KTCYx (30);
				}

				for (m=0; m<stop_time; m++){
					maneuvering (left_wheel_stop, right_wheel_stop);
					Delay1KTCYx (10);
				}
				
				if (turn_to1(5, 1) == 0){
					if (turn_to_with_back(4,0) == 0){
						return 0;
					}
				}
			}
			
			else if ((int)Get_Analog_Value(rc_ana_in05) < right_ref_thr){									//right sense smtg
				for (m=0; m<counter_back_time; m++){						//counter by moving back
					maneuvering (0, 255);
					Delay1KTCYx (30);
				}

				for (m=0; m<stop_time;m++){
					maneuvering (left_wheel_stop, right_wheel_stop);
					Delay1KTCYx (10);
				}
				
				if (turn_to1(4, 0) == 0){
					if (turn_to_with_back(5,1) == 0){
						return 0;
					
					}
				}
			}
		}
	}
	return 0;
	
}

/*******************************************************************************
* FUNCTION NAME: orient_home 
* PURPOSE:       orientate the car to face which home position
* CALLED FROM:   back_home
* ARGUMENTS:     void
* RETURNS:       0-fail to orientate, 1- sucessful to orientate
*******************************************************************************/
int orient_home (void){				// return 1-success, 0-stuck
	int curr_cmps, curr_cmps_index;
	int j=0;
	curr_cmps = compass_reading();

	if (curr_cmps == oran[0] || curr_cmps == oran[7] || curr_cmps == oran[6] || curr_cmps == oran[5]){
		if (turn_to1(4, 0) == 0){
			if (turn_to1(5,1) == 0){
				turn_to1(0,0);
				return 0;			//stuck after both rotational trial
			}
		}
	}
	
	else{
		if (turn_to1(5, 1) == 0){
			if (turn_to1(4,0) == 0){
				turn_to1(1,1);			
				return 0;			//stuck after both rotational trial
			}
		}
	}
	
	return 1;
}

/*******************************************************************************
* FUNCTION NAME: turn_to_with_back 
* PURPOSE:       turn with backward
* CALLED FROM:   check_boundary, back_home
* ARGUMENTS:     pos: target sector; direction: 0-left, 1-right
* RETURNS:       0-fail to turn, 1- sucessful to turn
*******************************************************************************/	
int turn_to_with_back(int pos, int direction) {
	
	int i=0,stop_time=400;
	int j=0;
	int ini_cmps, curr_cmps;
	
	//turn left
	ini_cmps = compass_reading(); 
	if (direction ==0){	
		do {
			i++;
			if (i%15000 == 0){ 
				curr_cmps = compass_reading();
				if (ini_cmps == curr_cmps){
					for (j=0; j<150; j++){					//counter by moving back
						maneuvering (0, 255);
						Delay1KTCYx (30);
					}
					return 0;
				}
				else{
					i =1;
					ini_cmps = curr_cmps;
				}
			}
			maneuvering(left_wheel_turn_left, right_wheel_turn_left);
		} while (compass_reading() != oran[pos]);
		
		for (i=0;i<300;i++){			//couter reaction by maximun turning right
			maneuvering(255, 255);
		}
		
		for (i=0;i<stop_time;i++){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay100TCYx (10);
		}
	}

	//turn right
	else{	
		do {
			i++;
			if (i%10000 == 0){ 
				curr_cmps = compass_reading();
				if (ini_cmps == curr_cmps){
					for (j=0; j<150; j++){					//counter by moving back
						maneuvering (0, 255);
						Delay1KTCYx (30);
					}
					return 0;
				}
				else{
					i =1;
					ini_cmps = curr_cmps;
				}
			}
			maneuvering(left_wheel_turn_right, right_wheel_turn_right);
			Delay100TCYx (10);
		} while (compass_reading() != oran[pos]);


		for (i=0;i<250;i++){ 			//couter reaction by maximun turning left
			maneuvering(0, 0);
		}
		
		for (i=0;i<stop_time;i++){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay100TCYx (10);
		}
	}
	return 1;
}


/*******************************************************************************
* FUNCTION NAME: ball_release
* PURPOSE:       release ball at home position
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-fail to release ball, 1- sucessful to release ball   
*******************************************************************************/
int ball_release(void){
	//release the ball from basket into box by turning the servor motor
	int i;
	Getdata(&rxdata);
	for (i = first_pos_servor2; i > sec_pos_servor2;i-=5){
		printf("rotating i= %d\n");
		pwm04 = i; //rotate basket
		Putdata (&txdata);
		Delay10KTCYx (10);
	}
	
	//keep for awhile
	for (i=0; i<100;i++){
		Putdata (&txdata);
		Delay10KTCYx (10);
	}
	
	//return initial position
	for (i = sec_pos_servor2; i <= first_pos_servor2;i+=5){
		pwm04 = i; //rotate basket back
		Putdata (&txdata);
		Delay10KTCYx (10);
	}
	return 1;


}

/*******************************************************************************
* FUNCTION NAME: check_scoop
* PURPOSE:       checking scoop see whether there is any ball
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-no ball in scoop, 1- successful to detect ball in scoop and transfer to basket
*******************************************************************************/
int check_scoop(void){
	int front_dist,i;

	Getdata(&rxdata);

	front_dist =(int)Get_Analog_Value(rc_ana_in03); //check the front sharp sensor at scoop
	
	if ((front_dist < front_sharp_min ) || ((front_dist > front_sharp_max)&&(front_dist < 600))){   //kokhou:change
		return 1;
	}
	else{
		return 0;
	}

}

/*******************************************************************************
* FUNCTION NAME: ball_to_basket
* PURPOSE:       transfer ball from scoop to basket
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       void
*******************************************************************************/
void ball_to_basket(void){
	int i;
	//moving tray
	
	for (i = first_pos_servor1; i > sec_pos_servor1; i-=5){
		pwm03 = i;
		Putdata (&txdata);
		Delay10KTCYx (10);
	}	
	//stop wheel from moving
		
	//keep tray for awhile
	for (i=0; i<200;i++){
		maneuvering (left_wheel_stop, right_wheel_stop);
		Putdata (&txdata);
		Delay10KTCYx (10);
	}
	
	//return initial position
	for (i = sec_pos_servor1; i <= first_pos_servor1; i+=5){
		pwm03 = i;
		Putdata (&txdata);
		Delay10KTCYx (10);
	}
}	
		
		
/*******************************************************************************
* FUNCTION NAME: check_ball
* PURPOSE:       finding the ball on the field
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-no ball at side, 1-ball at right side, 2-ball at left side
*******************************************************************************/
int check_ball (void){    
	int left_dist, right_dist, left, right;
	static int l_obj_count = 0;
	static int r_obj_count = 0;
	
	printf("check SIDE ball\n");
	
	Getdata(&rxdata); 
	left_dist = (int)Get_Analog_Value(rc_ana_in01);
	right_dist = (int)Get_Analog_Value(rc_ana_in02);
	
	if ((left_sharp_min < left_dist) && (left_dist < side_sharp_max)){
		l_obj_count++;
	}

	else if(left_dist <= left_sharp_min){
		if (l_obj_count == 0)
			left = 0;
		else if (l_obj_count <= enm_thr){
			l_obj_count = 0;
			left = 1;
		}
		else{
			l_obj_count = 0;
			left = 0;
		} 
	}	
	
	if((right_sharp_min < right_dist) && (right_dist < side_sharp_max)){
		r_obj_count++;
	}		
	
	else if(right_dist <= right_sharp_min){
		if (r_obj_count == 0)
			right = 0;
		else if (r_obj_count <= enm_thr){
			r_obj_count = 0;
			right = 1;
		}
		else{
			r_obj_count = 0;
			right = 0;
		} 
	}	
	
	if (left == 1)
		return 2;
	else if (right == 1)
		return 1;
	else
		return 0; 

}

/*******************************************************************************
* FUNCTION NAME: check_enemy
* PURPOSE:       see whether the car collide with enemy
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-no collision with enemy, 1-there is collision with enemy
*******************************************************************************/
int check_enemy (void){

	Getdata(&rxdata);
	if (rc_dig_in10 == CLOSED || rc_dig_in11 == CLOSED)
		return 1;
	else
		return 0;
}


/*******************************************************************************
* FUNCTION NAME: avoid_enemy
* PURPOSE:       to avoid enemy
* CALLED FROM:   Process_Data_From_Master_uP
* ARGUMENTS:     void
* RETURNS:       0-fail to avoid enemy, 1- successful to avoid enemy
*******************************************************************************/
int avoid_enemy (void){
	int back_time, turn_time;
	int i;

	//calibration value
	back_time=300;
	turn_time=500;

	while (i<back_time){
		maneuvering(left_wheel_backward, right_wheel_backward); //need to be calibrated
		check_boundary();
		Delay1KTCYx (30);
		i++;
	}
	
	while (i<turn_time){
		maneuvering(left_wheel_turn_right, right_wheel_turn_right); //need to be calibrated
		check_boundary();
		Delay1KTCYx (30);
		i++;
	}	
	return 1;
}


/*******************************************************************************
* FUNCTION NAME: compass_reading
* PURPOSE:       reading value from compass
* CALLED FROM:   check_boundary
* ARGUMENTS:     void
* RETURNS:       int
*******************************************************************************/
int compass_reading(void) {
	int north = 1, east = 1, south = 1,west = 1, value;
	
	Getdata(&rxdata); 
	if (rc_dig_in13 == CLOSED) //north
		north = 0;
	if (rc_dig_in14 == CLOSED) //east
		east = 0;
	if (rc_dig_in15 == CLOSED) //south
		south = 0;
	if (rc_dig_in16 == CLOSED) //west
		west = 0;
	Delay10TCYx (1);	
	value = (west<<3) + (south<<2) + (east<<1) + north;
	Putdata(&txdata);

	return value;
}


/*******************************************************************************
* FUNCTION NAME: maneuvering
* PURPOSE:       executing 2 wheels
* CALLED FROM:   check_boundary, Process_Data_From_Master_uP
* ARGUMENTS:     left-pulse out at left motor,
				 right-pulse out at right motor.
* RETURNS:       void
*******************************************************************************/
void maneuvering(int left, int right){
	pwm01 = left;
	pwm02 = right;
    Putdata(&txdata);
	Delay100TCYx (1);
} 


/*******************************************************************************
* FUNCTION NAME: turn_to1
* PURPOSE:       checking boundaries and return different actions
* CALLED FROM:   check_boundary, orient_home, back_home, timeout
* ARGUMENTS:     pos: target sector; direction:1-right, 0-left
* RETURNS:       void
*******************************************************************************/
int turn_to1(int pos, int direction) {
	
	int pos1;
	int i=0,count=0,stop_time=400, time_out = 20000;
	int j=0;
	int ini_cmps, curr_cmps;

	//turn left
	ini_cmps = compass_reading(); 
	if (direction ==0){	

		do {
			i++;
			if (i%15000 == 0){ 
				curr_cmps = compass_reading();
				if (ini_cmps == curr_cmps)
					return 0;
				else{
					i =1;
					ini_cmps = curr_cmps;
				}
			}

			maneuvering(left_wheel_turn_left, right_wheel_turn_left);
		} while (compass_reading() != oran[pos]);

		for (i=0;i<300;i++){
			maneuvering(255, 255);
		}
		
		for (i=0;i<stop_time;i++){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay100TCYx (10);
		}

	}
	//turn right
	else{	

		do {
			i++;
			if (i%10000 == 0){ 
				curr_cmps = compass_reading();
				if (ini_cmps == curr_cmps)
					return 0;
				else{
					i =1;
					ini_cmps = curr_cmps;
				}
			}

			maneuvering(left_wheel_turn_right, right_wheel_turn_right);
			Delay100TCYx (10);
		} while (compass_reading() != oran[pos]);

		for (i=0;i<250;i++){ //int =300
			maneuvering(0, 0);
		}
		
		for (i=0;i<stop_time;i++){
			maneuvering(left_wheel_stop, right_wheel_stop);
			Delay100TCYx (10);
		}

	}
	return 1;
}


/*******************************************************************************
* FUNCTION NAME: conv
* PURPOSE:       convert from binary to decimal
* CALLED FROM:   check_boundary
* ARGUMENTS:     
* RETURNS:       
*******************************************************************************/
int conv(int a, int b, int c){
	if (a==1 && b ==1 && c==1) return 7;
	else if (a==1 && b ==1 && c==0) return 6;
	else if (a==1 && b ==0 && c==1) return 5;
	else if (a==1 && b ==0 && c==0) return 4;
	else if (a==0 && b ==1 && c==1) return 3;
	else if (a==0 && b ==1 && c==0) return 2;
	else if (a==0 && b ==0 && c==1) return 1;
	else return 0;
}



/*******************************************************************************
* FUNCTION NAME: Setup_Who_Controls_Pwms
* PURPOSE:       Each parameter specifies what processor will control the pwm.  
*                 
* CALLED FROM:   User_Initialization
*     Argument             Type    IO   Description
*     --------             ----    --   -----------
*     pwmSpec1              int     I   USER/MASTER (defined in ifi_aliases.h)
*     pwmSpec2              int     I   USER/MASTER
*     pwmSpec3              int     I   USER/MASTER
*     pwmSpec4              int     I   USER/MASTER
*     pwmSpec5              int     I   USER/MASTER
*     pwmSpec6              int     I   USER/MASTER
*     pwmSpec7              int     I   USER/MASTER
*     pwmSpec8              int     I   USER/MASTER
* RETURNS:       void
*******************************************************************************/
static void Setup_Who_Controls_Pwms(int pwmSpec1,int pwmSpec2,int pwmSpec3,int pwmSpec4,
                                    int pwmSpec5,int pwmSpec6,int pwmSpec7,int pwmSpec8)
{
  txdata.pwm_mask = 0xFF;         /* Default to master controlling all PWMs. */
  if (pwmSpec1 == USER)           /* If User controls PWM1 then clear bit0. */
    txdata.pwm_mask &= 0xFE;      /* same as txdata.pwm_mask = txdata.pwm_mask & 0xFE; */
  if (pwmSpec2 == USER)           /* If User controls PWM2 then clear bit1. */
    txdata.pwm_mask &= 0xFD;
  if (pwmSpec3 == USER)           /* If User controls PWM3 then clear bit2. */
    txdata.pwm_mask &= 0xFB;
  if (pwmSpec4 == USER)           /* If User controls PWM4 then clear bit3. */
    txdata.pwm_mask &= 0xF7;
  if (pwmSpec5 == USER)           /* If User controls PWM5 then clear bit4. */
    txdata.pwm_mask &= 0xEF;
  if (pwmSpec6 == USER)           /* If User controls PWM6 then clear bit5. */
    txdata.pwm_mask &= 0xDF;
  if (pwmSpec7 == USER)           /* If User controls PWM7 then clear bit6. */
    txdata.pwm_mask &= 0xBF;
  if (pwmSpec8 == USER)           /* If User controls PWM8 then clear bit7. */
    txdata.pwm_mask &= 0x7F;
}


/*******************************************************************************
* FUNCTION NAME: User_Initialization
* PURPOSE:       This routine is called first (and only once) in the Main function.  
*                You may modify and add to this function.
*                The primary purpose is to set up the DIGITAL IN/OUT - ANALOG IN
*                pins as analog inputs, digital inputs, and digital outputs.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void User_Initialization (void)
{
  rom const	char *strptr = "IFI User Processor Initialized ...";

/* FIRST: Set up the pins you want to use as analog INPUTs. */
  IO1 = IO2 = IO3 = IO4 = IO5 = IO6 = INPUT;


/* SECOND: Configure the number of analog channels. */
  Set_Number_of_Analog_Channels(SIX_ANALOG);   

/* THIRD: Set up any extra digital inputs. */
		
    IO7 = IO8 = IO9 = IO10 = IO11 = IO12 = IO13 = IO14 = IO15 = IO16 = INPUT; 
	
/* FOURTH: Set up the pins you want to use as digital OUTPUTs. */

/* FIFTH: Initialize the values on the digital outputs. */

/* SIXTH: Set your initial PWM values.  Neutral is 127. */
  	pwm05 = pwm06 = pwm07 = pwm08 = 127;
	pwm02 = right_wheel_stop;
	pwm01 = left_wheel_stop;
	pwm03 = first_pos_servor1; 
	pwm04 = first_pos_servor2;

/* SEVENTH: Choose which processor will control which PWM outputs. */
  Setup_Who_Controls_Pwms(MASTER,MASTER,MASTER,MASTER,MASTER,MASTER,MASTER,MASTER);

/* EIGHTH: Set your PWM output type.  Only applies if USER controls PWM 1, 2, 3, or 4. */
  Setup_PWM_Output_Type(IFI_PWM,IFI_PWM,IFI_PWM,IFI_PWM);



/* Add any other user initialization code here. */

  Initialize_Serial_Comms();     

  Putdata(&txdata);             /* DO NOT CHANGE! */

  printf("%s\n", strptr);       /* Optional - Print initialization message. */

  User_Proc_Is_Ready();         /* DO NOT CHANGE! - last line of User_Initialization */
}


/*******************************************************************************
* FUNCTION NAME: Process_Data_From_Master_uP
* PURPOSE:       Executes every 17ms when it gets new data from the master 
*                microprocessor.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Process_Data_From_Master_uP(void)
{	
	int chk, check_side, check_catch_ball;
	int test,i,j, rot_time, stop_time, time_forward, time_backward ;//test
	int number =0, result;
	int time_count1=0, go_side=0, beg_count1=500;
	int start=0;
	
	Delay10KTCYx(50);

START:
	Putdata(&txdata);
	Getdata(&rxdata);
	
	//wait for press start button
	while (start ==0){
		if (rc_dig_in08 == 0){ // check back left switch
			start =1;
		}
		else
			return ;
	}
	
	if (time_count1<beg_count1) {
		time_count1++;
		go_side=0;
	}
	else{
		time_count1=beg_count1+1;
		go_side = 1;
	}
	
	//move forward
	maneuvering(left_wheel_forward, right_wheel_forward);

	//check boundary
	chk = check_boundary();

	if ( chk != 7 ||  chk != 0 )
		//if hitting boundary then avoid it and go back to START
		avoid_boundary();
		goto START;
		
	else
		//not touch boundary, then go to check if hitting enemy
		goto CHECK_ENEMY;


		
CHECK_ENEMY:	
	if (check_enemy() == 1){ // if hitting enemy, then avoid enemy
		avoid_enemy();
		goto START;
	}
	else //not hitting enemy check the basket
		goto CHECK_BASKET;

CHECK_BASKET:
	if (check_basket() == 1){ // if basket has ball, then go back home position and release ball
		if (back_home() == 1){
			maneuvering(127,127);
			ball_release();
		}
		goto CHECK_BASKET;
	}

	else{ // no ball at basket, then go to check scoop
		goto CHECK_SCOOP;            
	}

CHECK_SCOOP:
	if (check_scoop() == 1) { // if scoop has ball then transfer ball from scoop to basket
		maneuvering(left_wheel_forward+30,right_wheel_forward-30);
		Delay10KTCYx(30);
		ball_to_basket();
		goto CHECK_BASKET;
	}

	else{// if no ball in scoop, go check ball at side
		goto CHECK_BALL;		      // for the flow of program
	}

CHECK_BALL:
	if (go_side == 0) goto START;
	check_side = check_ball();
	if (check_side != 0){ // there is ball at side, go and catch the ball
		check_catch_ball = catch_ball(check_side);
		if (check_catch_ball == 1){
			goto CHECK_BASKET;
		}

		else{
			goto START;
		}
	}
	
	else{
		goto START;
	}
	
	Putdata(&txdata);             /* DO NOT CHANGE! */
}


