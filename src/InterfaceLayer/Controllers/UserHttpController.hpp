#pragma once
#include <drogon/HttpController.h>
#include <unordered_map>
#include "../Utils/Utils.hpp"
#include "../../DomainLayer/Services/UserManagmentService.hpp"


class UserHttpController final : public drogon::HttpController<UserHttpController>
{
	using ResponseType = drogon::HttpResponsePtr;
public:
	UserHttpController() : userServicePtr{ std::make_unique<UserManagmentService>() } {}

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
	std::unique_ptr<UserManagmentService> userServicePtr;
};


drogon::Task<UserHttpController::ResponseType> UserHttpController::create_user(drogon::HttpRequestPtr req_ptr)
{
	
	LOG_INFO << "UserHttpController::create_user()\n";
	try
	{
		co_await userServicePtr->setItem(utils::SerializeRequest(req_ptr));

		Json::Value json;
		json["status"] = "ok";
		json["message"] = "User was created successfuly!";

		auto response = drogon::HttpResponse::newHttpJsonResponse(json);
		co_return response;
	}
	catch (const std::exception& ex)
	{
		Json::Value error;
		error["status"] = "failed";
		error["reason"] = ex.what();

		auto error_response = drogon::HttpResponse::newHttpJsonResponse(error);
		co_return error_response;
	}
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::get_user(drogon::HttpRequestPtr req_ptr)
{
	LOG_INFO << "UserHttpController::get_user()\n";
	try
	{
		dto::User selected_user = co_await userServicePtr->getItem(utils::SerializeRequest(req_ptr));

		Json::Value json;
		json["status"] = "ok";
		json["user_id"] = selected_user.get_id().value();
		json["user_name"] = selected_user.get_name().value();
		json["user_email"] = selected_user.get_email().value();

		auto response = drogon::HttpResponse::newHttpJsonResponse(json);

		co_return response;
	}
	catch (const std::exception& ex)
	{
		Json::Value error;
		error["status"] = "failed";
		error["reason"] = ex.what();

		auto error_response = drogon::HttpResponse::newHttpJsonResponse(error);
		co_return error_response;
	}
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::get_all_users(drogon::HttpRequestPtr req_ptr)
{
	
	LOG_INFO << "UserHttpController::get_all_users()\n";
	try
	{
		Json::Value root;
		Json::Value users_root;
		Json::Value user_value;

		std::vector<dto::User> user_list = co_await userServicePtr->getItems(utils::SerializeRequest(req_ptr));

		for (const auto& user : user_list)
		{
			std::uint32_t id = user.get_id().value();
			std::string name = std::move(user.get_name().value());
			std::string email = std::move(user.get_email().value());

			user_value["id"] = id;
			user_value["name"] = name;
			user_value["email"] = email;

			root.append(user_value);
		}

		users_root["Users"] = Json::Value(root);

		auto response = drogon::HttpResponse::newHttpJsonResponse(users_root);

		co_return response;
	}
	catch (const std::exception& ex)
	{
		Json::Value error;
		error["status"] = "failed";
		error["reason"] = ex.what();

		auto error_response = drogon::HttpResponse::newHttpJsonResponse(error);
		co_return error_response;
	}
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::update_user(drogon::HttpRequestPtr req_ptr)
{

	LOG_INFO << "UserHttpController::update_user()\n";
	try
	{
		co_await userServicePtr->updateItem(utils::SerializeRequest(req_ptr));

		Json::Value json;
		json["status"] = "ok";
		json["message"] = "User was updated successfuly!";

		auto response = drogon::HttpResponse::newHttpJsonResponse(json);
		co_return response;
	}
	catch (const std::exception& ex)
	{
		Json::Value error;
		error["status"] = "failed";
		error["reason"] = ex.what();

		auto error_response = drogon::HttpResponse::newHttpJsonResponse(error);
		co_return error_response;
	}
}

drogon::Task<UserHttpController::ResponseType> UserHttpController::delete_user(drogon::HttpRequestPtr req_ptr)
{

	LOG_INFO << "UserHttpController::delete_user()\n";
	try
	{
		co_await userServicePtr->deleteItem(utils::SerializeRequest(req_ptr));

		Json::Value json;
		json["status"] = "ok";
		json["message"] = "User was deleted successfuly!";

		auto response = drogon::HttpResponse::newHttpJsonResponse(json);
		co_return response;
	}
	catch (const std::exception& ex)
	{
		Json::Value error;
		error["status"] = "failed";
		error["reason"] = ex.what();

		auto error_response = drogon::HttpResponse::newHttpJsonResponse(error);
		co_return error_response;
	}
}