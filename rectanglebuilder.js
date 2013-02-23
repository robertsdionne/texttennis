var RectangleBuilder = function() {
  this.center = new Vector();
  this.color = new Vector();
  this.width = 1;
  this.height = 1;
};


RectangleBuilder.prototype.build = function(gl, program) {
  var p0, p1, p2, p3;
  p0 = this.center.plus(new Vector(this.width / 2, this.height / 2));
  p1 = this.center.plus(new Vector(-this.width / 2, this.height / 2));
  p2 = this.center.plus(new Vector(-this.width / 2, -this.height / 2));
  p3 = this.center.plus(new Vector(this.width / 2, -this.height / 2));
  var buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([
      p0.x, p0.y, p0.z,
      p1.x, p1.y, p1.z,
      p3.x, p3.y, p3.z,
      p2.x, p2.y, p2.z
  ]), gl.STATIC_DRAW);
  return new Visual(program, buffer, 4, gl.TRIANGLE_STRIP, this.color);
};


RectangleBuilder.prototype.setCenter = function(center) {
  this.center = center;
  return this;
};


RectangleBuilder.prototype.setColor = function(color) {
  this.color = color;
  return this;
};


RectangleBuilder.prototype.setHeight = function(height) {
  this.height = height;
  return this;
};


RectangleBuilder.prototype.setSize = function(size) {
  this.width = this.height = size;
  return this;
};


RectangleBuilder.prototype.setWidth = function(width) {
  this.width = width;
  return this;
};
