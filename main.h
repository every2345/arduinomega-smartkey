#include <Keypad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 24, 4); 

//Bạn có thể tham khảo thêm tại: https://github.com/Chris--A/Keypad/blob/master/examples/HelloKeypad/HelloKeypad.ino
 
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
 
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 
byte rowPins[rows] = {14, 15, 16, 17}; //Cách nối chân với Arduino //Hàng
byte columnPins[columns] = {7, 6, 5, 4}; //Cột
 
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
//Word string
void setup()
{
  pinMode(8, OUTPUT); //Kèn báo
  pinMode(9, OUTPUT);// led xanh
  pinMode(10, OUTPUT);// ro le
  Serial.begin(9600);//bật serial, baudrate 9600

}

char pass[4] = {'5', '5', '5'};
char input[4];
int citem = 0;
int item = 0;
int itemstring1 = 0;
int itemstring2 = 0;
int itemstring3 = 0;
int countdown = 3;
int warning = 0;

void loop() {  
  //Banner chao mung
  itemstring3++;
  if(itemstring3 == 1)
  {  
    String myString1 = "----Welcome!---\n";
    Serial.print(myString1); 
    lcd.init();                    
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("arduino 01 ftptithcm");
    lcd.setCursor(0,1);
    lcd.print("  -ELECTRONIC KEY-");
    lcd.setCursor(0,2);
    lcd.print("     Ver: 0.1.0");    
    lcd.setCursor(0,3);  
    lcd.print("     Loading...");   
    delay(2000);
  }    
  itemstring2++;
  if(itemstring2 == 1)
  {  
    String myString1 = "----Welcome!---\n";
    Serial.print(myString1); 
    lcd.init();                    
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("*^----Welcome!----^*");
    lcd.setCursor(0,1);
    lcd.print("Nguyen Phuc");
    lcd.setCursor(0,2);
    lcd.print("Nguyen Khanh Toan");
    lcd.setCursor(0,3);
    lcd.print("Nguyen Phuc Thinh");    
    delay(3000);
  }
  //tao mat khau
  itemstring1++;
  if(itemstring1 == 1)
  {  
    lcd.clear();  
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("---Electronic key---");
    lcd.setCursor(0,1);
    lcd.print("Enter password:");   
       
    String myString = "Nhap mat khau: ";
    Serial.print(myString); 
  }

//Nhap mat khau  
  char key = keypad.getKey();
  if(key != NULL)
  {
    input[item] = key;
    item++;        
    

    lcd.setCursor(item -1,2);    
    lcd.print("*");
  
    
    Serial.print(key);
    //Khu vuc nhap mat khau
    if(item == 3)    
    {      
      if(strcmp(input, pass) == 0)
        {
          lcd.setCursor(0,1);
          lcd.print(" *Correct password*");   
          lcd.setCursor(0,2);   
          lcd.print("   ACCESS GRANTED");    
          lcd.setCursor(0,3);
          lcd.print("!Auto lock after 6s!");   

          Serial.println("\nMat khau dung, chao mung!");  
            
          item = 0;
          
          warning = 0;
          countdown = 3;
          itemstring1 = 0;
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          delay(6000);         
          lcd.setCursor(0,0);
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);          

        }    
       else
        {
          item = 0;
          itemstring1 = 0;
          warning++;
          if(warning < 3)   
          {
           countdown--;
           lcd.setCursor(0,1);
           lcd.print("  *Wrong password*");   
           lcd.setCursor(0,2);   
           lcd.print("   ACCESS DENIED!");    
           lcd.setCursor(0,3);     
           lcd.print("Warning after ");
           lcd.setCursor(14, 3);
           lcd.print(countdown);
           lcd.setCursor(16, 3);
           lcd.print("time");  
           Serial.println("\nMat khau sai");
           delay(3000);
          }
          if(warning == 3)
          {
           lcd.setCursor(0,1);
           lcd.print("*Wrong pass 3 times*");   
           lcd.setCursor(0,2);   
           lcd.print("  WARNING ACTIVATED");   

           countdown = 3;
           Serial.println("Canh bao!");
           digitalWrite(8, HIGH);
           warning = 0;
           delay(5000);
           digitalWrite(8, LOW);
          }
        }
      }

    }
  delay(100); 
  }
