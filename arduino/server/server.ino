#include <RCSwitch.h>

RCSwitch remote = RCSwitch();
char cmdbuf[100], cmd[100], args[5][100], c; int i = 0, k = 0, offset = 0, argscnt = 0;

void setup() {
    remote.enableTransmit(10);
    Serial.begin(9600);
}

void loop() {
    if(Serial.available()) {
        c = Serial.read();
        if(c == '\n') {
            i = 0, k = 0;
            while(cmdbuf[i] != ' ') { cmd[i] = cmdbuf[i]; i++; };
            while(i < 100 && k < 5) {
                i++;
                offset = i;
                while(cmdbuf[i] != ' ' && i < 100) { args[k][i - offset] = cmdbuf[i]; i++; }
                k++;
            }
            argscnt = k;
            for(int k = 0; k < 100; k++) { cmdbuf[k] = 0; }
            i = 0;
            if(strcmp(cmd, "lights") == 0 && argscnt == 3) {
                char* groupcode = args[0];
                char* unitcode = args[1];
                char* action = args[2];
                if(strcmp(action, "on") == 0) {
                    remote.switchOn(groupcode, unitcode);
                } else if(strcmp(action, "off") == 0) {
                    remote.switchOff(groupcode, unitcode);
                }
            }
         } else {
             cmdbuf[i++] = c;
         }
     }
}
