#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define course structure to hold the course details
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Define CourseCatalog class managing courses using a hash table
class CourseCatalog {
private:
    unordered_map<string, Course> courses;

public:
    // Load courses from the into the hash table
    void loadCourses(string filename) {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cout << "Error: Could not open file." << endl;
            return;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber, courseTitle, prereq;

            getline(ss, courseNumber, ',');
            getline(ss, courseTitle, ',');

            Course course;
            course.courseNumber = courseNumber;
            course.courseTitle = courseTitle;

            while (getline(ss, prereq, ',')) {
                // Only add non-empty prerequisites
                if (!prereq.empty()) {
                    course.prerequisites.push_back(prereq);
                }
            }

            courses[courseNumber] = course;
        }

        file.close();
        cout << "Courses loaded successfully." << endl;
    }

    // Print the alphanumeric list of all courses
    void printCourseList() {
        vector<Course> courseList;

        // Extract courses from the hash table into a vector for sorting
        for (auto const& pair : courses) {
            courseList.push_back(pair.second);
        }

        // Sort the courses alphanumerically by course number
        sort(courseList.begin(), courseList.end(), [](Course a, Course b) {
            return a.courseNumber < b.courseNumber;
            });

        for (auto const& course : courseList) {
            cout << course.courseNumber << ", " << course.courseTitle << endl;
        }
    }

    // Print both the title and prerequisites of the selected course
    void printCourseInformation(string courseNumber) {
        if (courses.find(courseNumber) != courses.end()) {
            Course course = courses[courseNumber];
            cout << course.courseNumber << ", " << course.courseTitle << endl;
            cout << "Prerequisites: ";

            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "Error: Course not found." << endl;
        }
    }
};

int main() {
    CourseCatalog catalog;
    int choice;
    string filename, courseNumber;

    while (true) {
        // Menu options
        cout << "1. Load Data" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";

        // Input validation 
        if (!(cin >> choice)) {
            // If the input is not an integer
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            continue; // Prompt the user again
        }

        // Menu choices
        switch (choice) {
        case 1:
            cout << "Enter the filename: ";
            cin >> filename;
            catalog.loadCourses(filename);
            break;
        case 2:
            catalog.printCourseList();
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            catalog.printCourseInformation(courseNumber);
            break;
        case 9:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}