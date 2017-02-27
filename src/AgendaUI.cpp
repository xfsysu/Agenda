#include "AgendaUI.hpp"
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

    AgendaUI::AgendaUI() {
    	m_userName = "";
    	m_userPassword = "";
    	startAgenda();
    }

    void AgendaUI::OperationLoop(void) {
    	while (true) {
    		for (int i = 1; i <= 37; i++) cout << "-";
    		cout << "Agenda";
   	 		for (int i = 1; i <= 37; i++) cout << "-";
    		cout << endl;
    		cout << "Action :" << endl << endl;
    		if (m_userName == "") {
    			cout << "l    -log in Agenda by user name and password" << endl ;
    			cout << "r    -register an Agenda account" << endl;
    			cout << "q    -quit Agenda" << endl;
    		}
    		else {
    			cout << "o    -log out Agenda" << endl
    				 << "dc   -delete Agenda account" << endl
    				 << "lu   -list all Agenda user" << endl
    			 	 << "cm   -create a meeting" << endl
    				 << "la   -list all meetings" << endl
    				 << "las  -list all sponsor meetings" << endl
    				 << "lap  -list all participate meetings" << endl
    				 << "qm   -query meeting by title" << endl
    				 << "qt   -query meeting by time interval" << endl
    				 << "dm   -delete meeting by title" << endl
    				 << "da   -delete all meetings" << endl;
    		}
    		cout << endl;
    		for (int i = 1; i <= 80; i++) cout << "-";
    		cout << endl << endl;
    		if (m_userName == "") {
    			cout << "Agenda : ~$ ";
    		}
    		else {
    			cout << "Agenda@" << m_userName << " : #";
    		}
    		if (!executeOperation(getOperation())) break;
    	}
    }

    /**
     * constructor
     */
    void AgendaUI::startAgenda(void) {
    	system("clear");
    }

    /**
     * catch user's operation
     * @return the operation
     */
    std::string AgendaUI::getOperation() {
    	string op;
    	cin >> op;
    	return op;
    }

    /**
     * execute the operation
     * @return if the operationloop continue
     */
    bool AgendaUI::executeOperation(std::string t_operation) {
    	bool flag = (m_userName == "") ? false : true;
    	if (t_operation == "l" && !flag) {
    		userLogIn();
    		return true;
    	}
    	if (t_operation == "r" && !flag) {
    		userRegister();
    		return true;
    	}
    	if (t_operation == "q" && !flag) {
    		quitAgenda();
    		return false;
    	}
    	if (t_operation == "o" && flag) {
    		userLogOut();
    		return true;
    	}
    	if (t_operation == "dc" && flag) {
    		deleteUser();
    		return true;
    	}
    	if (t_operation == "lu" && flag) {
    		listAllUsers();
    		return true;
    	}
    	if (t_operation == "cm" && flag) {
    		createMeeting();
    		return true;
    	}
    	if (t_operation == "la" && flag) {
    		listAllMeetings();
    		return true;
    	}
    	if (t_operation == "las" && flag) {
    		listAllSponsorMeetings();
    		return true;
    	}
    	if (t_operation == "lap" && flag) {
    		listAllParticipateMeetings();
    		return true;
    	}
    	if (t_operation == "qm" && flag) {
    		queryMeetingByTitle();
    		return true;
    	}
    	if (t_operation == "qt" && flag) {
    		queryMeetingByTimeInterval();
    		return true;
    	}
    	if (t_operation == "dm" && flag) {
    		deleteMeetingByTitle();
    		return true;
    	}
    	if (t_operation == "da" && flag) {
    		deleteAllMeetings();
    		return true;
    	}
    	cout << endl;
    	cout << "Please input the corret command" << endl;
    	cout << endl;
    	return true;
    }

    /**
     * user Login
     */
    void AgendaUI::userLogIn(void) {
    	cout << endl;
    	cout << "[log in] [user name] [password]" << endl;
    	cout << "[log in] ";
    	cin >> m_userName >> m_userPassword;
    	if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
    		cout << "[log in] successed!" << endl;
    	}
    	else {
    		cout << "[error] log in fail!" << endl;
            m_userName = "";
            m_userPassword = "";
    	}
    	cout << endl;
    }

    /**
     * user regist
     */
    void AgendaUI::userRegister(void) {
    	cout << endl;
    	cout << "[register] [user name] [password] [email] [phone]" << endl;
    	cout << "[register] ";
    	string username, password, email, phone;
    	cin >> username >> password >> email >> phone;
    	if (m_agendaService.userRegister(username, password, email, phone
    		)) {
    		cout << "[register] successed!" << endl;
    	}
    	else {
    		cout << "[error] register fail!" << endl;
    	}
    }

    /**
     * user logout
     */
    void AgendaUI::userLogOut(void) {//reset username and password
    	m_userName = "";
    	m_userPassword = "";
    	cout << endl;
    }

    /**
     * quit the Agenda
     */
    void AgendaUI::quitAgenda(void) {
    	m_agendaService.quitAgenda();
    }

    /**
     * delete a user from storage
     */
    void AgendaUI::deleteUser(void) {
    	cout << endl;
    	m_agendaService.deleteUser(m_userName, m_userPassword);
    	m_userName = "";
    	m_userPassword = "";
    	cout << "[delete agenda account] succeed!" << endl;
    	cout << endl;
    }

    /**
     * list all users from storage
     */
    void AgendaUI::listAllUsers(void) {
    	cout << endl;
    	cout << "[list all users]" << endl << endl;
    	list<User> l = m_agendaService.listAllUsers();
    	cout << setiosflags(ios::left) << setw(20) << "name"
    							  << setw(30) << "email" 
    							  << "phone" << endl;
    	for (auto each : l) {
    		cout << setw(20) << each.getName()
    			 << setw(30) << each.getEmail()
    			 << each.getPhone() << endl;
    	}
    	cout << resetiosflags(ios::left) << endl;
    }

    /**
     * user create a meeting with someone else
     */
    void AgendaUI::createMeeting(void) {
    	cout << endl;
    	cout << "[create meeting] [the number of participators]" << endl;
    	cout << "[create meeting] ";
    	int num;
    	cin >> num;
    	vector<string> partname;
    	for (int i = 1; i <= num; i++) {
    		cout << "[create meeting] [please enter the participator " << 
    			i << " ]" << endl;
    		cout << "[create meeting] ";
    		string name;
    		cin >> name;
    		partname.push_back(name);
    	} 
    	cout << "[create meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    	cout << "[create meeting] ";
    	string title, sDate, eDate;
    	cin >> title >> sDate >> eDate;
    	if (m_agendaService.createMeeting(m_userName, title, sDate, eDate, partname)) {
    		cout << "[create meeting] succeed!" << endl;
    	}
    	else {
    		cout << "[create meeting] error!" << endl;
    	}
    	cout << endl;
    }

    /**
     * list all meetings from storage
     */
    void AgendaUI::listAllMeetings(void) {//whether as a sponsor or participator
    	list<Meeting> l = m_agendaService.listAllMeetings(m_userName);
    	cout << endl;
    	cout << "[list all meetings]" << endl;
    	cout << endl;
    	if (l.empty()) {
    		cout << "none" << endl;
    		cout << endl;
    	}
    	else {
    		printMeetings(l);
    	}
    }

    /**
     * list all meetings that this user sponsored
     */
    void AgendaUI::listAllSponsorMeetings(void) {
    	list<Meeting> l = m_agendaService.listAllSponsorMeetings(m_userName);
    	cout << endl;
    	cout << "[list all sponsor metings]" << endl;
    	cout << endl;
    	if (l.empty()) {
    		cout << "none" << endl;
    		cout << endl;
    	}
    	else {
    		printMeetings(l);
    	}
    }

    /**
     * list all meetings that this user take part in
     */
    void AgendaUI::listAllParticipateMeetings(void) {
    	list<Meeting> l = m_agendaService.listAllParticipateMeetings(m_userName);
    	cout << endl;
    	cout << "[list all sponsor metings]" << endl;
    	cout << endl;
    	if (l.empty()) {
    		cout << "none" << endl;
    		cout << endl;
    	}
    	else {
    		printMeetings(l);
    	}
    }

    /**
     * search meetings by title from storage
     */
    void AgendaUI::queryMeetingByTitle(void) {
    	cout << endl;
    	cout << "[query meeting] [title]:" << endl;
    	cout << "[query meeting] ";
    	string title;
    	cin >> title;
    	list<Meeting> l = m_agendaService.meetingQuery(m_userName, title);
    	if (l.empty()) {
    		cout << "none" << endl;
    		cout << endl;
    	}
    	else {
    		printMeetings(l);
    	}
    }

    /**
     * search meetings by timeinterval from storage
     */
    void AgendaUI::queryMeetingByTimeInterval(void) {
    	cout << endl;
    	cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)][end time(yyyy-mm-dd/hh:mm)]" << endl;
    	cout << "[query meeting]";
    	string sDate, eDate;
    	cin >> sDate >> eDate;
    	cout << "[query meeting]" << endl;
    	list<Meeting> l = m_agendaService.meetingQuery(m_userName, sDate, eDate);
    	if (l.empty()) {
    		cout << "none" << endl;
    		cout << endl;
    	}
    	else {
			printMeetings(l);    		
    	}
    }

    /**
     * delete meetings by title from storage
     */
    void AgendaUI::deleteMeetingByTitle(void) {
    	cout << endl;
    	cout << "[delete meeting] [title]" << endl;
    	cout << "[delete meeting] ";
    	string title;
    	cin >> title;
    	cout << endl;
    	if (m_agendaService.deleteMeeting(m_userName, title)) {
    		cout << "[delete meeting by title] succeed!" << endl << endl;
    	}
    	else {
    		cout << "[error] deelete meeting fail!" << endl;
    	}
    }

    /**
     * delete all meetings that this user sponsored
     */
    void AgendaUI::deleteAllMeetings(void) {
    	cout << endl;
    	if (m_agendaService.deleteAllMeetings(m_userName)) {
    		cout << "[delete all meetings] succeed!" << endl << endl;
    	}
    	else {
    		cout << "[error] deelete meeting fail!" << endl;
    	}
    }

    string vector2string(vector<string> v) {
    	string ret = "";
    	bool isFirst = true;
    	for (auto each : v) {
    		if (isFirst) {
    			ret += each;
    			isFirst = false;
    		}
    		else {
    			ret += "," + each;
    		}
    	}
    	return ret;
    }
    /**
     * show the meetings in the screen
     */
    void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    	cout << setiosflags(ios::left);
    	cout << setw(20) << "title" 
    		 << setw(20) << "sponsor"
    	     << setw(30) << "start time"
    	     << setw(30) << "end time"
    	     << setw(20) << "participators" << endl;
    	for (auto each : t_meetings) {
    		cout << setw(20) << each.getTitle()
    			 << setw(20) << each.getSponsor()
    			 << setw(30) << Date::dateToString(each.getStartDate())
    			 << setw(30) << Date::dateToString(each.getEndDate())
    			 << setw(20) << vector2string(each.getParticipator()) << endl;
    	}
    	cout << resetiosflags(ios::left) << endl;
    }