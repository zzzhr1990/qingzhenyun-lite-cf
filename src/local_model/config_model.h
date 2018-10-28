//
// Created by zzzhr on 2018/10/27.
//

#ifndef QINGZHENYUN_LITE_CONFIG_MODEL_H
#define QINGZHENYUN_LITE_CONFIG_MODEL_H


#include <cpprest/details/basic_types.h>
#include "../entity/config_entity.hpp"

namespace qingzhen::model {
	class config_model {
	public:
		static config_model& instance();
		void update_token(const utility::string_t& token);
		void async_write_json(utility::string_t path, web::json::value json);
		pplx::task<std::pair<bool, web::json::value>> async_read_json(utility::string_t path);
		pplx::task<utility::string_t> async_read_token();
		void set_config_path(utility::string_t path);
	private:
		config_entity config;
		utility::string_t get_current_path();
		utility::string_t config_path = utility::string_t();
	};

}


#endif //QINGZHENYUN_LITE_CONFIG_MODEL_H
