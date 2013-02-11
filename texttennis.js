var LINE_COUNT = 4;
var SCROLL_DELAY = 80;
var CHARACTER_CURSOR_INCREMENT = 1;

var t = 0.0;
var lines = [new Line([new GameState(t, 'Text Tennis')])];
var lineCursor = 0;
var characterCursor = lines[0] ? lines[0].description.length : 0;
var container;
var commandline;
var cursor;
var scheme;
var isDark = true;
var scrollBehavior = new PerWordScrollBehavior();
var load = function() {
  document.addEventListener('mousewheel', mousewheel, false);
  document.addEventListener('touchmove', touchmove, false);
  document.addEventListener('keypress', command, false);
  document.addEventListener('keydown', backspace, false);
  container = document.getElementById('container');
  commandline = document.getElementById('commandline');
  cursor = document.getElementById('cursor');
  scheme = document.getElementById('scheme');
  display();
  window.setInterval(blinkCursor, 1000);
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
    } else {
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
    scheme.innerHTML = 'body {' +
        'background: white;' +
        'color: black;' +
      '}';
  } else {
    scheme.innerHTML = 'body {' +
        'background: black;' +
        'color: white;' +
      '}';
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
var touchmove = function(e) {
  for (var i = 0; i < e.touches.length; ++i) {
    document.body.appendChild(document.createTextNode(e.touches[i].pageX + '/' + e.touches[i].pageY));
    document.body.appendChild(document.createElement('br'));
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
window.addEventListener('load', load, false);
