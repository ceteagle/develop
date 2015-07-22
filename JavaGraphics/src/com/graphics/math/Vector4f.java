package com.graphics.math;

public class Vector4f extends Vector3f {

	public float alpha;
	
	public Vector4f() {
		alpha = 1.0f;
	}
	
	public Vector4f(float x, float y, float z, float alpha) {
		super(x,y,z);
		this.alpha = alpha;
	}
}
