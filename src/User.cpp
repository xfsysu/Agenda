#include "User.hpp"

User::User(std::string t_userName, std::string t_userPassword,
       std::string t_userEmail, std::string t_userPhone) {
	m_name = t_userName;
	m_password = t_userPassword;
	m_email = t_userEmail;
	m_phone = t_userPhone;
}

User::User(const User &t_user) {
	this->m_name = t_user.getName();
	this->m_password = t_user.getPassword();
	this->m_email = t_user.getEmail();
	this->m_phone = t_user.getPhone();
}

std::string User::getName() const {
	return m_name;
}

void User::setName(std::string t_name) {
	m_name = t_name;
}

std::string User::getPassword() const {
	return m_password;
}

void User::setPassword(std::string t_password) {
	m_password = t_password;
}

std::string User::getEmail() const {
	return m_email;
}

void User::setEmail(std::string t_email) {
	m_email = t_email;
}

std::string User::getPhone() const {
	return m_phone;
}

void User::setPhone(std::string t_phone) {
	m_phone = t_phone;
}