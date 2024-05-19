#include <iostream>
using namespace std;

class Person
{
    string name;
    int ID;
    string email;

public:
    Person() : name(""), ID(0), email("") {}
    Person(const string &name, int ID, string email) : name(name), ID(ID), email(email) {}
    virtual void displayDetails()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << ID << endl;
        cout << "Email: " << email << endl;
    }
    int getID() { return ID; }
    string getName() { return name; }
    string getEmail() { return email; }
};

class Student : public Person

{
    string major;
    static const int MAX_COURSES = 10;
    struct Course
    {
        string courseName;
        int credits;
        char grade;
    } courses[MAX_COURSES];
    int courseCount;

public:
    Student() : courseCount(0) {}
    Student(const string &name, int ID, string email, const string &major) : Person(name, ID, email), major(major), courseCount(0) {}
    void registerCourse(const string &name, int credits)
    {
        if (courseCount < MAX_COURSES)
        {
            courses[courseCount++] = {name, credits, 'N'};
        }
        else
        {
            cout << "Cannot register more than " << MAX_COURSES << " courses" << endl;
        }
    }
    void dropCourse(const string &name)
    {
        int index = -1;
        for (int i = 0; i < courseCount; i++)
        {
            if (courses[i].courseName == name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < courseCount - 1; ++i)
            {
                courses[i] = courses[i + 1];
            }
            courseCount--;
        }
    }
    void setGrades(const string &name, char grade)
    {
        for (int i = 0; i < courseCount; ++i)
        {
            if (courses[i].courseName == name)
            {
                courses[i].grade = grade;
                break;
            }
        }
    }
    int getTotalCredits()
    {
        int totalCredits = 0;
        for (int i = 0; i < courseCount; i++)
        {
            totalCredits += courses[i].credits;
        }
        return totalCredits;
    }
    double calculateGPA()
    {
        if (courseCount == 0)
            return 0.0;
        double totalPoints = 0.0;
        int totalCredits = 0;
        for (int i = 0; i < courseCount; i++)
        {
            double gradePoints = 0.0;
            switch (courses[i].grade)
            {
            case 'A':
                gradePoints = 4.0;
                break;
            case 'B':
                gradePoints = 3.0;
                break;
            case 'C':
                gradePoints = 2.0;
                break;
            case 'D':
                gradePoints = 1.0;
                break;
            case 'F':
                gradePoints = 0.0;
                break;
            default:
                continue;
            }
            totalPoints += gradePoints * courses[i].credits;
            totalCredits += courses[i].credits;
        }
        return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
    }
    void displayDetails()
    {
        Person::displayDetails();
        cout << "Major: " << major << endl;
        cout << "Courses Registered: " << endl;
        for (int i = 0; i < courseCount; ++i)
        {
            cout << courses[i].courseName << " (" << courses[i].credits << " credits)"
                 << ", Grade: " << courses[i].grade << endl;
        }
        cout << "Total Credits: " << getTotalCredits() << endl;
        cout << "GPA: " << calculateGPA() << endl;
    }
};

class Instructor : public Person
{
    static const int MAX_COURSES = 3;
    string department;
    struct Course
    {
        string courseName;
    } courses[MAX_COURSES];
    int coursesCount;

public:
    Instructor() : coursesCount(0) {}
    Instructor(const string &name, int ID, string email, const string &department) : Person(name, ID, email), department(department), coursesCount(0) {}
    void addCourse(const string &name)
    {
        if (coursesCount < MAX_COURSES)
        {
            courses[coursesCount++] = {name};
        }
        else
        {
            cout << "Cannot add more than " << MAX_COURSES << " courses" << endl;
        }
    }
    void removeCourse(const string &name)
    {
        int index = -1;
        for (int i = 0; i < coursesCount; i++)
        {
            if (courses[i].courseName == name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < coursesCount - 1; ++i)
            {
                courses[i] = courses[i + 1];
            }
            coursesCount--;
        }
    }
    void displayDetails()
    {
        Person::displayDetails();
        cout << "Department: " << department << endl;
        cout << "Courses Teaching: " << endl;
        for (int i = 0; i < coursesCount; i++)
        {
            cout << courses[i].courseName << endl;
        }
    }
};

class Course
{
    string courseName;
    int courseCode;
    int credit;
    int maxStudents;
    int enrolledCount;
    Student *students[30];
    Instructor instructor;

public:
    Course() : enrolledCount(0) {}
    Course(const string &name, int code, int credit, int maxStudents, const Instructor &instructor)
        : courseName(name), courseCode(code), credit(credit), maxStudents(maxStudents), instructor(instructor), enrolledCount(0) {}
    void enrollStudent(Student *s)
    {
        if (enrolledCount < maxStudents)
        {
            students[enrolledCount++] = s;
        }
        else
        {
            cout << "Cannot enroll more than " << maxStudents << " students" << endl;
        }
    }
    int getCredit() { return credit; }
    string getCourseName() { return courseName; }
    void removeStudent(int studentID)
    {
        int index = -1;
        for (int i = 0; i < enrolledCount; ++i)
        {
            if (students[i]->getID() == studentID)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < enrolledCount - 1; i++)
            {
                students[i + 1] = students[i];
            }
            enrolledCount--;
        }
        else
        {
            cout << "Student not found" << endl;
        }
    }
    void listStudents()
    {
        cout << "Course Name: " << courseName << endl;
        cout << "Course Code: " << courseCode << endl;
        cout << "Course Credits: " << credit << endl;
        cout << "Instructor Name: " << instructor.getName() << endl;
        cout << "Enrolled Students Details: " << endl;
        for (int i = 0; i < enrolledCount; i++)
        {
            cout << "Student Name: " << students[i]->getName() << ", Student ID: " << students[i]->getID() << ", Student Email: " << students[i]->getEmail() << endl;
        }
    }
    void displayDetails()
    {
        cout << "Course Name: " << courseName << endl;
        cout << "Course Code: " << courseCode << endl;
        cout << "Course Credits: " << credit << endl;
        cout << "Instructor Name: " << instructor.getName() << endl;
        cout << "Max Students: " << maxStudents << endl;
        cout << "Enrolled Students: " << enrolledCount << endl;
    }
};

class Department
{
    static const int MAX_COURSES = 10;
    static const int MAX_FACULTY = 10;
    string depName;
    Course offeredCourse[MAX_COURSES];
    Instructor faculty[MAX_FACULTY];
    int courseCount;
    int facultyCount;

public:
    Department() : courseCount(0), facultyCount(0) {}
    Department(const string &name) : depName(name), courseCount(0), facultyCount(0) {}
    void addCourse(const Course &course)
    {
        if (courseCount < MAX_COURSES)
        {
            offeredCourse[courseCount++] = course;
        }
        else
        {
            cout << "Cannot add more than " << MAX_COURSES << " courses" << endl;
        }
    }
    void addFaculty(const Instructor &instructor)
    {
        if (facultyCount < MAX_FACULTY)
        {
            faculty[facultyCount++] = instructor;
        }
        else
        {
            cout << "Cannot add more than " << MAX_FACULTY << " faculty members" << endl;
        }
    }
    void removeCourse(const string &name)
    {
        int index = -1;
        for (int i = 0; i < courseCount; ++i)
        {
            if (offeredCourse[i].getCourseName() == name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < courseCount - 1; ++i)
            {
                offeredCourse[i] = offeredCourse[i + 1];
            }
            courseCount--;
        }
    }
    void removeFaculty(const string &name)
    {
        int index = -1;
        for (int i = 0; i < facultyCount; ++i)
        {
            if (faculty[i].getName() == name)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < facultyCount - 1; ++i)
            {
                faculty[i] = faculty[i + 1];
            }
            facultyCount--;
        }
    }
    void displayDetails()
    {
        cout << "Department Name: " << depName << endl;
        cout << "List of Offered Courses: " << endl;
        for (int i = 0; i < courseCount; ++i)
        {
            offeredCourse[i].displayDetails();
        }
        cout << "List of Faculty: " << endl;
        for (int i = 0; i < facultyCount; ++i)
        {
            faculty[i].displayDetails();
        }
    }
    string getName() { return depName; }
};

void showMenu()
{
    cout << "Menu:" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Instructor" << endl;
    cout << "3. Add Course" << endl;
    cout << "4. Register Student for Course" << endl;
    cout << "5. Drop Student from Course" << endl;
    cout << "6. Set Grades for Student" << endl;
    cout << "7. Display Student Details" << endl;
    cout << "8. Display Instructor Details" << endl;
    cout << "9. Display Course Details" << endl;
    cout << "10. Add Department" << endl;
    cout << "11. Display Department Details" << endl;
    cout << "12. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    const int MAX_STUDENTS = 100;
    const int MAX_INSTRUCTORS = 50;
    const int MAX_COURSES = 50;
    const int MAX_DEPARTMENTS = 10;

    Student students[MAX_STUDENTS];
    Instructor instructors[MAX_INSTRUCTORS];
    Course courses[MAX_COURSES];
    Department departments[MAX_DEPARTMENTS];

    int studentCount = 0;
    int instructorCount = 0;
    int courseCount = 0;
    int departmentCount = 0;

    int choice;
    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            if (studentCount < MAX_STUDENTS)
            {
                string name, email, major;
                int ID;
                cout << "Enter Student Name: ";
                cin >> name;
                cout << "Enter Student ID: ";
                cin >> ID;
                cout << "Enter Student Email: ";
                cin >> email;
                cout << "Enter Student Major: ";
                cin >> major;
                students[studentCount++] = Student(name, ID, email, major);
            }
            else
            {
                cout << "Cannot add more students." << endl;
            }
            break;
        }
        case 2:
        {
            if (instructorCount < MAX_INSTRUCTORS)
            {
                string name, email, department;
                int ID;
                cout << "Enter Instructor Name: ";
                cin >> name;
                cout << "Enter Instructor ID: ";
                cin >> ID;
                cout << "Enter Instructor Email: ";
                cin >> email;
                cout << "Enter Instructor Department: ";
                cin >> department;
                instructors[instructorCount++] = Instructor(name, ID, email, department);
            }
            else
            {
                cout << "Cannot add more instructors." << endl;
            }
            break;
        }
        case 3:
        {
            if (courseCount < MAX_COURSES)
            {
                string name;
                int code, credit, maxStudents;
                cout << "Enter Course Name: ";
                cin >> name;
                cout << "Enter Course Code: ";
                cin >> code;
                cout << "Enter Course Credit: ";
                cin >> credit;
                cout << "Enter Maximum Students: ";
                cin >> maxStudents;
                cout << "Choose Instructor by ID: ";
                int instructorID;
                cin >> instructorID;
                Instructor *instructor = nullptr;
                for (int i = 0; i < instructorCount; ++i)
                {
                    if (instructors[i].getID() == instructorID)
                    {
                        instructor = &instructors[i];
                        break;
                    }
                }
                if (instructor)
                {
                    courses[courseCount++] = Course(name, code, credit, maxStudents, *instructor);
                }
                else
                {
                    cout << "Instructor not found." << endl;
                }
            }
            else
            {
                cout << "Cannot add more courses." << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Enter Student ID to register for course: ";
            int studentID;
            cin >> studentID;
            Student *student = nullptr;
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].getID() == studentID)
                {
                    student = &students[i];
                    break;
                }
            }
            if (student)
            {
                cout << "Enter Course Name to register: ";
                string courseName;
                cin >> courseName;
                Course *course = nullptr;
                for (int i = 0; i < courseCount; ++i)
                {
                    if (courses[i].getCourseName() == courseName)
                    {
                        course = &courses[i];
                        break;
                    }
                }
                if (course)
                {
                    course->enrollStudent(student);
                    student->registerCourse(course->getCourseName(),course->getCredit());
                }
                else
                {
                    cout << "Course not found." << endl;
                }
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Enter Student ID to drop from course: ";
            int studentID;
            cin >> studentID;
            Student *student = nullptr;
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].getID() == studentID)
                {
                    student = &students[i];
                    break;
                }
            }
            if (student)
            {
                cout << "Enter Course Name to drop: ";
                string courseName;
                cin >> courseName;
                Course *course = nullptr;
                for (int i = 0; i < courseCount; ++i)
                {
                    if (courses[i].getCourseName() == courseName)
                    {
                        course = &courses[i];
                        break;
                    }
                }
                if (course)
                {
                    course->removeStudent(studentID);
                    student->dropCourse(course->getCourseName());
                }
                else
                {
                    cout << "Course not found." << endl;
                }
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        }
        case 6:
        {
            cout << "Enter Student ID to set grades: ";
            int studentID;
            cin >> studentID;
            Student *student = nullptr;
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].getID() == studentID)
                {
                    student = &students[i];
                    break;
                }
            }
            if (student)
            {
                cout << "Enter Course Name to set grade: ";
                string courseName;
                cin >> courseName;
                cout << "Enter Grade (A/B/C/D/F): ";
                char grade;
                cin >> grade;
                student->setGrades(courseName, grade);
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        }
        case 7:
        {
            cout << "Enter Student ID to display details: ";
            int studentID;
            cin >> studentID;
            Student *student = nullptr;
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].getID() == studentID)
                {
                    student = &students[i];
                    break;
                }
            }
            if (student)
            {
                student->displayDetails();
            }
            else
            {
                cout << "Student not found." << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Enter Instructor ID to display details: ";
            int instructorID;
            cin >> instructorID;
            Instructor *instructor = nullptr;
            for (int i = 0; i < instructorCount; ++i)
            {
                if (instructors[i].getID() == instructorID)
                {
                    instructor = &instructors[i];
                    break;
                }
            }
            if (instructor)
            {
                instructor->displayDetails();
            }
            else
            {
                cout << "Instructor not found." << endl;
            }
            break;
        }
        case 9:
        {
            cout << "Enter Course Name to display details: ";
            string courseName;
            cin >> courseName;
            Course *course = nullptr;
            for (int i = 0; i < courseCount; ++i)
            {
                if (courses[i].getCourseName() == courseName)
                {
                    course = &courses[i];
                    break;
                }
            }
            if (course)
            {
                course->displayDetails();
            }
            else
            {
                cout << "Course not found." << endl;
            }
            break;
        }
        case 10:
        {
            if (departmentCount < MAX_DEPARTMENTS)
            {
                cout << "Enter Department Name: ";
                string depName;
                cin >> depName;
                departments[departmentCount++] = Department(depName);
            }
            else
            {
                cout << "Cannot add more departments." << endl;
            }
            break;
        }
        case 11:
        {
            cout << "Enter Department Name to display details: ";
            string depName;
            cin >> depName;
            Department *department = nullptr;
            for (int i = 0; i < departmentCount; ++i)
            {
                if (departments[i].getName() == depName)
                {
                    department = &departments[i];
                    break;
                }
            }
            if (department)
            {
                department->displayDetails();
            }
            else
            {
                cout << "Department not found." << endl;
            }
            break;
        }
        case 12:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 12);

    return 0;
}
