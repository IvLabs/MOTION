#ifndef HERKULEX_H
#define HERKULEX_H

#include <iostream>

const unsigned int EEP_WRITE_REQ = 0x01
const unsigned int EEP_READ_REQ = 0x02
const unsigned int RAM_WRITE_REQ = 0x03
const unsigned int RAM_READ_REQ = 0x04
const unsigned int I_JOG_REQ = 0x05
const unsigned int S_JOG_REQ = 0x06
const unsigned int STAT_REQ = 0x07
const unsigned int ROLLBACK_REQ = 0x08
const unsigned int REBOOT_REQ = 0x09
const unsigned int EEP_WRITE_ACK = 0x41
const unsigned int EEP_READ_ACK = 0x42
const unsigned int RAM_WRITE_ACK = 0x43
const unsigned int RAM_READ_ACK = 0x44
const unsigned int I_JOG_ACK = 0x46
const unsigned int STAT_ACK = 0x47
const unsigned int ROLLBACK_ACK = 0x48
const unsigned int REBOOT_ACK = 0x49

//Addresses

const unsigned int MODEL_NO1_EEP = 0
const unsigned int VERSION1_EEP = 2
const unsigned int VERSION2_EEP = 3
const unsigned int BAUD_RATE_EEP = 4
const unsigned int SERVO_ID_EEP = 6
const unsigned int SERVO_ID_RAM = 0
const unsigned int ACK_POLICY_EEP = 7
const unsigned int ACK_POLICY_RAM = 1
const unsigned int ALARM_LED_POLICY_EEP = 8
const unsigned int ALARM_LED_POLICY_RAM = 2
const unsigned int TORQUE_POLICY_EEP 9
const unsigned int TORQUE_POLICY_RAM 3
const unsigned int MAX_TEMP_EEP 11
const unsigned int MAX_TEMP_RAM 5
const unsigned int MIN_VOLTAGE_EEP 12
const unsigned int MIN_VOLTAGE_RAM 6
const unsigned int MAX_VOLTAGE_EEP 13
const unsigned int MAX_VOLTAGE_RAM 7
const unsigned int ACCELERATION_RATIO_EEP 14
const unsigned int ACCELERATION_RATIO_RAM 8
const unsigned int MAX_ACCELERATION_TIME_EEP 15
const unsigned int MAX_ACCELERATION_TIME_RAM 9
const unsigned int DEAD_ZONE_EEP 16
const unsigned int DEAD_ZONE_RAM 10
const unsigned int SATURATOR_OFFSET_EEP 17
const unsigned int SATURATOR_OFFSET_RAM 11
const unsigned int SATURATOR_SLOPE_EEP 18
const unsigned int SATURATOR_SLOPE_RAM 12
const unsigned int PWM_OFFSET_EEP 20
const unsigned int PWM_OFFSET_RAM 14
const unsigned int MIN_PWM_EEP 21
const unsigned int MIN_PWM_RAM 15
const unsigned int MAX_PWM_EEP 22
const unsigned int MAX_PWM_RAM 16
const unsigned int OVERLOAD_PWM_THRESHOLD_EEP 24
const unsigned int OVERLOAD_PWM_THRESHOLD_RAM 18
const unsigned int MIN_POSITION_EEP 26
const unsigned int MIN_POSITION_RAM 20
const unsigned int MAX_POSITION_EEP 28
const unsigned int MAX_POSITION_RAM 22
const unsigned int POSITION_KP_EEP 30
const unsigned int POSITION_KP_RAM 24
const unsigned int POSITION_KD_EEP 32
const unsigned int POSITION_KD_RAM 26
const unsigned int POSITION_KI_EEP 34
const unsigned int POSITION_KI_RAM 28
const unsigned int POSITION_FEEDFORWARD_GAIN1_EEP 36
const unsigned int POSITION_FEEDFORWARD_GAIN1_RAM 30
const unsigned int POSITION_FEEDFORWARD_GAIN2_EEP 38
const unsigned int POSITION_FEEDFORWARD_GAIN2_RAM 32
const unsigned int VELOCITY_KP_EEP 40
const unsigned int VELOCITY_KP_RAM 34
const unsigned int VELOCITY_KI_EEP 42
const unsigned int VELOCITY_KI_RAM 36
const unsigned int LED_BLINK_PERIOD_EEP 44
const unsigned int LED_BLINK_PERIOD_RAM 38
const unsigned int ADC_FAULT_CHECK_PERIOD_EEP 45
const unsigned int ADC_FAULT_CHECK_PERIOD_RAM 39
const unsigned int PACKET_GARBAGE_CHECK_PERIOD_EEP 46

#define PACKET_GARBAGE_CHECK_PERIOD_RAM 40

#define STOP_DETECTION_PERIOD_EEP 47

#define STOP_DETECTION_PERIOD_RAM 41

#define OVERLOAD_DETECTION_PERIOD_EEP 48

#define OVERLOAD_DETECTION_PERIOD_RAM 42

#define STOP_THRESHOLD_EEP 49

#define STOP_THRESHOLD_RAM 43

#define INPOSITION_MARGIN_EEP 50

#define INPOSITION_MARGIN_RAM 44

#define CALIBRATION_DIFF_LOW_EEP 52

#define CALIBRATION_DIFF_LOW_RAM 46

#define CALIBRATION_DIFF_UP_EEP 53

#define CALIBRATION_DIFF_UP_RAM 47

#define STATUS_ERROR_RAM 48

#define STATUS_DETAIL_RAM 49

AUX1_RAM 50

TORQUE_CONTROL_RAM 52

LED_CONTROL_RAM 53

VOLTAGE_RAM 54

TEMPERATURE_RAM 55

CURRENT_CONTROL_MODE_RAM 56

TICK_RAM 57

CALIBRATED_POSITION_RAM 58

ABSOLUTE_POSITION_RAM 60

DIFFERENTIAL_POSITION_RAM 62

PWM_RAM 64

ABSOLUTE_SECOND_POSITION_RAM 66

ABSOLUTE_GOAL_POSITION_RAM 68

ABSOLUTE_DESIRED_TRAJECTORY_POSITION 70

DESIRED_VELOCITY_RAM 72

BYTE1 0x01

const unsigned int BYTE2 = 0x02
const unsigned int BROADCAST_ID = 0xFE

int servo::get_model(void)
{
  vector <unsigned int> data;
  data.push_back(0x09);
  data.push_back(servo_id);
  data.push_back(EEP_READ_REQ);
  data.push_back(MODEL_NO1_EEP);
  data.push_back(BYTE1);
  send_data(data);
  return get_data();
}

void servo::send_data(vector<unsigned int> &data)
{
  int datalength = data.size();
  int csm1 = checksum1(data, datalength);
  int csm2 = checksum2(csm1);
  data.insert(data.begin()+0, 0xFF); 
  data.insert(data.begin()+1, 0xFF);
  data.insert(data.begin()+5, csm1); 
  data.insert(data.begin()+6, csm2);
  uart(data);
}
void servo::get_data()

int checksum1(vector<unsigned int> data,int datalength)
{
  unsigned int value_buffer=0;
  for(int count=0; count<datalength; count++)
    value_buffer = value_buffer ^ data[count];
  return (value_buffer & 0xFE);
}

int checksum2(int csm1)
{
  csm2 = (~csm1) & 0xFE;
  return csm2;
}

float scale(int input_value,int input_min,int input_max,int out_min, out_max)
{
  int input_span = input_max - input_min;
  int output_span = out_max - out_min;
  float valuescaled = float(input_value - input_min) / float(input_span);
  return out_min + (valuescaled * output_span);
}

class servo
{
private:
  int servo_id, servomodel;
  
public:
  servo(int servoid)
  {
    servo_id = servoid;
    servomodel = get_model();
  }
    int get_model();
    int get_servo_status();
    float scale(int,int,int,int);
    int checksum2(int);
    int checksum1(vector<unsigned int>,int);
};

int servo::get_servo_status(void)

{
  vector <unsigned int> data;
  data.push_back(0x09);
  data.push_back(servo_id);
  data.push_back(EEP_READ_REQ);
  data.push_back(MODEL_NO1_EEP);
  data.push_back(BYTE1);
  send_data(data);
}

int servo::torque_on(void)

{

}

int servo::torque_off(void)

{

}

int servo::get_servo_angle(void)

{

}

int servo::set_servo_angle(int goalangle,int goaltime,int led)

{

}


