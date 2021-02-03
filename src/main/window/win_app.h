/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_WIN_APP_H
#define KNIITLIBRARY_WIN_APP_H

//#ifndef NOMINMAX
//#define NOMINMAX
//#endif
//
#include <Windows.h>
#include <tchar.h>
#include "../core/core.h"
#include "../core/string.h"
#include "../core/codecs.h"

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_API HINSTANCE getApplicationInstance() {
        return GetModuleHandleA(0);
    }

    KNIIT_LIB_API String createChooseFileDialog(String* title, String* fileFilter, DWORD flags) {
        TCHAR* filename = new TCHAR[MAX_PATH];

                #ifdef _UNICODE
                    const Codec* codec = Codecs::UTF16();
                #else
                    const Codec* codec = Codecs::ASCII();
                #endif

        OPENFILENAME ofn;
        ZeroMemory(filename, sizeof(*filename));
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        if (fileFilter != nullptr && fileFilter != 0) {
            ofn.lpstrFilter = (TCHAR*)fileFilter->to(codec, true, ByteOrder::BIG_ENDIAN).toArray();
        }
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = title != nullptr && title != 0 ? (TCHAR*)title->to(codec, true, ByteOrder::BIG_ENDIAN).toArray() : _T("Please choose file");
        ofn.Flags = flags;

        if (GetOpenFileName(&ofn)) {
            return std::move(String(filename));
        } else {
            return String();
        }
    }

};

#endif //KNIITLIBRARY_WIN_APP_H
