#pragma once
#include <drogon/HttpController.h>
#include <unordered_map>
#include "../DTO/User_DTO.hpp"

namespace drogon
{
	template <>
	inline dto::User fromRequest(const HttpRequest& req)
	{
		LOG_INFO << "fromRequest()\n";
		const static std::unordered_map<std::string, std::function<void(dto::User&,std::string)>> perform_map
		{
			{"id", [](dto::User& usr,std::string v)
			{
				usr.set_id(std::stoul(v));
			}},
			{"name",[](dto::User& usr,std::string v)
			{
				usr.set_name(std::move(v));
			}},
			{"email",[](dto::User& usr,std::string v)
			{
				usr.set_email(std::move(v));
			}}
		};
		dto::User user;
		for (auto params = req.getParameters(); const auto& param : params)
		{
			auto&& [key, value] = param;
			perform_map.at(key)(user, std::move(value));
		}
		return user;
	}
}
class UserHttpController final : public drogon::HttpController<UserHttpController>
{
	using Callback = std::function<void(const drogon::HttpResponsePtr&)>;
public:

	METHOD_LIST_BEGIN
		ADD_METHOD_TO(UserHttpController::create_user,  "/new",	           { drogon::Post   });
	    ADD_METHOD_TO(UserHttpController::get_user,     "/user",	       { drogon::Get    });
		ADD_METHOD_TO(UserHttpController::get_all_users,"/get/users",      { drogon::Get    });
		ADD_METHOD_TO(UserHttpController::update_user,  "/update/user",    { drogon::Patch  });
		ADD_METHOD_TO(UserHttpController::delete_user,  "/delete/user",    { drogon::Delete });
	METHOD_LIST_END
	
	void create_user  (dto::User&&, Callback&&);
	void get_user     (dto::User&&, Callback&&);
	void get_all_users(dto::User&&, Callback&&);
	void update_user  (dto::User&&, Callback&&);
	void delete_user  (dto::User&&, Callback&&);
};


void UserHttpController::create_user(dto::User&& user, Callback&& callback)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::create_user()\n";

	
}

void UserHttpController::get_user(dto::User&& user, Callback&& callback)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::get_user()\n";
	
}

void UserHttpController::get_all_users(dto::User&& user, Callback&& callback)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::get_all_users()\n";
	
}

void UserHttpController::update_user(dto::User&& user, Callback&& callback)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::update_user()\n";
	
}

void UserHttpController::delete_user(dto::User&& user, Callback&& callback)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::delete_user()\n";
	
}