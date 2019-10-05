#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


FPS_GT511C3 fps(4,5); 

SoftwareSerial ArduinoUno (6,7);

static int opt=0;
int att[15]={0};
int ap=0;
int idref;
void Enroll();
void EnrollTeacher();
void Clear();
void ClearAll();
void mainMenuDraw();
void drawCursor();
void operateMainMenu();
int evaluateButton(int x);
void drawInstructions();
void Attendance();




String menuItems[] = {"ATTENDANCE", "ENROLL STDNT", "ENROLL TCHR", "CLEAR ID", "CLEAR ALL"};
int readKey=A0;
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;


byte downArrow[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

byte upArrow[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};


void setup()
{
//  Wire.begin(D1,D2);
Serial.begin(9600);
ArduinoUno.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.backlight();
  delay(100);
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);   //turn on LED so fps can see fingerprint
}

void loop()
{
  
  mainMenuDraw();
  drawCursor();
  operateMainMenu();
  
 
}

void mainMenuDraw() {
  //Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}

void drawCursor() {
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
  }
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void operateMainMenu() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0: // When button returns as 0 there is no action taken
        break;
      case 1:  // This case will execute if the "forward" button is pressed
        button = 0;
        switch (cursorPosition) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.
          case 0:
            Attendance();
            break;
          case 1:
            Enroll();
            break;
          case 2:
            EnrollTeacher();
            break;
          case 3:
            Clear();
            break;
          case 4:
            ClearAll();
            break;
     
        }
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
        
                
       
    }
  }
}

int evaluateButton(int x) {
  int result = 0;
  Serial.println(x);
  if (x < 900&& x>800) { // x < 700&& x>620
    result = 1; // right
  } else if (x < 800&&x>700) { //x < 610&&x>570
    result = 2; // up
  } else if (x < 700&&x>600) { //x < 565&&x>520
    result = 3; // down
  } else if (x < 790) { //x < 500 
    result = 4; // left
  }
  return result;
}

void drawInstructions() {
  lcd.setCursor(0, 1); // Set cursor to the bottom line
  lcd.print("Use ");
  lcd.print(byte(1)); // Up arrow
  lcd.print("/");
  lcd.print(byte(2)); // Down arrow
  lcd.print(" buttons");
}


void Attendance() { 
  int activeButton = 0;
/*
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sub Menu 1");
*/
    int mast=1;
    
    while(mast){

    fps.SetLED(true);
    if (fps.IsPressFinger()){
    
    fps.CaptureFinger(false);
    int t = fps.Identify1_N();
   
    if (t<=10){
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Teacher ID");
    lcd.setCursor(3,1);
    lcd.print(t);  
    att[ap]=t;
    ap++;
    delay(2000);
    int flag=0;
    while(flag==0){
      
      lcd.clear();
      if (fps.IsPressFinger())
      {
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id <200) //<- change id value depending model you are using
        {
          
          idref=id;
          if(id==t)//id<11
          {
            flag++;
            lcd.setCursor(0,0);
            lcd.print("Att Over");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Transferring: ");
            int i;

            for (int i=0;i<ap;i++){
               ArduinoUno.write(att[i]);
              up:while(ArduinoUno.available()==0);
               char n=ArduinoUno.read();
               if(n=='n')
               continue;
              else
              goto up;
            }
            int x=235;
            ArduinoUno.write(x);
            ap=0;
            return;

              /*          
            for(i=0;i<ap;i++){             
            Serial.print(att[i]);
            Arduino.write(att[i]);            
            lcd.setCursor(0,1);
up:         while(Arduino.available()==0);
            char n=Arduino.read();
            Serial.println(n);
            continue;
            /*if(n=="n")
              continue;
            else
              goto up;    
            }
           // Arduino.write(235);
            ap=0;
            return;*/
          }
       else
          {  
          lcd.setCursor(0,0);   
          lcd.print("Verified ID:");
          lcd.setCursor(3,1);
          lcd.print(id);
          delay(1000);
          }
      }
      else
      {//if unable to recognize
      lcd.setCursor(0,0);
      lcd.print(" Error: Finger");
      lcd.setCursor(0,1);
      lcd.print(" Not Found");
      }
      }
    if(idref!=201){  
    att[ap]=idref;
    idref=201;
    ap++;  
    }
    }  
  }
  }
    }
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}


  
  
void Enroll()
{
  // Enroll test
 int activeButton = 0;
  // find open enroll id
  int enrollid = 11;
  bool usedid = true;
  yield();
  while (usedid == true)
  {    
    usedid = fps.CheckEnrolled(enrollid);
    yield();
    if (usedid==true) enrollid++;
  }
  fps.EnrollStart(enrollid);
  yield();
  // enroll
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press finger#");
  //lcd.clear();
  lcd.setCursor(3,1);
  lcd.print(enrollid);
  while(fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  yield();
  int iret = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  if (bret != false)
  {
    lcd.print("Remove finger1");
    fps.Enroll1();
    yield(); 
    while(fps.IsPressFinger() == true) delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press again");
    while(fps.IsPressFinger() == false) delay(100);
    yield();
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Remove finger2");
      fps.Enroll2();
      yield();
      while(fps.IsPressFinger() == true) delay(100);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press yet again");
      while(fps.IsPressFinger() == false) delay(100);
      yield();
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Remove finger");
        iret = fps.Enroll3();
        yield();
        if (iret == 0)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Successful");
        }
        else
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("error code:");
          lcd.setCursor(3,1);
          Serial.println(iret);
          delay(2000);
        }
      }
      else lcd.print("err 3rd finger");
    }
    else lcd.print("err 2nd finger");
  }
  else lcd.print("err 1st finger");

    while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void EnrollTeacher()
{
  // Enroll test
  int activeButton = 0;
  // find open enroll id
  int enrollid = 0;
  bool usedid = true;
  while (usedid == true)
  {
    usedid = fps.CheckEnrolled(enrollid);
    if (usedid==true) enrollid++;
  }
  
if(enrollid>=10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rsrvd space ovr");
    lcd.setCursor(0,1);
    lcd.print("CONTACT ADMIN");
    delay(2000);
    return;
    }
  
 
  fps.EnrollStart(enrollid);

  // enroll
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press finger to Enroll #");
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print(enrollid);
  while(fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  if (bret != false)
  {
    lcd.print("Remove finger");
    fps.Enroll1(); 
    while(fps.IsPressFinger() == true) delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press again");
    while(fps.IsPressFinger() == false) delay(100);
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Remove finger");
      fps.Enroll2();
      while(fps.IsPressFinger() == true) delay(100);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press yet again");
      while(fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Remove finger");
        iret = fps.Enroll3();
        if (iret == 0)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Successful");
        }
        else
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("error code:");
          lcd.setCursor(3,1);
          Serial.println(iret);
          delay(2000);
        }
      }
      else lcd.print("err 3rd finger");
    }
    else lcd.print("err 2nd finger");
  }
  else lcd.print("err 1st finger");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void Clear(){
  int activeButton = 0;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("press finger");
      lcd.setCursor(0,1);
      lcd.print("to delete");
      
      while(fps.IsPressFinger()==0);
      fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    Serial.println(id);
  fps.DeleteID(id);
  
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 4:  // This case will execute if the "back" button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
  }

void ClearAll(){
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Deleting All");
    for(int i=1;i<201;i++){
      fps.DeleteID(i);
    }
  
  }
