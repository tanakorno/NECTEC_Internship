#define OK        "OK"
#define ERR       "ERR"

#define AT        "AT"

#define CONAP     "CONAP"
#define SETAP     "SETAP"
#define GETIP     "GETIP"
#define ACT       "ACT"

#define UISerial Serial

void setup() {
  Serial.begin(115200);
  
  String temp = "AT+SETAP=";
  Serial.println(temp);

  parseAtCmd(temp);
}

void loop() {

}



void parseAtCmd(String atcmd) {
  
  atcmd.trim();

  int pid     = atcmd.indexOf('+');
  String at   = atcmd.substring(0, pid);
  String cmd  = atcmd.substring(pid + 1, atcmd.indexOf(' '));

  UISerial.println();
  UISerial.println(atcmd);


  // AT+
  if (not at.equals(AT)) {
    UISerial.println("missing command AT+");
    return;
  }
  

  if (cmd.equals(CONAP)) {

    UISerial.println("COOONNN");
    
  } else if (not cmd.equals(SETAP)) {

    int eid       = cmd.indexOf('=');
    int cid       = cmd.indexOf(',');
    String setap  = cmd.substring(0, eid); // |SETAP|=BS-IOT,123457890

    if (setap.equals(SETAP)) {
      String ssid = cmd.substring(eid + 1, cid);
      String pass = cmd.substring(cid + 1);

      UISerial.println(ssid);
      UISerial.println(pass == "");
    }
    
  }
}
