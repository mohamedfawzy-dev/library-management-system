/*  =====================| Library System |======================

	Student Name : Mohamed Ahmed Fawzy Mohamed Elsayed
	Student ID   : 8251818
	Major        : Data Science
	Teaching Assistant : Mariam AlKassaby

	============================================================= */

#include <iostream>
#include <string>
using namespace std;

void PauseAndClear()    // دي بتنضف الدنيا كده وتلمعها
{
	system("pause");
	system("cls");
}

class User      // الكلاس الاساسي اللي وارثين منه
{
private:
	int id;
	string password;
public:
	string name;

	void SetUser(int i, string n,string p)   // الايدي والاسم والباسوورد
	{
		id = i;
		password = p;
		name = n;
	}

	int GetID()   
	{
		return id;
	}

	string GetPassword()
	{
		return password;
	}

	void SetPassword(string p)    // عشان لو هتغير الباسوورد تغيره ويتحفظ يعني وكده
	{
		password = p;
	}

};

class Member : public User       // وارث من اليوزر ودا اللي بيستعير وبيتحط عليه غرامات 
{
private:
	int borrowed_books[5];    // الكتب بتتخزن هنا المفروض
	int borrowed_count;           // عدد الكتب اللي هو مستعيرها
	double fine;                        // الغرامة اللي على الراجل دا
public: 
	Member()
	{
		borrowed_count = 0; // المفروض كده انه مش مستعير اي حاجة لسه فاضي
		fine = 0;
	}

	int getBorrowedCount()        
	{
		return borrowed_count;
	}

	int getBorrowedBookAt(int index)       // بيرجع كتاب معين من المستعارة
	{
		return borrowed_books[index];
	}

	void AddBorrowedBook(int id)      // بتضيف الكتاب لما الجدع دا يستعيره
	{
		if (borrowed_count < 5)
		{
			borrowed_books[borrowed_count] = id;
			borrowed_count++;
		}
	}

	void RemoveBorrowedBook(int index)          // بتشيل كتاب
	{
		for (int i = index; i < borrowed_count - 1; i++)
		{
			borrowed_books[i] = borrowed_books[i + 1];
		}
		borrowed_count--;
	}

	void AddFine(double amount)
	{
		fine += amount;
	}

	double GetFine()
	{
		return fine;
	}

	void PayFine()
	{
		fine = 0;
	}
};

class Librarian : public User       // LibrarySystem كل الشغل في  
{
public:
	void addMember(){}
	void addBook(){}
};

class Book          // كلاس فيه بيانات الكتاب كلها و موجود ولا حد مستعيره
{
private:
	int id;
	string title;
	string author;
	bool available;
public:
	Book()
	{
		available = true; //كده بقا المفروض انه مش محجوز يعني متاح 
	}

	void SetBook(int i, string t, string a)     
	{
		id = i;
		title = t;
		author = a;
		available = true;
	}

	int GetId() { return id; }  

	string getTitle() { return title; }

	string getAuthor() { return author; }

	bool isAvailable() { return available; }   // متاح ولا ايه
	
	void SetAvailable(bool val)     // بتغير حالته
	{
		available = val;
	}
};

class LibrarySystem        // اللي مدور السيستم كله لو باظ البروجكت ودع الملاعب
{
private:
	Book books[100];
	int book_count;

	Member members[100];
	int member_count;

	string admin_password;
public:
	LibrarySystem()                     // بيبدا السيستم هنا .. كل حاجة متصفرة والميمبر الافتراضي
	{
		book_count = 0;
		member_count = 0;
		admin_password = "admin67";

		members[member_count].SetUser(1, "default", "1234");
		member_count++;
	}

	void AddBook()                 // دالة للادمن عشان يضيف كتب ويتحقق من صحة اللي كتبه 
	{
		system("cls");
		cout << "===| ADD NEW BOOK |===" << endl;
		if (book_count >= 100)
		{
			cout << "Library is full :(" << endl;
			return;       // بيطلع من الفانكشن كلها وبيفكه منها
		}
		bool op = true;         // بيعيد السؤال لغاية ما تكتبله صح
		while (op)
		{
			int id;
			string title, author;

			cout << "Enter Book's ID : ";
			if (!(cin >> id))
			{
				cout << "Invalid ID input!" << endl;

				cin.clear();
				cin.ignore(1000, '\n');

				op = true;
				continue;
			}
			op = false;            // ميعيدش اللوب تاني

			cout << "Enter Book's Title : ";
			cin.ignore();                      // دي برضوا جديدة اني اكتب اسم كامل من كلمتين او اكتر زي "Harry Potter"
			getline(cin, title);
			cout << "Enter Book's Author : ";
			getline(cin, author);

			books[book_count].SetBook(id, title, author); // 😐 .. طلع ممكن اضيف ايموجي
			book_count++;

			cout << "==============================" << endl;
			cout << "Book added successfully!" << endl;
		}
		// 💁 بنشوف في مكان فاضي ولا لا و بناخد بيانات الكتاب عشان نضيفه 
	}

	void ViewBooks()             // عرض كل الكتب الموجودة بالاسم والايدي ومتاح ولا حالته ايه بالظبط
	{
		system("cls");
		cout << "===========| BOOK LIST |===========" << endl;
		if (book_count == 0)
		{
			cout << "No Books!" << endl;
			return;
		}

		for (int i = 0; i < book_count; i++)
		{
			cout << "--------------------------------" << endl;
			cout << "Book #" << i + 1 << endl;
			cout << "ID     : " << books[i].GetId() << endl;
			cout << "Title  : " << books[i].getTitle() << endl;
			cout << "Author : " << books[i].getAuthor() << endl;

			if (books[i].isAvailable())
				cout << "Status : Available " << endl;
			else
				cout << "Status : Borrowed " << endl;
		}
		cout << "--------------------------------" << endl;
		
	}

	void AddMember()        // اضافة ميمبر والادمن بيحط الاسم والباسوورد والايدي ويتحقق برضوا من اللي اتكتب دا
	{
		system("cls");
		cout << "===| REGISTER NEW MEMBER |===" << endl;
		if (member_count >= 100)
		{
			cout << "FULL !" << endl;
			return;
		}
		bool op = true;    
		while (op)
		{
		int id;
		string name, password;

		cout << "Enter ur ID : ";      // نصـحني اخلي الايدي قبل الاسم عشان مميز اكتر .. مش عارف ايه الفكرة بس ماشي ^-^
		if (!(cin >> id))                     
		{
			cout << "Invalid ID input!" << endl;

			cin.clear();
			cin.ignore(1000, '\n');

			op = true;                             
			continue;
		}
		op = false;
		cout << "Enter ur name : ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter ur password : ";
		cin >> password;                    //نصـحني اني اشيل الجيت لاين من هنا مش عارف ليه :-:

		if (id < 0)
		{
			cout << "Invalid ID !" << endl;
			return;
		}

		members[member_count].SetUser(id, name, password);
		member_count++;

		cout << "==============================" << endl;
		cout << "Member Added Successfully :)" << endl;
		}
	}

	int Login()                   // كتبناها هنا مش في ميمبر عشان دي شغالة عالكل ميمبر شغال على واحد بس
	{
		system("cls");
		cout << "===========| LOGIN |===========" << endl;
		for (int i = 0; i < 3; i++)
		{
			int id;
			string password;

			cout << "Enter ur ID : ";

			if (!(cin >> id))                     // '-'
			{

				
				cout << "Invalid ID input!\n";

				cin.clear();
				cin.ignore(1000, '\n');

				i--;                              // ما تحسبهاش محاولة
				continue;
			}

			cout << "Enter ur Password : ";
			cin >> password;

			for (int j = 0; j < member_count; j++)
			{
				if (id == members[j].GetID() && password == members[j].GetPassword())
				{
					system("cls");

					cout << "============================================" << endl;
					cout << "             | LOGIN SUCCESSFUL |           " << endl;
					cout << "============================================" << endl;
					cout << "        | Welcome to Library System |          " << endl;
					cout << "============================================" << endl;

					system("pause");

					return j;
				}
			}
			cout << "Invalid ID or Password :O" << endl;
		}
		return -1;       ////
	}

	void BorrowBook(int userindex)         // استعارة .. بيتاكد ان الادخال صح والميمبر مش معدي القيمة الماكس ومش مستعير نفس الكتاب مرتين
	{                                               // لو كله صح بيضيفه للميمبر ويغير حالته من متاح ل مش متاح
		system("cls");
		cout << "===| BORROW BOOK |===" << endl;
		int id;
		cout << "Enter Book ID : ";

		if (!(cin >> id))
		{
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}

		if (members[userindex].getBorrowedCount() >= 5)
		{
			cout << "You reached max borrowed books!" << endl;
			return;
		}

		for (int i = 0; i < members[userindex].getBorrowedCount(); i++)
		{
			if (members[userindex].getBorrowedBookAt(i) == id)
			{
				cout << "You already borrowed this book!" << endl;
				return;
			}
		}

		for (int i = 0; i < book_count; i++)
		{
			if (books[i].GetId() == id)
			{
				if (books[i].isAvailable()) 
				{
					books[i].SetAvailable(false);
					members[userindex].AddBorrowedBook(id);
					
					cout << "Borrowed: " << books[i].getTitle() << endl;
					
				}
				else
				{
					
					cout << "Not Available :(" << endl;
				}
				return;
			}
		}
		
		cout << "Invalid Book ID !" << endl;
	}

	void ReturnBook(int userindex)              // بترجع الكتب وبتعرض الكتب اللي معاه ويختار وتضيفله غرامة '-'
	{
		system("cls");
		cout << "===| RETURN BOOK |===" << endl;

		if (members[userindex].getBorrowedCount() == 0)
		{
			cout << "No Borrowed Books!" << endl;
			return;
		}

		cout << "Your Borrowed Books:" << endl;

		for (int i = 0; i < members[userindex].getBorrowedCount(); i++)
		{
			int id = members[userindex].getBorrowedBookAt(i);

			for (int j = 0; j < book_count; j++)
			{
				if (books[j].GetId() == id)
				{
					cout << "[" << i + 1 << "] " << books[j].getTitle() << endl;
				}
			}
		}

		int choice;
		cout << "Choose book to return: ";

		if (!(cin >> choice))
		{
			cout << "Invalid input!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			return;
		}

		if (choice < 1 || choice > members[userindex].getBorrowedCount())
		{
			cout << "Invalid choice!" << endl;
			return;
		}

		int id = members[userindex].getBorrowedBookAt(choice - 1);

		for (int i = 0; i < book_count; i++)
		{
			if (books[i].GetId() == id)
			{
				books[i].SetAvailable(true);
				cout << "Returned: " << books[i].getTitle() << endl;
			}
		}

		members[userindex].RemoveBorrowedBook(choice - 1);

		members[userindex].AddFine(10);
		cout << "Fine added: 10" << endl;

		cout << "Book Returned Successfully!" << endl;
	}

	void ViewMyBooks(int userindex)               // الكتب اللي مع الميمبر تظهرله ... بيطابق الايديهات مع بعض يعني
	{
		system("cls");
		cout << "===| MY BORROWED BOOKS |===" << endl;

		if (members[userindex].getBorrowedCount() == 0)
		{
			cout << "You have no borrowed books." << endl;
			return;
		}

		for (int i = 0; i < members[userindex].getBorrowedCount(); i++)
		{
			int id = members[userindex].getBorrowedBookAt(i);

			for (int j = 0; j < book_count; j++)
			{
				if (books[j].GetId() == id)
				{
					cout << "- " << books[j].getTitle() << endl;
				}
			}
		}
	}

	void ChangePassword(int userindex)              // عشان يغير باسوورده
	{
		system("cls");
		string oldPass, newPass;

		cout << "Enter current password: ";
		cin >> oldPass;

		if (oldPass != members[userindex].GetPassword())
		{
			cout << "Wrong password!" << endl;
			return;
		}

		cout << "Enter new password: ";
		cin >> newPass;

		members[userindex].SetPassword(newPass);

		cout << "Password changed successfully!" << endl;
	}

	void ViewFine(int userindex)            // تعرضله الغرامة اللي عليه
	{
		system("cls");
		cout << "===| YOUR FINE |===" << endl;
		cout << "Fine: " << members[userindex].GetFine() << endl;
	}

	void PayFine(int userindex)         // يدفع اللي عليه بالتسليك ولو مفيش غرامة يقوله
	{
		system("cls");

		double f = members[userindex].GetFine();

		if (f == 0)
		{
			cout << "No fines to pay!" << endl;
			return;
		}

		cout << "Your fine is: " << f << endl;
		cout << "Paying..." << endl;

		members[userindex].PayFine();

		cout << "Fine paid successfully!" << endl;
	}

	void ViewMembers()           // تبع الادمن عشان يعرض الميمبرز وغرامتهم واساميهم وكل ده عشان يعرف يصـطادهم
	{ 
		system("cls");
		cout << "===========| MEMBERS LIST |===========" << endl;

		if (member_count == 0)
		{
			cout << "No Members!" << endl;
			return;
		}

		for (int i = 0; i < member_count; i++)
		{
			cout << "--------------------------------" << endl;
			cout << "Member #" << i + 1 << endl;
			cout << "ID   : " << members[i].GetID() << endl;
			cout << "Name : " << members[i].name << endl;
			cout << "Borrowed Books: " << members[i].getBorrowedCount() << endl;
			cout << "Fine : " << members[i].GetFine() << endl;
		}
		cout << "--------------------------------" << endl;
	}

	void ShowWelcome()
	{
		system("cls");

		cout << "====================================" << endl;
		cout << "          | LIBRARY SYSTEM |         " << endl;
		cout << "====================================" << endl;
		cout << "             | WELCOME |               " << endl;
		cout << "====================================" << endl;

		system("pause");   
	}

	void StartSystem()                 // main اهم دالة في دا كله وهي السبب ان الدنيا نضيفة تحت في ال
	{                                              // كل القوايم والتنقل مابينهم موجود هنا
		ShowWelcome();

		while (true)
		{
			system("cls");
			cout << "====================================" << endl;
			cout << "          | LIBRARY SYSTEM |         " << endl;
			cout << "====================================" << endl;
			cout << "[1] Admin" << endl;
			cout << "[2] Member" << endl;
			cout << "[3] Exit" << endl;
			cout << "====================================" << endl;
			cout << "Enter your choice: ";

			int choice;
			if (!(cin >> choice))              // كان بيحصل انفنتي لوب واقترح اني اعمل البتاع دي
			{
				cout << "Invalid input! Please enter a number." << endl;

				cin.clear();
				cin.ignore(1000, '\n');

				PauseAndClear();

				continue;
			}

			if (choice == 1)
			{
				string pass;
				cout << "Enter ur password : ";
				cin >> pass;

				if (pass == "admin67")
				{
					while (true)
					{
						system("cls");
						cout << "===========| ADMIN MENU |===========" << endl;
						cout << "[1] Add Book" << endl;
						cout << "[2] View Books" << endl;
						cout << "[3] Add Member" << endl;
						cout << "[4] View Members" << endl;
						cout << "[5] Back" << endl;
						cout << "=================================" << endl;
						cout << "Enter your choice: ";

						int c;
						if (!(cin >> c))
						{
							cout << "Invalid input!\n";

							cin.clear();
							cin.ignore(1000, '\n');

							PauseAndClear();

							continue;
						}

						if (c == 1)
						{
							AddBook();
							PauseAndClear();
						}
						else if (c == 2)
						{
							ViewBooks();
							PauseAndClear();
						}
						else if (c == 3)
						{
							AddMember();
							PauseAndClear();
						}
						else if (c == 4)
						{
							ViewMembers();
							PauseAndClear();
						}
						else if (c == 5)
						{
							break;
						}
						else
						{
							cout << "Invalid Choice .. Try again." << endl;
							PauseAndClear();
						}
					}
				}
				else
				{
					cout << "Wrong Password !" << endl;
					PauseAndClear();
				}
			}
			else if (choice == 2)
			{
				int userindex = Login();

				if (userindex != -1)
				{
					while (true)
					{
						system("cls");
						cout << "===========| MEMBER MENU |==========" << endl;
						cout << "[1] Borrow Book" << endl;
						cout << "[2] Return Book" << endl;
						cout << "[3] View Books" << endl;
						cout << "[4] My Books" << endl;
						cout << "[5] Change Password" << endl;
						cout << "[6] View Fine" << endl;
						cout << "[7] Pay Fine" << endl;
						cout << "[8] Logout" << endl;
						cout << "=================================" << endl;
						cout << "Enter your choice: ";

						int c;
						if (!(cin >> c))
						{
							cout << "Invalid input!\n";

							cin.clear();
							cin.ignore(1000, '\n');

							PauseAndClear();
							continue;
						}

						if (c == 1)
						{
							BorrowBook(userindex);
							PauseAndClear();
						}
						else if (c == 2)
						{
							ReturnBook(userindex);
							PauseAndClear();
						}
						else if (c == 3)
						{
							ViewBooks();
							PauseAndClear();
						}
						else if (c == 4)
						{
							ViewMyBooks(userindex);
							PauseAndClear();
						}
						else if (c == 5)
						{
							ChangePassword(userindex);
							PauseAndClear();
						}
						else if (c == 6)
						{
							ViewFine(userindex);
							PauseAndClear();
						}
						else if (c == 7)
						{
							PayFine(userindex);
							PauseAndClear();
						}
						else if (c == 8)
						{
							break;
						}
						else
						{
							cout << "Invalid Choice .. Try again." << endl;
							PauseAndClear();
						}
					}
				}
			}
			else if (choice == 3)
			{
				return ;
			}
			else
			{
				cout << "Invalid Choice!" << endl;
			}
		}
	}   
};

int main()
{
	LibrarySystem System;
	System.StartSystem();
}