#pragma once
#include <string>
#include <memory>
#include <drogon/orm/DbClient.h>
#include "../IRepository/IRepository.hpp"
#include "../../Entity/User_Entity.hpp"




class CRUDRepository final : public ICRUDRepository<std::string,entities::User>
{
public:
	drogon::Task<entities::User> get_value(const std::string&) override;
	drogon::Task<std::vector<entities::User>> get_values(const std::string&) override;
	drogon::Task<void> set_value(const entities::User&) override;
	drogon::Task<void> update_value(const entities::User&) override;
	drogon::Task<void> delete_value(const entities::User&) override;
private:
	drogon::orm::DbClientPtr dbContext;
};


