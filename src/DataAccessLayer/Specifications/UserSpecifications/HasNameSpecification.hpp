#pragma once
#include "../ISpecification/ISpecification.hpp"

class HasName final : public IQueryable, public ISpecification<entities::User>
{
public:
	std::pair<bool, std::string> SatisfyAndGet(const entities::User& candidate) override
	{
		if (auto requirement = candidate.get_name().has_value(); requirement)
		{
			m_name = candidate.get_name().value();
			return std::make_pair(true, asQuery());
		}
		return std::make_pair(false, asQuery());
	}

	std::string asQuery() const  override
	{
		return "name = " + m_name;
	}
private:
	std::string m_name;
};