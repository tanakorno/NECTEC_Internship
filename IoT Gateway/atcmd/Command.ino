// String.indexOf()
#define NotFound   -1

#define OK          "OK"
#define ERR         "ERR"

#define ARROWUP     ''
#define COMMA       ','
#define PLUS        '+'
#define EQUAL       '='

#define CMD         "AT"

#define HELP        "HELP"
#define GETAP       "GETAP"
#define SETAP       "SETAP"
#define SCANAP      "SCANAP"
#define CONAP       "CONAP"
#define DISAP       "DISAP"
#define GETIP       "GETIP"
#define APSTAT      "APSTAT"

#define ACT         "ACT"
#define SENSOR      "SNR"

#define SETCLOUD    "SETCLOUD"
#define CLOUDSTAT   "CLOUDSTAT"

bool actCloud = true;

void parseAtCmd(String atcmd) {

  atcmd.trim();

  int pid     = atcmd.indexOf(PLUS);
  String at   = atcmd.substring(0, pid);
  String cmd  = atcmd.substring(pid + 1);
  at.trim();
  cmd.trim();

  CMDSerial.println("");
  CMDSerial.println(atcmd);

  if (not at.equals(CMD)) {
    CMDSerial.print("missing command ");
    CMDSerial.print(CMD);
    CMDSerial.print("+");
    CMDSerial.println("");
    return;
  }

  if (cmd.equals(HELP)) {


  } else if (cmd.equals(GETAP)) {

    String ssid = getSsid();
    String pass = getPass();
    CMDSerial.print("ssid: "); CMDSerial.println(ssid);
    CMDSerial.print("password: "); CMDSerial.println(pass);

  } else if (cmd.startsWith(SETAP)) {

    int eid     = cmd.indexOf(EQUAL);
    int cid     = cmd.indexOf(COMMA);
    String str  = cmd.substring(0, eid);
    str.trim();

    if (eid == NotFound)  {
      printMissing(str, EQUAL);
    } else if (str.equals(SETAP)) {
      String ssid = cmd.substring(eid + 1, cid);
      String pass = cmd.substring(cid + 1);
      ssid.trim();
      pass.trim();
      setAP(ssid, pass);
    } else {
      printUnknown(cmd);
    }

  } else if (cmd.equals(SCANAP)) {

    scanWiFi();

  } else if (cmd.equals(CONAP)) {

    connectWiFi(getSsid(), getPass());

  } else if (cmd.equals(DISAP)) {

    disconnectWiFi();

  } else if (cmd.equals(GETIP)) {

    getIp();

  } else if (cmd.equals(APSTAT)) {

    getApStat();

  } else if (cmd.equals(ACT)) {

    writeHWSerial(cmd);

  } else if (cmd.startsWith(SENSOR)) {

    int eid     = cmd.indexOf(EQUAL);
    String str  = cmd.substring(0, eid);
    str.trim();

    if (eid == NotFound)  {
      printMissing(str, EQUAL);
    } else if (str.equals(SENSOR)) {
      String param = cmd.substring(eid + 1);
      param.trim();
      writeHWSerial(param);
    } else {
      printUnknown(cmd);
    }

  } else if (cmd.equals(CLOUDSTAT)) {

    CMDSerial.print(actCloud ? "enable" : "disable");
    CMDSerial.println(" send data from sensor to cloud");


  } else if (cmd.startsWith(SETCLOUD)) {

    int eid     = cmd.indexOf(EQUAL);
    String str  = cmd.substring(0, eid);
    str.trim();
    
    if (eid == NotFound)  {
      printMissing(str, EQUAL);
    } else if (str.equals(SETCLOUD)) {
      String param = cmd.substring(eid + 1);
      param.trim();
      if (param == "ENABLE" or param == "TRUE") {
        actCloud = true;
        CMDSerial.println(OK);
      } else if (param = "DISABLE" or param == "FALSE") {
        actCloud = false;
        CMDSerial.println(OK);
      } else {
        printUnknown(param);
      }
    } else {
      printUnknown(cmd);
    }

  } else {
    printUnknown(cmd);
  }

}

void printUnknown(String cmd) {
  CMDSerial.print("AT + : ");
  CMDSerial.print(cmd);
  CMDSerial.println(": unknown command");

  CMDSerial.println("I'm sorry, I'm afraid I can't let you do that.");
}

void printMissing(String str, char sym) {
  CMDSerial.print(str);
  CMDSerial.print(": missing ");
  CMDSerial.print(sym);
  CMDSerial.println(" identifier");
}

