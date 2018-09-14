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

static std::string Base64Encode(const unsigned char *input, int length, bool with_new_line, bool url_safe)
{
    BIO * b64 = nullptr;
    BUF_MEM * bptr = nullptr;

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    b64 = BIO_push(b64, BIO_new(BIO_s_mem()));
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    std::stringstream ss;
    ss << bptr->data;
    BIO_free_all(b64);
    if (url_safe) {
        //ss.str().replace("+=/",'-_~');
        auto str = ss.str();
        for (char &i : str) {
            if (i == '+') {
                i = '-';
            }
            if (i == '=') {
                i = '_';
            }
            if (i == '/') {
                i = '~';
            }
        }
        return str;
    }
    return ss.str();
    /*
    char * buff = (char *)malloc(bptr->length + 1);
    memset(buff, 0,bptr->length + 1 );
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    memcpy(xxx, buff, bptr->length);
    BIO_free_all(b64);
    return xxx;
     */
}




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
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}

static size_t WcsBlockCount(utility::size64_t fileLength) {
    int BLOCK_BITS = 22;
    int BLOCK_SIZE = 1 << BLOCK_BITS;

    return ((fileLength + (BLOCK_SIZE - 1)) >> BLOCK_BITS);
}

static utility::string_t WcsFileHash(const utility::string_t &filePath) {

    utility::string_t result;
    utility::string_t *resultD = &result;
    unsigned char BYTE_LOW_4 = 0x16;
    unsigned char BYTE_OVER_4 = 0x96;
    //Concurrency::streams::file_buffer<uint8_t>;
    auto task = Concurrency::streams::file_buffer<uint8_t>::open(filePath, std::ios::in).then(
            [=](Concurrency::streams::streambuf<uint8_t> outFile) {
                utility::size64_t size = outFile.size();
                auto blockCount = WcsBlockCount(size);
                unsigned char finalDigest[SHA_DIGEST_LENGTH + 1];
                if (blockCount <= 1) {
                    auto fSize = size;
                    unsigned char tempDigest[SHA_DIGEST_LENGTH];
                    outFile.set_buffer_size(1024, std::ios::in);

                    SHA_CTX shaCtx;
                    SHA1_Init(&shaCtx);
                    while (fSize > 0) {
                        unsigned char buffer[1024];
                        auto actSize = outFile.getn(buffer, 1024).get();
                        // calc sha1
                        SHA1_Update(&shaCtx, buffer, actSize);
                        fSize -= actSize;
                    }
                    SHA1_Final(tempDigest, &shaCtx);
                    finalDigest[0] = BYTE_LOW_4;
                    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {//SHA1 20
                        finalDigest[i + 1] = tempDigest[i];
                    }
                } else {
                    int BLOCK_BITS = 22;
                    int BLOCK_SIZE = 1 << BLOCK_BITS;//2^22 = 4M
                    unsigned char rec[SHA_DIGEST_LENGTH * blockCount];
                    unsigned char tempDigest[SHA_DIGEST_LENGTH];
                    finalDigest[0] = BYTE_OVER_4;
                    int i, cnt = 0;
                    outFile.set_buffer_size(1024, std::ios::in);
                    auto fSize = size;
                    for (i = 0; i < blockCount; i++) {
                        SHA_CTX shaCtx;
                        SHA1_Init(&shaCtx);
                        // Read Block..
                        size_t currentRead = 0;
                        while (fSize > 0) {
                            unsigned char buffer[1024];
                            auto actSize = outFile.getn(buffer, 1024).get();
                            // calc sha1
                            SHA1_Update(&shaCtx, buffer, actSize);
                            fSize -= actSize;
                            currentRead += actSize;
                            if (currentRead >= BLOCK_SIZE) {
                                break;
                            }
                        }
                        SHA1_Final(tempDigest, &shaCtx);
                        for (unsigned char j : tempDigest) {
                            rec[cnt++] = j;
                        }
                    }
                    //again. sh1
                    unsigned char fDigest[SHA_DIGEST_LENGTH];
                    SHA_CTX shaCtx;
                    SHA1_Init(&shaCtx);
                    SHA1_Update(&shaCtx, rec, SHA_DIGEST_LENGTH * blockCount);
                    SHA1_Final(fDigest, &shaCtx);
                    for (i = 0; i < SHA_DIGEST_LENGTH; ++i) {//0x96
                        finalDigest[i + 1] = fDigest[i];
                    }
                }
                //unsigned char * enc_output ;
                auto res = Base64Encode(finalDigest, SHA_DIGEST_LENGTH + 1, false, true);
                /*
                if( urlTask->hash == utility::conversions::to_string_t(res)){
                    urlTask->status = file_download_status::finished;
                }else{
                    urlTask->status = file_download_status::failed;
                }
                 */
                //free(res);
                *resultD = utility::conversions::to_string_t(res);
                return outFile.close();
            });
    try {
        task.get();
        return result;
    }
    catch (std::exception &e) {
        return result;
    }
}


#endif //FUCK_COMMON_UTIL_H
