#pragma once
#include <string>
#include <memory>
#include <tuple>
#include "../../Entity/User_Entity.hpp"

template <typename CandidateType>
class ISpecification
{
public:
	virtual std::pair<bool,std::string> SatisfyAndGet(const CandidateType&)= 0;
	virtual ~ISpecification() = default;
};

class IQueryable
{
public:
	virtual std::string asQuery() const = 0;
	virtual ~IQueryable() = default;
};


template <typename CandidateType,typename ... Specs>
class SpecificationComposer : public IQueryable
{
public:
	SpecificationComposer(const CandidateType& candidate, Specs... sp) :
		m_candidate{candidate},
		m_specifications(sp...) {}

	std::string asQuery() const
	{	
		std::string query;
		auto callable = [&query,this](auto arg)
		{
			auto&&[has_item,item] = arg.SatisfyAndGet(m_candidate);
			if (has_item)
				query+= item + " AND ";
		};
		std::apply([callable](auto&... specs)
			{
				(callable(specs),...);
			}, m_specifications);
		return query.erase(query.size() - 5);// removing last ' AND '
	}
private:
	CandidateType m_candidate;
	std::tuple<Specs...> m_specifications;
};



