
#ifdef COMMANDOFF
/* OFF */
const PROGMEM unsigned int Signal_OFF_0[] = {349,636,17800,3052,8916,548,448,548,1440,552,444,552,444,552,440,556,440,552,448,548,444,552,444,548,1440,556,444,548,472,524,1464,524,1468,472,520,520,1472,548,1444,548,1440,552,1440,548,1440,552,448,548,444,552,444,548,448,548,448,548,468,528,468,528,472,468,524,468,528,548,448,548,444,552,444,556,440,552,440,556,440,556,444,548,448,548,444,552,444,548,448,548,448,552,444,548,472,524,472,524,468,468,528,472,524,544,448,552,444,556,440,552,444,552,444,552,444,548,1440,548,1440,556,2944,3024,8916,552,1440,552,468,524,472,524,472,468,524,472,528,520,476,544,448,552,444,548,1440,552,444,548,444,556,1436,552,444,552,1440,548,1440,556,1464,524,1464,472,1516,520,1472,548,448,552,444,552,444,548,444,552,444,552,444,552,444,552,444,552,444,548,444,552,448,544,452,544,472,524,476,516,476,468,528,488,504,548,448,552,444,548,444,556,440,556,444,548,444,552,444,552,444,548,444,552,448,544,452,548,444,552,472,524,468,524,472,472,520,472,524,520,476,548,448,552,2916,3056,8912,552,1436,556,444,548,444,552,444,556,440,552,440,556,444,552,444,548,452,544,1464,524,472,472,520,496,1496,548,1444,552,1436,556,1436,552,440,556,1436,552,1440,552,1440,552,1440,548,1468,520,1468,472,1516,552,1436,556,444,552,444,548,444,556,1436,552,1436,556,1436,552,444,552,448,548,448,548,472,524,464,528,472,468,528,472,520,548,448,548,1440,556,1436,552,444,552,1440,548,1440,552,444,552,444,552,444,548,452,544,472,524,468,524,472,472,524,472,520,520,1472,528,1464,552};

void Cmd_off(){ 
  Serial.println("#Processing off command");
  ParseResult(sendBatch(Signal_OFF_0)); 
}
#endif

void ParseResult(int r){
  Serial.print("Result:");
  if(r==0){         Serial.print("OK"); }
  else if(r==-1) {  Serial.print("Err:-1:TempTooLow");    }
  else if(r==-2) {  Serial.print("Err:-2:TempTooHigh");   }
  else if(r==-3) {  Serial.print("Err:-3:FanTooLow");     }
  else if(r==-4) {  Serial.print("Err:-4:FanTooHigh");    }
  else if(r==-5) {  Serial.print("Err:-5:MissingRequiredParams");    }
  else if(r==-6) {  Serial.print("Err:-6:UnknownCommand");    }
  Serial.println();
}

void Cmd_unknown(){
  Serial.println("#Uknown Command, try ? or help!");
  ParseResult(-6);
}

void Cmd_test(){
  if(TestMode==0){
    TestMode=1;
    Serial.println("#TestMode:ON");
    ParseResult(0);
    delay(1000);
    return;
  }else{
    TestMode=0;
    Serial.println("#TestMode:OFF");
    ParseResult(0);
    delay(1000);
    return;
  }
}

#define COMMANDOFF 1
// #define COMMANDCOOL  1
// #define COMMANDHEAT  1
// #define COMMANDDRY   1
// #define COMMANDAUTO  1
// #define COMMANDFAN   1
// #define COMMANDOFF   1
// #define COMMANDTEST  1

void Cmd_HELP(){
  Serial.println("# Help:");
#ifdef COMMANDOFF
  Serial.println("# off |OFF |o");
#endif

#ifdef COMMANDHEAT
  Serial.println("# heat|HEAT|h <temp> <fan=4>");
#endif

#ifdef COMMANDCOOL
  Serial.println("# cool|COOL|c <temp> <fan=4>");
#endif
  
#ifdef COMMANDFAN  
  Serial.println("# fan |FAN |f <fan>");
#endif

#ifdef COMMANDDRY 
  Serial.println("# dry |DRY |d <temp>");
#endif

#ifdef COMMANDAUTO
  Serial.println("# auto|AUTO|a <temp>");
#endif

  Serial.println("# help|HELP|? ");
#ifdef COMMANDTEST
#ifdef COMMANDOFF
  Serial.println("# test|TEST|t - Toggle test mode (sends off every 1.5s)");
#endif
#endif
}

