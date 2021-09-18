#include <iostream>
#include <vector> 
#include <map>
#include <fstream>
#include <string>
using namespace std;
string path = "data_of_User.txt";
string path1 = "MQ_data.txt";
string path2 = "TQ_data.txt";
fstream database(path.c_str(), ios::in | ios::out | ios::app);
fstream DMQ(path1.c_str(), ios::in | ios::out | ios::app);
fstream DTQ(path2.c_str(), ios::in | ios::out | ios::app);
struct user
{
    int ID;
    string password;
    string Email;
    string User_Name;
    bool anonymous;
    user()
    {
        ID = 0;
        anonymous = true;
        password = Email = User_Name = "";
    }
};
struct main_question
{
    int ID_Q;          //                     <---- }
    bool is_Answer;
    bool is_Anonymous;
    string User_Name_to;       // line 1
    string Name_from_User;  //                 <----}

    vector<int>IDs_Thread;     // line 2           }

    string question;      //line 3                 }

    string Answer;      //line 4                  }
    main_question()
    {
        ID_Q = 0;
        is_Answer = is_Anonymous = false;
        Answer = "NOT Answer yet Please wait...";
    }

};
struct qouestion_thread
{
    int ID_Q;
    int ID_question_main;
    bool is_Answer;
    bool is_Anonymous;
    string User_Name_to;
    string Name_from_User;

    string question;
    string Answer;
    qouestion_thread()
    {
        ID_Q = ID_question_main = 0;
        is_Answer = is_Anonymous = 0;
        Answer = "NOT Answer yet Please wait...";
        User_Name_to = Name_from_User = question = "";
    }
};
void Up_dawnloud_Data_User(map<string, user>&);
void Update_UPloud_Data_MQ(map<int, main_question>&);
void Update_UPloud_Data_TQ(map<int, qouestion_thread>&);
void Update_dawnloud_Data_MQ(map<int, main_question>&);
void Update_dawnloud_Data_TQ(map<int, qouestion_thread>&);
string login_user(map<string, user>&);
string sign_up_user(map<string, user>&);
void List_System_users(map<string, user>&);
void Menu_Enter_to_project();
void Menu_operation_for_project();
void Ask_Question(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
void Print_Questions_To_Me(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
void Print_Questions_From_Me(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
void Delete_Question(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
void Answer_Question(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
void Feed(map<string, user>&, map<int, main_question>&, map<int, qouestion_thread>&, string);
int Choose_Menue1();
int Choose_Menue2();
void Project_Ask_me();
int main()
{
    Project_Ask_me();
}
void Project_Ask_me()
{
    map<string, user>User;
    map<int, main_question>MQ;
    map<int, qouestion_thread>TQ;
    string s;
    int c1 = 0, c2 = 0;

    while (!c1)
    {
        Up_dawnloud_Data_User(User);
        Update_dawnloud_Data_MQ(MQ);
        Update_dawnloud_Data_TQ(TQ);

        Menu_Enter_to_project();

        switch (Choose_Menue1())
        {
        case 1:
            s = login_user(User);
        case 2:
            break;
            s = sign_up_user(User);
            break;
        }

        //This body of project  
        cout << "\a\n\n\nWelcome , " << s << " \n\n\n" << endl;

        Menu_operation_for_project();
        while (!c2)
        {

            Up_dawnloud_Data_User(User);
            Update_dawnloud_Data_MQ(MQ);
            Update_dawnloud_Data_TQ(TQ);

            switch (Choose_Menue2())
            {
            case 1:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Print_Questions_To_Me(User, MQ, TQ, s);
                break;
            case 2:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Print_Questions_From_Me(User, MQ, TQ, s);
                break;
            case 3:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Answer_Question(User, MQ, TQ, s);
                break;
            case 4:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Delete_Question(User, MQ, TQ, s);
                break;
            case 5:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Ask_Question(User, MQ, TQ, s);
                break;
            case 6:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                List_System_users(User);
                break;
            case 7:
                Up_dawnloud_Data_User(User);
                Update_dawnloud_Data_MQ(MQ);
                Update_dawnloud_Data_TQ(TQ);
                Feed(User, MQ, TQ, s);
                break;
            case 8:
                c2++;
                break;
            case 9:
                c1++;
                c2++;
                break;
            }
            Up_dawnloud_Data_User(User);
            Update_dawnloud_Data_MQ(MQ);
            Update_dawnloud_Data_TQ(TQ);
        }
        cout << "\n\nGoodby, " << s << "\n\n\n\a";
        cout << "------------------------------------\n";
        cout << "------------------------------------\n";
        c2 = 0;
    }
    database.close();
}
void Up_dawnloud_Data_User(map<string, user>& User)
{
    string s;
    database.open(path.c_str(), ios::in | ios::out | ios::app);
    database.clear();
    User.clear();
    if (database.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {
        while (database >> s)
        {
            if (s != "" || User[s].ID != 0)
            {
                User[s].User_Name = s;
                database >> User[s].ID >> User[s].password >> User[s].Email >> User[s].anonymous;
            }
        }
        database.close();
    }

}
void Update_UPloud_Data_MQ(map<int, main_question>& MQ)
{
    string s;
    DMQ.open(path1.c_str(), ios::in | ios::out | ios::app);
    DMQ.clear();
    if (DMQ.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {
        fstream DMQ("MQ_data.txt", ios::in | ios::out | ios::trunc);
       
        DMQ.clear();
        for (auto Q : MQ)
        {
            DMQ << Q.first << " " << Q.second.Name_from_User << " " << Q.second.User_Name_to << " " << Q.second.is_Anonymous << " " << Q.second.is_Answer << endl;

            DMQ << Q.second.IDs_Thread.size() << endl;
            if (Q.second.IDs_Thread.size() > 0)
            {
                for (auto x : Q.second.IDs_Thread)
                {
                    DMQ << x << " ";
                }
                DMQ << endl;
            }

            DMQ << Q.second.question << endl;
            DMQ << Q.second.Answer << endl;
        }
        DMQ.close();
    }

}
void Update_UPloud_Data_TQ(map<int, qouestion_thread>& TQ)
{
    string s;
    DTQ.open(path2.c_str(), ios::in | ios::out | ios::app);
    DTQ.clear();
    if (DTQ.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {
        fstream DTQ("TQ_data.txt", ios::in | ios::out | ios::trunc);
        DTQ.clear();
        for (auto Q : TQ)
        {
            DTQ << Q.first << " " << Q.second.Name_from_User << " " << Q.second.User_Name_to << " " << Q.second.is_Anonymous << " " << Q.second.is_Answer << " " << Q.second.ID_question_main << endl;

            DTQ << Q.second.question << endl;

            DTQ << Q.second.Answer << endl;
        }
        DTQ.close();
    }

}
void Update_dawnloud_Data_MQ(map<int, main_question>& MQ)
{
    string s;
    int ID_Q = 0, sz = 0, id = 0;
    DMQ.open(path1.c_str(), ios::in | ios::out | ios::app);
    DMQ.clear();
    MQ.clear();
    if (DMQ.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {

        while (DMQ >> ID_Q)
        {

            if (ID_Q > 0)
            {
                MQ[ID_Q].ID_Q = ID_Q;
                DMQ >> MQ[ID_Q].Name_from_User >> MQ[ID_Q].User_Name_to >> MQ[ID_Q].is_Anonymous >> MQ[ID_Q].is_Answer;

                if (MQ[ID_Q].Name_from_User == "")
                    break;

                DMQ >> sz;
                if (sz > 0)
                {
                    for (int i = 0; i < sz; i++)
                    {
                        DMQ >> id;
                        MQ[ID_Q].IDs_Thread.push_back(id);
                    }
                }
                DMQ.ignore();
                getline(DMQ, MQ[ID_Q].question);
               //DMQ.ignore();
                getline(DMQ,MQ[ID_Q].Answer);
            }
        }
        DMQ.close();
    }
}
void Update_dawnloud_Data_TQ(map<int, qouestion_thread>& TQ)
{
    string s;
    int ID_Q = 0;
    DTQ.open(path2.c_str(), ios::in | ios::out | ios::app);
    DTQ.clear();
    TQ.clear();
    if (DTQ.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {

        while (DTQ >> ID_Q)
        {
            if (ID_Q > 0)
            {
                TQ[ID_Q].ID_Q = ID_Q;
                DTQ >> TQ[ID_Q].Name_from_User >> TQ[ID_Q].User_Name_to >> TQ[ID_Q].is_Anonymous >> TQ[ID_Q].is_Answer >> TQ[ID_Q].ID_question_main;

                if (TQ[ID_Q].Name_from_User == "")
                    break;

                DTQ.ignore();
                getline(DTQ, TQ[ID_Q].question);

               // DTQ.ignore();
                getline(DTQ, TQ[ID_Q].Answer);
            }
        }
        DTQ.close();

    }
}
void Menu_Enter_to_project()
{
    cout << "Menu: \n";
    cout << "          1: Login\n";
    cout << "          2: Sign UP\n\n";
}
int Choose_Menue1()
{
    int x, c = 0;
    while (c == 0)
    {
        cout << "Enter number in range 1 - 2 : ";
        cin >> x;
        if (x > 2 || x < 1)
        {
            cout << "ERROR: invalid number.....Try again\n\n";
        }
        else
            c = 10;
    }
    return x;
}
int Choose_Menue2()
{
    int x, c = 0;
    while (c == 0)
    {
        cout << "Enter number in range 1 - 9 : ";
        cin >> x;
        if (x > 9 || x < 1)
        {
            cout << "ERROR: invalid number.....Try again\n\n";
        }
        else
            c = 10;
    }
    cout << "\n\n";
    return x;
}
void Menu_operation_for_project()
{
    cout << "Menu: \n";
    cout << "          1: Print Questions To Me\n";
    cout << "          2: Print Questions From Me\n";
    cout << "          3: Answer Question\n";
    cout << "          4: Delete Question\n";
    cout << "          5: Ask Question\n";
    cout << "          6: List System Users\n";
    cout << "          7: Feed\n";
    cout << "          8: Logout\n";
    cout << "          9: Exit\n";
}
void List_System_users(map<string, user>& User)
{
    cout << "#####################################################\n";
    for (auto x : User)
    {
        cout << "ID: " << x.second.ID << "          Password: " << x.second.password << "          Name: " << x.second.User_Name << endl;
    }
    cout << "######################################################\n\n\n";
}
void Ask_Question(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{
    string User_Name, s;
    int Q_ID = 0, x, TQ_ID;
    cout << "\n\n######################################################\n";

    cout << "Enter User Name or NOT to cancel: ";
    cin >> User_Name;
    if (User_Name != "NOT")
    {
        if (User_Name == User_login)
        {
            cout << "\aERROR: You Can't Ask your self......Please Try agein\n";
            cout << "\n######################################################\n\n";
            return;
        }
        else
        {

            if (User[User_Name].anonymous == 0)
            {
                cout << "Note: Anonymous question are not allowed for this user\n";
            }
            else
            {
                cout << "is you want to make Anonymous question ? ( 0 _ 1 ) : ";
                cin >> x;
            }
            cout << "For theard question: Enter Question ID or -1 for new question: ";
            cin >> Q_ID;

            if (Q_ID < 0)
            {

                cout << "Enter ID Question main please : ";
                cin >> Q_ID;
                MQ[Q_ID].ID_Q = Q_ID;
                MQ[Q_ID].User_Name_to = User_Name;
                MQ[Q_ID].Name_from_User = User_login;

                if (User[User_Name].anonymous == 1 && x == 1)
                {
                    MQ[Q_ID].is_Anonymous = 1;
                }
                cout << "Enter question text: ";
                cin.ignore();
                getline(cin, MQ[Q_ID].question);
                cout << "\n######################################################\n\n";
                Update_UPloud_Data_MQ(MQ);
            }
            else
            {

                cout << "Enter ID Question Thread please : ";
                cin >> TQ_ID;
                TQ[TQ_ID].User_Name_to = User_Name;
                TQ[TQ_ID].Name_from_User = User_login;
                TQ[TQ_ID].ID_question_main = Q_ID;
                TQ[TQ_ID].ID_Q = TQ_ID;
                if (User[User_Name].anonymous == 1 && x == 1)
                {
                    TQ[TQ_ID].is_Anonymous = 1;
                }
                cout << "Enter question text: ";
                cin.ignore();
                getline(cin, TQ[TQ_ID].question);
                cout << "\n######################################################\n\n";
                Update_UPloud_Data_TQ(TQ);

            }
        }
    }

}
void Print_Questions_To_Me(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{
    cout << "\n\n####################################################################################################################\n";
    int c = 0;
    for (auto Q : MQ)
    {
        if (Q.second.User_Name_to == User_login)
        {
            c++;
            cout << "Question ID (" << Q.first << ") ";

            if (Q.second.is_Anonymous == 1 && User[User_login].anonymous == 1);
            else
            {
                cout << "From " << Q.second.Name_from_User;
            }

            cout << "         Question: " << Q.second.question << endl;
            cout << "                 Answer: " << Q.second.Answer << "\n\n";
            for (auto T : TQ)
            {
                if (T.second.ID_question_main == Q.second.ID_Q)
                {
                    cout << "        Theard: Question ID (" << T.first << ") ";
                    if (T.second.is_Anonymous == 1 && User[User_login].anonymous == 1);
                    else
                    {
                        cout << "From  " << T.second.Name_from_User;
                    }
                    cout << "              Question: " << T.second.question << endl;
                    cout << "       Theard:      Answer: " << T.second.Answer << "\n\n";
                }
            }
        }
    }
    if (c == 0)
    {
        cout << "NOT found any Question for you yet";
    }

    cout << "\n#####################################################################################################################\n";
}
void Print_Questions_From_Me(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{
    cout << "\n\n####################################################################################################################\n";
    int c = 0;
    for (auto Q : MQ)
    {
        if (Q.second.Name_from_User == User_login)
        {
            c++;
            cout << "Question ID (" << Q.first << ") ";

            if (Q.second.is_Anonymous == 1 && User[User_login].anonymous == 1)
            {
                cout << "!AQ ";
            }

            cout << "to " << Q.second.User_Name_to;

            cout << "         Question: " << Q.second.question << endl;

            cout << "               Answer: " << Q.second.Answer << "\n\n";
        }
    }
    for (auto T : TQ)
    {
        c++;
        if (T.second.Name_from_User == User_login)
        {
            cout << "Question ID (" << T.first << ") ";

            if (T.second.is_Anonymous == 1 && User[User_login].anonymous == 1)
            {
                cout << "!AQ ";
            }

            cout << "to " << T.second.User_Name_to;
            cout << "         Question: " << T.second.question << endl;
            cout << "               Answer: " << T.second.Answer << "\n\n";
        }
    }
    if (c == 0)
    {
        cout << "you did't asked any Question  yet";
    }

    cout << "\n#####################################################################################################################\n";
}
void Delete_Question(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{

    if (MQ.size() == 0)
    {
        cout << "ERROR: NOT found any Question for Delete it\n\a";
    }
    else
    {
        int ID_Q_D = 0;

        cout << "Enter Question ID or -1 to cancel: ";
        cin >> ID_Q_D;

        if (MQ[ID_Q_D].Name_from_User != User_login && TQ[ID_Q_D].Name_from_User != User_login)
        {
            cout << "ERROR: You Can't Delete Question is't Your Question \n\a";
        }
        else
        {
            vector<int>IDS;
            for (auto T : TQ)
            {
                if (T.second.ID_question_main == ID_Q_D)
                {
                    IDS.push_back(T.second.ID_Q);
                }
            }
            for (auto x : IDS)
            {
                TQ.erase(x);
            }
            IDS.clear();
            MQ.erase(ID_Q_D);

            TQ.erase(ID_Q_D);
            Update_UPloud_Data_MQ(MQ);
            Update_UPloud_Data_TQ(TQ);
        }
    }
}
void Answer_Question(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{
    int c = 0;
    int ID_Q = 0;
    if (MQ.size() == 0)
    {
        cout << "ERROR: NOT found any Question for Answered it\n\a";
    }
    else
    {

        cout << "Enter Question ID or -1 to cancel: ";
        cin >> ID_Q;

        if (MQ.count(ID_Q))
        {
            if (MQ[ID_Q].User_Name_to == User_login)
            {
                cout << "Question ID (" << MQ[ID_Q].ID_Q << ") ";

                if (MQ[ID_Q].is_Anonymous == 1 && User[User_login].anonymous == 1)
                {
                    cout << "!AQ ";
                }

                cout << "to " << MQ[ID_Q].User_Name_to;

                cout << "         Question: " << MQ[ID_Q].question << endl;
               
                if (MQ[ID_Q].is_Answer == 0)
                {
                    cout << "               Answer: NOT Answered yet.\n\n";
                }
                else
                {
                    cout << "               Answer: " << MQ[ID_Q].Answer << "\n\n";
                }
                cout << "\n\n\n";
                if (MQ[ID_Q].is_Answer == 0)
                {
                    MQ[ID_Q].is_Answer = 1;
                    cout << "Enter Answer: ";
                }
                else
                {
                    cout << "Warning: Already Answered. Answer will be Updated\n";
                    cout << "Enter Answer: ";
                }
                
                cin.ignore();
                getline(cin, MQ[ID_Q].Answer);
                Update_UPloud_Data_MQ(MQ);
            }
            else
            {
                cout << "ERROR: You Can't Answered Question is't to Your \n\a";
            }
        }
        else if(TQ.count(ID_Q))
        {
            if (TQ[ID_Q].User_Name_to == User_login)
            {
                cout << "Question ID (" << TQ[ID_Q].ID_Q << ") ";

                if (TQ[ID_Q].is_Anonymous == 1 && User[User_login].anonymous == 1)
                {
                    cout << "!AQ ";
                }

                cout << "to " << TQ[ID_Q].User_Name_to;

                cout << "         Question: " << TQ[ID_Q].question << endl;

                if (TQ[ID_Q].is_Answer == 0)
                {
                    cout << "               Answer: NOT Answered yet.\n\n";
                }
                else
                {
                    cout << "               Answer: " << TQ[ID_Q].Answer << "\n\n";
                }
                cout << "\n\n\n";

                if (TQ[ID_Q].is_Answer == 0)
                {
                    TQ[ID_Q].is_Answer = 1;
                    cout << "Enter Answer: ";
                }
                else
                {
                    cout << "Warning: Already Answered. Answer will be Updated\n";
                    cout << "Enter Answer: ";
                }
               
                cin.ignore();
                getline(cin, TQ[ID_Q].Answer);

     
                Update_UPloud_Data_TQ(TQ);
            }
            else
            {
                cout << "ERROR: You Can't Answered Question is't to Your \n\a";
            }

        }
        else
        {
            cout << "ERROR: This Question do't found ....\n\a";
        }

    }

}
void Feed(map<string, user>& User, map<int, main_question>& MQ, map<int, qouestion_thread>& TQ, string User_login)
{
    cout << "\n\n####################################################################################################################\n";
    int c = 0;

    for (auto Q : MQ)
    {
        if (Q.second.is_Answer == 1)
        {
            c++;
            cout << "Question ID (" << Q.first << ") ";

            if (Q.second.is_Anonymous == 1 && User[User_login].anonymous == 1);
            else
            {
                cout << "From " << Q.second.Name_from_User;
            }

            cout << "         Question: " << Q.second.question << endl;
            cout << "                 Answer: " << Q.second.Answer << "\n\n";
        }
        for (auto T : TQ)
        {
            if (T.second.is_Answer == 1)
            {
                c++;
                if (T.second.ID_question_main == Q.second.ID_Q)
                {
                    cout << "Theard Parent Question ID (" << Q.second.ID_Q << ") ";
                    cout << "Question ID (" << T.first << ") ";
                    if (T.second.is_Anonymous == 1 && User[User_login].anonymous == 1);
                    else
                    {
                        cout << "From  " << T.second.Name_from_User;
                    }
                    cout << "              Question: " << T.second.question << endl;
                    cout << "         Answer: " << T.second.Answer << "\n\n";
                }
            }
        }
    }

    if (c == 0)
    {
        cout << "NOT found any Question answered yet";
    }

    cout << "\n#####################################################################################################################\n";

}
string login_user(map<string, user>& User)
{
    string s, st;
    int c = 0, T = 0;
    while (c == 0)
    {
        cout << "\nPlease Enter User Name : ";
        Up_dawnloud_Data_User(User);
        cin >> s;
        if (User[s].ID == 0)
        {
            cout << "ERROR: This username does't exist.....Try agein\n\n";
        }
        else
        {
            cout << "Please Enter Password : ";
            cin >> st;
            if (st == User[s].password)
            {
                return s;
            }
            else
            {
                cout << "\n\nERROR: This password is incorrect.....Try agein\n\n";
            }
        }

    }
}
string sign_up_user(map<string, user>& User)
{
    string s, sE, st, se = "@gmail.com";
    int c = 0, ct = 0, c2 = 0;
    while (c == 0)
    {
        cout << "\nEnter User name Please : ";
        cin >> s;
        if (User[s].ID == 0 && User[s].password == "")
        {
            User[s].User_Name = s;
            cout << "Enter User ID Please : ";
            cin >> User[s].ID;
            while (c2 == 0)
            {
                ct = 0;
                cout << "Enter Email Please : ";
                cin >> sE;
                for (int i = 0; i < sE.size(); i++)
                {
                    if (sE[i] == '@')   ct = 10;

                    if (ct > 0)  st.push_back(sE[i]);
                }

                if (st == se)
                {
                    User[s].Email = sE;
                    cout << "Enter User Password Please : ";
                    cin >> User[s].password;
                    cout << "is you will allowe to  anonymous or NOT (1 or 0) : ";
                    cin >> User[s].anonymous;
                    c++;
                    c2++;
                    cout << "\n\n--------------------------------\n\n";
                }
                else
                {
                    cout << "\nERROR: Email must end with ""@gmail.com"".....Try agein\n\n";
                }
                st.clear();
            }

        }
        else
        {
            cout << "ERROR: This name is already reserved.....Try agein\n\n";
        }
    }
    database.open(path.c_str(), ios::in | ios::out | ios::app);
    database.clear();
    if (database.fail())
    {
        cout << "Can't open the file\n\a";
    }
    else
    {
        database.clear();
        database << User[s].User_Name << " " << User[s].ID << " " << User[s].password << " " << User[s].Email << " " << User[s].anonymous << endl;
        database.close();
    }
    return s;
}
