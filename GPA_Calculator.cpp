#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int MAX_COURSES = 10;
const int MAX_SEMESTERS = 8;    

class Course {
public:
    string courseName;
    int creditHours;
    double score;
    double gradePoint;
    string letterGrade;


    Course(string name = "", int credits = 0) {
        courseName = name;
        creditHours = credits;
        score = 0;
        gradePoint = 0;
        letterGrade = "";
    }
    void computeGradePoint() {
        if (score >= 90) {
            gradePoint = 4.00;
            letterGrade = "A";
        }
        else if (score >= 85) {
            gradePoint = 3.70;
            letterGrade = "A-";
        }
        else if (score >= 80) {
            gradePoint = 3.30;
            letterGrade = "B+";
        }
        else if (score >= 75) {
            gradePoint = 3.00;
            letterGrade = "B";
        }
        else if (score >= 70) {
            gradePoint = 2.70;
            letterGrade = "B-";
        }
        else if (score >= 65) {
            gradePoint = 2.30;
            letterGrade = "C+";
        }
        else if (score >= 60) {
            gradePoint = 2.00;
            letterGrade = "C";
        }
        else if (score >= 55) {
            gradePoint = 1.70;
            letterGrade = "C-";
        }
        else if (score >= 52.5) {
            gradePoint = 1.30;
            letterGrade = "D+";
        }
        else if (score >= 50) {
            gradePoint = 1.00;
            letterGrade = "D";
        }
        else {
            gradePoint = 0.00;
            letterGrade = "F";
        }
    }
};

class Semester {
public:
    Course courses[MAX_COURSES];
    int courseCount;

    Semester() { 
        courseCount = 0;
    }
    void addCourse(const Course& course) {
        if (courseCount < MAX_COURSES) {
            courses[courseCount++] = course;
        }
    }
};

class Student {
public:
    string id;
    Semester semesters[MAX_SEMESTERS];
    int semesterCount;
    Student(string studentId = "") 
    {
        id = studentId;
        semesterCount = 0;
    }
    void addCourse(int semester, const Course& course)
    {
        if (semester < MAX_SEMESTERS) {
            semesters[semester].addCourse(course);
        }
    }
    void enterScore(int semester, string courseName, double score) {
        if (semester < MAX_SEMESTERS) {
            for (int i = 0; i < semesters[semester].courseCount; ++i) {
                if (semesters[semester].courses[i].courseName == courseName) {
                    semesters[semester].courses[i].score = score;
                    semesters[semester].courses[i].computeGradePoint();
                    break;
                }
            }
        }
    }

    double computeGPA(int semester) {
        if (semester >= MAX_SEMESTERS) return 0.0;
        double totalQualityPoints = 0;
        int totalCreditHours = 0;
        for (int i = 0; i < semesters[semester].courseCount; ++i) {
            totalQualityPoints += semesters[semester].courses[i].gradePoint * semesters[semester].courses[i].creditHours;
            totalCreditHours += semesters[semester].courses[i].creditHours;
        }
        return totalCreditHours == 0 ? 0.0 : totalQualityPoints / totalCreditHours;
    }

    double computeCumulativeGPA() {
        double totalQualityPoints = 0;
        int totalCreditHours = 0;
        for (int semester = 0; semester < semesterCount; ++semester) {
            for (int i = 0; i < semesters[semester].courseCount; ++i) {
                totalQualityPoints += semesters[semester].courses[i].gradePoint * semesters[semester].courses[i].creditHours;
                totalCreditHours += semesters[semester].courses[i].creditHours;
            }
        }
        return totalCreditHours == 0 ? 0.0 : totalQualityPoints / totalCreditHours;
    }

    void printTranscript() {
        cout << "Transcript for student ID: " << id << endl;
        for (int semester = 0; semester < semesterCount; ++semester) {
            cout << "Semester " << semester + 1 << ":" << endl;
            for (int i = 0; i < semesters[semester].courseCount; ++i) {
                cout << fixed << setprecision(2);
                cout << "  Course: " << semesters[semester].courses[i].courseName
                    << ", Credits: " << semesters[semester].courses[i].creditHours
                    << ", Score: " << semesters[semester].courses[i].score
                    << ", Grade: " << semesters[semester].courses[i].letterGrade
                    << ", Grade Point: " << semesters[semester].courses[i].gradePoint << endl;
            }
            cout << "  GPA: " << computeGPA(semester) << endl;
        }
        cout << "Cumulative GPA: " << computeCumulativeGPA() << endl;
    }

    void loadCoursesFromFile(const string& filePath) {
        ifstream file(filePath);
        string line, courseName;
        int creditHours;

        if (file.is_open()) {
            while (getline(file, line)) {
                int pos = line.find(' ');
                courseName = line.substr(0, pos);
                creditHours = stoi(line.substr(pos + 1));
                for (int semester = 0; semester < MAX_SEMESTERS; ++semester) {
                    addCourse(semester, Course(courseName, creditHours));
                }
            }
            file.close();

        }
        else {
            cout << "Unable to open file " << filePath << endl;
        }
    }

    void loadScoresFromFile(const string& filePath) {
        ifstream file(filePath);
        string line, courseName;
        double score;
        int semester;
        string studentId;

        if (file.is_open()) {
            while (getline(file, line)) {
                int pos1 = line.find(' ');
                int pos2 = line.find(' ', pos1 + 1);
                int pos3 = line.find(' ', pos2 + 1);
                studentId = line.substr(0, pos1);
                semester = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                courseName = line.substr(pos2 + 1, pos3 - pos2 - 1);
                score = stod(line.substr(pos3 + 1));
                if (studentId == id) {
                    enterScore(semester - 1, courseName, score);
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file " << filePath << endl;
        }
    }

    void saveScoresToFile(const string& filePath) {
        ofstream file(filePath, ios::app);
        if (file.is_open()) {
            for (int semester = 0; semester < semesterCount; ++semester) {
                for (int i = 0; i < semesters[semester].courseCount; ++i) {
                    file << id << " " << semester + 1 << " "
                        << semesters[semester].courses[i].courseName << " "
                        << semesters[semester].courses[i].score << endl;
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file " << filePath << endl;
        }
    }

    double computeGPAForEnteredScores(int totalCreditHours, double totalQualityPoints) {
        return totalCreditHours == 0 ? 0.0 : totalQualityPoints / totalCreditHours;
    }
};

void adminMenu(Student& student) {
    int semester;
    double score;

    cout << "Admin Menu:\n";
    cout << "Enter semester number (1-" << MAX_SEMESTERS << "): ";
    cin >> semester;
    --semester; // Adjusting for 0-based index

    if (semester >= 0 && semester < MAX_SEMESTERS) {
        student.semesterCount = max(student.semesterCount, semester + 1);

        for (int i = 0; i < student.semesters[semester].courseCount; ++i) {
            do {
                cout << "Enter score for course: " << student.semesters[semester].courses[i].courseName << ": ";
                cin >> score;
                if (score < 0 || score >100)
                {
                    cout << "Invalid score!" << endl;
                }
            } while (score < 0 || score >100);
            student.enterScore(semester, student.semesters[semester].courses[i].courseName, score);
        }
        student.saveScoresToFile("C://Users//Lenovo//source//repos//ConsoleApplication1//ConsoleApplication1//students.txt");
    }
}

void studentMenu(Student& student) {
    cout << "Student Menu:\n";
    student.printTranscript();

    char choice;
    cout << "Do you want to calculate GPA for entered scores? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        double totalQualityPoints = 0;
        int totalCreditHours = 0;
        double score;
        int creditHours;

        cout << "Enter number of courses: ";
        int numCourses;
        cin >> numCourses;

        for (int i = 0; i < numCourses; ++i) {
            cout << "Enter score for course " << i + 1 << ": ";
            cin >> score;
            cout << "Enter credit hours for course " << i + 1 << ": ";
            cin >> creditHours;

            double gradePoint;
            if (score >= 90) gradePoint = 4.00;
            else if (score >= 85) gradePoint = 3.70;
            else if (score >= 80) gradePoint = 3.30;
            else if (score >= 75) gradePoint = 3.00;
            else if (score >= 70) gradePoint = 2.70;
            else if (score >= 65) gradePoint = 2.30;
            else if (score >= 60) gradePoint = 2.00;
            else if (score >= 55) gradePoint = 1.70;
            else if (score >= 52.5) gradePoint = 1.30;
            else if (score >= 50) gradePoint = 1.00;
            else gradePoint = 0.00;

            totalQualityPoints += gradePoint * creditHours;
            totalCreditHours += creditHours;
        }

        double calculatedGPA = student.computeGPAForEnteredScores(totalCreditHours, totalQualityPoints);
        cout << "Calculated GPA: " << calculatedGPA << endl;
    }
}

void mainMenu(Student& student) {
    int userType;
    bool exit = false;

    while (!exit) {
        cout << "\nMain Menu:\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Choose user type: ";
        cin >> userType;

        switch (userType) {
        case 1:
            adminMenu(student);
            break;
        case 2:
            studentMenu(student);
            break;
        case 3:
            exit = true;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    Student student;
    string studentId;

    cout << "Enter Student ID: ";
    cin >> studentId;
    student.id = studentId;

    // Load courses and scores from files
    student.loadCoursesFromFile("C://Users//Lenovo//source//repos//ConsoleApplication1//ConsoleApplication1//courses.txt");
    student.loadScoresFromFile("C://Users//Lenovo//source//repos//ConsoleApplication1//ConsoleApplication1//students.txt");

    mainMenu(student);

    return 0;
}