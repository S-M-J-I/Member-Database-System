#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class Members{
private:
    string FirstName;
    string LastName;
    string Department;
    string AddressLine1;
    string AddressLine2;
    string AddressLine3;
    long ID;
    long Mobile;
    long SLno;
    static long nextSL;

public:
    Members(){}

    Members(string firstName, string lastName, string department, string address, string address2, string address3, long id, long mobile){
        nextSL++;
        SLno = nextSL;
        FirstName = firstName;
        LastName = lastName;
        Department = department;
        AddressLine1 = address;
        AddressLine2 = address2;
        AddressLine3 = address3;
        ID = id;
        Mobile = mobile;
    }

    string getFirstName(){
        return FirstName;
    }

    string getLastName() {
        return LastName;
    }

    string getDepartment() {
        return Department;
    }

    string getAddress1(){
        return AddressLine1;
    }
    string getAddress2(){
        return AddressLine2;
    }
    string getAddress3(){
        return AddressLine3;
    }

    long getId() {
        return ID;
    }

    long getMobile() {
        return Mobile;
    }

    long getSLno() {
        return SLno;
    }

    static long getNextSl() {
        return nextSL;
    }

    static void setNextSl(long nextSl) {
        nextSL = nextSl;
    }

    friend ofstream &operator<<(ofstream &ofs, Members &members);
    friend ifstream &operator>>(ifstream &ifs, Members &members);
    friend ostream &operator<<(ostream &os, Members &members);
};
long Members :: nextSL = 0;

ostream &operator<<(ostream &os, Members &members) {
    os << "First Name: " << members.FirstName << endl;
    os << "Last Name: " << members.LastName << endl;
    os << "Department: "<< members.Department << endl;
    os << "Address: " << members.AddressLine1 << ", " << members.AddressLine2 << " ," << members.AddressLine3 << endl;
    os << "ID: " << members.ID << endl ;
    os << "Mobile: " << members.Mobile << endl ;
    os<< "SLno: " << members.SLno << endl;
    return os;
}
ofstream &operator<<(ofstream &ofs, Members &members){
    ofs << members.SLno << endl;
    ofs << members.FirstName << endl;
    ofs << members.LastName << endl;
    ofs << members.Department << endl;
    ofs << members.AddressLine1 << endl;
    ofs << members.AddressLine2 << endl;
    ofs << members.AddressLine3 << endl;
    ofs << members.ID << endl;
    ofs << members.Mobile << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Members &members){
    ifs >> members.SLno;
    ifs >> members.FirstName;
    ifs >> members.LastName;
    ifs >> members.Department;
    ifs >> members.AddressLine1;
    ifs >> members.AddressLine2;
    ifs >> members.AddressLine3;
    ifs >> members.ID;
    ifs >> members.Mobile;
    return ifs;
}


class System{
private:
    map<long, Members> mems;
public:
    System(){
        Members mem;
        ifstream infile("Edf.data");
        if (!infile){
            cout << "Error File not found!" << endl;
            return;
        }
        while (!infile.eof()){
            infile >> mem;
            mems.insert(pair<long, Members>(mem.getSLno(), mem));
        }
    }
    Members CreateProfile(string firstName, string lastName, string department, string address, string address2, string address3, long id, long mobile){
        ofstream outfile;
        Members mem(firstName, lastName,department, address, address2, address3,id,mobile);
        mems.insert(pair<long, Members>(mem.getSLno(), mem));

        outfile.open("Edf.data", ios::trunc);

        map<long, Members> :: iterator itr;
        for ( itr=mems.begin() ; itr != mems.end() ; itr++ ){
            outfile<<itr->second;
        }
        outfile.close();

        return mem;
    }
    void CloseProfile(long SLno){
        map<long, Members> :: iterator itr=mems.find(SLno);
        cout << "PROFILE DELETED\n" << itr->second;
        cout << endl;
        mems.erase(SLno);
    }
    void ShowAllProfiles(){
        map<long, Members> :: iterator itr;
        for(itr=mems.begin();itr!=mems.end();itr++)
        {
            cout << "Profile: " << itr->first << endl << itr->second << endl;
        }
    }
    virtual ~System() {
        ofstream outfile("Edf.data", ios::trunc);
        map<long, Members> :: iterator itr;
        for(itr=mems.begin();itr!=mems.end();itr++)
        {
            outfile << itr->second;
        }
        outfile.close();
    }

};

int main() {
    System sys;
    Members mems;
    string FirstName;
    string LastName;
    string Department;
    string AddressLine1;
    string AddressLine2;
    string AddressLine3;
    long ID;
    long Mobile;
    long SLno;
    int choice;
    cout << "EDF MEMBER PROFILES" << endl;
    do{
        cout << "\n\tSelect an option below: ";
        cout << "\n\t(1) Register a member";
        cout << "\n\t(2) Remove a member";
        cout << "\n\t(3) Show all members";
        cout << "\n\t(4) Quit";
        cout << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice){
            case 1:{
                cout << "==========CREATE PROFILE==========" << endl;
                cout << endl;
                cout << "Enter first name: ";
                fflush(stdin);
                cin >> FirstName;
                fflush(stdout);
                cout << "Enter last name: ";
                fflush(stdin);
                cin >> LastName;
                fflush(stdout);
                cout << "Enter Department: ";
                fflush(stdin);
                cin >> Department;
                fflush(stdout);
                cout << "Enter Area: ";
                fflush(stdin);
                cin >> AddressLine1;
                fflush(stdout);
                cout << "Enter Zone: ";
                fflush(stdin);
                cin >> AddressLine2;
                fflush(stdout);
                cout << "Enter District: ";
                fflush(stdin);
                cin >> AddressLine3;
                fflush(stdout);
                cout << "Enter ID: ";
                cin >> ID;
                cout << "Enter Mobile no.: ";
                cin >> Mobile;
                mems=sys.CreateProfile(FirstName, LastName, Department, AddressLine1, AddressLine2, AddressLine3, ID, Mobile);
                cout << endl << "Congratulations, profile has been created: " << endl;
                cout << mems;
                break;
            }
            case 2:{
                cout << "==========REMOVE MEMBER==========" << endl;
                cout << endl;
                cout<<"Enter Profile Number: ";
                cin>>SLno;
                sys.CloseProfile(SLno);
                cout<<endl<<"Member profile has been removed"<<endl;
                break;
            }
            case 3:{
                cout << "==========ALL MEMBERS==========" << endl;
                cout << endl;
                sys.ShowAllProfiles();
                break;
            }
            case 4:{
                break;
            }
            default:{
                cout << "Enter correct choice" << endl;
                exit(0);
            }
        }

    }while(choice != 4);

    return 0;
}