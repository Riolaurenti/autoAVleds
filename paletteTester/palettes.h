CRGBPalette16 primaryPalette;
//CRGBPalette16 secondaryPalette;
//CRGBPalette16 tertiaryPalette;
//simple pallets from 2 primary colors fading back to origin
//as smoother. light "L" and dark"D".
DEFINE_GRADIENT_PALETTE(Red_blueD1){
  0,255,0,0,
  128,0,0,255,
  255,255,0,0 
};
DEFINE_GRADIENT_PALETTE(Red_blueL1){
  0,255,191,191,
  128,204,191,255,
  255,255,191,191
};
DEFINE_GRADIENT_PALETTE(Blue_greenD1){
  0,0,0,255,
  128,0,255,0,
  255,0,0,255
};
DEFINE_GRADIENT_PALETTE(Blue_greenL1){
  0,144,144,255,
  128,144,255,0,
  255,144,144,255 
};
DEFINE_GRADIENT_PALETTE(Green_yellowD1){
  0,0,255,0,
  128,255,255,0,
  255,0,255,0
};
// further palettes.
DEFINE_GRADIENT_PALETTE(Red_blue_greenD1) {
  0,255,0,0,
  64,0,0,255,
  128,0,255,0,
  192,0,0,255,
  255,255,0,0
};
DEFINE_GRADIENT_PALETTE(Red_blue_greenL1) {
  0,255,191,191,
  64,191,191,255,
  128,144,255,0,
  192,191,191,255,
  255,255,191,191
};
