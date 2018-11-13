//
// Created by zzzhr on 2018/11/9.
//

#include "common_util.h"
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <chrono>
using namespace qingzhen;
std::string util::random_string() {
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::default_random_engine generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str
}

utility::string_t qingzhen::util::format_remote_path(utility::string_t str)
{
	for (auto &c_char : str) {
		if (c_char == _XPLATSTR('\\')) {
			c_char = _XPLATSTR('/');
		}
	}
	return str;
}

utility::string_t util::random_string_t() {
    return utility::conversions::to_string_t(random_string());
}

utility::string_t util::utf8_to_md5(utility::string_t &str) {
    unsigned char digest[16];
    const char* string = utility::conversions::to_utf8string(str).c_str();
    //const char* string = "";
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, string, strlen(string));
    MD5_Final(digest, &ctx);
    //MD5_DIGEST_LENGTH
    char mdString[MD5_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
    std::string res = std::string(mdString);
    return utility::conversions::to_string_t(res);
}

time_t util::get_current_linux_timestamp() {
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

utility::string_t qingzhen::util::convert_path(const common_fs::path & path)
{
//#if defined(_WIN32) || defined(__WINDOWS__) || defined(__WXMSW__)
#ifdef	_UTF16_STRINGS
	return utility::string_t(path.wstring()); //compatible for shit
#else
	return utility::string_t(path.string());
#endif
}
