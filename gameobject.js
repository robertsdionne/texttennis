/**
 * The game object.
 * @param {number=} opt_mass The mass, default: 1.
 * @param {Vector=} opt_position The initial position, default: 0.
 * @param {Vector=} opt_velocity The initial velocity, default: 0.
 */
var GameObject = function(opt_radius, opt_mass, opt_position, opt_velocity) {
  /**
   * @type {number}
   */
  this.radius = opt_radius || 1;

  /**
   * @type {number}
   */
  this.mass = opt_mass || 1;

  /**
   * @type {!Vector}
   */
  this.position = opt_position || new Vector();

  /**
   * @type {!Vector}
   */
  this.previousPosition = this.position.minus((opt_velocity || new Vector()).times(1 / 60));

  /**
   * @type {!Vector}
   */
  this.force = new Vector();
};


Object.defineProperties(GameObject.prototype, {
  momentum: {
    /**
     * @return {!Vector} The momentum, derived from velocity and mass.
     */
    get: function() {
      return this.velocity.times(this.mass);
    }
  },
  velocity: {
    /**
     * @return {!Vector} The velocity, derived position and frame rate.
     */
    get: function() {
      return this.position.minus(this.previousPosition).times(60);
    }
  },
  acceleration: {
    /**
     * @return {!Vector} The acceleration, derived from force.
     */
    get: function() {
      return this.force.over(this.mass);
    }
  }
});


GameObject.prototype.accelerate = function(dt) {
  this.position = this.position.plus(this.force.over(this.mass).times(dt*dt));
  this.force = new Vector();
};


/**
 * @param {number} dt
 * @param {boolean=} opt_debug
 */
GameObject.prototype.inertia = function(dt, opt_debug) {
  var position = this.position.times(2).minus(this.previousPosition);
  this.previousPosition = this.position;
  this.position = position;
};
