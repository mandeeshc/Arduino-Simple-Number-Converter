// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;

void input_message()
{
  Serial.println("Please enter a decimal no. to be converted.");
}

void setup ()
{
  Serial.begin (115200);
  input_message();
  
} // end of setup

// here to process incoming serial data after a terminator received
void process_data (char *data)
  {
    //Serial.println (data);
    String myString = data;
    Serial.println(myString);
    int val = myString.toInt();
    //Serial.println(val);
    Serial.print("The decimal-based value you entered is: ");    Serial.println (val,DEC);
    Serial.print("The binary-based value you entered is: ");   Serial.println (val,BIN);
    Serial.print("The octal-based value you entered is: ");    Serial.println (val,OCT);
    Serial.print("The hexadecimal-based value you entered is: ");      Serial.println (val,HEX);
    Serial.println();
    input_message();
  }  // end of process_data
  
void processIncomingByte (const byte inByte)
  {
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte)
    {

    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      
      // terminator reached! process input_line here ...
      process_data (input_line);
      
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;

    }  // end of switch
   
  } // end of processIncomingByte  

void loop()
  {
  // if serial data available, process it
  while (Serial.available () > 0)
    processIncomingByte (Serial.read ());
    
  }  // end of loop
