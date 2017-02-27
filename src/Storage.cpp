#include "Storage.hpp"
#include "Path.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

shared_ptr<Storage> Storage::m_instance = nullptr;

  Storage::Storage() {
  	m_dirty = false;
  }

  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
  vector<string> deli_quote(vector<string>& tokens) {
  	for (auto it = tokens.begin(); it != tokens.end(); it++) {
  		if ((*it)[0] == '\"') {
  			it->erase(it->begin());
  		}
  		if ((*it)[(*it).size()-1] == '\"') {
  			it->erase((*it).size()-1);
  		}
  	}
  	return tokens;
  }

  vector<string> delim(const string& str, char ch) {
  	vector<string> tokens;
  	stringstream ss(str);
  	string item;

  	while (getline(ss, item, ch)) {
  		tokens.push_back(item);
  	}
  	return deli_quote(tokens);
  }

  vector<string> stringTovector(const string& str) {
  	vector<string> ret;
  	stringstream ss(str);
  	string item;

  	while (getline(ss, item, '&')) {
  		ret.push_back(item);
  	}
  	return ret;
  }

  bool Storage::readFromFile(void) {
  	ifstream user(Path::userPath, ios::in);
  	ifstream meeting(Path::meetingPath, ios::in);

  	if (!user.is_open() || !meeting.is_open()) {
  		return false;
  	}
  	string line;

  	while (getline(user, line)) {
  		if (line.size() < 1) continue;
  		vector<string> tokens = delim(line, ',');

  		if (tokens.size() != 4) continue;
  		m_userList.push_back({tokens[0], tokens[1], tokens[2], tokens[3]});
  	}
  	while (getline(meeting, line)) {
  		if (line.size() < 1) continue;
  		vector<string> tokens = delim(line, ',');

  		if (tokens.size() != 5) continue;
  		m_meetingList.push_back({tokens[0], stringTovector(tokens[1]), 
  			tokens[2], tokens[3], tokens[4]});
  	}
  	user.close();
  	meeting.close();
  	return true;
  }

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
  string generate_csv(vector<string> tokens) {
  	bool first = true;
  	string rst = "";

  	for (int i = 0; i < tokens.size(); i++) {
  		if (!first) {
  			rst += ',';
  		}
  		rst += '\"';
  		rst += tokens[i];
  		rst += '\"';
  		first = false;
  	}
  	return rst;
  }

  string vectorTostring(vector<string> participator) {
  	bool first = true;
  	string rst = "";

  	for (int i = 0; i < participator.size(); i++) {
  		if (!first) {
  			rst += '&';
  		}
  		rst += participator[i];
  		first = false;
  	}
  	return rst;
  }

  bool Storage::writeToFile(void) {
  	if (!m_dirty) {
  		return false;
  	}
  	ofstream user(Path::userPath, ios::out);
  	ofstream meeting(Path::meetingPath, ios::out);

  	if (!user.is_open() || !meeting.is_open()) {
  		return false;
  	}
  	for (auto& each : m_userList) {
  		user << generate_csv({each.getName(), each.getPassword(), 
  			each.getEmail(), each.getPhone()}) << endl;
  	}
  	for (auto& each : m_meetingList) {
  		meeting << generate_csv({each.getSponsor(), 
  			vectorTostring(each.getParticipator()), Date::dateToString(each.getStartDate()),
  		 							Date::dateToString(each.getEndDate()), each.getTitle()});
  	}
  	user.close();
  	meeting.close();
  	m_dirty = false;
  	return true;
  }

  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  shared_ptr<Storage> Storage::getInstance(void) {
  	if (m_instance == nullptr) {
  		m_instance = shared_ptr<Storage>(new Storage);
  	}
  	return m_instance;
  }

  /**
  *   destructor
  */
  Storage::~Storage() {
  	if (m_dirty) {
  		writeToFile();
  	}
  }

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void Storage::createUser(const User & t_user) {
  	m_userList.push_back(t_user);
  	m_dirty = true;
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  list<User> Storage::queryUser(function<bool(const User &)> filter) const {
  	list<User> l;

  	for (auto each : m_userList) {
  		if (filter(each)) {
  			l.push_back(each);
  		}
  	}
  	return l;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(function<bool(const User &)> filter,
                 function<void(User &)> switcher) {}

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(function<bool(const User &)> filter) {
  	int delete_num = 0;

  	for (auto it = m_userList.begin(); it != m_userList.end();) {
  		if (filter(*it)) {
  			it = m_userList.erase(it);
  			m_dirty = true;
  			delete_num++;
  		}
  		else {
  			it++;
  		}
  	}
  	return delete_num;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting & t_meeting) {
  	m_meetingList.push_back(t_meeting);
  	m_dirty = true;
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const {
  	list<Meeting> l;

  	for (auto each : m_meetingList) {
  		if (filter(each)) {
  			l.push_back(each);
  		}
  	}
  	return l;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(function<bool(const Meeting &)> filter,
                    function<void(Meeting &)> switcher) {}

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(function<bool(const Meeting &)> filter) {
  	int delete_num = 0;

  	for (auto it = m_meetingList.begin(); it != m_meetingList.end();) {
  		if (filter(*it)) {
  			delete_num++;
  			it = m_meetingList.erase(it);
  			m_dirty = true;
  		}
  		else {
  			it++;
  		}
  	}
  	return delete_num;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void) {
  	return writeToFile();//put the data of memory into the file and store
  }

