//
// Created by zzzhr on 2018/9/10.
//

#include "file_download_model.h"
#include "../util/common_api.h"
#include <cpprest/filestream.h>
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace utility;

using namespace web;
using namespace concurrency;
using namespace web::http;
using namespace web::http::client;

//using namespace functional::http::utilities;

FileDownloadModel& FileDownloadModel::Instance() {
    static FileDownloadModel c;
    return c;

}


void FileDownloadModel::DownloadTestFile(const utility::string_t &url) {
    
    const method mtd = methods::GET;
	///cancellation_token cancellation;
    int calls = 0;
	const  utility::string_t outputFileName = U("/Users/zzzhr/Downloads/download.ppp");
	auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
	utility::size64_t upsize = 0, downsize = 0;
	streams::ostream responseStream = streams::bytestream::open_ostream<std::vector<uint8_t>>();
	http_client_config config;
	config.set_chunksize(512);
	http_client client(url, config);
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
	file_buffer<uint8_t>::open(outputFileName, std::ios::out).then([=,&client,&msg](streambuf<uint8_t> outFile) {
		*fileBuffer = outFile;
		msg.set_response_stream(outFile);
		return client.request(msg).wait();
	})
	.then([=](http_response response) -> pplx::task<http_response>
	{
		printf("Response status code %u returned.\n", response.status_code());
		return response.content_ready();
		//return response.body().read_to_end(*fileBuffer);
	}).then([=](http_response response)->pplx::task<void> {
		return fileBuffer->close();
	}).wait();

		// Close the file buffer

		// Wait for the entire response body to be written into the file.;
	std::cout << "Progress end called..." << std::endl;
	//.wait();
	/*
	//auto psp =*fileBuffer;
	//streams::producer_consumer_buffer<uint8_t> rwbuf;
	//auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
	
	file_buffer<uint8_t>::open(outputFileName, std::ios::out).then([=](streambuf<uint8_t> outFile) -> pplx::task<http_response>
	{
		*fileBuffer = outFile;

		// Create an HTTP request.
		// Encode the URI query since it could contain special characters like spaces.
		http_client_config config;
		//config.set_chunksize(2048);
		http_client client(url, config);
		http_request msg(mtd);
		//utility::size64_t upsize = 0, downsize = 0;
		msg.set_progress_handler(
			[&](message_direction::direction direction, utility::size64_t so_far)
		{
			std::cout << "Progress called..." << so_far << std::endl;
			//calls += 1;
			
			if (direction == message_direction::upload)
				upsize = so_far;
			else
				downsize = so_far;
			
			
			//msg.body()
			//msg.get_response()
		});
		//auto ostr = streams::ostream();
		//msg.set_response_stream(outFile);
		
		//http_client client(U("http://www.bing.com/"),);
		//return client.request(methods::GET, uri_builder(U("/search")).append_query(U("q"), searchTerm).to_string());
	});
	fileBuffer->close();
	//
   */
    

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

   // auto response = .get();
    //http_asserts::assert_response_equals(response, status_codes::OK);

    //VERIFY_ARE_EQUAL(0, upsize);

    //response.content_ready().wait();

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
