var TextTennis = function() {
  this.gl = null;
  this.keys = [];
  this.previousKeys = [];
  this.objects = [];
  this.projection = null;
  this.program = null;
  this.ballVisual = null;
  this.courtVisual = null;
};


TextTennis.BALL_RADIUS = 0.03429;


TextTennis.COURT_LENGTH = 23.78;


TextTennis.COURT_THICKNESS = 0.5;


TextTennis.DAMPING = 0.98;


TextTennis.DT  = 1.0 / 60.0;


TextTennis.GRAVITY = 9.81;


TextTennis.VERTEX_SHADER_SOURCE =
    'uniform mat4 uniform_projection;' +
    'uniform vec3 uniform_position;' +
    'attribute vec3 attribute_position;' +
    'void main() {' +
      'gl_Position = uniform_projection * vec4(attribute_position + uniform_position, 1.0);' +
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
  this.court = new GameObject(1, 1, new Vector(0, -4));
  this.objects.push(new GameObject(TextTennis.BALL_RADIUS, 1, new Vector(), new Vector(10)));
  this.gl.clearColor(1.0, 1.0, 1.0, 1.0);
  this.gl.viewport(0, 0, window.innerWidth, window.innerHeight);
  var inverseAspectRatio = window.innerHeight / window.innerWidth;
  this.leftX = -12.0;
  this.rightX = 12.0;
  this.floorY = -12.0 * inverseAspectRatio;
  this.ceilingY = 12.0 * inverseAspectRatio;
  this.projection = this.ortho(this.leftX, this.rightX, this.floorY, this.ceilingY, -5.0, 5.0);
  this.gl.enable(this.gl.DEPTH_TEST);
  this.program = this.createProgram([
      this.createShader(this.gl.VERTEX_SHADER, TextTennis.VERTEX_SHADER_SOURCE),
      this.createShader(this.gl.FRAGMENT_SHADER, TextTennis.FRAGMENT_SHADER_SOURCE)
  ]);
  this.ballVisual = new CircleBuilder()
      .setRadius(TextTennis.BALL_RADIUS)
      .build(this.gl, this.program);
  this.courtVisual = new RectangleBuilder()
      .setCenter(new Vector(0, this.floorY))
      .setHeight(2.0 * TextTennis.COURT_THICKNESS)
      .setWidth(TextTennis.COURT_LENGTH)
      .build(this.gl, this.program);
};


TextTennis.prototype.update = function() {
  this.gravity();
  this.accelerate(TextTennis.DT);
  this.borderCollide();
  this.inertia(TextTennis.DT);
  this.borderCollidePreserveImpulse();
};


TextTennis.prototype.gravity = function() {
  this.objects.forEach(function(object) {
    object.addForce(Vector.J.times(-TextTennis.GRAVITY));
  });
};


TextTennis.prototype.accelerate = function(dt) {
  this.objects.forEach(function(object) {
    object.accelerate(dt);
  });
};


TextTennis.prototype.borderCollide = function() {
  var ball = this.objects[0];
  if (ball.position.y - ball.radius - TextTennis.COURT_THICKNESS < this.floorY) {
    ball.position.y = ball.radius + TextTennis.COURT_THICKNESS + this.floorY;
  }
  if (ball.position.x - ball.radius < this.leftX) {
    ball.position.x = ball.radius + this.leftX;
  } else if (ball.position.x + ball.radius > this.rightX) {
    ball.position.x = this.rightX - ball.radius;
  }
};


TextTennis.prototype.inertia = function(dt) {
  this.objects.forEach(function(object) {
    object.inertia(dt);
  });
};


TextTennis.prototype.borderCollidePreserveImpulse = function() {
  var ball = this.objects[0];
  if (ball.position.y - ball.radius - TextTennis.COURT_THICKNESS < this.floorY) {
    var vy = (ball.previousPosition.y - ball.position.y) * TextTennis.DAMPING;
    ball.position.y = ball.radius + TextTennis.COURT_THICKNESS + this.floorY;
    ball.previousPosition.y = ball.position.y - vy;
  }
  if (ball.position.x - ball.radius < this.leftX) {
    var vx = (ball.previousPosition.x - ball.position.x) * TextTennis.DAMPING;
    ball.position.x = ball.radius + this.leftX;
    ball.previousPosition.x = ball.position.x - vx;
  } else if (ball.position.x + ball.radius > this.rightX) {
    var vx = (ball.previousPosition.x - ball.position.x) * TextTennis.DAMPING;
    ball.position.x = this.rightX - ball.radius;
    ball.previousPosition.x = ball.position.x - vx;
  }
};


TextTennis.prototype.draw = function() {
  this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
  var textTennis = this;
  this.courtVisual.enable(this.gl);
  this.courtVisual.draw(this.gl, this.projection, Vector.ZERO);
  this.courtVisual.disable(this.gl);
  this.ballVisual.enable(this.gl);
  this.objects.forEach(function(object) {
    textTennis.ballVisual.draw(textTennis.gl, textTennis.projection, object.position);
  });
  this.ballVisual.disable(this.gl);
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
  var textTennis = this;
  shaders.forEach(function(shader) {
    textTennis.gl.attachShader(program, shader);
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


// var toFloatArray = function(trail, position) {
//   var result = [];
//   trail.forEach(function(entry) {
//     result.push(entry.position.x, entry.position.y + 3 * (t2 - entry.time), entry.position.z);
//   });
//   return result;
// };
