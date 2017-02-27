#include "AgendaService.hpp"
#include <list>
#include <iostream>
using namespace std;

	/**
     * constructor
     */
 	AgendaService::AgendaService() {
 		startAgenda();
 	}

    /**
     * destructor
     */
    AgendaService::~AgendaService() {
    	quitAgenda();
    }

	/**
     * start Agenda service and connect to storage
     */
    void AgendaService::startAgenda(void) {
    	m_storage = Storage::getInstance();
    }

    /**
     * quit Agenda service
     */
    void AgendaService::quitAgenda(void) {}

    /**
     * check if the username match password
     * @param userName the username want to login
     * @param password the password user enter
     * @return if success, true will be returned
     */
    bool AgendaService::userLogIn(const string userName, const string password) {
    	list<User> l = m_storage->queryUser([&userName](const User& a) {//the define of lambda function 
    		if (a.getName() == userName) return true;
    		else return false;
    	});

    	if (l.empty()) return false;
    	if ((l.begin())->getPassword() != password) return false;
    	return true;
    }

    /**
     * regist a user
     * @param userName new user's username
     * @param password new user's password
     * @param email new user's email
     * @param phone new user's phone
     * @return if success, true will be returned
     */
    bool AgendaService::userRegister(const string userName, const string password,
                      const string email, const string phone) {
    	list<User> l = m_storage->queryUser([&userName](const User& a) {//the define of lambda function 
    		if (a.getName() == userName) return true;
    		else return false;
    	});

    	if (!l.empty()) return false;//username existed
    	User temp(userName, password, email, phone);

    	m_storage->createUser(temp);
    	return true;
    }

    /**
     * delete a user
     * @param userName user's username
     * @param password user's password
     * @return if success, true will be returned
     */
    bool AgendaService::deleteUser(const string userName, const string password) {
    	list<User> l = m_storage->queryUser([&userName](const User& a) { 
    		if (a.getName() == userName) return true;
    		else return false;
    	});

    	if (l.empty()) return false;
    	if (l.begin()->getPassword() != password) return false;
    	m_storage->deleteUser([&userName](const User& a) {
    		if (a.getName() == userName) return true;
    		else return false;
    	});
    	m_storage->deleteMeeting([&userName](const Meeting& a) {//delete all meeting include user
    		if (userName == a.getSponsor() || a.isParticipator(userName)) return true;
    		else return false;
    	});
    	return true;
    }

    /**
     * list all users from storage
     * @return a user list result
     */
    list<User> AgendaService::listAllUsers(void) const {
    	list<User> l = m_storage->queryUser([](const User& a){
    		return true;
    	});

    	return l;
    }

    /**
     * create a meeting
     * @param userName the sponsor's userName
     * @param title the meeting's title
     * @param participator the meeting's participator
     * @param startData the meeting's start date
     * @param endData the meeting's end date
     * @return if success, true will be returned
     */
    bool AgendaService::createMeeting(const string userName, const string title,
                       const string startDate, const string endDate,
                       const vector<string> participator) {
    	Date sDate = Date::stringToDate(startDate);
    	Date eDate = Date::stringToDate(endDate);
    	if (!Date::isValid(sDate)) return false;
    	if (!Date::isValid(eDate)) return false;
    	if (sDate >= eDate) return false;

    	list<User> lu;
    	list<Meeting> lm;

    	lm = m_storage->queryMeeting([&title](const Meeting& a){//meeting of same title
    		if (title == a.getTitle()) return true;
    		else return false;
    	});
    	if (!lm.empty()) return false;

    	lu = m_storage->queryUser([&userName](const User& a){
    		if (a.getName() == userName) return true;
    		else return false;
    	});
    	if (lu.empty()) return false;
    	lm = m_storage->queryMeeting([&userName, &sDate, &eDate](const Meeting& a){//judge overlap 
    		if (a.getSponsor() == userName || a.isParticipator(userName)) {
    			if (a.getStartDate() <= sDate && a.getEndDate() > sDate) return true;
    			if (a.getStartDate() < eDate && a.getEndDate() >= eDate) return true;
    			if (a.getStartDate() >= sDate && a.getEndDate() <= eDate) return true;
    			return false;
    		}
    		else {
    			return false;
    		}
    	});
    	if (!lm.empty()) return false;

    	for (auto iti = participator.begin(); iti != participator.end(); iti++) {//check if existed same participators
    		for (auto itj = participator.begin(); itj != iti; itj++) {
    			if (*iti == *itj) return false;
    		}
    	}
    	for (auto it = participator.begin(); it != participator.end(); it++) {
    		string partName = *it;
    		lu = m_storage->queryUser([&partName](const User& a){
    			if (a.getName() == partName) return true;
    			else return false;
    		});
    		if (lu.empty()) return false;
    		lm = m_storage->queryMeeting([&partName, &sDate, &eDate](const Meeting& a){//judge overlap 
    			if (a.getSponsor() == partName || a.isParticipator(partName)) {
    				if (a.getStartDate() <= sDate && a.getEndDate() > sDate) return true;
    				if (a.getStartDate() < eDate && a.getEndDate() >= eDate) return true;
    				if (a.getStartDate() >= sDate && a.getEndDate() <= eDate) return true;
    				return false;
    			}
    			else {
    				return false;
    			}
    		});
    		if (!lm.empty()) return false;
    	}

    	Meeting temp(userName, participator, startDate, endDate, title);
    	m_storage->createMeeting(temp);
    	return true;
    }

    /**
     * search meetings by username and title (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param title the meeting's title
     * @return a meeting list result
     */
    list<Meeting> AgendaService::meetingQuery(const string userName,
                                    const string title) const {
    	list<Meeting> l = m_storage->queryMeeting([&userName, &title](const Meeting& a){
    		if (a.getSponsor() == userName || a.isParticipator(userName)) {
    			if (a.getTitle() == title) return true;
    			else return false;
    		}
    		else return false;
    	});
    	return l;
    }

    /**
     * search a meeting by username, time interval (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param startDate time interval's start date
     * @param endDate time interval's end date
     * @return a meeting list result
     */
    list<Meeting> AgendaService::meetingQuery(const string userName,
                                    const string startDate,
                                    const string endDate) const {
    	list<Meeting> l;
    	Date sDate = Date::stringToDate(startDate);
    	Date eDate = Date::stringToDate(endDate);
    	if (!Date::isValid(sDate)) return l;
    	if (!Date::isValid(eDate)) return l;
    	if (sDate >= eDate) return l;
    	l = m_storage->queryMeeting([&userName, &sDate, &eDate](const Meeting& a){//list all overlap meeting
    		if (a.getSponsor() == userName || a.isParticipator(userName)) {
    			if (a.getStartDate() <= sDate && a.getEndDate() > sDate) return true;
    			if (a.getStartDate() < eDate && a.getEndDate() >= eDate) return true;
    			if (a.getStartDate() >= sDate && a.getEndDate() <= eDate) return true;
   				return false;
    		}
    		else {
    			return false;
    		}
    	});
    	return l;
    }

    /**
     * list all meetings the user take part in
     * @param userName user's username
     * @return a meeting list result
     */
    list<Meeting> AgendaService::listAllMeetings(const string userName) const {
    	list<Meeting> l = m_storage->queryMeeting([&userName](const Meeting& a){
    		if (a.getSponsor() == userName || a.isParticipator(userName)) {
    			return true;
    		}
    		else {
    			return false;
    		}
    	});
    	return l;
    }

    /**
     * list all meetings the user sponsor
     * @param userName user's username
     * @return a meeting list result
     */
    list<Meeting> AgendaService::listAllSponsorMeetings(const string userName) const {
    	list<Meeting> l = m_storage->queryMeeting([&userName](const Meeting& a){
    		if (a.getSponsor() == userName) {
    			return true;
    		}
    		else {
    			return false;
    		}
    	});
    	return l;
    }

    /**
     * list all meetings the user take part in and sponsor by other
     * @param userName user's username
     * @return a meeting list result
     */
    list<Meeting> AgendaService::listAllParticipateMeetings(
        const string userName) const {
    	list<Meeting> l = m_storage->queryMeeting([&userName](const Meeting& a){
    		if (a.isParticipator(userName)) {
    			return true;
    		}
    		else {
    			return false;
    		}
    	});
    	return l;
    }

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
    bool AgendaService::deleteMeeting(const string userName, const string title) {
    	int n = 0;
    	n = m_storage->deleteMeeting([&userName, &title](const Meeting& a){
    		if (a.getSponsor() == userName && a.getTitle() == title) {
    			return true;
    		}
    		else {
    			return false;
    		}
    	});
    	if (n > 0) return true;
    	return false;
    }

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
    bool AgendaService::deleteAllMeetings(const string userName) {
    	int n = 0;
    	n = m_storage->deleteMeeting([&userName](const Meeting& a){
    		if (a.getSponsor() == userName) {
    			return true;
    		}
    		else {
    			return false;
    		}
    	});
    	if (n > 0) return true;
    	return false;
    }
