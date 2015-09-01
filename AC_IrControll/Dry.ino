#ifdef COMMANDDRY 
void Cmd_dry(){
  Serial.println("#Dry command interpreter");
  int temp;
  char *arg;
  arg = SCmd.next(); 
  if (arg != NULL){
    temp=atoi(arg);
  }else{
    Serial.println("#Temperature missing");
    ParseResult(-5);
    return ;
  }
  ParseResult(Cmd_Dry_Temp(temp));
}
#endif
