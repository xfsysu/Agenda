#include "Date.hpp"
#include <sstream>

  Date::Date() {
  	m_year = 0;
  	m_month = 0;
  	m_day = 0;
  	m_hour = 0;
  	m_minute = 0;
  };

  /**
  * @brief constructor with arguments
  */
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
  	m_year = t_year;
  	m_month = t_month;
  	m_day = t_day;
  	m_hour = t_hour;
  	m_minute = t_minute;
  }

  /**
  * @brief constructor with a string
  */
  Date::Date(std::string dateString) {
  	(*this) = stringToDate(dateString);
  }
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int Date::getYear(void) const {
  	return m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void Date::setYear(const int t_year) {
  	m_year = t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int Date::getMonth(void) const {
  	return m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void Date::setMonth(const int t_month) {
  	m_month = t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int Date::getDay(void) const {
  	return m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void Date::setDay(const int t_day) {
  	m_day = t_day;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int Date::getHour(void) const {
  	return m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void Date::setHour(const int t_hour) {
  	m_hour = t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int Date::getMinute(void) const {
  	return m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void Date::setMinute(const int t_minute) {
  	m_minute = t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
   bool Date::isValid(const Date t_date) {
  	int curYear = t_date.getYear();
  	int curMonth = t_date.getMonth();
  	int curDay = t_date.getDay();

  	if (curYear < 1000 || curYear > 9999 || curMonth < 1 || curMonth > 12 || curDay < 1 || t_date.getHour() < 0 || 
  		t_date.getHour() > 23 || t_date.getMinute() < 0 || t_date.getMinute() > 59) return false;
  	if (curMonth == 1 || curMonth == 3 || curMonth == 5 || curMonth == 7 || curMonth == 8 || curMonth == 10 || curMonth == 12) {
  		if (curDay > 31) return false;
  	}
  	else if (curMonth == 4 || curMonth == 6 || curMonth == 9 || curMonth == 11) {
  		if (curDay > 30) return false;
  	}
  	else {
  		if ((curYear % 4 == 0 && curYear % 100 != 0) || (curYear % 400 == 0)) {
  			if (curDay > 29) return false;
  		}
  		else {
  			if (curDay > 28) return false;
  		}
  	}
  	return true;
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  int stringToint(std::string str) {
  	int result;
  	std::stringstream ss;

  	ss << str;
  	ss >> result;
  	return result;
  }

 Date Date::stringToDate(const std::string t_dateString) {
  	Date curDate;

  	if (t_dateString.size() != 16) return curDate;
  	for (int i = 0; i < 16; i++) {
  		switch(i) {
  			case 4: if (t_dateString[i] != '-') return curDate;
  					break;

  			case 7: if (t_dateString[i] != '-') return curDate;
  					break;

  			case 10: if (t_dateString[i] != '/') return curDate;
  					break;

  			case 13: if (t_dateString[i] != ':') return curDate;
  					break;

  			default: if (t_dateString[i] < '0' || t_dateString[i] > '9') return curDate;
  		}
  	}

  	curDate.setYear(stringToint(t_dateString.substr(0, 4)));
  	curDate.setMonth(stringToint(t_dateString.substr(5, 2)));
  	curDate.setDay(stringToint(t_dateString.substr(8, 2)));
  	curDate.setHour(stringToint(t_dateString.substr(11, 2)));
  	curDate.setMinute(stringToint(t_dateString.substr(14, 2)));
  	return curDate;
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string intTostring(int val) {
  	std::string result;
  	std::stringstream ss;

  	ss << val;
  	ss >> result;
  	if (result.size() == 1) {
  		result = "0" + result;
  	}
  	return result;
  }

 std::string Date::dateToString(Date t_date) {
  	if (!isValid(t_date)) return "0000-00-00/00:00";
  	std::string result = "";

  	result += intTostring(t_date.getYear()) + "-" + intTostring(t_date.getMonth()) + "-" + intTostring(t_date.getDay()) + "/" + 
  				intTostring(t_date.getHour()) + ":" + intTostring(t_date.getMinute());
  	return result;
  }

  /**
  *  @brief overload the assign operator
  */
  Date& Date::operator=(const Date &t_date) {
  	this->m_year = t_date.getYear();
  	this->m_month = t_date.getMonth();
  	this->m_day = t_date.getDay();
  	this->m_hour = t_date.getHour();
  	this->m_minute = t_date.getMinute();
  	return (*this);//return object so return *this
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const {
  	return this->m_year == t_date.getYear() && this->m_month == t_date.getMonth() && this->m_day == t_date.getDay() && 
  		this->m_hour == t_date.getHour() && this->m_minute == t_date.getMinute();
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const {
  	return dateToString(*this) > dateToString(t_date);
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const {
  	return !(*this > t_date || *this == t_date);
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const {
  	return !(*this < t_date);
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const {
  	return !(*this > t_date);
  }
