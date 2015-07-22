package com.graphics.input;

import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWMouseButtonCallback;

import com.graphics.math.Vector3f;

public class Mouse extends GLFWMouseButtonCallback {

	public static boolean[] buttons = new boolean[10];
	public static Vector3f[] position = new Vector3f[10];
	@Override
	public void invoke(long window, int button, int action, int mods) {
		buttons[button] = action != GLFW.GLFW_RELEASE;
		position[button] = new Vector3f( MousePosition.getX(), MousePosition.getY(), 0.0f );
		System.out.println("Button " + button + " pressed at " + position[button].x + "," + position[button].y);
	}

	public static boolean isButtonDown( int button ) {
		return buttons[button];
	}

	public static Vector3f getPosition( int button ) {
		return position[button];
	}
}
