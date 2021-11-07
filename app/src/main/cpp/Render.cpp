//
// Created by yan xianwei on 2021/11/6.
//


#include <jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include "RenderContext.h"


extern "C" jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_yan_opengltest_NativeRender_nInit(JNIEnv *env, jobject obj) {
    return reinterpret_cast<long >(new RenderContext());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_yan_opengltest_NativeRender_nOnSurfaceCreated(JNIEnv *env, jobject thiz,
                                                       jlong pRender) {

    const char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    const char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 1.0, 1.0 );  \n"
            "}                                            \n";

    auto *renderContext = reinterpret_cast<RenderContext *>(pRender);
    if (renderContext == nullptr)return;
    renderContext->AttachShader2Program(RenderContext::LoadShader(GL_VERTEX_SHADER, vShaderStr),
                                        RenderContext::LoadShader(GL_FRAGMENT_SHADER, fShaderStr));
    renderContext->OnSurfaceCreated();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yan_opengltest_NativeRender_nOnSurfaceChanged(JNIEnv *env, jobject thiz, jlong pRender,
                                                       jint width, jint height) {
    auto *renderContext = reinterpret_cast<RenderContext *>(pRender);
    if (renderContext == nullptr)return;
    renderContext->OnSurfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yan_opengltest_NativeRender_nOnDrawFrame(JNIEnv *env, jobject thiz, jlong pRender) {
    auto *renderContext = reinterpret_cast<RenderContext *>(pRender);
    if (renderContext == nullptr)return;
    renderContext->OnDrawFrame();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_yan_opengltest_NativeRender_nRelease(JNIEnv *env, jobject thiz, jlong pRender) {
    auto *renderContext = reinterpret_cast<RenderContext *>(pRender);
    if (renderContext == nullptr)return;
    renderContext->Release();
    delete renderContext;
}
