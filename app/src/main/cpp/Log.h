//
// Created by yan xianwei on 2021/11/6.
//

#ifndef OPENGLTEST_LOG_H
#define OPENGLTEST_LOG_H
#include "android/log.h"

#define LOGE(...)\
((void)__android_log_print(ANDROID_LOG_ERROR,"RENDER",__VA_ARGS__))

#endif //OPENGLTEST_LOG_H
