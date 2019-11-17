static int indexNo = 0;
void parser(){
	 static int indexNo = 0;
  Serial.println("parser triggered");
	while (incomingString.length() >1) {
    if (!incomingString.endsWith(","))incomingString.concat(",");
			String temp = incomingString.substring(0, (incomingString.indexOf(',')));
			Serial.print("printing temp ");
			Serial.println(temp);
			rgbValues[indexNo]= temp.toInt();
			indexNo++;
      Serial.print("indexNo = ");
      Serial.println(indexNo);
      delay(50);
			incomingString.remove(0, (incomingString.indexOf(",") +1 ));
       
		}
   incomingString="";
   Serial.println("parser complete");
   indexNo=0;
 for (int i=0; i<6; i++){
	  Serial.println(rgbValues[i]);
   rgbValues[i]=0;
 }
}
