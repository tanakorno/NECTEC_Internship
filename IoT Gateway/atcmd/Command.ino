// String.indexOf()
#define NotFound   -1

#define OK          "OK"
#define ERR         "ERR"

#define PLUS        '+'
#define EQUAL       '='
#define QUEST       '?'
#define COMMA       ','

#define AT          "AT"

#define HELP        "HELP"
#define GETAP       "GETAP"
#define SETAP       "SETAP"
#define SCANAP      "SCANAP"
#define CONAP       "CONAP"
#define DISAP       "DISAP"
#define GETIP       "GETIP"
#define STATAP      "STATAP"

#define ACT         "ACT"
#define SENSOR      "SNR"

#define GETCLD      "GETCLD"
#define SETCLD      "SETCLD"
#define ACTCLD      "ACTCLD"
#define STATCLD     "STATCLD"

bool actCloud = true;

void parser(String atcmd) {

  CMDSerial.println("");
  CMDSerial.println(atcmd);

  int     pid     = atcmd.indexOf(PLUS);
  int     eid     = atcmd.indexOf(EQUAL);

  String  at      = atcmd.substring(0, pid);
  String  cmd     = atcmd.substring(pid + 1, eid);
  String  params  = atcmd.substring(eid + 1 );

  at.trim();
  cmd.trim();
  params.trim();

  if (not at.equals(AT) or pid == NotFound) {
    printUnknown(atcmd);
    return;
  }

  if (cmd.equals(HELP)) {

    CMDSerial.println("at command syntax: AT+<CMD> - <CMD> list: ");
    CMDSerial.println("1.  GETAP               - display ssid and password           ");
    CMDSerial.println("2.  SETAP=<SSID>,<PASS> - set ssid and password               ");
    CMDSerial.println("3.  SCANAP              - scan for ap                         ");
    CMDSerial.println("4.  CONAP               - connect to ap                       ");
    CMDSerial.println("5.  DISAP               - disconnect from ap                  ");
    CMDSerial.println("6.  STATAP              - display connected ap and ip         ");
    CMDSerial.println("7.  SNR=<STRING>        - send <STRING> to sensor module      ");
    CMDSerial.println("8.  GETCLD              - display cloud url                   ");
    CMDSerial.println("9.  SETCLD=<URL>        - set cloud url                       ");
    CMDSerial.println("10. ACTCLD=<MODE>       - <MODE>=<ON>/<OFF> send data to cloud");
    CMDSerial.println("11. STATCLD             - display cloud mode                  ");

  } else if (cmd.equals(GETAP)) {

    CMDSerial.print("ssid: ");
    CMDSerial.println(getSsid());
    CMDSerial.print("password: ");
    CMDSerial.println(getPass());

  } else if (cmd.equals(SETAP)) {

    if (eid == NotFound) {
      printMissing(cmd, EQUAL);
      return;
    }

    int cid = params.indexOf(COMMA);
    String ssid = params.substring(0, cid);
    String pass = params.substring(cid + 1);
    ssid.trim();
    pass.trim();
    setAP(ssid, pass);

  } else if (cmd.equals(SCANAP)) {

    scanWiFi();

  } else if (cmd.equals(CONAP)) {

    connectWiFi(getSsid(), getPass());

  } else if (cmd.equals(DISAP)) {

    disconnectWiFi();

  } else if (cmd.equals(GETIP)) {

    getIp();

  } else if (cmd.equals(STATAP)) {

    getApStat();

  } else if (cmd.equals(SENSOR)) {

    if (eid == NotFound) {
      printMissing(cmd, EQUAL);
      return;
    }

    writeHWSerial(params);

  } else if (cmd.equals(GETCLD)) {

    CMDSerial.print("cloud url: ");
    CMDSerial.println(getCloud());

  } else if (cmd.equals(SETCLD)) {

    if (eid == NotFound) {
      printMissing(cmd, EQUAL);
      return;
    }

    setCloud(params);

  } else if (cmd.equals(STATCLD)) {

    CMDSerial.print(actCloud ? "ON: enable" : "OFF: disable");
    CMDSerial.println(" send data to cloud");

  } else if (cmd.equals(ACTCLD)) {

    if (eid == NotFound) {
      printMissing(cmd, EQUAL);
      return;
    }

    actCloud = params == "ON";
    CMDSerial.println(OK);

  } else {

    printUnknown(atcmd);

  }
}

void printUnknown(String atcmd) {
  CMDSerial.print(atcmd);
  CMDSerial.println(": unknown command");
}

void printMissing(String str, char sym) {
  CMDSerial.print(str);
  CMDSerial.print(": missing ");
  CMDSerial.print(sym);
  CMDSerial.println(" identifier");
}


