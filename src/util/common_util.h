//
// Created by zzzhr on 2018/8/29.
//

#ifndef FUCK_COMMON_UTIL_H
#define FUCK_COMMON_UTIL_H

#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>
#include <wx/clipbrd.h>

static wxString ConvertSizeToDisplay(int64_t size){
    const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    int i = 0;
    while (size > 1024 && i < 9) {
        size /= 1024;
        i++;
    }
    return wxString::Format(_T("%lld%s"), size, units[i]);
}

static wxString ConvertTimeToDisplay(time_t time,  const std::string& format = "%Y-%m-%d %H:%M:%S"){
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), format.data()); // 4 time
    //current.
    return (wxString::Format(_T("%s"),ss.str())); // 4 time
}

static wxString Utf8MD5(const wxString& str) {
	unsigned char digest[16];
	const char* string = str.data();

	//printf("string length: %d\n", strlen(string));

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, string, strlen(string));
	MD5_Final(digest, &ctx);

	char mdString[33];
	for (int i = 0; i < 16; i++)
		sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
	return wxString::FromAscii(mdString);

}


static void CopyTextToClipboard(const wxString& str) {
	if (wxTheClipboard->Open())
	{
		// This data objects are held by the clipboard,
		// so do not delete them in the app.
		wxTheClipboard->SetData(new wxTextDataObject(str));
		wxTheClipboard->Close();
	}

}

static wxString CopyTextToClipboard() {
	wxString x = _T("");
	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported(wxDF_TEXT))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData(data);
			x = data.GetText();
		}
		wxTheClipboard->Close();
	}
	return x;
}

#endif //FUCK_COMMON_UTIL_H
