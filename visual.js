/**
 * @param {WebGLProgram} program
 * @param {WebGLBuffer} buffer
 * @param {number} count
 * @param {Vector=} color
 */
var Visual = function(program, buffer, count, opt_color) {
  this.program = program;
  this.buffer = buffer;
  this.count = count;
  this.color = opt_color || new Vector(1, 1, 1);
};


/**
 * @param {WebGLRenderingContext} gl
 */
Visual.prototype.disable = function(gl) {
  gl.disableVertexAttribArray(gl.getAttribLocation(program, 'attribute_position'));
};


/**
 * @param {WebGLRenderingContext} gl
 */
Visual.prototype.draw = function(gl, projection, position, scale) {
  gl.uniformMatrix4fv(gl.getUniformLocation(program, 'uniform_projection'), false, projection);
  gl.uniform3f(
      gl.getUniformLocation(program, 'uniform_position'), position.x, position.y, position.z);
  gl.uniform1f(gl.getUniformLocation(program, 'uniform_scale'), scale);
  gl.uniform3f(
      gl.getUniformLocation(program, 'uniform_color'), this.color.x, this.color.y, this.color.z);
  gl.drawArrays(gl.TRIANGLES, 0, this.count);
};


/**
 * @param {WebGLRenderingContext} gl
 * @param {Float32Array} projection
 * @param {Vector} position
 */
Visual.prototype.enable = function(gl) {
  gl.useProgram(this.program);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
  var attributePosition = gl.getAttribLocation(program, 'attribute_position');
  gl.vertexAttribPointer(attributePosition, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(attributePosition);
};
