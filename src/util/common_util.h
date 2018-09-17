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

static std::vector<uint8_t > ReadFileToVector(Concurrency::streams::streambuf<uint8_t> & outFile,const utility::size64_t & size){
    std::vector<uint8_t> bufferVector = std::vector<uint8_t >(size);
    // create block 0, read block data.
    size_t read = 0;
    uint8_t buffer[1024];
    while (read < size){
        auto data = outFile.getn(buffer, 1024).get();
        for(size_t i = 0; i < data; i++){
			auto currentReadIndex = i + read;
			if (currentReadIndex >= size) {
				return bufferVector;
			}
			bufferVector[currentReadIndex] = buffer[i];
        }
        read += data;
    }
    return bufferVector;
}

static web::http::client::http_client CreateWcsClient(const utility::string_t& url){
    // = ;
    web::http::client::http_client_config config;
    config.set_timeout(std::chrono::seconds(30));
    config.set_chunksize(1024 * 4);

    web::http::client::http_client client(url, config);

    return client;
}

static web::http::http_request CreateWcsRequest(const web::http::method& mtd = web::http::methods::POST){
    // = ;
    web::http::http_request request(mtd);
    auto & headers = request.headers();
    headers.add(web::http::header_names::accept, _XPLATSTR("application/json"));
    return request;
}


static utility::size64_t WcsBlockCount(utility::size64_t fileLength) {
	utility::size64_t BLOCK_BITS = 22;
	utility::size64_t BLOCK_SIZE = 1 << BLOCK_BITS;

    return ((fileLength + (BLOCK_SIZE - 1)) >> BLOCK_BITS);
}

static void WcsStartPost(const utility::string_t &filePath, const utility::string_t &token, const utility::string_t &url) {

}

static utility::string_t WcsFileHash2(const utility::string_t &filePath) {
	utility::string_t result;
	auto task = Concurrency::streams::file_buffer<uint8_t>::open(filePath, std::ios::in).then([](Concurrency::streams::streambuf<uint8_t> outFile) {
		//outFile.nextc()
		utility::size64_t size = outFile.size();
		return outFile.close();
	});
	task.get();
	return result;
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
                const auto blockCount = WcsBlockCount(size);
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
                    unsigned int BLOCK_BITS = 22;
					auto BLOCK_SIZE = static_cast<unsigned int>(1 << BLOCK_BITS);//2^22 = 4M
                    //unsigned char rec[];
					std::vector<unsigned char> rec = std::vector<unsigned char>(SHA_DIGEST_LENGTH * blockCount);
                    unsigned char tempDigest[SHA_DIGEST_LENGTH];
                    finalDigest[0] = BYTE_OVER_4;
					unsigned int i, cnt = 0;
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
                    SHA1_Update(&shaCtx, rec.data(), SHA_DIGEST_LENGTH * blockCount);
                    SHA1_Final(fDigest, &shaCtx);
                    for (i = 0; i < SHA_DIGEST_LENGTH; ++i) {//0x96
                        finalDigest[i + 1] = fDigest[i];
                    }
                }
                //unsigned char * enc_output ;
                //auto res = Base64Encode(finalDigest);
                std::vector<unsigned char > v(std::begin(finalDigest), std::end(finalDigest));
                auto base64 = utility::conversions::to_base64(v);
                //char * ch = base64.data();
				
                for (auto &i : base64) {
                    if (i == '+') {
                        i = '-';
                    }

                    if (i == '/') {
                        i = '_';
                    }
                }

                *resultD = base64;
                return outFile.close();
            });
    try {
        task.get();
        return result;
    }
    catch (std::exception &e) {
		std::cout << e.what() << std::endl;
        return result;
    }
}


#endif //FUCK_COMMON_UTIL_H
