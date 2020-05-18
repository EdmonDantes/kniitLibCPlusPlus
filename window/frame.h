/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_FRAME_H
#define KNIITLIBRARY_FRAME_H

#include <string>
#include "../core/core.h"
#include "win_app.h"

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS Frame {
    private:
        std::string windowClassName;
        HINSTANCE hIns;
        HWND hwnd;
    public:
        Frame();
        Frame(std::string windowClassName);
        Frame(char* windowClassName);
        Frame(HINSTANCE hIns, std::string windowClassName);
        Frame(HINSTANCE hIns, char* windowClassName);
    };



};
#endif //KNIITLIBRARY_FRAME_H
