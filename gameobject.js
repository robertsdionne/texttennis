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
  this.position = opt_position || new Vector();

  this.position0 = new Vector();

  this.position1 = new Vector();

  this.velocity0 = new Vector();

  this.velocity1 = new Vector();

  /**
   * @type {!Vector}
   */
  this.oldPosition = this.position.minus((opt_velocity || new Vector()).times(1 / 60));

  /**
   * @type {number}
   */
  this.scale = opt_scale || 1;

  /**
   * @type {!Vector}
   */
  this.force = new Vector();

  /**
   * @type {Array.<Event>}
   */
  this.eventLog = [];
};


/**
 * @type {number}
 */
GameObject.EPSILON = 1e-1;


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
      return this.position.minus(this.oldPosition).times(60);
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


/**
 * @param {WebGLRenderingContext} gl
 * @param {Float32Array} projection
 */
GameObject.prototype.draw = function(gl, projection) {
  this.visual.enable(gl);
  this.visual.draw(gl, projection, this.position, this.scale);
  this.visual.disable(gl);
};


GameObject.prototype.calculateForces = function(dt) {
  this.position = this.position.plus(this.force.over(this.mass).times(dt*dt));
};


GameObject.prototype.saveEvent0 = function() {
  this.position0 = this.position.times(1);
  this.velocity0 = this.velocity.times(1);
};


GameObject.prototype.saveEvent1 = function() {
  this.position1 = this.position.times(1);
  this.velocity1 = this.velocity.times(1);
};


GameObject.prototype.updateEventLog = function() {
  // if (this.velocity0.x < 0 && this.velocity1.x > 0) {
  //   this.eventLog.push('right');
  // }
  // if (this.velocity1.x < 0 && this.velocity0.x > 0) {
  //   this.eventLog.push('left');
  // }
  // if (this.velocity0.y < 0 && this.velocity1.y > 0) {
  //   this.eventLog.push('forward');
  // }
  // if (this.velocity1.y < 0 && this.velocity0.y > 0) {
  //   this.eventLog.push('backward');
  // }
  // if (this.velocity0.z < 0 && this.velocity1.z > 0) {
  //   this.eventLog.push('bounce');
  // }
  // if (this.velocity1.z < 0 && this.velocity0.z > 0) {
  //   this.eventLog.push('fall');
  // }
  // document.getElementById('eventLog').textContent = this.eventLog.join();
};


/**
 * @param {number} dt
 * @param {boolean=} opt_debug
 */
GameObject.prototype.update = function(dt, opt_debug) {
  var newPosition = this.position.times(2).minus(this.oldPosition);
  this.oldPosition = this.position;
  this.position = newPosition;
  if (opt_debug) {
    var ids = ['positionX', 'positionY', 'positionZ', 'velocityX', 'velocityY', 'velocityZ'];
    var data = [this.position.x, this.position.y, this.position.z, this.velocity.x, this.velocity.y, this.velocity.z];
    for (var i = 0; i < ids.length; ++i) {
      var value = Math.round(data[i] * 1000) / 1000;
      var prefix = value > 0 ? '\u00A0' : '';
      document.getElementById(ids[i]).textContent = prefix + value;
    }
  }
};
