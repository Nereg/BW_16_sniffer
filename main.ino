#include <wifi_conf.h>
//have to undefine these arduino definss for the RTL std library
#undef max
#undef min
#define SCAN_CHANNEL_NUM 2 //2.4GHz + 5GHz

void setup() {
  //Initialize serial and wait for port to open:
  //    pinMode(PA12, OUTPUT);
  //    digitalWrite(PA12, LOW);
  //    pinMode(PB3, OUTPUT);
  //    digitalWrite(PB3, HIGH);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  wifi_on(RTW_MODE_PROMISC);
  wifi_enter_promisc_mode();
  wifi_set_promisc(RTW_PROMISC_ENABLE_2, promisc_callback, 0);
}

/*  Make callback simple to prevent latency to wlan rx when promiscuous mode */
static void promisc_callback(unsigned char *buf, unsigned int len, void* userdata)
{
  const ieee80211_frame_info_t *frameInfo = (ieee80211_frame_info_t *)userdata;
  printMac(frameInfo->bssid);
//  Serial.print("\n");
  Serial.print("BUF: ");
  for (int i = 0; i<len/sizeof(buf[0]); i++) Serial.print(buf[i], HEX);
  Serial.print("\n");
//  //    if(frameInfo->i_addr1[0] == 0xff && frameInfo->i_addr1[1] == 0xff && frameInfo->i_addr1[2] == 0xff && frameInfo->i_addr1[3] == 0xff && frameInfo->i_addr1[4] == 0xff && frameInfo->i_addr1[5] == 0xff)
//  //        return;
//  if (frameInfo->rssi == 0)
//    return;
//  WiFiSignal wifisignal;
//  wifisignal.rssi = frameInfo->rssi;
//  memcpy(&wifisignal.addr, &frameInfo->i_addr2, 6);
//
//
//  std::list<WiFiSignal>::iterator next = _signals.begin();
//  while (next != _signals.end())
//  {
//    if (next->addr[0] == wifisignal.addr[0] &&
//        next->addr[1] == wifisignal.addr[1] &&
//        next->addr[2] == wifisignal.addr[2] &&
//        next->addr[3] == wifisignal.addr[3] &&
//        next->addr[4] == wifisignal.addr[4] &&
//        next->addr[5] == wifisignal.addr[5]
//       )
//      _signals.erase(next);
//    next++;
//  }
//  _signals.push_back(wifisignal);
}

void loop()
{
  
}

void printMac(const unsigned char mac[6]) {
  for (u8 i = 0; i < 6; i ++) {
    Serial.print(mac[i], HEX);
    Serial.print(":");
  }
}
