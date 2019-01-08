   /*This code accepts the votes obtained from the EVM, computes the total, displays the winning party along with the number of votes by which it has won, on the Liquid Crystal Display*/
   /*Using EEPROM, the polling data is saved even if the power supply is interrupted and also clears the memory when the clear button is pressed*/
    #include<LiquidCrystal.h> // lcd library
    #include <EEPROM.h> //EEPROM library
    LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LCD control and data lines
    // button pin definitions
    int result=A4;
    int closed=6;
    int total=7;
    int clearbutton=A0;
    int a=A1;
    int b=A2;
    int c=A3;
    // temporary variables used in program
    int v1;
    int v2;
    int v3;
    int v;
    int cflag;
    
    void setup()
    {
        cflag=EEPROM.read(0); //read the status of cflag from memory
        v1=EEPROM.read(1);// v1 stores the vote count of party A
        v2=EEPROM.read(2); // v2 stores the vote count of party B
        v3=EEPROM.read(3); // v3 stores the vote count of party C
        pinMode(a,INPUT); // declaration of buttons as input
        pinMode(b,INPUT);
        pinMode(c,INPUT);
        pinMode(total,INPUT);
        pinMode(closed,INPUT);
        pinMode(result,INPUT);
        pinMode(clearbutton,INPUT);
        digitalWrite(a,HIGH); //default status of buttons when not pressed is high
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(total,HIGH);
        digitalWrite(closed,HIGH);
        digitalWrite(result,HIGH);
        digitalWrite(clearbutton,HIGH);
        lcd.begin(16,2);
        if(cflag==0)
          {
            lcd.print("   ELECTRONIC");
            lcd.setCursor(0,1);
            lcd.print(" VOTING MACHINE");
            delay(5000);
            lcd.clear();
            lcd.print("  Press button");
            lcd.setCursor(0,1);
            lcd.print("   to vote...");
            delay(1000);
          }
        if(cflag==1)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("  Voting Closed");
            lcd.setCursor(0,1);
            v=v1+v2+v3;
            lcd.print("Total Votes:");
            lcd.print(v);
          }
      }
      
      void rpt()
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("  Press button");
        lcd.setCursor(0,1);
        lcd.print("   to vote...");
      }
        
        
      void votedifference() // function to calculate vote difference
      {
        if(v1>v2)
        {
          if(v2>v3)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("A wins by");
            lcd.setCursor(0,1);
            lcd.print(v1-v2);
            lcd.print(" votes");
          }
          else
          {
            if(v1>v3)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("A wins by");
              lcd.setCursor(0,1);
              lcd.print(v1-v3);
              lcd.print(" votes");
            }
            if(v1<v3)
            {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("C wins by");
              lcd.setCursor(0,1);
              lcd.print(v3-v1);
              lcd.print(" votes");
            }
          }
        }
         
        else
        {
          if(v1>v3)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("B wins by");
            lcd.setCursor(0,1);
            lcd.print(v2-v1);
            lcd.print(" votes");
          }
         
          else
          {
              if(v2>v3)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("B wins by");
                lcd.setCursor(0,1);
                lcd.print(v2-v3);
                lcd.print(" votes");
              }
              if(v2<v3)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("C wins by");
                lcd.setCursor(0,1);
                lcd.print(v3-v2);
                lcd.print(" votes");
              }
          }
        }
     }
    
    void loop()
    {
      if(digitalRead(a)==LOW && cflag==0) // if party A button is pressed
      {
        v1=v1+1;
        EEPROM.write(1,v1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Vote received...");
        lcd.setCursor(0,1);
        lcd.print("  Thank You!!");
        delay(1500);
        rpt(); 
      }
    
      if(digitalRead(b)==LOW && cflag==0) // if party B button is pressed
      {
        v2=v2+1;
        EEPROM.write(2,v2);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Vote received...");
         lcd.setCursor(0,1);
        lcd.print("  Thank You!!");
        delay(1500);
        rpt(); 
      }
    
      if(digitalRead(c)==LOW && cflag==0) // if party C button is pressed
      {
        v3=v3+1;
        EEPROM.write(3,v3);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Vote received...");
         lcd.setCursor(0,1);
        lcd.print("  Thank You!!");
        delay(1500);
        rpt(); 
      }
       // if total button is pressed but close button was not pressed earlier
      if(digitalRead(total)==LOW && cflag==0)
      {
        v=v1+v2+v3;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Total votes:");
        lcd.setCursor(0,1);
        lcd.print(v);
        delay(2000);
        rpt();
      }
    
      if(digitalRead(closed)==LOW) // if close button is pressed
      {
        cflag=1;
        EEPROM.write(0,cflag);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Voting Closed!!!");
        lcd.setCursor(0,1);
        v=v1+v2+v3;
        lcd.print(" Total Votes:");
        lcd.print(v);
        while(digitalRead(result)==HIGH);
      }
    
      // if result button is pressed after the close button was pressed
      if(digitalRead(result)==LOW && cflag==1)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("A:");
        lcd.print(v1);
        lcd.setCursor(7,0);
        lcd.print("B:");
        lcd.print(v2);
        lcd.setCursor(0,1);
        lcd.print("C:");
        lcd.print(v3);
        delay(3000);
       
          // logic for result of voting process
        if(v1==v2 && v2==v3)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" Result Tied!!!");
          delay(3000);
        }
   
        if(v1==v2 && v1>v3)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Tie b/w A and B");
          delay(3000);
        }
     
        if(v2==v3 && v2>v1)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Tie b/w B and C");
          delay(3000);
        }
        if(v1==v3 && v1>v2)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Tie b/w A and C");
          delay(3000);
        }
   
        if(v1>v2)
        {
          if(v1>v3)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" Party A wins!!!");
            delay(3000);
            votedifference();
          }
          else if(v3>v1)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" Party C wins!!!");
            delay(3000);
            votedifference();
          }
        }
   
        else
        {
          if(v2>v3 && v1!=v2)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" Party B wins!!!");
            delay(3000);
            votedifference();
          }
          else if(v3>v2)
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(" Party C wins!!!");
            delay(3000);
            votedifference();
          }
        }
    }
    
    if(digitalRead(clearbutton)==LOW) // if clear button is pressed
    {
      for (int i = 0; i < 512; i++)
      {
        EEPROM.write(i, 0);
      }
      v1=0;
      v2=0;
      v3=0;
      cflag=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Memory Cleared");
      lcd.setCursor(0,1);
      lcd.print("  ***********  ");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Press button");
      lcd.setCursor(0,1);
      lcd.print("   to vote...");
    }
  }

