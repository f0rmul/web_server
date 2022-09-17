#pragma once
#include "../ISpecification/ISpecification.hpp"


class HasId final: public IQueryable, public ISpecification<entities::User>
{

public:
	std::pair<bool,std::string> SatisfyAndGet(const entities::User& candidate) override
	{	
		if (auto requirement = candidate.get_id().has_value(); requirement)
		{
			m_id = candidate.get_id().value();
			return std::make_pair(true,asQuery());
		}
		return std::make_pair(false,asQuery());
	}

	std::string asQuery() const  override
	{
		return "id = " + std::to_string(m_id);
	}

private:
	std::uint32_t m_id;
};