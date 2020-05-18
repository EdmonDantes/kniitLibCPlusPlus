/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_WIN_APP_H
#define KNIITLIBRARY_WIN_APP_H
#include <windows.h>
#include "../core/core.h"

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_API HINSTANCE getApplicationInstance() {
        return GetModuleHandleA(0);
    }

};

#endif //KNIITLIBRARY_WIN_APP_H
