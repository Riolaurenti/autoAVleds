void drawLines(int16_t  x0, int16_t  y0, int16_t  x1, int16_t  y1, CRGBPalette16 col){
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;
  for(;;){ //while(true)
   leds[XY(x0,y0)] = ColorFromPalette( cPal, cycHue, brightness, currentBlending);
   if (x0==x1 && y0==y1) {
      break;
      }
   e2 = err;
   if (e2 >-dx) { err -= dy; x0 += sx; }
   if (e2 < dy) { err += dx; y0 += sy; }
  }
}
void drawPixels(int16_t  x, int16_t  y, CRGBPalette16 col) {
  drawLines(x,y,x,y,col);
}
void drawRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGBPalette16 col){
  drawLines(x0, y0, x0, y1, col);
  drawLines(x0, y1, x1, y1, col);
  drawLines(x1, y1, x1, y0, col);
  drawLines(x1, y0, x0, y0, col);
}
void drawPi(int x, int y, int radius, int sAng, int eAng, CRGBPalette16 col) {
  for (int i=sAng; i<eAng; i++) {
    double radians = i * PI / 180;
    double px = x + radius * cos(radians);
    double py = y + radius * sin(radians);
    drawPixels(px, py, col);
  }
}
void drawCircles(int x, int y, int radius,CRGBPalette16 col){
  drawPi(x,y,radius,0,360,col);
}
