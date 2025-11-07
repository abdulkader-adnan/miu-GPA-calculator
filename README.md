# miu-GPA-calculator
🎓 MIU GPA Calculator
A console-based C++ application designed for Misr International University (MIU) Computer Science students to calculate and manage their GPA.

✨ Features
This project provides a simple interface with two primary roles:

🧑‍💻 Admin Role
Enter Scores: Allows administrators to enter and save new scores for students by semester.

Data Persistence: Saves all new scores to the students.txt file.

🧑‍🎓 Student Role
View Transcript: Displays a full academic transcript, including courses, scores, letter grades, and grade points.

Calculate GPA: Computes both semester and cumulative GPA based on the scores entered.

🛠️ Technical Details
Language: C++

Core Structure: Built using object-oriented principles. The main classes are:

Course: Manages course name, credit hours, score, and grade points.

Semester: Holds an array of Course objects for a specific semester.

Student: Manages student ID and an array of Semester objects.

Data Handling: The program reads and writes data from local text files:

courses.txt: Stores the university's course catalog (course name, credit hours).

students.txt: Stores student IDs and their corresponding scores for each course.
