#pragma once
#include "../../InterfaceLayer/DTO/User_DTO.hpp"
#include "../../DataAccessLayer/Repository/CRUDRepository/CRUDRepository.hpp"
#include <drogon/HttpAppFramework.h>

class UserManagmentService
{
public:
	UserManagmentService()
	{
		repositoryPtr = std::make_unique<CRUDRepository>(drogon::app().getDbClient("postgresql_client"));
	}

	drogon::Task<dto::User> getItem(const dto::User&);
	drogon::Task<std::vector<dto::User>> getItems(const dto::User&);
	drogon::Task<void> setItem(const dto::User&);
	drogon::Task<void> updateItem(const dto::User&);
	drogon::Task<void> deleteItem(const dto::User&);
private:
	std::unordered_map<std::string, std::string> SerializeUser(const dto::User&);
private:
	std::unique_ptr<CRUDRepository> repositoryPtr;
};


std::unordered_map<std::string, std::string> UserManagmentService::SerializeUser(const dto::User&  user)
{
	std::unordered_map<std::string, std::string> mapped_fields;

	if (user.get_id().has_value())
		mapped_fields["id"] = std::to_string(user.get_id().value());
	if (user.get_name().has_value())
		mapped_fields["name"] = user.get_name().value();
	if (user.get_email().has_value())
		mapped_fields["email"] = user.get_email().value();

	return mapped_fields;
}

drogon::Task<dto::User> UserManagmentService::getItem(const dto::User& user)
{
	try
	{
		LOG_INFO << "UserManagmentService::getItem(const dto::User& user)\n";
		entities::User user_entity = co_await repositoryPtr->get_value(SerializeUser(user));

		std::uint32_t u_id = user_entity.get_id().value();
		std::string u_name = std::move(user_entity.get_name().value());
		std::string u_email = std::move(user_entity.get_email().value());

		co_return{ u_id,std::move(u_name),std::move(u_email) };
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return{};
	}
}

drogon::Task<std::vector<dto::User>> UserManagmentService::getItems(const dto::User& user)
{
	try
	{
		LOG_INFO << "UserManagmentService::getItems(const dto::User& user)\n";
		std::vector<entities::User> user_list = co_await repositoryPtr->get_values(SerializeUser(user));

		std::vector<dto::User> user_dtos;
		user_dtos.reserve(user_list.size());

		for (const auto& user : user_list)
		{
			std::uint32_t u_id = user.get_id().value();
			std::string u_name = std::move(user.get_name().value());
			std::string u_email = std::move(user.get_email().value());

			user_dtos.emplace_back(dto::User{ u_id,std::move(u_name),std::move(u_email) });
		}
		co_return user_dtos;
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return{};
	}
}

drogon::Task<void> UserManagmentService::setItem(const dto::User& user)
{
	LOG_INFO << "UserManagmentService::setItem(const dto::User& user)\n";
	co_await repositoryPtr->set_value(SerializeUser(user));
	co_return;
}

drogon::Task<void> UserManagmentService::updateItem(const dto::User& user)
{
	LOG_INFO << "UserManagmentService::updateItem(const dto::User& user)\n";
	co_await repositoryPtr->update_value(SerializeUser(user));
	co_return;
}

drogon::Task<void> UserManagmentService::deleteItem(const dto::User& user)
{
	LOG_INFO << "UserManagmentService::deleteItem(const dto::User& user)\n";
	co_await repositoryPtr->delete_value(SerializeUser(user));
	co_return;
}



