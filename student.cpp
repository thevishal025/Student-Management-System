// Include all standard C++ libraries
#include <bits/stdc++.h>
using namespace std;

// Student class to store and manage student information
class Student {
protected:
    // Protected data (visible only inside class & derived classes)
    string email;
    string mobile;

public:
    // Public data members
    int roll;
    string name;
    string father;
    string course;
    string scholar;
    string dob;

    // Marks of different subjects
    float c_marks;
    float p_marks;
    float com_marks;
    float dig_marks;

    // Marks of different subjects
    void input() {
        cout <<endl<<"Enter Roll Number: ";
        cin >>roll;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout <<"Enter Name: ";
        getline(cin, name);

        cout<<"Enter Father's Name: ";
        getline(cin, father);

        cout <<"Enter Course: ";
        getline(cin, course);

        cout<<"Enter Scholar Number: ";
        getline(cin, scholar);

        cout <<"Enter Date of Birth (DD/MM/YYYY): ";
        getline(cin, dob);

        cout <<"Enter C++ Marks: ";
        cin >>c_marks;

        cout <<"Enter Python Marks: ";
        cin >>p_marks;

        cout <<"Enter Communication Marks: ";
        cin >>com_marks;

        cout <<"Enter Digital Marketing Marks: ";
        cin >>dig_marks;

        // Clear buffer again
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout <<"Enter E-mail: ";
        getline(cin, email);

        cout <<"Enter Mobile: ";
        getline(cin, mobile);
    }

    // Function to calculate percentage
    float percentage() {
        return (c_marks + p_marks + com_marks + dig_marks) / 4;
    }

    // Function to calculate grade based on percentage
    string grade() {
        float per = percentage();
        if (per >= 90) return "A+";
        else if (per >= 80) return "A";
        else if (per >= 70) return "B";
        else if (per >= 60) return "C";
        else if (per >= 50) return "D";
        else return "F";
    }

    // Admin view (shows full details including contact)
    void admin() {
        cout<<endl<<"<<<--- STUDENT DETAILS --->>>";
        cout<<endl<<"Roll Number: "<<roll;
        cout<<endl<<"Name: "<<name;
        cout<<endl<<"Father's Name: "<<father;
        cout<<endl<<"Course: "<<course;
        cout<<endl<<"Scholar Number: "<<scholar;
        cout<<endl<<"Date of Birth: "<<dob;
        cout<<endl<<endl<<"<<<--- MARKS DETAILS --->>>";
        cout<<endl<<"C++ Marks: "<<c_marks;
        cout<<endl<<"Python Marks: "<<p_marks;
        cout<<endl<<"Communication Marks: "<<com_marks;
        cout<<endl<<"Digital Marketing Marks: "<<dig_marks;
        cout<<endl<<"Grade: "<<grade();
        cout<<endl<<endl<<"<<<--- CONTACT DETAILS --->>>";
        cout<<endl<<"E-mail: "<<email;
        cout<<endl<<"Mobile Number: "<<mobile;
    }

    // User view (no contact details)
    void user() {
        cout<<endl<<"<<<--- STUDENT DETAILS --->>>";
        cout<<endl<<"Roll Number: "<<roll;
        cout<<endl<<"Name: "<<name;
        cout<<endl<<"Father's Name: "<<father;
        cout<<endl<<"Course: "<<course;
        cout<<endl<<"Scholar Number: "<<scholar;
        cout<<endl<<"Date of Birth: "<<dob;
        cout<<endl<<endl<<"<<<--- MARKS DETAILS --->>>";
        cout<<endl<<"C++ Marks: "<<c_marks;
        cout<<endl<<"Python Marks: "<<p_marks;
        cout<<endl<<"Communication Marks: "<<com_marks;
        cout<<endl<<"Digital Marketing Marks: "<<dig_marks;
        cout<<endl<<"Grade: "<<grade();
    }

    // Write student data into file using '|' separator
    void file(ofstream &out) {
        out << roll << "|" << name << "|" << father << "|" << course << "|" << scholar << "|" << dob << "|" << c_marks << "|" << p_marks << "|" << com_marks << "|" << dig_marks
            << "|" << email << "|" << mobile << endl;
    }

    // Save data into students.txt file
    void save() {
        ofstream out("students.txt", ios::app);
        file(out);
        out.close();
    }
};

// Function for admin login verification
bool admin_login() {
    string id, pass;
    cout <<endl<<"Admin ID: ";
    cin >> id;
    cout <<"Password: ";
    cin >> pass;

    // Hardcoded admin credentials
    return (id == "vishal" && pass == "0025");
}

// Function to search student by roll number
void searchStudent(bool isAdmin) {
    ifstream in("students.txt");
    int searchRoll;
    cout<<endl<<"Enter Roll Number: ";
    cin >> searchRoll;

    int roll;
    string name, father, course, scholar, dob, email, mobile;
    float c_marks, p_marks, com_marks, dig_marks;
    char ch;
    bool found = false;

    // Read file data line by line
    while (in >> roll >> ch) {
        getline(in, name, '|');
        getline(in, father, '|');
        getline(in, course, '|');
        getline(in, scholar, '|');
        getline(in, dob, '|');
        in>> c_marks>>ch;
        in>>p_marks>>ch;
        in>>com_marks>>ch;
        in>>dig_marks>>ch;
        getline(in, email, '|');
        getline(in, mobile);

        // If roll number matches
        if (roll == searchRoll) {
            found = true;
            
            float per = (c_marks + p_marks + com_marks + dig_marks) / 4;
            string grade;

            if (per >= 90) grade = "A+";
            else if (per >= 80) grade = "A";
            else if (per >= 70) grade = "B";
            else if (per >= 60) grade = "C";
            else if (per >= 50) grade = "D";
            else grade = "F";
            
            cout<<endl<<"*** Student Found ***";
            cout<<endl<<endl<<"<<<--- STUDENT DETAILS --->>>";
            cout<<endl<<"Roll Number: " <<roll;
            cout<<endl<<"Name: " <<name;
            cout<<endl<<"Father's Name: " <<father;
            cout<<endl<<"Course: " <<course;
            cout<<endl<<"Scholar Number: " <<scholar;
            cout<<endl<<"Date of Birth: " <<dob;
            cout<<endl<<endl<<"<<<--- MARKS DETAILS --->>>";
            cout<<endl<<"C++ Marks: " <<c_marks;
            cout<<endl<<"Python Marks: "<<p_marks;
            cout<<endl<<"Communication Marks: "<<com_marks;
            cout<<endl<<"Digital Marketing: "<<dig_marks;
            cout<<endl<<"Grade: "<<grade;

            // Admin can see contact details
            if (isAdmin) {
                cout<<endl<<endl<<"<<<--- CONTACT DETAILS --->>>";
                cout<<endl<<"Email: "<< email;
                cout<<endl<<"Mobile: "<< mobile;
            }
            break;
        }
    }

    if (!found)
        cout <<endl<<"Student Not Found!";

    in.close();
}

// Function to delete student record
void deleteStudent() {
    int searchRoll;
    cout << "Enter Roll Number to Delete: ";
    cin >> searchRoll;

    ifstream in("students.txt");
    ofstream out("temp.txt");

    int roll;
    string name, father, course, scholar, dob, email, mobile;
    float c_marks, p_marks, com_marks, dig_marks;
    char ch;
    bool found = false;

    // Copy all records except the one to be deleted
    while (in >> roll >> ch) {
        getline(in, name, '|');
        getline(in, father, '|');
        getline(in, course, '|');
        getline(in, scholar, '|');
        getline(in, dob, '|');
        in>>c_marks>>ch;
        in>>p_marks>>ch;
        in>>com_marks>>ch;
        in>>dig_marks>>ch;
        getline(in, email, '|');
        getline(in, mobile);

        if (roll != searchRoll) {
            out << roll << "|" << name << "|" << father << "|" << course << "|" << scholar << "|" << dob << "|" << c_marks << "|" << p_marks << "|" << com_marks << "|" << dig_marks
                << "|" << email << "|" << mobile << endl;
        } else {
            found = true;
        }
    }

    in.close();
    out.close();

    // Replace old file with updated file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout <<endl<<"Record Deleted Successfully!";
    else
        cout <<endl<<"Student Not Found!";
}

// Main function (Program execution starts here)
int main() {
    int choice;
    Student s;

    cout<<endl<<"STUDENT REGISTER OF SGSU";
    cout <<endl<<"1. Admin Login";
    cout <<endl<<"2. User Search";
    cout <<endl<<"Enter Choice: ";
    cin >> choice;

    // Admin section
    if (choice == 1) {
        if (!admin_login()) {
            cout <<endl<<"Invalid Login!";
            return 0;
        }

        do {
            cout <<endl<<endl<<"--- ADMIN MENU ---";
            cout <<endl<<"1. Add Student";
            cout <<endl<<"2. Search Student";
            cout <<endl<<"3. Delete Student";
            cout <<endl<<"4. Exit";
            cout <<endl<<"Enter Choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                s.input();
                s.save();
                cout <<endl<<endl<<"Student Added Successfully!";
                break;
            case 2:
                searchStudent(true);
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                cout <<endl<<"Logged Out!";
                break;
            default:
                cout <<endl<<"Invalid Choice!";
            }
        } while (choice != 4);
    }
    // User section
    else if (choice == 2) {
        searchStudent(false);
    }

    return 0;

}
