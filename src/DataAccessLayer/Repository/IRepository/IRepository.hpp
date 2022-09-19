#pragma once
#include <vector>
#include <drogon/HttpAppFramework.h>

template <typename KeyType,typename  ValueType>
class IRepository
{
public:
	virtual ValueType get_value(const KeyType&) = 0;
	virtual void set_value(const ValueType&) = 0;
	virtual ~IRepository() = default;
};


template <typename KeyType,typename ValueType>
class ICRUDRepository
{
public:
	virtual drogon::Task<ValueType> get_value(const KeyType&) = 0;
	virtual drogon::Task<void> set_value(const KeyType&) = 0;
	virtual drogon::Task<std::vector<ValueType>> get_values(const KeyType&) = 0;
	virtual drogon::Task<void> update_value(const KeyType&) = 0;
	virtual drogon::Task<void> delete_value(const KeyType&) = 0;
	virtual ~ICRUDRepository() = default;
};

