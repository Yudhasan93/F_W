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
               }
            //    else if (lastButtonState == LOW && currentButtonState == HIGH && EPT== LOW)
            //    {}
               else if (EPT == LOW)
               {
                   ALL_OFF();
                   Serial.println("SEMUA MATI");
               }
               
            lastButtonState = currentButtonState;
            Serial.print("UV State = ");
            Serial.println(uv_State);
            statusChanged = true;
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