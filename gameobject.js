var GameObject = function(opt_mass, opt_position, opt_velocity) {
  this.mass = opt_mass || 1;
  this.position = opt_position || Vector.ZERO;
  this.momentum = opt_velocity ? opt_velocity.times(this.mass) : Vector.ZERO;
  this.force = Vector.ZERO;
};


Object.defineProperties(GameObject.prototype, {
  "velocity": {
    get: function() {
      return this.momentum.over(this.mass);
    },
    set: function(velocity) {
      this.momentum = velocity.times(this.mass);
    }
  },
  "acceleration": {
    get: function() {
      return this.force.over(this.mass);
    },
    set: function(acceleration) {
      this.force = acceleration.times(this.mass);
    }
  }
});


GameObject.prototype.update = function(dt) {
  this.position = this.position.plus(this.velocity.times(dt));
  this.momentum = this.momentum.plus(this.force.times(dt));
  this.force = Vector.ZERO;
};
