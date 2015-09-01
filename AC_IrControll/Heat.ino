#ifdef COMMANDHEAT
int Cmd_Heat_Fan_Temp(int fan, int temp){
  if(fan<0){ return -3; }
  if(fan>4){ return -4; }   
  
       if(fan==0){ return Cmd_Heat_Fan0_Temp(temp); }
  else if(fan==1){ return Cmd_Heat_Fan1_Temp(temp); }
  else if(fan==2){ return Cmd_Heat_Fan2_Temp(temp); }
  else if(fan==3){ return Cmd_Heat_Fan3_Temp(temp); }
  else if(fan==4){ return Cmd_Heat_Fan4_Temp(temp); }
}

void Cmd_heat(){
  Serial.println("#Heat command interpreter");
  int fan;
  int temp;
  char *arg;
  arg = SCmd.next(); 
  if (arg != NULL){
    temp=atoi(arg);
  }else{
    Serial.println("#Temperature [and fan] missing");
    ParseResult(-5);
    return ;
  }
  arg = SCmd.next(); 
  if (arg != NULL){
    fan=atoi(arg);
  }else{
    fan=3;
  }
  ParseResult(Cmd_Heat_Fan_Temp(fan,temp));
}
#endif
