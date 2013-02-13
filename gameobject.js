/**
 * The base game object.
 * @param {Visual} visual The visual.
 * @param {number=} opt_mass The mass, default: 1.
 * @param {Vector=} opt_position The initial position, default: 0.
 * @param {Vector=} opt_velocity The initial velocity, default: 0.
 * @param {number=} opt_scale The scale, default: 1.
 */
var GameObject = function(visual, opt_mass, opt_position, opt_velocity, opt_scale) {
  /**
   * @type {Visual}
   */
  this.visual = visual;

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
   * @type {number}
   */
   this.scale = opt_scale || 1;

  /**
   * @type {!Vector}
   */
  this.force = Vector.ZERO;
};


Object.defineProperties(GameObject.prototype, {
  velocity: {
    /**
     * @return {!Vector} The velocity, derived from momentum.
     */
    get: function() {
      return this.momentum.over(this.mass);
    },
    /**
     * @param {!Vector} velocity The new velocity.
     */
    set: function(velocity) {
      this.momentum = velocity.times(this.mass);
    }
  },
  acceleration: {
    /**
     * @return {!Vector} The acceleration, derived from force.
     */
    get: function() {
      return this.force.over(this.mass);
    },
    /**
     * @param {!Vector} acceleration The new acceleration.
     */
    set: function(acceleration) {
      this.force = acceleration.times(this.mass);
    }
  }
});


/**
 * @param {WebGLRenderingContext} gl
 * @param {Float32Array} projection
 */
GameObject.prototype.draw = function(gl, projection) {
  this.visual.enable(gl);
  this.visual.draw(gl, projection, this.position, this.scale);
  this.visual.disable(gl);
};


/**
 * @param {number} dt
 */
GameObject.prototype.update = function(dt) {
  this.position = this.position.plus(this.velocity.times(dt));
  this.momentum = this.momentum.plus(this.force.times(dt));
  this.force = Vector.ZERO;
};
