//
// Created by zzzhr on 2018/9/10.
//

#include "file_download_model.h"
#include "../util/common_api.h"

using namespace web::http;
using namespace web::http::client;

//using namespace functional::http::utilities;

FileDownloadModel& FileDownloadModel::Instance() {
    static FileDownloadModel c;
    return c;

}


void FileDownloadModel::DownloadTestFile(const utility::string_t &url) {
    http_client_config config;
    config.set_chunksize(512);

    http_client client(url, config);
    const method mtd = methods::GET;

    utility::size64_t upsize = 4711u, downsize = 4711u;
    int calls = 0;

    http_request msg(mtd);
    msg.set_progress_handler(
            [&](message_direction::direction direction, utility::size64_t so_far)
            {
                std::cout << "Progress called..." << so_far << std::endl;
                calls += 1;
                if (direction == message_direction::upload)
                    upsize = so_far;
                else
                    downsize = so_far;
                //msg.body()
                //msg.get_response()
            });

    //const size_t repeats = 6000;

    /*
    test_http_server::scoped_server scoped(m_uri);
    scoped.server()->next_request().then([&](test_request *p_request)
                                         {
                                             http_asserts::assert_test_request_equals(p_request, mtd, U("/"));
                                             std::string resp_data;
                                             for (size_t i = 0; i < repeats; ++i)
                                                 resp_data.append("abcdefghihklmnopqrstuvwxyz");

                                             std::map<utility::string_t, utility::string_t> headers;
                                             headers[U("Content-Type")] = U("text/plain");
                                             p_request->reply(200, utility::string_t(U("OK")), headers, resp_data);
                                         });
                                         */

    auto response = client.request(msg).get();
    //http_asserts::assert_response_equals(response, status_codes::OK);

    //VERIFY_ARE_EQUAL(0, upsize);

    response.content_ready().wait();

    //VERIFY_ARE_EQUAL(26u*repeats, downsize);
    // We don't have very precise control over how much of a message is transferred
    // in each chunk being sent or received, so we can't make an exact comparison here.
    //VERIFY_IS_TRUE(calls > 4);

}

void FileDownloadModel::StartDownloadFile(const web::json::value &value) {
    // detr
    if(value.at(U("type")).as_integer() == 1){
        std::cout << "Explorer all files" << std::endl;
    }
    else{
        DownloadSingleFile(value);

    };
}

void FileDownloadModel::DownloadSingleFile(const web::json::value &value) {
    web::json::value request;
    request[U("path")] = value.at(U("path"));
    CommonApi::Instance().PostData(U("/v1/files/get"),request).then([&](ResponseEntity v){
        //SendCommonThreadEvent(handler,USER_REMOTE_FILE_PAGE_DATA,v, true);
        if(v.success && v.result.has_field(U("downloadAddress"))){
            //std::cout << v.result.at(U("downloadAddress")).as_string() << std::endl;
            this->DownloadTestFile(v.result.at(U("downloadAddress")).as_string());
        }
        else{
            std::cout << "File Could not be download!" << std::endl;
        }
    });
}
