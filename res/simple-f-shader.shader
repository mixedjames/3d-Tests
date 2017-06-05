precision mediump float;

// VARYING
// = Interpolated input from the VS
varying vec2 fUV;

// UNIFORM
// = constants
uniform sampler2D texture;

void main() {
  gl_FragColor = texture2D(texture, fUV);
}