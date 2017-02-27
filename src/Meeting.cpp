#include "Meeting.hpp"
//最好使用构造函数初始值列表
  /**
  *   @brief constructor with argument
  */
  Meeting::Meeting(std::string t_sponsor, std::vector<std::string> t_participator, Date t_startTime,
          Date t_endTime, std::string t_title) {
  	m_sponsor = t_sponsor;
  	m_participators = t_participator;
  	m_startDate = t_startTime;
  	m_endDate = t_endTime;
  	m_title = t_title;
  }

  /**
  * @brief copy constructor of left value
  */
  Meeting::Meeting(const Meeting &t_meeting) {
  	this->m_sponsor = t_meeting.getSponsor();
  	this->m_startDate = t_meeting.getStartDate();
  	this->m_endDate = t_meeting.getEndDate();
  	this->m_participators = t_meeting.getParticipator();
  	this->m_title = t_meeting.getTitle();
  }

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
  std::string Meeting::getSponsor(void) const {
  	return m_sponsor;
  }

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
  void Meeting::setSponsor(const std::string t_sponsor) {
  	m_sponsor = t_sponsor;
  }

  /**
  * @brief  get the participators of a meeting
  * @return return a string vector indicate participators
  */
  std::vector<std::string> Meeting::getParticipator(void) const {
  	return m_participators;
  }

  /**
  *   @brief set the new participators of a meeting
  *   @param the new participators vector
  */
  void Meeting::setParticipator(const std::vector<std::string> t_participators) {
  	for (int i = 0; i < t_participators.size(); i++) {
  		m_participators.push_back(t_participators[i]);
  	}
  }

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
  Date Meeting::getStartDate(void) const {
  	return m_startDate;
  }

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
  void Meeting::setStartDate(const Date t_startTime) {
  	m_startDate = t_startTime;
  }

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
  Date Meeting::getEndDate(void) const {
  	return m_endDate;
  }

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
  void Meeting::setEndDate(const Date t_endTime) {
  	m_endDate = t_endTime;
  }

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
  std::string Meeting::getTitle(void) const {
  	return m_title;
  }

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
  void Meeting::setTitle(const std::string t_title) {
  	m_title = t_title;
  }


  /**
  * @brief check if the user take part in this meeting
  * @param t_username the source username
  * @return if the user take part in this meeting
  */
  bool Meeting::isParticipator(const std::string t_username) const {
  	for (int i = 0; i < m_participators.size(); i++) {
  		if (this->m_participators[i] == t_username) return true;
  	}
  	return false;
  }
