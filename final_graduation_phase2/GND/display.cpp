#include"DISPLAY.h"
#include"AX_25_LIB.h"
uint8_t gnd_addr[AX_25_CALLSIGN_LEN]={'N','J','7','P',' ',' '};       /*callsign of the destination*/
uint8_t flag=0;
uint8_t comm_addr[AX_25_CALLSIGN_LEN]={'N','7','L','E','M',' '};    /*callsign of the source*/
char t1='1';
uint8_t done=0;

void dis_ax(uint8_t *frame,uint8_t pp){
  

      int i=0;
  for(;i<100;i++){
    
 Serial.print("*");}

 
 Serial.println("");
  if(pp==1)Serial.print("GND_TX: ");
  else {Serial.print("GND_RX:");

  
  }
  Serial.println("");


Serial.println("AX_25_Frame: ");
i=0; 
for(;i<AX_25_FRAME_LEN;i++){
  Serial.print(frame[i],HEX);
  if(frame[i]==0)Serial.print(" ");
  Serial.print(" ");
  if((i+1)%32==0){Serial.println(""); }
  }

  Serial.print("Destination: ");
   flag=0;
    i=1;
    for(;i<7;i++){
      if(gnd_addr[i-1]!=(frame[i]>>1)){
        
        flag=1;
        
        
        
        }
    }

    if(flag==1){
      Serial.println("COMM");
      
      }

      else{Serial.println("GND");}

Serial.print("source: ");

     flag=0;
     i=8;
    for(;i<14;i++)
    {
    if(gnd_addr[i-8]!=(frame[i]>>1))
    {
        flag=1;
    }
    }
    if(flag==1){
      Serial.println("COMM");
      
      }

    else{Serial.println("GND");}

    Serial.print("Type: ");


    if(!(frame[15]&0x01)){
   Serial.println("I frame");
    }
    
    else {
            if(frame[15]&0x02){
                switch(frame[15]){
                    case U_SABM:// U_SABM ;
                               Serial.println("U_SABM frame");
                                break;
                    case U_DISC:// U_DISC;
                                Serial.println("U_DISC frame");
                                break;
                    case U_DM: // U_DM;
                                Serial.println("U_DM frame");
                                break;
                    case U_UA: // U_UA;
                                Serial.println("U_UA frame");
                                break;
                    case U_TEST://U_TEST;
                               Serial.println("U_TEST frame");
                                break;
                }}
            else {
                    switch((frame[15] & 0x0c)>>2){
                        case S_RR: // S_RR;
                                    Serial.println("S_RR frame");
                                    break;
                        case S_RNR: // S_RNR
                                    Serial.println("S_RNR frame");
                                    break;
                        case S_REJ: // S_REJ
                                    Serial.println("S_REJ frame");
                                    break;
                        case S_SREJ: // S_SREJ
                                    Serial.println("S_SREJ frame");
                                    break;
                }
        }
    }
    


Serial.print("Data: ");
if(!(frame[15]&0x01)){
Serial.println("");
if(pp==0){
dis_ssp(&frame[17],get_len0(&frame[17]));}
else{
dis_ssp(&frame[17],get_len1());
}



}


else{Serial.println("NO DATA FIELD IN THIS FRAME");}




  
    i=0;
  for(;i<100;i++){
    
 Serial.print("*");
    }
  
  Serial.println("");
  }








  

  
  
  
  





  
void dis_ssp(uint8_t *frame,uint8_t len){



 
 
 /*****************ssp frame*****************/
Serial.print("  SSP_Frame: ");

   int i=0;
  for(;i<len;i++){
    
 Serial.print(frame[i],HEX);
  Serial.print(" ");

  
    }  
 
Serial.println("");

 /*****************destination*****************/
Serial.print("  Desination: ");

switch(frame[1]){
case GND:Serial.println("GND");break;
case COMM:Serial.println("COMM");break;
case OBC:Serial.println("OBC");break;
default:break;          
  }
  
   /*****************Source*****************/
  Serial.print("  Source: ");
  
switch(frame[2]){
case GND:Serial.println("GND");break;
case COMM:Serial.println("COMM");break;
case OBC:Serial.println("OBC");break;
default:break;          
  }

   Serial.print("  Type: ");
  switch(frame[3]){
case GET_TEL_1:Serial.println("GET_TEL_1");break;
case GET_PACKET_2:Serial.println("GET_TEL_2");break;
case GET_PACKET_3:Serial.println("GET_TEL_3");break;
case INIT:Serial.println("INIT");break;
case PING_:Serial.println("PING");break;
case TEL_1_RESPONSE:Serial.println("TEL_1_RESPONSE");break;
case PACKET_2_RESPONSE:Serial.println("TEL_2_RESPONSE");break;
case PACKET_3_RESPONSE:Serial.println("TEL_3_RESPONSE");break;
case ACK:Serial.println("ACK");break;
case NACK:Serial.println("NACK");break;
case DISREQ:Serial.println("DISREQ");break;
default:break;          
  }
    /*****************Data*****************/
  Serial.print("  Data: ");
  
  switch(frame[3]){
case TEL_1_RESPONSE:
Serial.println("");
 Serial.print("   VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }
 Serial.print("   Packet_Type: ");
 
 Serial.println("telemetry_packet");

  Serial.print("   Length: ");
 Serial.println(frame[6]);
 
   Serial.print("   Sensor1_Temp: ");
 Serial.println(frame[7]);
    Serial.print("   Sensor2_Temp: ");
 Serial.println(frame[8]);
    Serial.print("   Sensor3_Temp: ");
 Serial.println(frame[9]);

     Serial.print("   Sensor4_Temp: ");
 Serial.println(frame[10]);

      Serial.print(" OBC_State: ");
 switch(frame[11]){
  case 14:Serial.println("Stable");break;
  case 13:Serial.println("Connection Failed");break;
  case 12:Serial.println("Connection Error"); break;
  case 15:Serial.println("Not Stable"); break;
  
  }
 
       Serial.print(" GND_State: ");
 switch(frame[12]){
  case 14:Serial.println("Stable");break;
  case 13:Serial.println("Connection Failed");break;
  case 12:Serial.println("Connection Error"); break;
  case 15:Serial.println("Not Stable"); break;
  
  }
        Serial.print("   Satlite_Mode: ");
 Serial.println(frame[13]);

break;
case PACKET_2_RESPONSE:
Serial.println("");
 Serial.print("   VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }

 Serial.print("   Packet_Type: ");
Serial.println("OBC_Login packet");

  Serial.print("   Length: ");
 Serial.println(frame[6]);
 Serial.println("   Login_History: ");
  Serial.print("  ");
  i=0;
 for(;i<20;i++){
  if(frame[7+i]==0x99){break;}
  switch(frame[7+i]){
case GET_TEL_1:Serial.print("GET_TEL_1 ");break;
case GET_PACKET_2:Serial.print("GET_TEL_2 ");break;
case GET_PACKET_3:Serial.print("GET_TEL_3 ");break;
case INIT:Serial.print("INIT ");break;
case PING_:Serial.print("PING ");break;
case TEL_1_RESPONSE:Serial.print("TEL_1_RESPONSE ");break;
case PACKET_2_RESPONSE:Serial.print("TEL_2_RESPONSE ");break;
case PACKET_3_RESPONSE:Serial.print("TEL_3_RESPONSE ");break;
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
 Serial.print("   VN: ");
 switch(frame[4]){
  case VN_ground :Serial.println("GND Version");break; 
  case VN_OBC :Serial.println("OBC Version");break;
  
  
  }

 Serial.print("   Packet_Type: ");
 Serial.println("GND_Login packet");

  Serial.print("   Length: ");
 Serial.println(frame[6]);
 Serial.println("   Login_History: ");
 Serial.print("  ");
 i=0;
 for(;i<20;i++){
   if(frame[7+i]==0x99){break;}
  switch(frame[7+i]){
case GET_TEL_1:Serial.print("GET_TEL_1 ");break;
case GET_PACKET_2:Serial.print("GET_TEL_2 ");break;
case GET_PACKET_3:Serial.print("GET_TEL_3 ");break;
case INIT:Serial.print("INIT ");break;
case PING_:Serial.print("PING ");break;
case TEL_1_RESPONSE:Serial.print("TEL_1_RESPONSE ");break;
case PACKET_2_RESPONSE:Serial.print("TEL_2_RESPONSE ");break;
case PACKET_3_RESPONSE:Serial.print("TEL_3_RESPONSE ");break;
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
  
  
  
  
  

  

  }
