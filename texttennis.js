var TextTennis = function() {
  this.gl = null;
  this.keys = [];
  this.previousKeys = [];
};


TextTennis.VERTEX_SHADER_SOURCE =
    'uniform mat4 uniform_projection;' +
    'uniform vec3 uniform_position;' +
    'uniform vec3 uniform_position_offset;' +
    'uniform float uniform_scale;' +
    'attribute vec3 attribute_position;' +
    'void main() {' +
      'gl_Position = uniform_projection * vec4(' +
          'uniform_scale * attribute_position + uniform_position + uniform_position_offset, 1.0);' +
    '}';


TextTennis.FRAGMENT_SHADER_SOURCE =
    'precision highp float;' +
    'uniform vec3 uniform_color;' +
    'void main() {' +
      'gl_FragColor = vec4(uniform_color, 1.0);' +
    '}';


TextTennis.handleLoad = function() {
  var textTennis = new TextTennis();
  textTennis.setup();
  requestAnimationFrame(textTennis.animate.bind(textTennis));
};
window.addEventListener('load', TextTennis.handleLoad);


TextTennis.prototype.animate = function() {
  this.update();
  this.draw();
  this.previousKeys = this.keys.slice();
  requestAnimationFrame(this.animate.bind(this));
};


TextTennis.prototype.setup = function() {
  this.gl = document.getCSSCanvasContext(
      'experimental-webgl', 'c', window.innerWidth, window.innerHeight);
  document.addEventListener('keydown', this.handleKeyDown.bind(this), false);
  document.addEventListener('keyup', this.handleKeyUp.bind(this), false);
  this.gl.clearColor(1.0, 0.0, 0.0, 1.0);

  // gl = document.getCSSCanvasContext(
  //     'experimental-webgl', 'c', window.innerWidth, window.innerHeight);
  // gl.viewport(0, 0, window.innerWidth, window.innerHeight);
  // var inverseAspectRatio = window.innerHeight / window.innerWidth;
  // projection = perspective(-1.0, 1.0, -inverseAspectRatio, inverseAspectRatio, 1.0, 1000.0);
  // gl.clearColor(0.9, 0.9, 0.9, 1.0);
  // gl.enable(gl.DEPTH_TEST);
  // vertexShader = createShader(gl.VERTEX_SHADER, vertexShaderSource);
  // fragmentShader = createShader(gl.FRAGMENT_SHADER, fragmentShaderSource);
  // program = createProgram([vertexShader, fragmentShader]);
  // courtVisual = createVisual(program, [
  //     -0.5, -0.5, 0.0,
  //      0.5, -0.5, 0.0,
  //      0.5,  0.5, 0.0,
  //     -0.5, -0.5, 0.0,
  //      0.5,  0.5, 0.0,
  //     -0.5,  0.5, 0.0
  // ], 6, gl.TRIANGLES, new Vector(1, 1, 1));
  // ballVisual = createVisual(program, [
  //     -0.5, -0.5, 0.0,
  //      0.5, -0.5, 0.0,
  //      0.5,  0.5, 0.0,
  //     -0.5, -0.5, 0.0,
  //      0.5,  0.5, 0.0,
  //     -0.5,  0.5, 0.0
  // ], 6, gl.TRIANGLES, new Vector(208/255, 229/255, 19/255), Vector.K);
  // trailBuffer = gl.createBuffer();
  // trailVisual = new Visual(program, trailBuffer, trail.length, gl.LINE_STRIP, new Vector(), Vector.K.times(0.9));
  // objects = [
  //     //new GameObject(courtVisual, Infinity, Vector.K.times(-22), Vector.ZERO, 10.0),
  //     new GameObject(ballVisual, 0.5, Vector.K.times(-20), new Vector(1, 0.01).times(20.0), 1)
  // ];
};


TextTennis.prototype.update = function() {

};


TextTennis.prototype.draw = function() {
  // gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  // if (trail.length) {
  //   trailVisual.enable(gl);
  //   trailVisual.draw(gl, projection, new Vector(), 1);
  //   trailVisual.disable(gl);
  // }
  // objects.forEach(function(object) {
  //   object.draw(gl, projection);
  // });
};


TextTennis.prototype.handleKeyDown = function(e) {
  this.keys[e.keyCode] = true;
};


TextTennis.prototype.handleKeyUp = function(e) {
  this.keys[e.keyCode] = false;
};


TextTennis.prototype.createShader = function(type, source) {
  var shader = this.gl.createShader(type);
  this.gl.shaderSource(shader, source);
  this.gl.compileShader(shader);
  if (!this.gl.getShaderParameter(shader, this.gl.COMPILE_STATUS)) {
    var log = this.gl.getShaderInfoLog(shader);
    this.gl.deleteShader(shader);
    throw new Error(log);
  }
  return shader;
};


TextTennis.prototype.createProgram = function(shaders) {
  var program = this.gl.createProgram();
  shaders.forEach(function(shader) {
    this.gl.attachShader(program, shader);
  });
  this.gl.linkProgram(program);
  if (!this.gl.getProgramParameter(program, this.gl.LINK_STATUS)) {
    var log = this.gl.getProgramInfoLog(program);
    this.gl.deleteProgram(program);
    throw new Error(log);
  }
  return program;
};


TextTennis.prototype.createVisual = function(program, geometry, count, mode, opt_color, opt_offset) {
  var buffer = this.gl.createBuffer();
  this.gl.bindBuffer(this.gl.ARRAY_BUFFER, buffer);
  this.gl.bufferData(this.gl.ARRAY_BUFFER, new Float32Array(geometry), this.gl.STATIC_DRAW);
  return new Visual(program, buffer, count, mode, opt_color, opt_offset);
};


TextTennis.prototype.ortho = function(left, right, bottom, top, near, far) {
  return new Float32Array([
      2.0 / (right - left), 0.0, 0.0, 0.0,
      0.0, 2.0 / (top - bottom), 0.0, 0.0,
      0.0, 0.0, -2.0 / (far - near), 0.0,
      -(right + left) / (right - left), -(top + bottom) / (top - bottom),
          -(far + near) / (far - near), 1.0
  ]);
};


TextTennis.prototype.perspective = function(left, right, bottom, top, near, far) {
  return new Float32Array([
      2.0 * near / (right - left), 0, 0, 0,
      0, 2 * near / (top - bottom), 0, 0,
      (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1,
      0, 0, -(2 * far * near) / (far - near), 0
  ]);
};


var toFloatArray = function(trail, position) {
  var result = [];
  trail.forEach(function(entry) {
    result.push(entry.position.x, entry.position.y + 3 * (t2 - entry.time), entry.position.z);
  });
  return result;
};
var draw = function() {
  
};
