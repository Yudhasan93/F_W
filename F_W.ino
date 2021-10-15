                        /********WATER FOUNTAIN BARDI **********/

#define BUTTON 13           //AKTIF LOW
#define LED_BIRU 16         //AKTIF LOW
#define UV 5                //AKTIF HIGH
#define EPT_SENSOR  14      /*https://www.eptsensor.com/photoelectric-sensor/photoelectric-proximity-sensor.html*/
#define PUMP 4              //AKTIF HIGH
const int DEBOUNCE_DELAY = 100;

int lastButtonState = LOW;
int lastFlickerState = LOW;
int currentButtonState;
int EPT;
char bacadata;

unsigned long lastDebounceTime = 0;

boolean statusChanged = false;
boolean uv_State = false;
boolean pump_State = false;

void setup(){
    Serial.begin(9600);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(EPT_SENSOR, INPUT);

    pinMode(LED_BIRU, OUTPUT);
    pinMode(UV, OUTPUT);
    pinMode(PUMP, OUTPUT);
    digitalWrite(LED_BIRU, HIGH);

    currentButtonState = digitalRead(BUTTON);
}


void loop(){
    if(Serial.available()){
        bacadata = Serial.read();
        if(bacadata == 'A'){bacadata=1;}
        if(bacadata == 'B'){bacadata=2;}
        if(bacadata == 'C'){bacadata=3;}
        if(bacadata == 'D'){bacadata=4;}
    }

    if (bacadata == 1){toggleUV();}
    if (bacadata == 2){UV_OFF();}
    if (bacadata == 3){togglePUMP();}
    if (bacadata == 4){PUMP_OFF();}
        
    EPT = digitalRead(EPT_SENSOR);
    currentButtonState = digitalRead(BUTTON);
    // Serial.println(EPT);
    if(currentButtonState != lastFlickerState){
        lastDebounceTime = millis();
        lastFlickerState = currentButtonState;
    }

    if((millis() - lastDebounceTime) > DEBOUNCE_DELAY){

           if(lastButtonState == HIGH && currentButtonState == LOW && EPT== HIGH){
               Serial.println("SEMUA MENYALA");          
               togglePUMP();
               toggleUV();
               Serial.print("PUMP STATE = ");
               Serial.println(pump_State);
               statusChanged = true;
               }
               else if(pump_State == false && currentButtonState == LOW){
                Serial.println("SEMUA MATI");
               }
               else if (EPT == LOW)
               {
                   ALL_OFF();
                   Serial.println("AIR KURANG");
                   delay(500);
                   statusChanged = false;
               }
               
            lastButtonState = currentButtonState;
    }
    
    
    
}

void ALL_ON(){
    PUMP_ON();
    UV_ON();
}

void ALL_OFF(){
    PUMP_OFF();
    UV_OFF();
}

void PUMP_ON(){
    digitalWrite(PUMP, HIGH);
    pump_State = true;
}

void PUMP_OFF(){
    digitalWrite(PUMP, LOW);
    pump_State = false;
}

void UV_ON(){
    digitalWrite(UV, HIGH);
    uv_State = true;
}

void UV_OFF(){
    digitalWrite(UV, LOW);
    uv_State = false;
}

void toggleUV(){
    if(uv_State){UV_OFF();}
    else{UV_ON();}
}

void togglePUMP(){
    if(pump_State){PUMP_OFF();}
    else{PUMP_ON();}
}

void toogleALL(){
    togglePUMP();
    toggleUV();
}