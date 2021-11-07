package com.yan.opengltest;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author Bevan (Contact me: https://github.com/genius158)
 * @since 2021/11/6
 */
public class TestGLSurfaceView extends GLSurfaceView {
    public TestGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        setRenderer(new GlRender());
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    public static class GlRender implements GLSurfaceView.Renderer{
        NativeRender nativeRender = new NativeRender();
        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            nativeRender.onSurfaceCreated();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            nativeRender.onSurfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            nativeRender.onDrawFrame();
        }
    }
}
