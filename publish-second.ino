#include <stdlib.h>

int boardLed = D7;
int timer;
bool isWave = true;


void myHandler(const char *event, const char *data); // forward declaration

// We start with the setup function.

void setup() {
	Particle.subscribe("ext", myHandler);
	pinMode(boardLed, OUTPUT);
}

void sendEvent(){
    int time = 4; //time in seconds to send event
    delay(100);
    if(timer == (time*10)){
        if(isWave){
            Particle.publish("ext", "wave", PUBLIC);
        }
        if(!isWave){
            Particle.publish("ext", "pat", PUBLIC);
        }
        
        isWave = !isWave; //switch from pat to wave or vice versa
        timer = 0;
        return;
    }
    timer++;
}


void loop() {
    sendEvent();
}

void flashLight(int numFlashes){
    for(int i=0; i<numFlashes; i++){
        digitalWrite(boardLed, HIGH);
        delay(400);
        digitalWrite(boardLed, LOW);
        delay(400);
    }
    
}


// Now for the myHandler function, which is called when the cloud tells us that our buddy's event is published.
void myHandler(const char *event, const char *data)
{
    String dataString = String(data);

	if (dataString.compareTo("wave")==0) {
		Particle.publish("Reply", "Thanks for waving", PUBLIC);
		flashLight(3);
	}
	else if (dataString.compareTo("pat")==0) {
		Particle.publish("Reply", "Did you pat me?", PUBLIC);
		flashLight(2);
	}
	else {
	    flashLight(1);
		// if the data is something else, don't do anything.
		// Really the data shouldn't be anything but those two listed above.
	};
}