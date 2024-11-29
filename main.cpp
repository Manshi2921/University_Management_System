#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Abstract Base Class
class Person {
protected:
    string ID, name, email, phone;

public:
    Person(string id, string n, string e, string p) : ID(id), name(n), email(e), phone(p) {}
    virtual void displayDetails() const = 0; // Pure virtual method
    virtual ~Person() {}
};

// Derived Class: Student
class Student : public Person {
    string studentID, department;
    vector<string> enrolledCourses;

public:
    Student(string id, string n, string e, string p, string sid, string dept)
            : Person(id, n, e, p), studentID(sid), department(dept) {}

    void enrollCourse(string course) {
        enrolledCourses.push_back(course);
        cout << "Course " << course << " enrolled successfully!" << endl;
    }

    string getStudentID() const { return studentID; }

    void displayDetails() const override {
        cout << "Student Details:" << endl;
        cout << "ID: " << studentID << ", Name: " << name << ", Department: " << department
             << ", Email: " << email << ", Phone Number: " << phone << endl;
        cout << "Courses Enrolled: ";
        for (const auto& course : enrolledCourses) {
            cout << course << " ";
        }
        cout << endl;
    }
};

// Derived Class: Faculty
class Faculty : public Person {
    string facultyID, department;
    vector<string> assignedCourses;

public:
    Faculty(string id, string n, string e, string p, string fid, string dept)
            : Person(id, n, e, p), facultyID(fid), department(dept) {}

    void assignCourse(string course) {
        assignedCourses.push_back(course);
        cout << "Course " << course << " assigned to faculty!" << endl;
    }

    string getFacultyID() const { return facultyID; }

    void displayDetails() const override {
        cout << "Faculty Details:" << endl;
        cout << "ID: " << facultyID << ", Name: " << name << ", Department: " << department << endl;
        cout << "Assigned Courses: ";
        for (const auto& course : assignedCourses) {
            cout << course << " ";
        }
        cout << endl;
    }
};

// Class: Course
class Course {
    string courseID, courseName, department;
    int creditHours;
    vector<string> studentsEnrolled;

public:
    Course(string id, string name, string dept, int credits)
            : courseID(id), courseName(name), department(dept), creditHours(credits) {}

    void addStudent(string studentID) {
        studentsEnrolled.push_back(studentID);
        cout << "Student " << studentID << " added to course " << courseName << endl;
    }

    string getCourseID() const { return courseID; }

    void displayCourseDetails() const {
        cout << "Course Details:" << endl;
        cout << "ID: " << courseID << ", Name: " << courseName
             << ", Department: " << department << ", Credits: " << creditHours << endl;
        cout << "Enrolled Students: ";
        for (const auto& student : studentsEnrolled) {
            cout << student << " ";
        }
        cout << endl;
    }
};

// Class: University Management System
class UniversityManagementSystem {
    vector<Student> students;
    vector<Faculty> faculties;
    vector<Course> courses;

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void addStudent() {
        string id, name, email, phone, studentID, department;
        cout << "Enter Student Details:" << endl;
        cout << "ID: "; cin >> id;
        clearInputBuffer();
        cout << "Name: "; getline(cin, name);
        cout << "Email: "; cin >> email;
        cout << "Phone: "; cin >> phone;
        cout << "Student ID: "; cin >> studentID;
        cout << "Department: "; cin >> department;
        students.emplace_back(id, name, email, phone, studentID, department);
        cout << "Student added successfully!" << endl;
    }

    void addFaculty() {
        string id, name, email, phone, facultyID, department;
        cout << "Enter Faculty Details:" << endl;
        cout << "ID: "; cin >> id;
        clearInputBuffer();
        cout << "Name: "; getline(cin, name);
        cout << "Email: "; cin >> email;
        cout << "Phone: "; cin >> phone;
        cout << "Faculty ID: "; cin >> facultyID;
        cout << "Department: "; cin >> department;
        faculties.emplace_back(id, name, email, phone, facultyID, department);
        cout << "Faculty added successfully!" << endl;
    }

    void addCourse() {
        string id, name, department;
        int credits;
        cout << "Enter Course Details:" << endl;
        cout << "Course ID: "; cin >> id;
        clearInputBuffer();
        cout << "Course Name: "; getline(cin, name);
        cout << "Department: "; cin >> department;
        cout << "Credit Hours: "; cin >> credits;
        courses.emplace_back(id, name, department, credits);
        cout << "Course added successfully!" << endl;
    }

    void enrollStudentInCourse() {
        string studentID, courseID;
        cout << "Enter Student ID: "; cin >> studentID;
        cout << "Enter Course ID: "; cin >> courseID;

        auto studentIt = find_if(students.begin(), students.end(),
                                 [&studentID](const Student& s) { return s.getStudentID() == studentID; });
        auto courseIt = find_if(courses.begin(), courses.end(),
                                [&courseID](const Course& c) { return c.getCourseID() == courseID; });

        if (studentIt != students.end() && courseIt != courses.end()) {
            studentIt->enrollCourse(courseID);
            courseIt->addStudent(studentID);
        } else {
            cout << "Invalid Student ID or Course ID!" << endl;
        }
    }

    void displayAllStudents() const {
        cout << "All Students:" << endl;
        for (const auto& student : students) {
            student.displayDetails();
        }
    }

    void displayAllFaculties() const {
        cout << "All Faculties:" << endl;
        for (const auto& faculty : faculties) {
            faculty.displayDetails();
        }
    }

    void displayAllCourses() const {
        cout << "All Courses:" << endl;
        for (const auto& course : courses) {
            course.displayCourseDetails();
        }
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nUniversity Management System" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Add Faculty" << endl;
            cout << "3. Add Course" << endl;
            cout << "4. Enroll Student in Course" << endl;
            cout << "5. Display All Students" << endl;
            cout << "6. Display All Faculties" << endl;
            cout << "7. Display All Courses" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            clearInputBuffer();

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    addFaculty();
                    break;
                case 3:
                    addCourse();
                    break;
                case 4:
                    enrollStudentInCourse();
                    break;
                case 5:
                    displayAllStudents();
                    break;
                case 6:
                    displayAllFaculties();
                    break;
                case 7:
                    displayAllCourses();
                    break;
                case 0:
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 0);
    }
};

// Main Function
int main() {
    UniversityManagementSystem ums;
    ums.displayMenu();
    return 0;
}
