
 void iic(String x){
  Wire.beginTransmission(2);
  char c[x.length()+1];
  x.toCharArray(c,x.length()+1);
  Wire.write(c);
 // DPRINTLN("Sent I2c");
  Wire.endTransmission();
}
