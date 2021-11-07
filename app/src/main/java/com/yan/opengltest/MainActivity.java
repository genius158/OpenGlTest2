package com.yan.opengltest;

import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private GLSurfaceView gLSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(gLSurfaceView = new TestGLSurfaceView(this, null));
    }

    @Override
    protected void onPause() {
        super.onPause();
        gLSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        gLSurfaceView.onResume();
    }
}