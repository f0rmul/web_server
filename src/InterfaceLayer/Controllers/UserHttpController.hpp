#pragma once
#include <drogon/HttpController.h>
#include <unordered_map>
#include "../Utils/Utils.hpp"
#include "../../DomainLayer/Services/UserManagmentService.hpp"


class UserHttpController final : public drogon::HttpController<UserHttpController>
{
	using ResponseType = drogon::HttpResponsePtr;
public:
	METHOD_LIST_BEGIN
		ADD_METHOD_TO(UserHttpController::create_user,  "/new",	           { drogon::Post   });
	    ADD_METHOD_TO(UserHttpController::get_user,     "/get/user",	   { drogon::Get    });
		ADD_METHOD_TO(UserHttpController::get_all_users,"/get/users",      { drogon::Get    });
		ADD_METHOD_TO(UserHttpController::update_user,  "/update/user",    { drogon::Patch  });
		ADD_METHOD_TO(UserHttpController::delete_user,  "/delete/user",    { drogon::Delete });
	METHOD_LIST_END
	
	drogon::Task<ResponseType> create_user  (drogon::HttpRequestPtr);
	drogon::Task<ResponseType> get_user	    (drogon::HttpRequestPtr);
	drogon::Task<ResponseType> get_all_users(drogon::HttpRequestPtr);
	drogon::Task<ResponseType> update_user  (drogon::HttpRequestPtr);
	drogon::Task<ResponseType> delete_user  (drogon::HttpRequestPtr);
private:
};


drogon::Task<UserHttpController::ResponseType> UserHttpController::create_user(drogon::HttpRequestPtr req_ptr)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::create_user()\n";
	co_return HttpResponse::newHttpResponse();
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::get_user(drogon::HttpRequestPtr req_ptr)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::get_user()\n";

	co_return HttpResponse::newHttpResponse();
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::get_all_users(drogon::HttpRequestPtr req_ptr)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::get_all_users()\n";
	co_return HttpResponse::newHttpResponse();
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::update_user(drogon::HttpRequestPtr req_ptr)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::update_user()\n";
	co_return HttpResponse::newHttpResponse();
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::delete_user(drogon::HttpRequestPtr req_ptr)
{
	using namespace drogon;
	LOG_INFO << "UserHttpController::delete_user()\n";
	co_return HttpResponse::newHttpResponse();
}