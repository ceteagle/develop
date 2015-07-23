package com.TeillaSirhc.level;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL12.*;
import static org.lwjgl.opengl.GL30.*;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.Random;

import org.lwjgl.BufferUtils;
import org.lwjgl.glfw.GLFWvidmode;
import org.lwjgl.opengl.GL11;

import com.TeillaSirhc.main;
import com.TeillaSirhc.graphics.Shader;
import com.graphics.Texture;
import com.graphics.VertexArray;
import com.graphics.math.Matrix4f;
import com.graphics.math.Vector3f;
import com.graphics.utils.GLU.GLU;

public class Sprite {
	private float SIZE = 1.0f;
	private VertexArray mesh;
	private Texture texture;
	
	private Vector3f position = new Vector3f();
	private float rot;
	private float delta = -0.1f;
	private Random random = new Random();
	
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
		//position.y -= delta;
		//if (Input.isKeyDown(GLFW_KEY_SPACE)) 
		//	delta = -0.15f;
		//else
		//	delta += 0.01f;

		ByteBuffer vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int width = GLFWvidmode.width(vidmode);
		int height = GLFWvidmode.height(vidmode);

		//System.out.println("sprite postion = " + position.x + ", " + position.y + " window width = " + width + " height = " + height);
	
		int screenCoords[] = convertWorldToWindowCoordinates( position.x, position.y, width, height );
		if(screenCoords == null)
			return;
		
		//System.out.println("window coords x = " + screenCoords[0] + " y = " + screenCoords[1]);
		
		int bottom = height;
		int top = 0;
		int left = 0;
		int right = width;

		if(screenCoords[1] >= bottom)
			delta *= -1.0f;
		else if( screenCoords[1] <= top)
			delta *= -1.0f;
		
		if(screenCoords[0] >= right)
			delta *= -1.0f;
		else if( screenCoords[0] <= left)
			delta *= -1.0f;
		
		position.x -= delta*random.nextFloat();	
		position.y -= delta*random.nextFloat();
		
		if(rot > 90.0f)
			rot = 0.0f;
		else
			rot += 1.0f;
		//System.out.println("** Sprite position (" + position.x + "," + position.y + ")");
	}
	
	public static int[] convertWindowToWorldCoordinates(double x, double y) {
		
		double l1, r1, l2, r2, x2, y2;
		
		ByteBuffer vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int width = GLFWvidmode.width(vidmode);
		int height = GLFWvidmode.height(vidmode);
		
	    /*FloatBuffer screenCoords = BufferUtils.createFloatBuffer(4);
	    IntBuffer viewport = BufferUtils.createIntBuffer(16);
	    FloatBuffer modelView = BufferUtils.createFloatBuffer(16);
	    FloatBuffer projection = BufferUtils.createFloatBuffer(16);
	    
	    glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
	    glGetFloatv(GL_PROJECTION_MATRIX, projection);
	    glGetIntegerv(GL_VIEWPORT, viewport);*/
	    
	    l2 = 0;
	    r2 = width;
	    l1 = main.VIEWPORT_LEFT;
	    r1 = main.VIEWPORT_RIGHT;
	    x2 = (x - l1) * (r2-l2)/(r1-l1) + l2;
	    
	    l2 = 0;
	    r2 = height;
	    l1 = main.VIEWPORT_TOP;
	    r1 = main.VIEWPORT_BOTTOM;
	    y2 = (y - l1) * (r2-l2)/(r1-l1) + l2;
	    
	    return new int[] { (int) x2, (int) y2 };
	}
	
	public static int[] convertWorldToWindowCoordinates(double x, double y, double width, double height ) {
		
		double l1, r1, l2, r2, x2, y2;
		
	    l1 = 0;
	    r1 = width;
	    l2 = main.VIEWPORT_LEFT;
	    r2 = main.VIEWPORT_RIGHT;
	    x2 = (x - l2) * (r1 - l1)/(r2 - l2) + l1;
	    
	    l1 = 0;
	    r1 = height;
	    l2 = main.VIEWPORT_TOP;
	    r2 = main.VIEWPORT_BOTTOM;
	    y2 = (y - l2) * (r1 - l1)/(r2 - l2) + l1;
	    
	    return new int[] { (int) x2, (int) y2 };
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

	public float getX() {
		return position.x;
	}
	public float getY() {
		return position.y;
	}

	public float getSize() {
		return SIZE;
	}
}
