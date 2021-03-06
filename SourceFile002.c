#pragma config(Sensor, in1,    light_right,    sensorLineFollower)
#pragma config(Sensor, in2,    light_left,     sensorLineFollower)
#pragma config(Motor,  port1,           right,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          left,          tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void movewheel2control(){
	motor[port1]=vexRT[ch2];
	motor[port10]=-vexRT[ch3];
}
void movewheel(){
	float y = vexRT[ch2]/2;
	float x = vexRT[ch1]/2;
	float left_motor;
	float right_motor;
	float power, st;
	power = sqrt(x*x+y*y);
	if(y>=0&&power!=0){
		st = x * 100/power;
		if(x>=0){
			left_motor = power;
			right_motor = (1-0.02*st)*power;
		}
		else{
			right_motor = power;
			left_motor = (1+0.02*st)*power;
		}
	}
	if(y<=0&&power!=0){
		power*=-1;
		st = x * 100/power;
		if(x>=0){
			left_motor = power;
			right_motor = (1+0.02*st)*power;
		}
		else{
			right_motor = power;
			left_motor = (1-0.02*st)*power;
		}
	}
	if(x==0&&y==0){
		motor[port10] = 0;
		motor[port1] = 0;
	}
	motor[port10] = -left_motor;
	motor[port1] = right_motor;
}
void moveclaw(){
	if(vexRT[Btn5U] == 1){
		motor[port7] = 100;
	}
	else if(vexRT[Btn5D] == 1){
		motor[port7] = -30;
	}
	else if(vexRT(Btn6U) == 1){
		motor[port6] = 100;
	}
	else if(vexRT(Btn6D) == 1){
		motor[port6] = -100;
	}else{


		motor[port6] = 0;
		motor[port7] = 15;
	}
}

task main(){
	float motor1 = 25;//initial speed
	float motor10 = -25;//initial speed
	float e = 0;//difference between two sensor value
	float a = 0.04;//adjustment constant
	while(true){
		if(vexRT[Btn8U]==1){//button for safety
			e = sensorValue(light_right)-sensorValue(light_left);
			//higer value -> darker lower value -> lighter
																//    white color:100 - 200
			//limit 0~4095									black color:2300 - 3000
			motor[port1] = motor1+e*a;
			motor[port10] = motor10+e*a;
		}else{
			motor[port1] = 0; //stop for safety
			motor[port10] = 0;
		}
		moveclaw();//move claw and arm
	}
}
