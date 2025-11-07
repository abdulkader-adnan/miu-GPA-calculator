# MIU GPA Calculator

This C++ project is a GPA calculator developed for MIU Computer Science students.  
It provides a console-based interface with two main roles:

## Admin Feature
- Allows administrators to enter and save student scores.

## Student Feature
- Allows students to view their full academic transcript.
- Calculates both semester and cumulative GPA.

---

### Technical Details
The program is built using C++ with classes for:
- **Course** – manages course information such as code, name, credits, and grade.
- **Semester** – stores and manages multiple courses per semester.
- **Student** – represents a student with their semesters and GPA data.

The application reads and writes data from text files:
- `courses.txt` – stores course information.
- `students.txt` – stores student records and grades.

All changes made by the admin are saved back to the respective files for future use.
