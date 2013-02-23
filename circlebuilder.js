var CircleBuilder = function() {
  this.center = new Vector();
  this.color = new Vector();
  this.radius = 1;
  this.resolution = 30;
};


CircleBuilder.prototype.build = function(gl, program) {
  var geometry = [
      this.center.x, this.center.y, this.center.z
  ];
  for (var i = 0; i <= this.resolution; ++i) {
    var theta = 2.0 * i * Math.PI / this.resolution;
    var point = this.center.plus(
        new Vector(this.radius * Math.cos(theta), this.radius * Math.sin(theta)));
    geometry.push(point.x, point.y, point.z);
  }
  var buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(geometry), gl.STATIC_DRAW);
  return new Visual(program, buffer, this.resolution + 2, gl.TRIANGLE_FAN, this.color);
};


CircleBuilder.prototype.setCenter = function(center) {
  this.center = center;
  return this;
};


CircleBuilder.prototype.setColor = function(color) {
  this.color = color;
  return this;
};


CircleBuilder.prototype.setRadius = function(radius) {
  this.radius = radius;
  return this;
};


CircleBuilder.prototype.setResolution = function(resolution) {
  this.resolution = resolution;
  return this;
};
