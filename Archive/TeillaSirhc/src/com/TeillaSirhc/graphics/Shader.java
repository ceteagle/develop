package com.TeillaSirhc.graphics;

public class Shader extends com.graphics.Shader {

	public static com.graphics.Shader BG, SPRITE;	
	
	public Shader(String vertex, String fragment) {
		super(vertex, fragment);
	}
	
	public static void loadAll() {
		BG = new Shader("shaders/bg.vert", "shaders/bg.frag");
		SPRITE = new com.graphics.Shader("shaders/sprite.vert", "shaders/sprite.frag");
	}
}
