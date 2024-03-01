//==========================================================================//
// Copyright 2024 - 2024 YungHua-Peng                                       //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//         http://www.apache.org/licenses/LICENSE-2.0                       //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
//==========================================================================//

#include "ConstantDefinition.h"

//
// Declare the interrupt functions
//
void IRAM_ATTR ISR_Function_0(void);
void IRAM_ATTR ISR_Function_1(void);

// Declare the variables to save the time;
unsigned long Time;
unsigned long Time_temp;

void setup() {
  // Set the serial baud rate. 
  Serial.begin(Baud_Rate);

  //
  // Hardware interrupt
  // Set the pin mode of GPIO for interruption
  //
  pinMode(Interrupt_Pin_0, INPUT_PULLUP);
  attachInterrupt(Interrupt_Pin_0, ISR_Function_0, FALLING);
  pinMode(Interrupt_Pin_1, INPUT_PULLUP);
  attachInterrupt(Interrupt_Pin_1, ISR_Function_1, FALLING);

  // Save the time for debounce
  Time = millis();
}

void loop() {
  // Do nothing
}

//
// This function will be called when the Interrupt_Pin_0 has falling detected
//
void IRAM_ATTR ISR_Function_0() {
  // Check the time interval first for debounce
  Time_temp = millis();
  if ((Time_temp - Time) > Debounce_Time) {
    // Save the new time
    Time = Time_temp;

    //
    // Note that we cannot use the delay() nor Serial.println() with an interrupt
    // Use ets_printf() instead
    //
    ets_printf("ISR_Function_0 triggered!\n");
  }
}

//
// This function will be called when the Interrupt_Pin_1 has falling detected
//
void IRAM_ATTR ISR_Function_1() {
  // Check the time interval first for debounce
  Time_temp = millis();
  if ((Time_temp - Time) > Debounce_Time) {
    // Save the new time
    Time = Time_temp;

    //
    // Note that we cannot use the delay() nor Serial.println() with an interrupt
    // Use ets_printf() instead
    //
    ets_printf("ISR_Function_1 triggered!\n");
  }
}