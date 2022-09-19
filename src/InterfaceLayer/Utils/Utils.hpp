#pragma once
#include <drogon/HttpAppFramework.h>
#include "../DTO/User_DTO.hpp"

namespace utils
{
	inline dto::User SerializeRequest(drogon::HttpRequestPtr req_ptr)
	{
		LOG_INFO << "fromRequest()\n";
		const static std::unordered_map<std::string, std::function<void(dto::User&, std::string)>> perform_map
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
		for (auto params = req_ptr->getParameters(); const auto & param : params)
		{
			auto&& [key, value] = param;
			perform_map.at(key)(user, std::move(value));
		}
		return user;
	}
}