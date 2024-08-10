#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// This Class I Made It To Implement A Static Methods To Help Me In Specific Cases
static class Helper
{
	public:
		static vector<string> split(const string& s, char delimiter) {
			vector<string> tokens;
			stringstream ss(s);
			string token;
			while (getline(ss, token, delimiter)) {
				tokens.push_back(token);
			}
			return tokens;
		}

		static void read_int(int Temp, string msg)
		{
			while (true)
			{
				cout << msg;
				cin >> Temp;

				if (Temp >= numeric_limits<int>::min() && Temp <= numeric_limits<int>::max())
				{
					break;
				}
				else
				{
					cout << "Please Enter Valid Numeric Value\n";
				}
			}
		}

		static void read_long(long Temp, string msg)
		{
			while (true)
			{
				cout << msg;
				cin >> Temp;

				if (Temp >= numeric_limits<long>::min() && Temp <= numeric_limits<long>::max())
				{
					break;
				}
				else
				{
					cout << "Please Enter Valid Numeric Value\n";
				}
			}
		}

		static int string_to_int(string s)
		{
			stringstream ss(s);

			int num;

			ss >> num;

			return num;
		}

		static long string_to_long(string s)
		{
			stringstream ss(s);

			long num;

			ss >> num;

			return num;
		}
};

class question
{
private:
	int num_of_threads;
public:
	bool thread_or_not;
	int id_of_question;
	string text;
	string answer;

	int user_id_from;
	int user_id_to;

	int id_of_parent_question;

	void make_new_question(int n, int id1, int id2, int anonymous, int id3, bool thr)
	{
		if (thr)
		{
			thread_or_not = true;
		}
		else
		{
			thread_or_not = false;
		}

		id_of_question = n;

		// Clear Input Buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		string q_text;
		cout << "Enter The Question Text Which You Need To Ask It\n";
		getline(cin, q_text);
		text = q_text;

		if (anonymous == 1)
		{
			user_id_from = -1;
		}
		else
		{
			user_id_from = id1;
		}

		user_id_to = id2;

		id_of_parent_question = id3;
	}

	void answer_question()
	{
		if (answer != "")
		{
			cout << "Question : " << text << "\n";
			cout << "Enter Your Answer : ";
			string _answer;
			cin >> _answer;

			answer = _answer;
		}
		else
		{
			cout << "This Question Already Answered\n";
			cout << "This Is The Answer : " << answer << "\n";
		}
	}
};

class Users;

class User
{
	private:
		// For Calling Users Class Methods
		Users* _users;
	public:
		int id;
		string user_name;
		long password;
		string full_name;
		string email;
		bool allow_anonymous;

		User()
		{
			
		}

		User(Users* _us)
		{
			_users = _us;
		}

		void add_user(int num)
		{
			id = num;

			cout << "Enter Your UserName Without Space : ";
			string _username;
			cin >> _username;

			user_name = _username;

			cout << "Enter Your Password : ";
			long _password;
			cin >> _password;

			password = _password;

			cout << "Enter Your FullName Without Space : ";
			string _full_name;
			cin >> _full_name;

			full_name = _full_name;

			cout << "Enter Your Email : ";
			string _email;
			cin >> _email;

			email = _email;

			cout << "Allow Anonymous Questions Or Not\n1 - Yes\n2- No\n";
			int choice2;
			while (true)
			{
				cout << "Enter Your Choice : ";
				cin >> choice2;

				if (choice2 == 1 || choice2 == 2)
				{
					break;
				}
				else
				{
					cout << "Wrong Choice Please Try Again";
				}
			}

			bool _allow = 1;

			if (choice2 == 2)
			{
				_allow = 0;
			}

			allow_anonymous = _allow;
		}

		int get_id()
		{
			return id;
		}

		void ask_question();

		bool check_question_id(int _id);

		question get_question(int _id);

		void delete_question();

		void delete_question_by_id(int _id);

		void answer_question();

		void logout()
		{
			cout << "Thanks For Using Our System Waiting You ASAP :)\n";
		}

		void add_question_to_file(question q)
		{
			ofstream fout("questions.txt", ios::app);

			fout << q.thread_or_not << ",";
			fout << q.id_of_question << ",";
			fout << q.text << ",";
			fout << q.answer << ",";
			fout << q.user_id_from << ",";
			fout << q.user_id_to << ",";
			fout << q.id_of_parent_question << "\n";

			fout.close();
		}

		void print_questions_from_me();

		void print_questions_to_me();
};

void print_question(question q);

class Users
{
	public:

		User current_user;

		void add_new_user()
		{
			User U;
			U.add_user(get_nums_of_users() + 1);

			add_new_user_to_file(U);
			current_user = U;
		}

		void add_new_user_to_file(User U)
		{
			ofstream fout("users.txt", ios::app);

			fout << U.id << ",";
			fout << U.user_name << ",";
			fout << U.password << ",";
			fout << U.full_name << ",";
			fout << U.email << ",";
			fout << U.allow_anonymous << "\n";

			fout.close();
		}

		bool login()
		{
			ifstream fin("users.txt");

			if (fin.fail())
			{
				cout << "No Users Now In The System\n";
				return false;
			}
			else
			{
				while (true)
				{
					cout << "Enter Your UserName : ";
					string _username;
					cin >> _username;

					cout << "Enter Your Password : ";
					long _password;
					cin >> _password;

					bool Flag = check_data(_username, _password);

					if (Flag == true)
					{
						current_user = get_current_user(_username);
						break;
					}
					else
					{
						cout << "Wrong Username Or Password Try Again !\n";
					}
				}

				return true;
			}

			fin.close();
		}

		bool check_data(string _username, long _password)
		{
			vector<User>users = read_users_from_file();

			for (int i = 0; i < users.size(); ++i)
			{
				if (users[i].user_name == _username && users[i].password == _password)
				{
					return true;
				}
			}

			return false;
		}

		vector<User>read_users_from_file()
		{
			ifstream fin("users.txt");

			vector<string>Temp;
			string str;

			while (getline(fin, str))
			{
				Temp.push_back(str);
			}

			vector<User>users;
			for (int i = 0; i < Temp.size(); ++i)
			{
				vector<string>Temps = Helper::split(Temp[i], ',');

				User U;
				U.id = Helper::string_to_int(Temps[0]);
				U.user_name = Temps[1];
				U.password = Helper::string_to_long(Temps[2]);
				U.full_name = Temps[3];
				U.email = Temps[4];
				if (Temps[5] == "1")
				{
					U.allow_anonymous = true;
				}
				else
				{
					U.allow_anonymous = false;
				}

				users.push_back(U);

				Temps.clear();
			}

			fin.close();

			return users;
		}

		vector<question>read_questions_from_file()
		{
			ifstream fin("questions.txt");

			vector<string>Temp;
			string str;

			vector<question>Temps;

			// Check If The File Is Empty Or Not
			char ch;
			if (!fin.get(ch))
			{
				return Temps;
			}

			while (getline(fin, str))
			{
				Temp.push_back(str);
			}

			for (int i = 0; i < Temp.size(); ++i)
			{
				vector<string>ques = Helper::split(Temp[i], ',');

				question q;

				if (ques[0] == "1")
				{
					q.thread_or_not = true;
				}
				else
				{
					q.thread_or_not = false;
				}
				q.id_of_question = Helper::string_to_int(ques[1]);
				q.text = ques[2];
				q.answer = ques[3];
				q.user_id_from = Helper::string_to_int(ques[4]);
				q.user_id_to = Helper::string_to_int(ques[5]);
				q.id_of_parent_question = Helper::string_to_int(ques[6]);

				Temps.push_back(q);
			}

			fin.close();

			return Temps;
		}

		int get_nums_of_users()
		{
			vector<User>users = read_users_from_file();

			return users.size();
		}

		int get_nums_of_questions()
		{
			vector<question> ques = read_questions_from_file();

			return ques.size();
		}

		void print_all_users()
		{
			vector<User>users = read_users_from_file();

			for (int i = 0; i < users.size(); ++i)
			{
				cout << "ID : " << users[i].id << " Name : " << users[i].full_name << "\n";
			}
		}

		User get_current_user(string _username)
		{
			vector<User>users = read_users_from_file();

			for (int i = 0; i < users.size(); ++i)
			{
				if (users[i].user_name == _username)
				{
					current_user = users[i];
					return current_user;
				}
			}
		}

		vector<int> get_users_ids()
		{
			vector<User>users = read_users_from_file();

			vector<int>ids;

			for (int i = 0; i < users.size(); ++i)
			{
				ids.push_back(users[i].id);
			}

			return ids;
		}

		User get_user(int _id)
		{
			vector<User>users = read_users_from_file();

			for (int i = 0; i < users.size(); ++i)
			{
				if (users[i].id == _id)
				{
					return users[i];
				}
			}
		}

		bool check_id(int _id)
		{
			vector<int>ids = get_users_ids();

			for (int i = 0; i < ids.size(); ++i)
			{
				if (ids[i] == _id)
				{
					return true;
				}
			}

			return false;
		}

		void feed_questions()
		{
			vector<question>questions = read_questions_from_file();

			if (questions.size() == 0)
			{
				cout << "No Questions Currently In The ASKfm System\n";
				return;
			}

			for (int i = 0; i < questions.size(); ++i)
			{
				print_question(questions[i]);
			}
		}

		int nums_of_question_from_user(User U)
		{
			vector<question>questions = read_questions_from_file();

			int sum = 0;

			for (int i = 0; i < questions.size(); ++i)
			{
				if (questions[i].user_id_from == U.id)
				{
					sum++;
				}
			}

			return sum;
		}

		int nums_of_question_to_user(User U)
		{
			vector<question>questions = read_questions_from_file();

			int sum = 0;

			for (int i = 0; i < questions.size(); ++i)
			{
				if (questions[i].user_id_to == U.id)
				{
					sum++;
				}
			}

			return sum;
		}
};

// User Class Implemented Methods
void User::ask_question()
{
	// [1]
	int _id;
	while (true)
	{
		cout << "Enter User ID Who Need To Ask Him\n";
		cin >> _id;

		bool Flag = _users->check_id(_id);

		if (Flag)
		{
			break;
		}
		else
		{
			cout << "This User ID Not Exsits In This System : Try Again!\n";
		}
	}

	if (id == _id)
	{
		cout << "You Cannot Ask Itself\n";
		return;
	}

	// [2]
	// Get The User Who I Need To Ask Him
	User U = _users->get_user(_id);
	int choice2 = 0;

	if (!U.allow_anonymous)
	{
		cout << "Note : Anonymous Questions Are Not Allowed For This User\n";
		choice2 = 2;
	}
	else
	{
		cout << "Are You Need To Be Anonymous User Or Not\n";
		cout << "1 - Yes\n";
		cout << "2 - No\n";
		while (true)
		{
			cout << "Enter Your Choice : ";
			cin >> choice2;

			if (choice2 == 1 || choice2 == 2)
			{
				break;
			}
			else
			{
				cout << "Wrong Choice Please Try Again";
			}
		}
	}

	// [3]
	int choice3 = 0;
	cout << "Do You Want To Ask In Thread Or New Question\n";
	cout << "1 - InThread\n";
	cout << "2 - New Question\n";
	while (true)
	{
		cout << "Enter Your Choice : ";
		cin >> choice3;

		if (choice3 == 1 || choice3 == 2)
		{
			break;
		}
		else
		{
			cout << "Wrong Choice Please Try Again";
		}
	}

	// Make A New Question
	question q;

	if (choice3 == 1)
	{
		// Case Thread
		int _id;
		while (true)
		{
			cout << "Enter The Question ID : ";
			cin >> _id;

			bool Flag = U.check_question_id(_id);

			if (Flag)
			{
				break;
			}
			else
			{
				cout << "This Quesion ID Not Exsits In This System : Try Again!\n";
			}
		}

		q.make_new_question(_users->get_nums_of_questions() + 1, id, U.id, choice2, _id, true);

		add_question_to_file(q);
	}
	else if (choice3 == 2)
	{
		// Case New Question
		q.make_new_question(_users->get_nums_of_questions() + 1, id, U.id, choice2, -1, false);

		add_question_to_file(q);
	}
}

// Stand-Alone Method
void print_question(question q)
{
	if (q.thread_or_not)
	{
		cout << "Thread Question \n";
	}

	cout << "------------------\n";

	cout << "Question ID " << q.id_of_question << "\n";

	if (q.user_id_from == -1)
	{
		cout << "From Anonymous User ";
	}
	else
	{
		cout << "From User ID " << q.user_id_from << "\n";
	}

	cout << "To User ID " << q.user_id_to << "\n";

	cout << "QuestionText : " << q.text << "\n";

	if (q.answer != "")
	{
		cout << "Answer " << q.answer << "\n";
	}
	else
	{
		cout << "This Question Still Dont Have An Answer From User ID " << q.user_id_to << "\n";
	}
}

void User::print_questions_from_me()
{
	vector<question>questions_from_me = _users->read_questions_from_file();

	for (int i = 0; i < questions_from_me.size(); ++i)
	{
		if (questions_from_me[i].user_id_from == id)
		{
			print_question(questions_from_me[i]);
		}
	}
}

void User::print_questions_to_me()
{
	vector<question>questions_to_me = _users->read_questions_from_file();

	for (int i = 0; i < questions_to_me.size(); ++i)
	{
		if (questions_to_me[i].user_id_to == id && questions_to_me[i].thread_or_not == false)
		{
			print_question(questions_to_me[i]);

			cout << "--------------------\n";

			for (int j = 0; j < questions_to_me.size(); ++j)
			{
				if (questions_to_me[j].id_of_parent_question == questions_to_me[i].id_of_question)
				{
					print_question(questions_to_me[j]);
				}
			}
		}
	}
}

bool User::check_question_id(int _id)
{
	vector<question>questions = _users->read_questions_from_file();

	for (int i = 0; i < questions.size(); ++i)
	{
		if (questions[i].id_of_question == _id)
		{
			return true;
		}
	}

	return false;
}

question User::get_question(int _id)
{
	vector<question>questions = _users->read_questions_from_file();

	for (int i = 0; i < questions.size(); ++i)
	{
		if (questions[i].id_of_question == _id)
		{
			return questions[i];
		}
	}
}

void User::delete_question_by_id(int _id)
{
	int Indx = -1;

	vector<question>questions = _users->read_questions_from_file();

	for (int i = 0; i < questions.size(); ++i)
	{
		if (questions[i].id_of_question == _id)
		{
			Indx = i;
		}
	}

	if (Indx == -1)
	{
		return;
	}

	questions.erase(questions.begin() + Indx);

	// Here I Will Delete All Questions In The File
	ofstream fout("questions.txt", ios::trunc);
	fout.close();

	for (int i = 0; i < questions.size(); ++i)
	{
		add_question_to_file(questions[i]);
	}
}

void User::answer_question()
{
	vector<question>questions4 = _users->read_questions_from_file();

	for (int i = 0; i < questions4.size(); ++i)
	{
		if (questions4[i].user_id_to == id)
		{
			if (questions4[i].thread_or_not)
			{
				cout << "Thread ";
			}

			cout << "Question : " << questions4[i].text << "\n";
			cout << "ID : " << questions4[i].id_of_question << "\n";

			if (questions4[i].answer != "")
			{
				cout << "Answer : " << questions4[i].answer << "\n";
			}

			cout << "------------------------\n";
		}
	}

	int _id;
	while (true)
	{
		cout << "Enter The Question ID Which You Need To Answer It: ";
		cin >> _id;

		bool Flag = check_question_id(_id);

		if (Flag)
		{
			break;
		}
		else
		{
			cout << "This User ID Not Exsits In This System : Try Again!\n";
		}
	}

	vector<question>questions = _users->read_questions_from_file();

	for (int i = 0; i < questions.size(); ++i)
	{
		if (questions[i].id_of_question == _id)
		{
			if (questions[i].answer != "")
			{
				cout << "Sorry This Question Already Answered\n";
				cout << questions[i].text << " : " << questions[i].answer << "\n";
				return;
			}
		}
	}

	question q = get_question(_id);

	delete_question_by_id(_id);

	cout << "Enter Your Answer : ";
	string _answer;
	cin >> _answer;

	q.answer = _answer;

	add_question_to_file(q);
}

void User::delete_question()
{
	vector<question>questions4 = _users->read_questions_from_file();

	for (int i = 0; i < questions4.size(); ++i)
	{
		if (questions4[i].user_id_to == id)
		{
			if (questions4[i].thread_or_not)
			{
				cout << "Thread ";
			}

			cout << "Question : " << questions4[i].text << "\n";
			cout << "ID : " << questions4[i].id_of_question << "\n";

			if (questions4[i].answer != "")
			{
				cout << "Answer : " << questions4[i].answer << "\n";
			}

			cout << "------------------------\n";
		}
	}

	int _id;
	while (true)
	{
		cout << "Enter Question ID Which You Need To Delete It : ";
		cin >> _id;

		bool Flag = check_question_id(_id);

		if (Flag)
		{
			break;
		}
		else
		{
			cout << "This Question ID Not Exsits In This System : Try Again!\n";
		}
	}

	delete_question_by_id(_id);
}

class ASKfm_sys
{
	public:

		void launch()
		{
			cout << "================= ASKfm Application =================" << "\n";

			cout << "Menu :" << "\n";
			cout << "1 - Login" << "\n";
			cout << "2 - Sign Up" << "\n";

			int choice;
			while (true)
			{
				cout << "Enter Your Choice : ";
				cin >> choice;

				if (choice == 1 || choice == 2)
				{
					break;
				}
				else
				{
					cout << "Wrong Choice Please Try Again";
				}
			}

			// Create Object From Users Class
			Users _users;
			bool Flag = true;

			switch (choice)
			{
			case 1:
				Flag = _users.login();
				int choice2;
				if (Flag == false)
				{
					while (true)
					{
						cout << "Do You Want To Be First User : -\n";
						cout << "1 - Yes\n";
						cout << "2 - No\n";
						cin >> choice2;

						if (choice2 == 1 || choice2 == 2)
						{
							break;
						}
						else
						{
							cout << "Please Enter 1 For Yes Or 2 For No";
						}
					}

					if (choice2 == 1)
					{
						_users.add_new_user();
						Flag = true;
					}
					else
					{
						cout << "GoodBye :)\n";
						break;
					}
				}

				break;

			case 2:
				_users.add_new_user();
				break;
			}

			// Login
			if (Flag)
			{
				// Current User 
				User U(&_users);
				U = _users.current_user;

				while (true)
				{
					cout << "====================================\n";

					cout << "Menu :" << "\n";
					cout << "1 - Print Questions To Me\n"; // Done
					cout << "2 - Print Questions Form Me\n"; // Done
					cout << "3 - Answer Question\n"; // Done
					cout << "4 - Delete Question From Your Questions\n"; // Done
					cout << "5 - Ask Question For Any User\n"; // Done
					cout << "6 - Users In The System\n"; // Done
					cout << "7 - Feed\n"; // Done
					cout << "8 - Logout\n"; // Done

					int choice;
					while (true)
					{
						cout << "Choose Number From 1 To 8 : ";
						cin >> choice;

						if (choice >= 1 && choice <= 8)
						{
							break;
						}
						else
						{
							cout << "Please Enter Number From 1 To 8\n";
						}
					}

					switch (choice)
					{
					case 1:
						if (_users.nums_of_question_to_user(U) == 0)
						{
							cout << "Sorry : You Dont Have Any Question\n";
							break;
						}
						U.print_questions_to_me();
						break;

					case 2:
						if (_users.nums_of_question_from_user(U) == 0)
						{
							cout << "Sorry : You Didn't Ask Any Question For Any User\n";
							break;
						}
						U.print_questions_from_me();
						break;

					case 3:
						if (_users.nums_of_question_to_user(U) == 0)
						{
							cout << "Sorry : You Dont Have Any Question To Answer It\n";
							break;
						}
						U.answer_question();
						break;

					case 4:
						if (_users.nums_of_question_to_user(U) == 0)
						{
							cout << "Sorry : You Dont Have Any Question To Delete It\n";
							break;
						}
						U.delete_question();
						break;

					case 5:
						U.ask_question();
						break;

					case 6:
						_users.print_all_users();
						break;

					case 7:
						_users.feed_questions();
						break;

					case 8:
						U.logout();
						break;
					}

					cout << "--------------\n";
					cout << "User " << U.id << ": Are You Need To Make Another Operation\n";
					cout << "1 - Yes\n";
					cout << "2 - No\n";
					cout << "Choose Number 1 For Yes And Number 2 For No : ";
					int choice4;
					cin >> choice4;

					if (choice4 == 2)
					{
						U.logout();
						break;
					}
				}
			}
		}
};

int main()
{
	ASKfm_sys system;
	system.launch();
}