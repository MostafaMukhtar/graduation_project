#include"DISPLAY.h"

char t1='1';
uint8_t done=0;
 
void dis_ssp(uint8_t *frame,uint8_t len,uint8_t pp){
  int i=0;
  for(;i<64;i++){
    
 Serial.print("*");
    }




    

Serial.println("");
if(pp==1)Serial.print("OBC_TX:");
else {Serial.print("OBC_RX:");
      t1++;
      done=0;
      }
Serial.println("");





Serial.print("SSP_Frame: ");

   i=0;
  for(;i<len;i++){
    
 Serial.print(frame[i],HEX);
  Serial.print(" ");

  
    } 





     
 
Serial.println("");
Serial.print("Desination: ");

switch(frame[1]){
case GND:Serial.println("GND");break;
case COMM:Serial.println("COMM");break;
case OBC:Serial.println("OBC");break;
default:break;          
  }




  
  
  Serial.print("Source: ");
  
switch(frame[2]){
case GND:Serial.println("GND");break;
case COMM:Serial.println("COMM");break;
case OBC:Serial.println("OBC");break;
default:break;          
  }





   Serial.print("Type: ");
  switch(frame[3]){
case GET_TEL_1:Serial.println("GET_TEL_1");break;
case GET_PACKET_2:Serial.println("GET_PACKET_2");break;
case GET_PACKET_3:Serial.println("GET_PACKET_3");break;
case INIT:Serial.println("INIT");break;
case PING_:Serial.println("PING");break;
case TEL_1_RESPONSE:Serial.println("TEL_1_RESPONSE");break;
case PACKET_2_RESPONSE:Serial.println("PACKET_2_RESPONSE");break;
case PACKET_3_RESPONSE:Serial.println("PACKET_3_RESPONSE");break;
case ACK:Serial.println("ACK");break;
case NACK:Serial.println("NACK");break;
case DISREQ:Serial.println("DISREQ");break;
default:break;          
  }





  
  
  Serial.print("Data: ");
  
  switch(frame[3]){
case TEL_1_RESPONSE:
Serial.println("");
 Serial.print(" VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }
 

 Serial.print(" Packet_Type: ");
 
 Serial.println("telemetry_packet");

  


  Serial.print(" Length: ");
 Serial.println(frame[6]);
 
   Serial.print(" Sensor1_Temp: ");
 Serial.println(frame[7]);
    Serial.print(" Sensor2_Temp: ");
 Serial.println(frame[8]);
    Serial.print(" Sensor3_Temp: ");
 Serial.println(frame[9]);

     Serial.print(" Sensor4_Temp: ");
 Serial.println(frame[10]);

      Serial.print(" OBC_State: ");
 switch(frame[11]){
  case 14:Serial.println("Stable");break;
  case 13:Serial.println("Connection Error");break;
  case 12:Serial.println("Not Stable"); break;
  
  }
 
       Serial.print(" GND_State: ");
 switch(frame[12]){
  case 14:Serial.println("Stable");break;
  case 13:Serial.println("Connection Error");break;
  case 12:Serial.println("Not Stable"); break;
  
  }
        Serial.print(" Satlite_Mode: ");
 Serial.println(frame[13]);

break;
case PACKET_2_RESPONSE:
Serial.println("");
 Serial.print(" VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }
 

 Serial.print(" Packet_Type: ");

Serial.println("OBC_Login packet");


  Serial.print(" Length: ");
 Serial.println(frame[6]);
 Serial.println(" Login_History: ");
  Serial.print("  ");
  i=0;
 for(;i<20;i++){
  if(frame[7+i]==0x99){break;}
  switch(frame[7+i]){
case GET_TEL_1:Serial.print("GET_TEL_1 ");break;
case GET_PACKET_2:Serial.print("GET_PACKET_2 ");break;
case GET_PACKET_3:Serial.print("GET_PACKET_3 ");break;
case INIT:Serial.print("INIT ");break;
case PING_:Serial.print("PING ");break;
case TEL_1_RESPONSE:Serial.print("TEL_1_RESPONSE ");break;
case PACKET_2_RESPONSE:Serial.print("PACKET_2_RESPONSE ");break;
case PACKET_3_RESPONSE:Serial.print("PACKET_3_RESPONSE ");break;
case ACK:Serial.print("ACK ");break;
case NACK:Serial.print("NACK ");break;
case DISREQ:Serial.print("DISREQ ");break;
default:break;          
  }
  }
  Serial.println("");
break;
case PACKET_3_RESPONSE:
Serial.println("");
 Serial.print(" VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }
 

 Serial.print(" Packet_Type: ");

 Serial.println("GND_Login packet");


  Serial.print(" Length: ");
 Serial.println(frame[6]);
 Serial.println(" Login_History: ");
 Serial.print("  ");
 i=0;
 for(;i<20;i++){
   if(frame[7+i]==0x99){break;}
  switch(frame[7+i]){
case GET_TEL_1:Serial.print("GET_TEL_1 ");break;
case GET_PACKET_2:Serial.print("GET_PACKET_2 ");break;
case GET_PACKET_3:Serial.print("GET_PACKET_3 ");break;
case INIT:Serial.print("INIT ");break;
case PING_:Serial.print("PING ");break;
case TEL_1_RESPONSE:Serial.print("TEL_1_RESPONSE ");break;
case PACKET_2_RESPONSE:Serial.print("PACKET_2_RESPONSE ");break;
case PACKET_3_RESPONSE:Serial.print("PACKET_3_RESPONSE ");break;
case ACK:Serial.print("ACK ");break;
case NACK:Serial.print("NACK ");break;
case DISREQ:Serial.print("DISREQ ");break;
default:break;          
  }
  }
  Serial.println("");
break;
default:
Serial.println("NO DATA FIELD IN THIS FRAME");break;
break;          
  }
  
  
  
  


  
    i=0;
  for(;i<64;i++){
    
 Serial.print("*");
    }
  
  Serial.println("");
  }
