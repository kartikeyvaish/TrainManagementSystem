// Project by
//     Kartikey Vaish & Souryamann Singh

// GitHub Repository Link -  https://github.com/kartikeyvaish/Train-Management-System.git
// JSON for C++ used in this project - https://github.com/nlohmann/json

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <vector>
#include <iterator>
#include <map>
#include <time.h>
#include <unistd.h>
#include <Credentials.h>
using namespace std;
using json = nlohmann::json; // for Reading and Writing into JSON file

class Profile
{
public:
    string name, username;
    int age;

    Profile()
    {
        name = "";
        age = 0;
        username = "";
    }

    void EnterDetails(string getName, int getAge)
    {
        this->name = getName;
        this->age = getAge;
    }

    void DisplayDetails()
    {
        if (name == "" && age == 0)
        {
            cout << "No Details Found";
        }
        else
        {
            cout << "Details are - \n"
                 << endl;
            cout << "Name - " << name << endl;
            cout << "Age - " << age << endl;
        }
    }
};

class Ticket : public Profile
{
private:
    string Source, Destination, Name, Age, SeatType, TrainName, Aadhar;
    int Fare, Seats, TrainNumber, PNR;

public:
    void CreateTicket(string Source, string Destination, string Name, string Age, string SeatType, string TrainName, int TrainNumber, int Fare, int PNR, string Aadhar)
    {
        this->Source = Source;
        this->Destination = Destination;
        this->Name = Name;
        this->Age = Age;
        this->SeatType = SeatType;
        this->TrainName = TrainName;
        this->TrainNumber = TrainNumber;
        this->Fare = Fare;
        this->PNR = PNR;
        this->Aadhar = Aadhar;
        this->name = Name;
        this->age = stoi(Age);
    }

    void DisplayTicket()
    {
        cout << "Name - " << Name << endl;
        cout << "Age - " << Age << endl;
        cout << "Train Name - " << TrainName << endl;
        cout << "Train Number - " << TrainNumber << endl;
        cout << "Journey From - " << Source << endl;
        cout << "Destination - " << Destination << endl;
        cout << "Seat Type - " << SeatType << endl;
        cout << "Fare - " << Fare << endl;
        cout << "PNR - " << PNR << endl;
        cout << "Aadhar - " << Aadhar << endl;
    }
};

int GoBackMenu()
{
    int ch;
    cout << endl
         << "\n1.) Go Back " << endl;
    cout << "2.) Exit " << endl;
    cin >> ch;
    system("CLS");
    if (ch == 1)
    {
        return 0;
    }
    else
    {
        return 9;
    }
}

int SeatSelection()
{
    int Seat;
    cout << "1.) 1A" << endl;
    cout << "2.) 2A" << endl;
    cout << "3.) 3A" << endl;
    cout << "4.) SL" << endl;
    cout << "Choose Seat - ";
    cin >> Seat;
    return Seat;
}

void MainMenu()
{
    cout << "************************************************************************************************************" << endl;
    cout << "\t\t\tT R A I N  M A N A G E M E N T  S Y S T E M" << endl
         << endl;
    cout << "1.) Show Trains List " << endl;
    cout << "2.) Book a Train " << endl;
    cout << "3.) My Tickets " << endl;
    cout << "7.) New/Edit Profile " << endl;
    cout << "8.) Show Profile " << endl;
    cout << "9.) Exit" << endl;
    cout << "10.) Logout" << endl;
    cout << "Enter Option - ";
}

int RandomPNR()
{
    int result, digitIndex, curDigit;
    int resultNum;
    int numResultsWanted = 10;
    srand(time(NULL));

    for (resultNum = 0; resultNum < numResultsWanted; resultNum++)
    {
        result = 0;
        for (digitIndex = 0; digitIndex < 8; digitIndex++)
        {
            curDigit = rand() % 10;
            curDigit *= pow(10, digitIndex);
            result += curDigit;
        }
    }
    return result;
}

void PrintTicket(string Name, string SeatType, string PNR, string TrainName, string TrainNumber, string Fare)
{
    cout << "Passenger Name - " << Name << endl;
    cout << "Train Name - " << TrainName << endl;
    cout << "Train Number - " << TrainNumber << endl;
    cout << "Passenger Name - " << Name << endl;
    cout << "Seat Type - " << SeatType << endl;
    cout << "PNR Number - " << PNR << endl;
    cout << "Fare - " << Fare << endl;
    cout << endl;
}

void ShowYourTickets()
{
    string Aadhar;
    cout << "Enter Aadhar Card Number - ";
    cin >> Aadhar;
    std::ifstream i("Tickets.json");
    json j;
    i >> j;
    int k, Count = 0;

    cout << "Your Tickets\n\n";
    for (k = 0; k < j["Tickets"].size(); k++)
    {
        if (j["Tickets"][k]["Aadhar"] == Aadhar)
        {
            Count += 1;
            PrintTicket(j["Tickets"][k]["Name"], j["Tickets"][k]["SeatType"], j["Tickets"][k]["PNR"], j["Tickets"][k]["TrainName"], j["Tickets"][k]["TrainNumber"], j["Tickets"][k]["Fare"]);
        }
    }
    if (Count == 0)
    {
        cout << "No Tickets Found ....\n\n";
    }
}

void AddToTicketList(string Source, string Destination, string Name, string Age, string SeatType, string TrainName, int TrainNumber, int Fare, int PNR, string Aadhar)
{
    std::ifstream i("Tickets.json");
    json j;
    json out;
    json array = {};
    i >> j;
    int k = 0;
    for (k = 0; k < j["Tickets"].size(); k++)
    {
        array.push_back(j["Tickets"][k]);
    }
    map<string, string> NewTicket;
    NewTicket.insert(pair<string, string>("Name", Name));
    NewTicket.insert(pair<string, string>("Age", Age));
    NewTicket.insert(pair<string, string>("TrainName", TrainName));
    NewTicket.insert(pair<string, string>("TrainNumber", to_string(TrainNumber)));
    NewTicket.insert(pair<string, string>("JourneyFrom", Source));
    NewTicket.insert(pair<string, string>("Destination", Destination));
    NewTicket.insert(pair<string, string>("SeatType", SeatType));
    NewTicket.insert(pair<string, string>("PNR", to_string(PNR)));
    NewTicket.insert(pair<string, string>("Fare", to_string(Fare)));
    NewTicket.insert(pair<string, string>("Aadhar", Aadhar));
    array.push_back(NewTicket);
    i.close();
    std::ofstream output_file("Tickets.json");
    out["Tickets"] = array;
    output_file << out.dump(4);
    output_file.close();
}

void BookTickets(int TrainNumber)
{
    std::ifstream i("TrainList.json");
    json j;
    i >> j;
    int k;
    Ticket NewTicket;
    string Source, Destination, Name, Age, SeatType, TrainName, Aadhar;
    int Fare, Seats, PNRNUM;
    map<string, int> SeatsTypeCost;
    for (k = 0; k < j["Trains"].size(); k++)
    {
        if (TrainNumber == j["Trains"][k]["TrainNumber"])
        {
            cout << "Train Number\tTrain Name\t \t \tSource\tDestination\t3A\t2A\t1A\tSL\n";
            cout << j["Trains"][k]["TrainNumber"] << "\t\t";
            cout << j["Trains"][k]["TrainName"] << "\t  ";
            cout << j["Trains"][k]["START"] << "\t   ";
            cout << j["Trains"][k]["END"] << "\t";
            cout << j["Trains"][k]["COST"]["3A"] << "\t";
            cout << j["Trains"][k]["COST"]["2A"] << "\t";
            cout << j["Trains"][k]["COST"]["1A"] << "\t";
            cout << j["Trains"][k]["COST"]["SL"] << "\n\n";

            SeatsTypeCost.insert(pair<string, int>("3A", j["Trains"][k]["COST"]["3A"]));
            SeatsTypeCost.insert(pair<string, int>("2A", j["Trains"][k]["COST"]["2A"]));
            SeatsTypeCost.insert(pair<string, int>("1A", j["Trains"][k]["COST"]["1A"]));
            SeatsTypeCost.insert(pair<string, int>("SL", j["Trains"][k]["COST"]["SL"]));

            Source = j["Trains"][k]["START"];
            Destination = j["Trains"][k]["END"];
            TrainName = j["Trains"][k]["TrainName"];
            break;
        }
    }

    srand(time(0)); // Random TIme to generate random numbers
    int name;

    cout << "Enter Passenger Name - ";
    fflush(stdin);
    getline(cin, Name);

    cout << "Enter Age - ";
    cin >> Age;

    cout << "Enter Aadhar Number - ";
    cin >> Aadhar;

    cout << "Enter Seat Type (3A/2A/1A/SL) - ";
    cin >> SeatType; //3A

    transform(SeatType.begin(), SeatType.end(), SeatType.begin(),
              [](unsigned char c) { return std::toupper(c); });

    Fare = SeatsTypeCost[SeatType];
    PNRNUM = RandomPNR();

    system("CLS");
    cout << "Booking Ticket....Please Wait...\n";
    NewTicket.CreateTicket(Source, Destination, Name, Age, SeatType, TrainName, TrainNumber, Fare, PNRNUM, Aadhar);
    sleep(2);
    system("CLS");
    cout << "Ticket Booked Successfull\n\nThese are the details\n\n";
    AddToTicketList(Source, Destination, Name, Age, SeatType, TrainName, TrainNumber, Fare, PNRNUM, Aadhar);
    NewTicket.DisplayTicket();
}

int SearchTrains(string FROM, string TO)
{
    vector<int> SearchResults;
    map<string, string> Results;

    std::ifstream i("TrainList.json");
    json j;
    i >> j;

    transform(FROM.begin(), FROM.end(), FROM.begin(),
              [](unsigned char c) { return std::toupper(c); });
    transform(TO.begin(), TO.end(), TO.begin(),
              [](unsigned char c) { return std::toupper(c); });

    int k = 0;
    int OPT;
    int z = 1;
    string Seat;
    bool Found = false;
    system("CLS");

    for (k = 0; k < j["Trains"].size(); k++)
    {
        if (FROM == j["Trains"][k]["START"] && TO == j["Trains"][k]["END"])
        {
            Found = true;
            break;
        }
    }

    if (Found == true)
    {
        cout << "\t\tT R A I N S  F O U N D" << endl;
        cout << "    Train Number\tTrain Name\tSource\tDestination\t3A\t2A\t1A\tSL\n";
        for (k = 0; k < j["Trains"].size(); k++)
        {
            if (FROM == j["Trains"][k]["START"] && TO == j["Trains"][k]["END"])
            {
                cout << z << ".) " << j["Trains"][k]["TrainNumber"] << "\t   ";
                cout << j["Trains"][k]["TrainName"] << "\t ";
                cout << j["Trains"][k]["START"] << "\t   ";
                cout << j["Trains"][k]["END"] << "\t";
                cout << j["Trains"][k]["COST"]["3A"] << "\t";
                cout << j["Trains"][k]["COST"]["2A"] << "\t";
                cout << j["Trains"][k]["COST"]["1A"] << "\t";
                cout << j["Trains"][k]["COST"]["SL"] << "\n";
                z = z + 1;
                SearchResults.push_back(j["Trains"][k]["TrainNumber"]); // TO CHECK CHOICE NUMBERS
            }
        }
        cout << "\n\nEnter Desired Option to Book\nPress 0 to go Back";
        cout << "\n\nEnter Choice - ";
        cin >> OPT;
        if (OPT == 0)
        {
            system("CLS");
            return 0;
        }
        else
        {
            system("CLS");
            BookTickets(SearchResults[OPT - 1]);
            cout << "Press Desired Option - ";
            return GoBackMenu();
        }
    }
    else
    {
        system("CLS");
        cout << "No Trains Found Betwween " << FROM << " to " << TO << endl
             << endl;
        cout << "Press Desired Option - ";
        return GoBackMenu();
    }
}

void ShowTrainList()
{
    system("CLS");
    std::ifstream i("TrainList.json");
    json j;
    i >> j;
    int k = 0;
    cout << "Train No.\tTrain Name\t\t\t\tSource\t  Destination\t3A\t2A\t1A\tSL\n";
    for (k = 0; k < j["Trains"].size(); k++)
    {
        cout << j["Trains"][k]["TrainNumber"] << "\t      ";
        cout << j["Trains"][k]["TrainName"] << "\t\t\t";
        cout << j["Trains"][k]["START"] << "\t   ";
        cout << j["Trains"][k]["END"] << "   \t";
        cout << j["Trains"][k]["COST"]["3A"] << "\t";
        cout << j["Trains"][k]["COST"]["2A"] << "\t";
        cout << j["Trains"][k]["COST"]["1A"] << "\t";
        cout << j["Trains"][k]["COST"]["SL"] << "\n";
    }
}

int main()
{
    system("CLS");
    int ch = 0, CHOICE;
    string name, firstName, secondName, from, to;
    int age;
    int subMenu;
    Profile User;
    string Username = GetUsername();
    string Password = GetPassword();
    string EnterUsername, EnterPassword;
    while (ch != 9)
    {
        if (EnterUsername != Username && EnterPassword != Password)
        {
            cout << "************************************************************************************************************" << endl;
            cout << "\t\t\tT R A I N  M A N A G E M E N T  S Y S T E M" << endl
                 << endl;
            cout << "1.) Login";
            cout << "\n2.) Exit";
            cout << "\nEnter Choice - ";
            cin >> CHOICE;
            if (CHOICE == 2)
            {
                system("CLS");
                ch = 9;
            }
            else if (CHOICE == 1)
            {
                system("CLS");
                cout << "\nUsername - ";
                cin >> EnterUsername;
                cout << "\nPassword - ";
                cin >> EnterPassword;
                if (EnterUsername != Username && EnterPassword != Password)
                {
                    system("CLS");
                    cout << "WRONG CREDENTIALS...LOGIN AGAIN";
                    sleep(2); // Readable
                    system("CLS");
                }
                else
                {
                    system("CLS");
                }
            }
        }
        else
        {
            MainMenu();
            cin >> ch;
            cout << endl;
            system("CLS");
            if (ch == 1)
            {
                ShowTrainList();
                ch = GoBackMenu();
            }
            else if (ch == 2)
            {
                cout << "From - ";
                cin >> from;
                cout << "To - ";
                cin >> to;
                SearchTrains(from, to);
            }
            else if (ch == 3)
            {
                ShowYourTickets();
                ch = GoBackMenu();
            }
            else if (ch == 7)
            {
                cout << "Enter Name - ";
                fflush(stdin);
                getline(cin, firstName);
                cout << "Enter Age - ";
                cin >> age;
                User.EnterDetails(firstName, age);
                system("CLS");
            }
            else if (ch == 8)
            {
                User.DisplayDetails();
                ch = GoBackMenu();
            }
            else if (ch == 10)
            {
                system("CLS");
                EnterUsername = "";
                EnterPassword = "";
            }
            cout << endl;
        }
    }
    return 0;
}