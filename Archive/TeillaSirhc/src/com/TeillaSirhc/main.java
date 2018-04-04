package com.TeillaSirhc;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL13.*;
import static org.lwjgl.system.MemoryUtil.*;

import java.nio.ByteBuffer;

import org.lwjgl.glfw.GLFWvidmode;
import org.lwjgl.opengl.GLContext;

import com.TeillaSirhc.graphics.Shader;
import com.TeillaSirhc.level.Level;
import com.graphics.input.Input;
import com.graphics.input.Mouse;
import com.graphics.input.MousePosition;
import com.graphics.math.Matrix4f;

public class main implements Runnable  {
	private int width = 1280;
	private int height = 720;
	
	private Thread thread;
	private boolean running = false;
	
	private long window;
	
	private Level level;
	
	// Callbacks
	private static Input input = new Input();
	private static MousePosition mousePosition = new MousePosition();
	private static Mouse mouse = new Mouse();
	
	
	public void start() {
		running = true;
		thread = new Thread(this, "Teilla Sirhc");
		thread.start();
	}
	
	public void run() {
		init();	// must be on same thread as render()
		long lastTime = System.nanoTime();
		double delta = 0.0;
		double ns = 1000000000.0 / 60.0;
		int updates = 0;
		int frames = 0;
		long timer = System.currentTimeMillis();
		
		while(running) {
			long now = System.nanoTime();
			delta += (now - lastTime) / ns;
			if(delta >= 1.0) {
				update();
				updates++;
				delta--;
			}
			render();
			frames++;
			if( System.currentTimeMillis() - timer > 1000 ) {
				timer += 1000;
				System.out.println(updates + " ups, " + frames + " fps");
				updates = 0;
				frames = 0;
			}
			
			if(glfwWindowShouldClose(window) == GL_TRUE) {
				running = false;
			}
		}
	}
	
	private void init() {
		if( glfwInit() == GL_FALSE) {
			return;
		}
		
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		window = glfwCreateWindow(width, height, "Teilla Sirhc", NULL, NULL);
		
		ByteBuffer vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xpos = (GLFWvidmode.width(vidmode) - width) / 2;
		int ypos = (GLFWvidmode.height(vidmode) - height) / 2;
		glfwSetWindowPos(window, xpos, ypos);
		
		glfwSetKeyCallback(window, input);
		glfwSetCursorPosCallback(window, mousePosition);
		glfwSetMouseButtonCallback(window, mouse);
		
		glfwMakeContextCurrent(window);
		glfwShowWindow(window);

		GLContext.createFromCurrent();

		glClearColor(1.0f,  1.0f,  1.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE1);
		
		System.out.println("OpenGL: " + glGetString(GL_VERSION));
		
		Shader.loadAll();
		
		//Shader.BG.enable();

		Matrix4f pr_matrix = Matrix4f.orthographic(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.f * 9.0f / 16.0f, -1.0f, 1.0f);
		Shader.BG.setUniformMat4f("pr_matrix", pr_matrix);
		Shader.BG.setUniform1i("tex", 1);
		
		Shader.SPRITE.setUniformMat4f("pr_matrix", pr_matrix);
		Shader.SPRITE.setUniform1i("tex", 1);
		
		//Shader.PIPE.setUniformMat4f("pr_matrix", pr_matrix);
		//Shader.PIPE.setUniform1i("tex", 1);
		
		level = new Level();
		
	}
	
	private void update() {
		glfwPollEvents();
		if(Input.keys[GLFW_KEY_SPACE]){
			System.out.println("SPACE!");
		}
		
		level.update();
	}
	
	private void render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 level.render();
		glfwSwapBuffers(window);
	}
	
	public static void main(String[] args) {
		new main().start();
	}
}
