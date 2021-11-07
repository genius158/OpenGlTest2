//
// Created by yan xianwei on 2021/11/6.
//

#ifndef OPENGLTEST_RENDERCONTEXT_H
#define OPENGLTEST_RENDERCONTEXT_H


#include <GLES3/gl3.h>
#include <jni.h>
#include <vector>

class RenderContext {
public:
    RenderContext();

    void OnSurfaceCreated() const;

    void OnSurfaceChanged(int width, int height);

    void OnDrawFrame() const;

    void Release() const;

    static GLuint LoadShader(GLenum shaderType, const char *source);

    void AttachShader2Program(GLuint vertex,GLuint fragment);

private:

    jint g_width{};
    jint g_height{};
    GLint programObj;
};


#endif //OPENGLTEST_RENDERCONTEXT_H
