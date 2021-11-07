package com.yan.opengltest;

/**
 * @author Bevan (Contact me: https://github.com/genius158)
 * @since 2021/11/6
 */
public class NativeRender {

    static {
        System.loadLibrary("render");
    }

    long pNativeRender;

    NativeRender() {
        pNativeRender = nInit();
    }

    public void release() {
        nRelease(pNativeRender);
    }

    public void onSurfaceCreated() {
        nOnSurfaceCreated(pNativeRender);
    }

    public void onSurfaceChanged(int width, int height) {
        nOnSurfaceChanged(pNativeRender, width, height);
    }

    public void onDrawFrame() {
        nOnDrawFrame(pNativeRender);
    }

    private native long nInit();

    private native void nRelease(long pNativeRender);

    private native void nOnSurfaceCreated(long pNativeRender);

    private native void nOnSurfaceChanged(long pNativeRender, int width, int height);

    private native void nOnDrawFrame(long pNativeRender);


}
