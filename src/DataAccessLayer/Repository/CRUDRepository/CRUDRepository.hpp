#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <variant>
#include <drogon/orm/DbClient.h>
#include "../IRepository/IRepository.hpp"
#include "../../Entity/User_Entity.hpp"


class CRUDRepository final : public ICRUDRepository<std::unordered_map<std::string,std::string>,entities::User>
{
	using ParametersMap = std::unordered_map<std::string, std::string>;
public:

	CRUDRepository(drogon::orm::DbClientPtr contextPtr) : dbContext{ contextPtr } {}

	drogon::Task<entities::User> get_value(const ParametersMap&) override;
	drogon::Task<std::vector<entities::User>> get_values(const ParametersMap&) override;
	drogon::Task<void> set_value(const ParametersMap&) override;
	drogon::Task<void> update_value(const ParametersMap&) override;
	drogon::Task<void> delete_value(const ParametersMap&) override;
private:
	drogon::orm::DbClientPtr dbContext;
};


drogon::Task<entities::User> CRUDRepository::get_value(const ParametersMap& params)
{
	try
	{
		LOG_INFO << "CRUDRepository::get_value(const ParametersMap& params)\n";
		std::string main_query;
		main_query.reserve(1024);
		main_query.assign("SELECT * FROM users WHERE ");

		for (const auto& [key, value] : params)
			if (key == "id")
				main_query += key + " = " + value + " AND ";
			else
				main_query += key + " = " + "'" + value + "'" + " AND ";

		main_query.erase(main_query.size() - 4);
		main_query += "LIMIT 1;";

		LOG_INFO << main_query << '\n';

		const auto& rows = co_await dbContext->execSqlCoro(main_query);
		const auto& row = rows.front();

		std::uint32_t u_id = row["id"].as<std::uint32_t>();
		std::string u_name = std::move(row["name"].as<std::string>());
		std::string u_email = std::move(row["email"].as<std::string>());

		co_return{ u_id,std::move(u_name),std::move(u_email)};
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return {};
	}
}

drogon::Task<std::vector<entities::User>> CRUDRepository::get_values(const ParametersMap& params)
{
	try
	{
		LOG_INFO << "CRUDRepository::get_values(const ParametersMap& params)\n";
		std::string main_query;
		main_query.reserve(1024);
		main_query.assign("SELECT * FROM users WHERE ");

		for (const auto& [key, value] : params)
			if (key == "id")
				main_query += key + " = " + value + " AND ";
			else
				main_query += key + " = " + "'" + value + "'" + " AND ";

		main_query.erase(main_query.size() - 4);
		main_query.push_back(';');

		LOG_INFO << main_query << '\n';

		const auto& rows = co_await dbContext->execSqlCoro(main_query);
		
		std::vector<entities::User> selected_users;
		selected_users.reserve(rows.size());

		for (const auto& row : rows)
		{
			std::uint32_t u_id = row["id"].as<std::uint32_t>();
			std::string u_name = row["name"].as<std::string>();
			std::string u_email = row["email"].as<std::string>();

			selected_users.emplace_back(entities::User{u_id,std::move(u_name),std::move(u_email)});
		}
		co_return selected_users;
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return{};
	}
}

drogon::Task<void> CRUDRepository::set_value(const ParametersMap& params)
{
	try
	{
		LOG_INFO << "CRUDRepository::set_value(const ParametersMap& params)\n";
		std::string main_query;
		main_query.reserve(1024);
		main_query += "INSERT INTO users ";

		std::string key_part, values_part;
		key_part.reserve(256); values_part.reserve(256);
		key_part.push_back('('); values_part += "VALUES (";
		for (const auto& [key, value] : params)
		{
			key_part += key + ',';
			if (key == "id")
				values_part += value + ',';
			else
				values_part += "'" + value + "'" + ',';
		}
		key_part.pop_back(); values_part.pop_back();

		key_part.push_back(')'); values_part.append(");");

		main_query.append(key_part + values_part);

		const auto& rows = co_await dbContext->execSqlCoro(main_query);
		LOG_INFO << rows.size() << " affected! \n";
		co_return;
	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return;
	}
}

drogon::Task<void> CRUDRepository::update_value(const ParametersMap& params)
{
	try
	{
		LOG_INFO << " CRUDRepository::update_value(const ParametersMap& params)\n";
		std::string main_query;
		main_query.reserve(1024);

		std::string updated_fields, condition;
		updated_fields.reserve(256); condition.reserve(256);

		main_query.append("UPDATE users SET ");

		updated_fields += "name = '" + params.at("name") + "'" + "," + " email = " + "'" + params.at("email")+"'";

		condition += " WHERE id = " + params.at("id") + ";";

		main_query += updated_fields + condition;

		const auto& rows = co_await dbContext->execSqlCoro(main_query);

		LOG_INFO << rows.size() << " affected! \n";
		co_return;

	}
	catch (const std::exception& ex)
	{
		LOG_ERROR << ex.what() << '\n';
		co_return;
	}
}

drogon::Task<void> CRUDRepository::delete_value(const ParametersMap& params)
{
	try
	{
		LOG_INFO << "CRUDRepository::delete_value(const ParametersMap& params)\n";
		std::string main_query;
		main_query.reserve(1024);

		main_query += "DELETE FROM users WHERE ";

		for (const auto& [key, value] : params)
			if (key == "id")
				main_query += key + " = " + value + " AND ";
			else
				main_query += key + " = " + "'" + value + "'" + " AND ";
		main_query.erase(main_query.size() - 4);
		main_query.push_back(';');

		const auto& rows = co_await dbContext->execSqlCoro(main_query);

		LOG_INFO << rows.size() << " affected! \n";
		co_return;
	}
	catch (const std::exception& ex)
	{
		co_return;
	}
}