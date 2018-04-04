package com.graphics.input;

import org.lwjgl.glfw.*;
public class MousePosition extends GLFWCursorPosCallback {

	private static float x, y;
	
	@Override
	public void invoke(long window, double xpos, double ypos) {
		x = (float)xpos;
		y = (float)ypos;
		//System.out.println("x = " + x + " y = " + y);
	}
	
	public static float getX() {
		return x;
	}
	
	public static float getY() {
		return y;
	}

}
