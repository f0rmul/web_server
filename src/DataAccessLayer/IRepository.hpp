#pragma once

template<typename KeyType,typename ValueType>
class IRepository
{
public:
	virtual ValueType get_value_by_key(const KeyType&) = 0;

	virtual void set_value(const KeyType&, const ValueType&) = 0;

	virtual ~IRepository() {}
};


template<typename ValueType>
class IRepository<void, ValueType>
{
public:
	virtual ValueType get_value_by_key() = 0;
	virtual void set_value(const ValueType& ) = 0;

	virtual ~IRepository() {};
};