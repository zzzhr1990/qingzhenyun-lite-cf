//
// Created by zzzhr on 2018/10/27.
//

#include <cpprest/filestream.h>
#include "cpprest/containerstream.h"
#include "config_model.h"

#include "../common/common_fs.h"
//using namespace qingzhen::model;
qingzhen::model::config_model &qingzhen::model::config_model::instance() {
    //return ;
    static config_model c;
    return c;


}

void qingzhen::model::config_model::update_token(const utility::string_t &token) {
    if(token.empty()){
        return;
    }
    config.token = token;
    // trying to save
    auto token_file_path = this->get_current_path();
    if(token_file_path.empty()){
        return;
    }
    if(token_file_path.at(token_file_path.length() - 1) != common_fs::path::preferred_separator){
        token_file_path += common_fs::path::preferred_separator;
    }
    // try and save

    token_file_path += _XPLATSTR(".qingzhen_token_store");

    web::json::value val;
    val[_XPLATSTR("token")] = web::json::value::string(token);
    this->async_write_json(token_file_path, val);
    //std::cout << "Update token: " << token_file_path << std::endl;
}

utility::string_t qingzhen::model::config_model::get_current_path() {
	if (!this->config_path.empty()) {
		return config_path;
	}
    try {
        common_fs::path p = common_fs::current_path();
		this->config_path = utility::conversions::to_string_t(p.string());
		return this->config_path;
    }catch (std::exception &ex){
        std::cout << ex.what() << std::endl;
        return utility::string_t();
    }

}

void qingzhen::model::config_model::async_write_json(utility::string_t path, web::json::value json) {


    utility::stringstream_t ost;
    try {
        json.serialize(ost);
    }catch (std::exception &s){
        std::cout << "Ser json failed" << s.what() << std::endl;
        return;
    }
    std::string result = utility::conversions::to_utf8string(ost.str());

    auto fin = pplx::create_task([path,json,result]()->void {
        auto fileBuffer = std::make_shared<concurrency::streams::streambuf<char>>();
        auto cx = concurrency::streams::file_buffer<char>::open(path, std::ios::out | std::ios::binary | std::ios::trunc).then(
                [&json, &fileBuffer,&result](concurrency::streams::streambuf <char> outFile) {

                    *fileBuffer = outFile;
                    auto c = result.c_str();
                    return outFile.putn_nocopy(c, strlen(c));
                }).then([fileBuffer](size_t size){ return fileBuffer->close(); });

        try {
            cx.get();
        } catch (std::exception &ex) {
            if(fileBuffer != nullptr){
                fileBuffer->close();
            }
        }
    });

	pplx::create_task([fin]() {
		try {
			fin.get();
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
			return;
		}
	});
}

pplx::task<std::pair<bool, web::json::value>> qingzhen::model::config_model::async_read_json(utility::string_t path) {
    //return pplx::task<std::pair<bool, web::json::value>>();

    auto fin = pplx::create_task([path]()-> std::pair<bool, web::json::value> {
        auto fileBuffer = std::make_shared<concurrency::streams::streambuf<char>>();
        concurrency::streams::stringstreambuf ost;
        auto cx = concurrency::streams::file_buffer<char>::open(path, std::ios::in | std::ios::binary).then(
                [&fileBuffer,&ost](concurrency::streams::streambuf <char> inFile) {
                    *fileBuffer = inFile;
                    return inFile.create_istream().read_to_end(ost);
                }).then([fileBuffer](size_t size){ return fileBuffer->close(); });
        try {
            cx.get();
            auto json = web::json::value::parse(utility::conversions::to_string_t(ost.collection()));
            return std::make_pair(true, json);
        } catch (std::exception &ex) {
            if(fileBuffer != nullptr){
                fileBuffer->close();
            }
            std::cout << "read json exp" << std::endl;
            return std::make_pair(true, web::json::value());
        }
    });

	auto ccx = pplx::create_task([fin]() {
		try {
			return fin.get();
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
			return std::make_pair(true, web::json::value());
		}
	});
    return ccx;
}

pplx::task<utility::string_t> qingzhen::model::config_model::async_read_token() {
    auto token_file_path = this->get_current_path();
    if(token_file_path.empty()){
        return pplx::task_from_result(utility::string_t());
    }
    if(token_file_path.at(token_file_path.length() - 1) != common_fs::path::preferred_separator){
        token_file_path += common_fs::path::preferred_separator;
    }

    // try and save

    token_file_path += _XPLATSTR(".qingzhen_token_store");
    if(!common_fs::exists(token_file_path)){
        return pplx::task_from_result(utility::string_t());
    }

    auto cx = pplx::create_task([token_file_path,this](){
        auto x = this->async_read_json(token_file_path).get();
        if(!x.first){
            return utility::string_t();
        } else {
            auto val = x.second;
            if(val.has_field(_XPLATSTR("token"))){
                return val.at(_XPLATSTR("token")).as_string();
            } else {
                return utility::string_t();
            }
        }
    });
    return cx;
}

void qingzhen::model::config_model::set_config_path(utility::string_t path)
{
	this->config_path = path;
}

