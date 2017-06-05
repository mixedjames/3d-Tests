// UNIFORMS
// = Values that are constant for a whole set of verteces
uniform mat4 mv;
uniform mat4 p;

// ATTRIBUTES
// = Values that are specified per-vertex
attribute vec4 srcPosition;
attribute vec2 srcUV;

// VARYING
// = Outputs to the fragment shader
varying vec2 fUV;

void main() {
  fUV = srcUV;
  gl_Position = mv * p * srcPosition;
}