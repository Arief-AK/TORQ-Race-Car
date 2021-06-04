/******************************************************************************
*                                                                             *
*   Program : TORQ_RACE_CAR                                                      *
*                                                                             *
*   FILE : torq_beta.ino                                                      *
*                                                                             *
*   Date : 1 / 06 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "hardwareInterface.h"

#define MAX_SPEED 500
#define DEFAULT_SPEED 180
#define TURNING_SPEED 160
#define OBSTACLE_SPEED 120
#define UP_HILL_SPEED 300
#define DOWN_HILL_SPEED 30

const int threshold = 22;

int turning_angle = 8;

int current_speed = 0;

int long_counter = 0;
 
int last_condition = FRONT; //BY DEFAULT SET TO FRONT TO ROTATE BY DEFAULT ALGHORITHIM

int obstacle_trigger = 0; //GLOBAL VARIABLE TO TRACK OBSTACLE CHECKS

int exit_trigger = 0;


HardwareInterface hardwareInterface(
        13, A3, //Ultrasonic_LEFT
        8, 12, //Ultrasonic_RIGHT
        
        A1, 0, //Infrared_LEFT
        A5, 0, //Infrared_RIGHT
        A4, 0,  //Infrared_FRONT
        
        6, 5, //ENGINE
        4,
        
        3 // SERVO
        );

//INIT
void setup()
{ 
  hardwareInterface.driveShaft.p_mainMotor.init();
  hardwareInterface.driveShaft.p_servoMotor.init(); 
  
  hardwareInterface.sensorPanel.Ultrasonic_LEFT.init();
  hardwareInterface.sensorPanel.Ultrasonic_RIGHT.init();

  hardwareInterface.sensorPanel.Infrared_LEFT.init();
  hardwareInterface.sensorPanel.Infrared_RIGHT.init();
  hardwareInterface.sensorPanel.Infrared_FRONT.init();
  
  Serial.begin(9600);
  
  hardwareInterface.driveShaft.powerStart();
}

void loop() // THE ONE AND THE ONLY RUNNING LOOP, STANDARD ONE
{
  Serial.print("\n");
  Serial.print("0-LEFT | 1-RIGHT | 2-FRONT : ");
  Serial.print(last_condition);
//  // RAMP CASE
//  if(hardwareInterface.sensorPanel.Ultrasonic_RIGHT.get_distance() < 40 && hill_tigger == 0)
//  {
//    hardwareInterface.driveShaft.moveForward(1000);
//    delay(2000);
//    hardwareInterface.driveShaft.p_mainMotor.stopMovement();
//    delay(500);
//    hardwareInterface.driveShaft.powerStart();
//    delay(500);
//
//    hill_trigger++;
//  }

  // Ultrasonic distance check if it is below threshold, avoid obstacle
  if(hardwareInterface.sensorPanel.Ultrasonic_LEFT.get_distance() < threshold && obstacle_trigger == 0)
  {
    // OBJECT CASE 
    if(hardwareInterface.sensorPanel.Ultrasonic_LEFT.get_distance() < threshold)
    {
      Serial.print("Object is detected\n");
      Serial.print("LUS:");
      Serial.print(hardwareInterface.sensorPanel.Ultrasonic_LEFT.get_distance());
    
      obstacle_trigger = 1;
      
      hardwareInterface.driveShaft.stopMovement();
      hardwareInterface.driveShaft.p_mainMotor.rotate_anti_clockwise();
      delay(1050);
      
      hardwareInterface.driveShaft.turnRight(500, 15);
      delay(750);
      hardwareInterface.driveShaft.turnRight(TURNING_SPEED, 12);
      delay(600);
      hardwareInterface.driveShaft.turnLeft(TURNING_SPEED, 14);
      delay(1000);
      hardwareInterface.driveShaft.moveForward(120);
      delay(800);
      hardwareInterface.driveShaft.moveForward(90);
      delay(350);

      current_speed = DEFAULT_SPEED;
      last_condition = FRONT;
    }
  }
  else
  {   
    if(hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH)
    {
      hardwareInterface.driveShaft.p_mainMotor.rotate_anti_clockwise();
      delay(850);
      hardwareInterface.driveShaft.stopMovement();
    }
    else
    {
    // NORMAL ALIGNING CONDITION 
    if (last_condition == FRONT)
    { 
      if (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH)
      {
        if (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH) 
        {
          current_speed = TURNING_SPEED;
          
          Serial.print("\n");
          Serial.print("STATE: ");
          Serial.print(last_condition);
          
          hardwareInterface.driveShaft.turnLeft(current_speed, 8);
          
          last_condition = SLEFT;
        }
        else if (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH)
        {
          current_speed = TURNING_SPEED;
          
          Serial.print("\n");
          Serial.print("STATE: ");
          Serial.print(last_condition);
          
          hardwareInterface.driveShaft.turnRight(current_speed, 8);
          
          last_condition = SRIGHT;
        }
        else
        {
          current_speed = DEFAULT_SPEED;
          Serial.print("\n");
          Serial.print("STATE: ");
          Serial.print(last_condition);
          hardwareInterface.driveShaft.moveForward(current_speed);
        }
      }
      else
      {
        if(hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH)
        {
          current_speed = TURNING_SPEED;
          
          Serial.print("\n");
          Serial.print("STATE: ");
          Serial.print(last_condition);
          
          hardwareInterface.driveShaft.turnLeft(current_speed, 12);
          
          last_condition = LEFT;
        }
        else if(hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH)
        {
          current_speed = TURNING_SPEED;
          
          Serial.print("\n");
          Serial.print("STATE: ");
          Serial.print(last_condition);
          
          hardwareInterface.driveShaft.turnRight(current_speed, 12);
          
          last_condition = RIGHT;
        }
      }
    }
    else //states exeptions
    {
      if (last_condition == LEFT) // exeption for long left turning condition
      {
        if(exit_trigger == 0)
        {
          hardwareInterface.driveShaft.stopMovement();
          exit_trigger++;
          delay(100);
        }
        
        //long_counter++;
        current_speed = TURNING_SPEED ;
        
        while(turning_angle <= 18)
        {
          
        hardwareInterface.driveShaft.turnLeft(current_speed, turning_angle);
          turning_angle++;
        }
        
        //hardwareInterface.driveShaft.turnLeft(current_speed, turning_angle);
        Serial.print("\nI am here (1)\n");
        Serial.print("STATE: ");
        Serial.print(last_condition);
        if((hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH || hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH) || (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH) )
        {
          turning_angle = 1;
          obstacle_trigger = 0;
          exit_trigger = 0;
          last_condition = FRONT;
        }
      }
      
      if(last_condition == RIGHT) // exeption for long right turning condition
      {
        if(exit_trigger == 0)
        {
          hardwareInterface.driveShaft.stopMovement();
          exit_trigger++;
          delay(100);
        }
        
        //long_counter++;
        current_speed = TURNING_SPEED ;

        while(turning_angle <= 18)
        {
          hardwareInterface.driveShaft.turnRight(current_speed, turning_angle);
          turning_angle++;
        }
        
        //hardwareInterface.driveShaft.turnRight(current_speed, turning_angle);
        Serial.print("\nI am here (2)\n");
        Serial.print("STATE: ");
        Serial.print(last_condition);
        
        if((hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH || hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH) || (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH))
        {
          turning_angle = 1;
          obstacle_trigger = 0;
          exit_trigger = 0;
          last_condition = FRONT;
        }
      }

      if(last_condition == SLEFT) // exeption for slightly left turning condition
      {
        current_speed = TURNING_SPEED ;

        if (hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == LOW && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == LOW && hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == LOW)
        {
          while(turning_angle <= 18)
          {
            hardwareInterface.driveShaft.turnLeft(current_speed, turning_angle);
            turning_angle++;
          }
        }
        else
        {
          while(turning_angle <= 6)
          {
            hardwareInterface.driveShaft.turnLeft(current_speed, turning_angle);
            turning_angle++;
          }
        }
                
        if((hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH || hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH) || (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == HIGH))
        {
          turning_angle = 1;
          obstacle_trigger = 0;
          last_condition = FRONT;
        }
      }

      if(last_condition == SRIGHT) // exeption for slightly right turning condition
      {
        current_speed = TURNING_SPEED ;

        if (hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == LOW && hardwareInterface.sensorPanel.Infrared_RIGHT.read_pin() == LOW && hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == LOW)
        {
          while(turning_angle <= 18)
          {
            hardwareInterface.driveShaft.turnRight(current_speed, turning_angle);
            turning_angle++;
          }
        }
        else
        {
          while(turning_angle <= 6)
          {
            hardwareInterface.driveShaft.turnRight(current_speed, turning_angle);
            turning_angle++;
          }
        }
                
        if((hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH || hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH) || (hardwareInterface.sensorPanel.Infrared_FRONT.read_pin() == HIGH && hardwareInterface.sensorPanel.Infrared_LEFT.read_pin() == HIGH))
        {
          turning_angle = 1;
          obstacle_trigger = 0;
          last_condition = FRONT;
        }
      }
    }
   }
  } // Comment me if you dont have an ultrasonic sensor
}
