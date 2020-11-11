//
// Created by JunhaoW on 2020/2/15.
//

#ifndef MAIN_MYTOOL_CHECK_ERROR_H_
#define MAIN_MYTOOL_CHECK_ERROR_H_


#include <glad/glad.h>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)


#endif //MAIN_MYTOOL_CHECK_ERROR_H_
