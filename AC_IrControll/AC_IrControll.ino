
#define DEBUGUNCODE  0

/* Compile only what commands you need */
#define COMMANDTEST   1
#define COMMANDOFF    1
#define COMMANDCOOL   1
// #define COMMANDHEAT   1
#define COMMANDDRY    1
#define COMMANDAUTO   1
#define COMMANDFAN    1
#define COMMANDOFF    1

#define MAX_SEND_BUFFER 351

#include <avr/pgmspace.h>
#include <IRremote.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>

SerialCommand SCmd;

IRsend irsend;
int counter;

byte TestMode;

const unsigned int KHZ = 38;

unsigned int sendbuffer[MAX_SEND_BUFFER];

int sendBatch(const unsigned int* Storage){
  unsigned int Size;
  Size = pgm_read_word_near(Storage);
  Size = min(Size,MAX_SEND_BUFFER);
  //unsigned int* sendbuffer=0;
  //sendbuffer=(unsigned int*)malloc(Size * sizeof(unsigned int));
  for(counter=0;counter<Size;counter++){
    sendbuffer[counter]=pgm_read_word_near(Storage+counter+1);
    #ifdef DEBUGUNCODE
    Serial.print(counter);
    Serial.print(" - ");
    Serial.println(sendbuffer[counter]);
    #endif
  }  
  #ifdef DEBUGUNCODE
    Serial.print("Sending ");
    Serial.print(Size);
    Serial.println(" array elements");
  #endif
  irsend.sendRaw(sendbuffer, Size, KHZ);
  return 0;
}

void setup()
{
  Serial.begin(115200);

  TestMode=0;

#ifdef COMMANDOFF
  SCmd.addCommand("OFF",               Cmd_off     );
  SCmd.addCommand("off",               Cmd_off     );
  SCmd.addCommand("o"  ,               Cmd_off     );
#endif

#ifdef COMMANDCOOL  
  SCmd.addCommand("COOL",              Cmd_cool    );
  SCmd.addCommand("cool",              Cmd_cool    );
  SCmd.addCommand("c"   ,              Cmd_cool    );
#endif

#ifdef COMMANDHEAT
  SCmd.addCommand("heat",              Cmd_heat    );
  SCmd.addCommand("HEAT",              Cmd_heat    );
  SCmd.addCommand("h"   ,              Cmd_heat    );
#endif

#ifdef COMMANDDRY
  SCmd.addCommand("dry",               Cmd_dry     );
  SCmd.addCommand("DRY",               Cmd_dry     );
  SCmd.addCommand("d"  ,               Cmd_dry     );
#endif

#ifdef COMMANDAUTO
  SCmd.addCommand("auto",              Cmd_auto    );
  SCmd.addCommand("AUTO",              Cmd_auto    );
  SCmd.addCommand("a"   ,              Cmd_auto    );
#endif

#ifdef COMMANDFAN
  SCmd.addCommand("fan",               Cmd_fan     );
  SCmd.addCommand("FAN",               Cmd_fan     );
  SCmd.addCommand("f"  ,               Cmd_fan     );
#endif

  SCmd.addCommand("help",              Cmd_HELP    );
  SCmd.addCommand("HELP",              Cmd_HELP    );
  SCmd.addCommand("?"   ,              Cmd_HELP    );

#ifdef COMMANDOFF
#ifdef COMMANDTEST
  SCmd.addCommand("TEST",              Cmd_test    );
  SCmd.addCommand("test",              Cmd_test    );
  SCmd.addCommand("t"   ,              Cmd_test    );
#endif
#endif

  SCmd.addDefaultHandler(Cmd_unknown);

  Serial.println("#Ready");
}

void loop(){  
  SCmd.readSerial(); 
#ifdef COMMANDOFF
#ifdef COMMANDTEST
  if(TestMode==1){
    Cmd_off();
    delay(1500);
  }
#endif
#endif
}
