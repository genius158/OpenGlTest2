//
// Created by yan xianwei on 2021/11/6.
//

#include <malloc.h>
#include "RenderContext.h"
#include <GLES3/gl3.h>

#include "Log.h"

RenderContext::RenderContext() {

}

void RenderContext::AttachShader2Program(GLuint vertex, GLuint fragment) {
   programObj = glCreateProgram();
    if (programObj == 0)return;

    glAttachShader(programObj, vertex);
    glAttachShader(programObj, fragment);
}


void RenderContext::OnSurfaceCreated() const {
    LOGE("RenderContext::OnSurfaceCreated");
    if (programObj == 0) return;

    GLint linked;

    // 通过 glLinkProgram 成功链接到一个程序对象。
    glLinkProgram(programObj);

    glGetProgramiv(programObj, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;
        //一个或多个可执行着色器通过 glAttachShader 附加到程序对象来创建，
        // 通过 glComileShader 成功编译的 shader 对象，
        // 通过 glLinkProgram 成功链接到一个程序对象。
        // 通过调用 glUseProgram 将这些可执行的对象组成了当前的状态。
        // 程序对象可以通过 glDeleteProgram 来删除。
        // 当他不再是当前上下文渲染状态后对象的程序内存将被删除
        glGetProgramiv(programObj, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = (char *) malloc(sizeof(char) * infoLen);

            glGetProgramInfoLog(programObj, infoLen, NULL, infoLog);
            LOGE("Error linking program:[%s]", infoLog);

            free(infoLog);
        }

        Release();
        return;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void RenderContext::OnSurfaceChanged(int width, int height) {
    LOGE("RenderContext::OnSurfaceChanged [w, h] = [%d, %d]", width, height);
    g_width = width;
    g_height = height;
}

void RenderContext::OnDrawFrame() const {
    LOGE("RenderContext::OnDrawFrame");
    GLfloat vVertices[] = {0.5f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           -0.5f, -0.9f, 0.0f,
                           0.5f, -0.4f, 0.0f
    };

    glViewport(0, 0, g_width, g_height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);


    // 使用程序对象作为当前渲染状态的一部分
    glUseProgram(programObj);
    //定义通用顶点属性数据的数组
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    //启用或禁用通用顶点属性数组
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


/**
 * private
 * @param shaderType 指定要创建的着色器的类型。
 *        只能是GL_VERTEX_SHADER或GL_FRAGMENT_SHADER。
 *        GL_VERTEX_SHADER类型的着色器是一个用于在可编程顶点处理器上运行的着色器。
 *        GL_FRAGMENT_SHADER类型的着色器是一个着色器，旨在在可编程片段处理器上运行。
 * @param source
 * @return
 */
GLuint RenderContext::LoadShader(GLenum shaderType, const char *source) {
    // 创建一个 shader 对象
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)return 0;
    // 替换着色器对象中的source
    // shader 着色器对象句柄
    // count 自定字符串和长度数组中的元素个数
    glShaderSource(shader, 1, &source, NULL);
    // 编译一个着色器对象
    glCompileShader(shader);

    GLint compiled;

    // 从着色器对象返回对应的参数
    // 检测着色器编译是否成功
    // [
    //      GL_SHADER_TYPE
    //      如果着色器是顶点着色器对象，则params返回GL_VERTEX_SHADER;如果着色器是片段着色器对象，则                                  返回GL_FRAGMENT_SHADER。
    //      GL_DELETE_STATUS
    //      如果shader当前被标记为删除，则params返回GL_TRUE，否则返回GL_FALSE。
    //      GL_COMPILE_STATUS
    //      对于支持着色器编译器的实现，如果着色器上的最后一次编译操作成功，则params返回GL_TRUE，否则返回GL_FALSE。
    //      GL_INFO_LOG_LENGTH
    //      对于支持着色器编译器的实现，params返回着色器信息日志的字符数，包括空终止字符（即，存储信息日志所需的字符缓冲区的大小）。 如果着色器没有信息日志，则返回值0。
    //      GL_SHADER_SOURCE_LENGTH
    //      对于支持着色器编译器的实现，params返回构成着色器着色器源的源字符串的串联长度，包括空终止字符。 （即，存储着色器源所需的字符缓冲区的大小）。 如果不存在源代码，则返回0
    // ]
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;
        // 返回着色器日志长度
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *buf = (char *) malloc(sizeof(char) * infoLen);
            //返回 shader 对象的日志信息
            glGetShaderInfoLog(shader, infoLen, NULL, buf);
            LOGE("Error %d  %s", shaderType, buf);
            free(buf);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


void RenderContext::Release() const {
    glDeleteProgram(programObj);
}

