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

#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <boost/uuid/uuid.hpp>

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

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, string, strlen(string));
	MD5_Final(digest, &ctx);
    //MD5_DIGEST_LENGTH
	char mdString[MD5_DIGEST_LENGTH * 2 + 1];
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
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

static wxString CopyTextFromClipboard() {
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


static void WcsSHABytes(const unsigned char * buffer,size_t size, unsigned char * out){
    SHA_CTX shaCtx;
    SHA1_Init( &shaCtx );
    SHA1_Update(&shaCtx,buffer, size > 0 ? size :sizeof(buffer));
    SHA1_Final( out, &shaCtx );
}


static void WcsBin2Hex( unsigned char * src, int len, char * hex )
{
    int i, j;

    for( i = 0, j = 0; i < len; i++, j+=2 )
        sprintf( &hex[j], "%02x", src[i] );
}

/*
static std::string Base64Encode(const unsigned char* input)
{
    //utility::conversions::to_base64(std::vector<const unsigned char>(std::begin(input), std::end(input)))
}
*/



static char * Base64Decode(const unsigned char * input, size_t length, bool with_new_line)
{
    BIO * b64 = nullptr;
    BIO * bmem = nullptr;
    char * buffer = (char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, static_cast<int>(length));
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, static_cast<int>(length));

    BIO_free_all(bmem);

    return buffer;
}










#endif //FUCK_COMMON_UTIL_H
