package com.graphics;

import static org.lwjgl.opengl.GL20.*;

import java.util.HashMap;
import java.util.Map;

import com.graphics.math.Matrix4f;
import com.graphics.math.Vector3f;
import com.graphics.utils.ShaderUtils;

public class Shader {

	public static final int VERTEX_ATTRIB = 0;
	public static final int TCOORD_ATTRIB = 1;
	//public static Shader BG, BIRD, PIPE;	
	private final int ID;
	private Map<String,Integer> LocationCache = new HashMap<String, Integer>();
	private boolean enabled = false;
	
	public Shader(String vertex, String fragment) {
		ID = ShaderUtils.load(vertex, fragment);
	}
	
	public static void loadAll() {
		//BG = new Shader("shaders/bg.vert", "shaders/bg.frag");
		//BIRD = new Shader("shaders/bird.vert", "shaders/bird.frag");
		//PIPE = new Shader("shaders/pipe.vert", "shaders/pipe.frag");
	}
	
	public int getUniform(String name) {
		if(LocationCache.containsKey(name)) {
			return LocationCache.get(name);
		}
		
		int result = glGetUniformLocation(ID, name);
		if(result == -1 ) {
			System.err.println("Could not find uniform variable '" + name + ";!");
		}
		
		LocationCache.put(name, result);
		
		return result;
	}

	public void setUniform1i(String name, int value) {
		if( !enabled) enable();
		glUniform1i(getUniform(name), value);	
	}
	
	public void setUniform1f(String name, float value) {
		if( !enabled) enable();
		glUniform1f(getUniform(name), value);	
	}
	
	public void setUniform2fi(String name, float x, float y) {
		if( !enabled) enable();
		glUniform2f(getUniform(name), x, y);	
	}
	
	public void setUniform3f(String name, Vector3f vector) {
		if( !enabled) enable();
		glUniform3f(getUniform(name), vector.x, vector.y, vector.z);	
	}
	
	public void setUniformMat4f(String name, Matrix4f matrix) {
		if( !enabled) enable();
		glUniformMatrix4fv(getUniform(name), false, matrix.toFloatbuffer());
	}
	
	public void enable() {
		glUseProgram(ID);
		enabled = true;
	}
	
	public void disable() {
		glUseProgram(0);
		enabled = false;
	}
}
