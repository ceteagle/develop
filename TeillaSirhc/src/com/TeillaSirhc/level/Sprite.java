package com.TeillaSirhc.level;

import static org.lwjgl.glfw.GLFW.*;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.Random;

import org.lwjgl.BufferUtils;
import org.lwjgl.glfw.GLFWvidmode;
import org.lwjgl.opengl.GL11;

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
	
		/*int screenCoords[] = getScreenCoords( width, height, 0.0f);
		if(screenCoords != null)
		{
			System.out.println("screen width = " + screenCoords[0] + " height = " + screenCoords[1]);
		}*/
		
		int bottom = height / -2;
		int top = height / 2;
		int left = width / -2;
		int right = width / 2;

		if(position.x >= 9.5f)
			delta *= -1.0f;
		else if( position.x <= -9.5f)
			delta *= -1.0f;
		
		if(position.y >= 5.0f)
			delta *= -1.0f;
		else if( position.y <= -5.0 )
			delta *= -1.0f;
		
		position.x -= delta*random.nextFloat();	
		position.y -= delta*random.nextFloat();
		
		//rot = -delta * 90.0f;
		if(rot > 90.0f)
			rot = 0;
		else
			rot += 3.0f;
	}
	/*
	public Vector3f convertScreenToWorldCoords(int x, int y)
    {
        int[] viewport = new int[4];
        Matrix4f modelViewMatrix = Shader.SPRITE.getUniform("mv_matrix");
        
        GL.GetFloat(GetPName.ModelviewMatrix, out modelViewMatrix);
        GL.GetFloat(GetPName.ProjectionMatrix, out projectionMatrix);
        GL.GetInteger(GetPName.Viewport, viewport);
        Vector2 mouse;
        mouse.X = x;
        mouse.Y = viewport[3] - y;
        Vector4 vector = UnProject(ref projectionMatrix, modelViewMatrix, new Size(viewport[2], viewport[3]), mouse);
        Point coords = new Point((int)vector.X, (int)vector.Y);
        return coords;
    }
	*/
	
	public static int[] getScreenCoords(double x, double y, double z) {
	    FloatBuffer screenCoords = BufferUtils.createFloatBuffer(4);
	    IntBuffer viewport = BufferUtils.createIntBuffer(16);
	    FloatBuffer modelView = BufferUtils.createFloatBuffer(16);
	    FloatBuffer projection = BufferUtils.createFloatBuffer(16);
	    
	    GL11.glGetFloatv(GL11.GL_MODELVIEW_MATRIX, modelView);
	    GL11.glGetFloatv(GL11.GL_PROJECTION_MATRIX, projection);
	    GL11.glGetIntegerv(GL11.GL_VIEWPORT, viewport);
	    boolean result = GLU.gluProject((float) x, (float) y, (float) z, modelView, projection, viewport, screenCoords);
	    if (result) {
	        return new int[] { (int) screenCoords.get(3), (int) screenCoords.get(1) };
	    }
	    return null;
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
