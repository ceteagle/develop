package com.TeillaSirhc.level;

import static org.lwjgl.glfw.GLFW.*;

import com.TeillaSirhc.graphics.Shader;
import com.graphics.Texture;
import com.graphics.VertexArray;
import com.graphics.input.Input;
import com.graphics.math.Matrix4f;
import com.graphics.math.Vector3f;

public class Sprite {
	private float SIZE = 1.0f;
	private VertexArray mesh;
	private Texture texture;
	
	private Vector3f position = new Vector3f();
	private float rot;
	private float delta = 0.0f;
	
	public Sprite() {
		float[] vertices = new float[] {
			-SIZE / 2.0f, -SIZE / 2.0f, 0.2f,
			-SIZE / 2.0f,  SIZE / 2.0f, 0.2f,
			 SIZE / 2.0f,  SIZE / 2.0f, 0.2f,
			 SIZE / 2.0f, -SIZE / 2.0f, 0.2f
		};
			
		byte[] indices = new byte[] {
			0, 1, 2,
			2, 3, 0
		};
		
		float[] tcs = new float[] {
			0, 1,
			0, 0,
			1, 0,
			1, 1
		};
		
		mesh = new VertexArray(vertices, indices, tcs);
		texture = new Texture("res/sprite.png");
	}
	
	public void update() {
		position.y -= delta;
		if (Input.isKeyDown(GLFW_KEY_SPACE)) 
			delta = -0.15f;
		else
			delta += 0.01f;
		
		rot = -delta * 90.0f;
	}
	
	public void fall() {
		delta = -0.15f;
	}
	
	public void render() {
		Shader.SPRITE.enable();
		Shader.SPRITE.setUniformMat4f("ml_matrix", Matrix4f.translate(position).multiply(Matrix4f.rotate(rot)));
		texture.bind();
		mesh.render();
		Shader.SPRITE.disable();
	}

	public float getY() {
		return position.y;
	}

	public float getSize() {
		return SIZE;
	}
}
