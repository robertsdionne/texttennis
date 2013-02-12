/**
 * The base game object.
 * @param {number=} opt_mass The mass, default: 1.
 * @param {Vector=} opt_position The initial position, default: 0.
 * @param {Vector=} opt_velocity The initial velocity, default: 0.
 */
var GameObject = function(opt_mass, opt_position, opt_velocity) {
  /**
   * @type {number}
   */
  this.mass = opt_mass || 1;

  /**
   * @type {!Vector}
   */
  this.position = opt_position || Vector.ZERO;

  /**
   * @type {!Vector}
   */
  this.momentum = opt_velocity ? opt_velocity.times(this.mass) : Vector.ZERO;

  /**
   * @type {!Vector}
   */
  this.force = Vector.ZERO;
};


Object.defineProperties(GameObject.prototype, {
  /**
   * The velocity, derived momentum.
   * @type {!Vector}
   */
  velocity: {
    get: function() {
      return this.momentum.over(this.mass);
    },
    set: function(velocity) {
      this.momentum = velocity.times(this.mass);
    }
  },
  /**
   * The acceleration, derived from force.
   * @type {!Vector}
   */
  acceleration: {
    get: function() {
      return this.force.over(this.mass);
    },
    set: function(acceleration) {
      this.force = acceleration.times(this.mass);
    }
  }
});


/**
 * @param {number} dt
 */
GameObject.prototype.update = function(dt) {
  this.position = this.position.plus(this.velocity.times(dt));
  this.momentum = this.momentum.plus(this.force.times(dt));
  this.force = Vector.ZERO;
};
