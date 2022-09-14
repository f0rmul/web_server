#pragma once

namespace bo
{
	class User final
	{
	public:
		User() = default;
		User(std::uint32_t id, std::string name, std::string email) :
			u_id{ id },
			u_name{ std::move(name) },
			u_email{ std::move(email) } {}

		void set_id(std::uint32_t id) { u_id = id };
		void set_name(std::string name) { u_name = std::move(name); }
		void set_email(std::string email) { u_email = std::move(email); }

		[[nodiscard]] std::uint32_t get_id() const { return u_id; }
		[[nodiscard]] std::string	  get_name() const { return u_name; }
		[[nodiscard]] std::string	  get_email() const { return u_email; }
	private:
		std::uint32_t u_id{};
		std::string	  u_name{};
		std::string   u_email{};
	};
}