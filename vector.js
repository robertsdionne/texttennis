var Vector = function(opt_x, opt_y, opt_z) {
  this.x = opt_x || 0;
  this.y = opt_y || 0;
  this.z = opt_z || 0;
};


Vector.ZERO = new Vector();


Vector.I = new Vector(1);


Vector.J = new Vector(0, 1);


Vector.K = new Vector(0, 0, 1);


Vector.prototype.magnitude = function() {
  return Math.sqrt(this.dot(this));
};


Vector.prototype.negated = function() {
  return new Vector(-this.x, -this.y, -this.z);
};


Vector.prototype.normalized = function() {
  return this.over(this.magnitude());
};


Vector.prototype.plus = function(that) {
  return new Vector(this.x + that.x, this.y + that.y, this.z + that.z);
};


Vector.prototype.minus = function(that) {
  return new Vector(this.x - that.x, this.y - that.y, this.z - that.z);
};


Vector.prototype.times = function(that) {
  return new Vector(this.x * that, this.y * that, this.z * that);
};


Vector.prototype.over = function(that) {
  return new Vector(this.x / that, this.y / that, this.z / that);
};


Vector.prototype.cross = function(that) {
    return new Vector(
        this.y * that.z - this.z * that.y,
        this.z * that.x - this.x * that.z,
        this.x * that.y - this.y * that.x);
};


Vector.prototype.dot = function(that) {
  return this.x * that.x + this.y * that.y + this.z * that.z;
};
