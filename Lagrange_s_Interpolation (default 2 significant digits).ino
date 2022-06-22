#include<WiFi.h>

const char* ssid = "Redmi";
const char* password = "Redmi123";

WiFiServer server(5000);

String dummy = "";
long t;
float x[20];
float y[20];
float X;

float n[20];
float d[20];
float sol = 0.00;

void setup(){
Serial.begin(115200);

Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);

while(WiFi.status()!=WL_CONNECTED)
{ delay(100);
  Serial.print(".");
}

Serial.println();
Serial.println("WiFi connected");
Serial.println(WiFi.localIP());

server.begin();
Serial.println("Server started.");

}

void loop() {
 
  WiFiClient client = server.available();
  
  
  if(!client)
  { return;
  }

  Serial.println("Got a client !");
  client.println("Connected.");

for(;;){

  client.println("");
  client.print("n(>0) = ");

  while(!client.available())
  { delay(1);
  }
   
   if(client.available())
   { dummy = client.readStringUntil('\r');
     t = dummy.toInt();
     dummy = "";
     client.print(t);
    
     Serial.print("n=");
     Serial.println(t);
  
    } 

   for(long i=0 ; i<t ; i++)
    { 
     while(!client.available())
     { delay(1);
      }

      if(client.available()){
       dummy = client.readStringUntil('\r');
        x[i] = dummy.toFloat();
       dummy = "";
     
     client.println();
     client.print("x[" + String(i) + "] =");

     while(!client.available())
     { delay(1);
      }

      if(client.available()){
       dummy = client.readStringUntil('\r');
        x[i] = dummy.toFloat();
       dummy = "";
       client.print(x[i]);
       Serial.print("x[" + String(i) + "] =");
       Serial.println(x[i]);
     }

      }
    }

     for(long i=0 ; i<t ; i++)
    {
      while(!client.available())
     { delay(1);
      }

     if(client.available())
    {  dummy = client.readStringUntil('\r');
       y[i] = dummy.toFloat();
       dummy = "";
     }

     client.println();
     client.print("y[" + String(i) + "] =");

      while(!client.available())
     { delay(1);
      }

     if(client.available())
    {  dummy = client.readStringUntil('\r');
       y[i] = dummy.toFloat();
       dummy = "";
       client.print(y[i]);
       Serial.print("y[" + String(i) + "] =");
       Serial.println(y[i]);
     }
    }
      while(!client.available())
     { delay(1);
      }

     if(client.available())
    {  dummy = client.readStringUntil('\r');
       X = dummy.toFloat();
       dummy = "";
     }

     client.println();
    client.println();
    client.print("X =");

      while(!client.available())
     { delay(1);
      }

     if(client.available())
    {  dummy = client.readStringUntil('\r');
       X = dummy.toFloat();
       dummy = "";
       client.print(X);
       Serial.print("X =");
       Serial.println(X);
     }

     /*for( long i=0 ; i<t ; i++)
     { Serial.print("x[" + String(i) + "]=");
       Serial.println(x[i]);
       }
       for( long i=0 ; i<t ; i++)
     { Serial.print("y[" + String(i) + "]=");
       Serial.println(y[i]);
       }
     Serial.print("X=");
     Serial.println(X); */

    for( long j=0 ; j<t ; j++ )
    { n[j]=1;
      d[j]=1;
      
        for( long i=0 ; i<t ; i++ )
        {
          if(i==j)
          { delay(1);}
          else
          {
            n[j] = n[j]*(X-x[i]);
            d[j] = d[j]*(x[j]-x[i]);
            delay(1);
          }
        }
      client.println();
      client.println( "(" + String(j) + ") " + "n[" + String(j) + "] = " + String(n[j]) + "  d[" + String(j) + "] = " + String(d[j]));
      Serial.println( "(" + String(j) + ") " + "n[" + String(j) + "] = " + String(n[j]) + "  d[" + String(j) + "] = " + String(d[j]));
    }

    for( long i=0 ; i<t ; i++)
    { 
      sol = sol + (( n[i]/d[i] )*y[i]);
      delay(1);     
    }
    client.println();
    Serial.print("Y=");
    Serial.println(String(sol));
    client.print("Y=");
     client.println(String(sol));

     sol=0.00;
     

     while(!client.available())
     { delay(1);
      }
     if(client.available())
     { dummy = client.readStringUntil('\r');
     t = dummy.toInt();
     dummy = "";
     }

}
}
