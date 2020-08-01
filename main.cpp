#include <ctime>
#include <sunset.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pin = 0;
int i, h;

#define code1_on "1000101111011010001100000"
#define code1_off "1000111111100100000100000"

void sendBit(int bit) {
  if(bit == 1) {
    //printf("1 Sending long.\n");
    digitalWrite(pin, HIGH);
    delayMicroseconds(975);
    digitalWrite(pin, LOW);
    delayMicroseconds(475);
  }

  if(bit == 0) {
    //printf("0 Sending short.\n");
    digitalWrite(pin, HIGH);
    delayMicroseconds(475);
    digitalWrite(pin, LOW);
    delayMicroseconds(975);
  }
}

void pulse(char codeString[], int amount) {
  for (h = 0; h < amount; h++) {
    for (i = 0; i < strlen(codeString); i++){
      char b = codeString[i];
      if(b != *"1" && b != *"0") {
        //printf("Skipping character \"%c\"\n", b);
        continue;
      }
      int bit = b - '0';
      sendBit(bit);
    }
    delayMicroseconds(1300);
  }
  //delayMicroseconds(2950);
}

#include "rc_switch_control.h" 


int main(int argc, char **argv)
{
    wiringPiSetup();
  
    RCSwitchControl rc_switch_ctrl{};
    try
    {
        while(true)
        {
            pinMode (pin, OUTPUT);
            digitalWrite(pin, LOW);
            if(rc_switch_ctrl.SwitchLight())
            {
                std::cout << "time to turn on Lights" << std::endl;
                std::cout << "yaay" << std::endl;                
                pulse(code1_on, 10);
            }
            else
            {
                std::cout << "time to turn off Lights" << std::endl;
                pulse(code1_off, 10);
            }
            std::this_thread::sleep_for(std::chrono::minutes(2)); 
        }
    }

    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
    return 1;
}