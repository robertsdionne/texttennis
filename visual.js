/**
 * @param {WebGLProgram} program
 * @param {WebGLBuffer} buffer
 * @param {number} count
 * @param {Vector=} opt_color
 */
var Visual = function(program, buffer, count, mode, opt_color) {
  this.program = program;
  this.buffer = buffer;
  this.count = count;
  this.mode = mode;
  this.color = opt_color || new Vector(1, 1, 1);
};


/**
 * @param {WebGLRenderingContext} gl
 */
Visual.prototype.disable = function(gl) {
  gl.disableVertexAttribArray(gl.getAttribLocation(this.program, 'attribute_position'));
};


/**
 * @param {WebGLRenderingContext} gl
 */
Visual.prototype.draw = function(gl, projection, position) {
  gl.uniformMatrix4fv(gl.getUniformLocation(this.program, 'uniform_projection'), false, projection);
  gl.uniform3f(
      gl.getUniformLocation(this.program, 'uniform_position'), position.x, position.y, position.z);
  gl.uniform3f(
      gl.getUniformLocation(this.program, 'uniform_color'), this.color.x, this.color.y, this.color.z);
  gl.drawArrays(this.mode, 0, this.count);
};


/**
 * @param {WebGLRenderingContext} gl
 * @param {Float32Array} projection
 * @param {Vector} position
 */
Visual.prototype.enable = function(gl) {
  gl.useProgram(this.program);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
  var attributePosition = gl.getAttribLocation(this.program, 'attribute_position');
  gl.vertexAttribPointer(attributePosition, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(attributePosition);
};
