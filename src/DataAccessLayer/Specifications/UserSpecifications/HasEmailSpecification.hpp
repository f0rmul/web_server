#pragma once

#include "../ISpecification/ISpecification.hpp"

class HasEmail final: public IQueryable, public ISpecification<entities::User>
{
public:
	std::pair<bool, std::string> SatisfyAndGet(const entities::User& candidate) override
	{
		if (auto requirement = candidate.get_email().has_value(); requirement)
		{
			m_email = candidate.get_email().value();
			return std::make_pair(true, asQuery());
		}
		return std::make_pair(false, asQuery());
	}

	std::string asQuery() const  override
	{
		return "email = " + m_email;
	}

private:
	std::string m_email;
};