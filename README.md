# -University-Course-Registration-System
Develop a C++ application that simulates a university course registration system using inheritance and polymorphism. This system should manage courses, students, and faculty

Classes to Implement:
Person:
Base class with attributes like name, ID, and email.
Include virtual functions for displaying personal details.
Student:
Derived from Person.
Additional attributes: major, list of courses registered, total credits.
Methods to register/drop courses, calculate GPA, and display student details.
Instructor:
Derived from Person.
Additional attributes: department, list of courses teaching.
Methods to add/remove courses they teach, display instructor details.
Course:
Attributes: course name, course code, credits, maximum students, list of enrolled students, instructor.
Methods to enroll a student, remove a student, and list all students.
Department:
Attributes: department name, list of courses offered, list of faculty.
Methods to add/remove courses and faculty.
Functionality to Implement:
Create a menu-driven program where users can add/remove students or instructors, enroll/drop courses, and display course rosters.
Implement checks for maximum course enrollments and prerequisites met before enrolling a student.
Provide functionality to assign instructors to courses.

