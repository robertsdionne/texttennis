var LINE_COUNT = 4;
var CHARACTER_CURSOR_INCREMENT = 1;

var t = 0.0;
var lines = [new Line([new GameState(t, 'Text Tennis')])];
var lineCursor = 0;
var characterCursor = lines[0] ? lines[0].description.length : 0;
var container;
var commandline;
var cursor;
var isDark = false;
var gl;
var scrollBehavior = new PerWordScrollBehavior();
var load = function() {
  document.addEventListener('mousewheel', mousewheel, false);
  document.addEventListener('touchmove', touchmove, false);
  document.addEventListener('keypress', command, false);
  document.addEventListener('keydown', backspace, false);
  container = document.getElementById('container');
  commandline = document.getElementById('commandline');
  cursor = document.getElementById('cursor');
  display();
  window.setInterval(blinkCursor, 1000);
  setup();
  requestAnimationFrame(animate);
};
var blinkCursor = function() {
  cursor.textContent = cursor.textContent ? '' : '\u2588';
};
var scrollDown = function() {
  if (lineCursor >= 0 && characterCursor < scrollBehavior.length(lines[lineCursor].description)) {
    characterCursor += CHARACTER_CURSOR_INCREMENT;
  } else {
    if (!lines[lineCursor] || !lines[lineCursor].isDeath) {
      characterCursor = CHARACTER_CURSOR_INCREMENT;
      lineCursor += 1;
    }
    if (lineCursor < 1) {
      lines.push(new Line([new GameState(t, 'Text Tennis')]));
    } else if (!lines[lineCursor] || !lines[lineCursor].isDeath) {
      lines.push(new Line([
          makeClockState(t += Math.random() * 1000),
          makeClockState(t += Math.random() * 10),
          makeClockState(t += Math.random() * 100),
          maybeDie(t += Math.random() * 10)
      ]));
    }
  }
  display();
};
var toggleScheme = function() {
  if (isDark) {
    // document.body.style.background = 'white';
    // document.body.style.color = 'black';
  } else {
    // document.body.style.background = 'black';
    // document.body.style.color = 'white';
  }
  isDark = !isDark;
};
var maybeDie = function(time) {
  if (Math.random() < 0.1) {
    return new GameState(time, 'You died! . . .', true, true);
  } else {
    return new GameState(time, '');
  }
};
var makeClockState = function(time) {
  var choice = Math.random() * 8;
  var description;
  if (0 <= choice && choice < 1) {
    description = 'The clock on the wall reads ';
  } else if (1 <= choice && choice < 2) {
    description = 'The time is ';
  } else if (2 <= choice && choice < 3) {
    description = 'The clock says ';
  } else if (3 <= choice && choice < 4) {
    description = 'The time reads ';
  } else if (4 <= choice && choice < 5) {
    description = 'You read the clock to be ';
  } else if (5 <= choice && choice < 6) {
    description = 'Clock\'s busy at ';
  } else if (6 <= choice && choice < 7) {
    description = 'Clock says ';
  } else if (7 <= choice && choice < 8) {
    description = 'Clock tells you ';
  }
  return new GameState(time, description + makeTime(time) + '.')
};
var makeTime = function(time) {
  return new Date(5*3600*1000+1000 * Math.floor(time)).toTimeString().split(' ')[0];
};
var scrollUp = function() {
  if (characterCursor > CHARACTER_CURSOR_INCREMENT) {
    characterCursor -= CHARACTER_CURSOR_INCREMENT;
  } else {
    while (lineCursor >= 0 && lines.length > lineCursor) {
      lines.pop();
    }
    if (lineCursor >= 0) {
      lineCursor -= 1;
    }
    if (lines[lineCursor]) {
      characterCursor = scrollBehavior.length(lines[lineCursor].description);
      t = lines[lineCursor].timestamp - 1;
    }
  }
  display();
};
var mousewheel = function(e) {
  if (e.wheelDelta < 0) {
    scrollDown();
  } else if (e.wheelDelta > 0) {
    scrollUp();
  }
  e.preventDefault();
};
var lastTouch;
var touchmove = function(e) {
  for (var i = 0; i < e.touches.length; ++i) {
    var touch = e.touches[i];
    if (lastTouch) {
      if (touch.pageY - lastTouch.pageY > 0) {
        scrollDown();
      } else if (touch.pageY - lastTouch.pageY < 0) {
        scrollUp();
      }
    }
    lastTouch = touch;
  }
  e.preventDefault();
};
var backspace = function(e) {
  if (e.keyCode == KeyCode.BACKSPACE) {
    commandline.textContent = commandline.textContent.slice(0, -1);
    e.preventDefault();
  } else if (e.keyCode == KeyCode.UP || e.keyCode == KeyCode.LEFT) {
    scrollUp();
  } else if (e.keyCode == KeyCode.DOWN || e.keyCode == KeyCode.RIGHT) {
    scrollDown();
  }
};
var command = function(e) {
  if (e.keyCode == KeyCode.RETURN) {
    if (commandline.textContent) {
      var index = scrollBehavior.indexInto(lines[lineCursor], characterCursor);
      if (commandline.textContent == 'die') {
        lines[lineCursor].gameStates[index] = new GameState(
            t += Math.random() * 10, 'You died! . . . ', true, true);
      } else {
        lines[lineCursor].gameStates[index] = new GameState(t += Math.random() * 10,
            'You ' + lowerCaseFirstLetter(commandline.textContent) + '. ', true);
       }
      commandline.textContent = '';
      display();
    }
  } else if (e.keyCode == KeyCode.TILDE) {
    toggleScheme();
  } else {
    commandline.textContent = commandline.textContent + String.fromCharCode(e.keyCode);
  }
};
var lowerCaseFirstLetter = function(value) {
  return value.slice(0, 1).toLowerCase() + value.slice(1);
};
var display = function () {
  while (container.childNodes.length) {
    container.removeChild(container.childNodes[0]);
  }
  var startIndex = lineCursor - LINE_COUNT >= 0 ? lineCursor - LINE_COUNT : 0;
  lines.slice(startIndex, lineCursor).forEach(function(line, index) {
    var prefix = (startIndex + index) % 4 == 1 ? '\u00A0\u00A0' : '';
    var content = line.toDomNode(prefix, line.description.length, scrollBehavior);
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  });
  if (lineCursor >= 0 && lines.length > lineCursor) {
    var prefix = lineCursor % 4 == 1 ? '\u00A0\u00A0' : '';
    var content = lines[lineCursor].toDomNode(prefix, characterCursor, scrollBehavior);
    var newline = document.createElement('br');
    container.appendChild(content);
    container.appendChild(newline);
  }
};
var animate = function() {
  update();
  draw();
  requestAnimationFrame(animate);
};
var createShader = function(type, source) {
  var shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    var log = gl.getShaderInfoLog(shader);
    gl.deleteShader(shader);
    throw new Error(log);
  }
  return shader;
};
var createProgram = function(shaders) {
  var program = gl.createProgram();
  shaders.forEach(function(shader) {
    gl.attachShader(program, shader);
  });
  gl.linkProgram(program);
  if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
    var log = gl.getProgramInfoLog(program);
    gl.deleteProgram(program);
    throw new Error(log);
  }
  return program;
};
var createVisual = function(program, geometry, count, opt_color) {
  var buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(geometry), gl.STATIC_DRAW);
  return new Visual(program, buffer, count, opt_color);
};
var ortho = function(left, right, bottom, top, near, far) {
  return new Float32Array([
      2.0 / (right - left), 0.0, 0.0, 0.0,
      0.0, 2.0 / (top - bottom), 0.0, 0.0,
      0.0, 0.0, -2.0 / (far - near), 0.0,
      -(right + left) / (right - left), -(top + bottom) / (top - bottom),
          -(far + near) / (far - near), 1.0
  ]);
};
var perspective = function(left, right, bottom, top, near, far) {
  return new Float32Array([
      2.0 * near / (right - left), 0, 0, 0,
      0, 2 * near / (top - bottom), 0, 0,
      (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1,
      0, 0, -(2 * far * near) / (far - near), 0
  ]);
};
var vertexShaderSource =
    'uniform mat4 uniform_projection;' +
    'uniform vec3 uniform_position;' +
    'uniform float uniform_scale;' +
    'attribute vec3 attribute_position;' +
    'void main() {' +
      'gl_Position = uniform_projection * vec4(' +
          'uniform_scale * attribute_position + uniform_position, 1.0);' +
    '}';
var fragmentShaderSource =
    'precision highp float;' +
    'uniform vec3 uniform_color;' +
    'void main() {' +
      'gl_FragColor = vec4(uniform_color, 1.0);' +
    '}';
var vertexShader, fragmentShader, program;
var courtVisual, boxVisual;
var projection;
var objects;
var setup = function() {
  gl = document.getCSSCanvasContext(
      'experimental-webgl', 'c', window.innerWidth, window.innerHeight);
  gl.viewport(0, 0, window.innerWidth, window.innerHeight);
  var inverseAspectRatio = window.innerHeight / window.innerWidth;
  projection = perspective(-1.0, 1.0, -inverseAspectRatio, inverseAspectRatio, 1.0, 1000.0);
  gl.clearColor(0.9, 0.9, 0.9, 1.0);
  gl.enable(gl.DEPTH_TEST);
  vertexShader = createShader(gl.VERTEX_SHADER, vertexShaderSource);
  fragmentShader = createShader(gl.FRAGMENT_SHADER, fragmentShaderSource);
  program = createProgram([vertexShader, fragmentShader]);
  courtVisual = createVisual(program, [
      -0.5, -0.5, 0.0,
       0.5, -0.5, 0.0,
       0.5,  0.5, 0.0,
      -0.5, -0.5, 0.0,
       0.5,  0.5, 0.0,
      -0.5,  0.5, 0.0
  ], 6, new Vector(1, 1, 1));
  boxVisual = createVisual(program, [
      -0.5, -0.5, 0.0,
       0.5, -0.5, 0.0,
       0.5,  0.5, 0.0,
      -0.5, -0.5, 0.0,
       0.5,  0.5, 0.0,
      -0.5,  0.5, 0.0
  ], 6, new Vector(208/255, 229/255, 19/255));
  objects = [
      new GameObject(courtVisual, 1, Vector.K.times(-10), Vector.ZERO, 10.0),
      new GameObject(boxVisual, 1, Vector.K.times(-9), Vector.Zero, 1)
  ];
};
var update = function() {
  objects[1].position.x = 0.0001 * t;
  objects.forEach(function(object) {
    object.update(1.0 / 60.0);
  });
};
var draw = function() {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  objects.forEach(function(object) {
    object.draw(gl, projection);
  });
};
window.addEventListener('load', load, false);
