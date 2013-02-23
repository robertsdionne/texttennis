var container;
var stream;
var stack = [];
var load = function() {
  stream = JSON.parse(document.getElementById('stream').textContent);
  container = document.getElementById('container');
  linkObjects(stream);
  var object = stream;
  for (var i = 0; i < 100; ++i) {
    object = printStatement(object);
  }
};
var linkObjects = function(object, opt_parent) {
  object.parent = opt_parent;
  for (var property in object) {
    if (property != 'parent' && typeof object[property] != 'string') {
      linkObjects(object[property], object);
    }
  }
};
var printStatement = function(object) {
  var properties = [];
  for (var property in object) {
    properties.push(property);
  }
  var choice = Math.floor(properties.length * Math.random());
  var property = properties[choice];
  if (typeof object[property] == 'string') {
    var content = document.createElement('p');
    var prefix = document.createElement('b');
    prefix.textContent = stack.join(' > ') + ': ';
    var suffix = document.createTextNode(object[property]);
    content.appendChild(prefix);
    content.appendChild(suffix);
    container.appendChild(content);
    return object;
  } else if (object[property]) {
    if (property == 'parent') {
      stack.pop();
    } else {
      stack.push(property);
    }
    return printStatement(object[property]);
  } else {
    return printStatement(stream);
  }
};
var printObject = function(object) {
  for (var property in object) {
    if (typeof object[property] == 'string') {
      var content = document.createElement('p');
      content.textContent = object[property];
      container.appendChild(content);
    } else {
      printObject(object[property]);
    }
  }
};
window.addEventListener('load', load, false);