#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// chek file exist
bool fileExists(const std::string &filename)
{
    std::ifstream file(filename);
    return file.good();
}

struct StudentData
{
    std::string studentName;
    std::string className;
    std::string subjectStream;
    int biologyMarks;
    int physicsMarks;
    int chemistryMarks;
    int combinedMathsMarks;
    int totalMarks;
    int schoolRank;
    int classRank;
};

// Get data from the students and append to the file using those data
void appendDataToFile(const std::string &filename)
{
    std::ofstream file(filename, std::ios::app); // Open the file in append mode
    if (file)
    {
        std::string addOrCal;
        std::cout << "To add type (add). To calculate type (cal) :";
        std::cin >> addOrCal;

        if (addOrCal == "add")
        {

            std::string studentName, className, subjectStream;
            int biologyMarks, physicsMarks, chemistryMarks, combinedMathsMarks;

            while (true)
            {
                std::cout << "Enter your name (or 'exit' to quit): ";
                std::cin >> studentName;
                if (studentName == "exit")
                {
                    break;
                }

                std::cout << "Enter your class name (b1, b2, b3, m1, m2, m3, m4, or m5): ";
                std::cin >> className;

                std::cout << "Enter your subject stream (bio or maths): ";
                std::cin >> subjectStream;

                if (subjectStream == "bio")
                {
                    std::cout << "Enter your biology subject marks: ";
                    std::cin >> biologyMarks;

                    std::cout << "Enter your physics subject marks: ";
                    std::cin >> physicsMarks;

                    std::cout << "Enter your chemistry subject marks: ";
                    std::cin >> chemistryMarks;

                    file << studentName << "," << className << "," << subjectStream << ","
                         << biologyMarks << "," << physicsMarks << "," << chemistryMarks << "\n";
                }
                else if (subjectStream == "maths")
                {
                    std::cout << "Enter your combined maths subject marks: ";
                    std::cin >> combinedMathsMarks;

                    std::cout << "Enter your physics subject marks: ";
                    std::cin >> physicsMarks;

                    std::cout << "Enter your chemistry subject marks: ";
                    std::cin >> chemistryMarks;

                    file << studentName << "," << className << "," << subjectStream << ","
                         << combinedMathsMarks << "," << physicsMarks << "," << chemistryMarks << "\n";
                }
                else
                {
                    std::cout << "Invalid subject stream. Please enter 'bio' or 'maths'." << std::endl;
                }
            }
            std::cout << "Data has been appended to the file." << std::endl;
        }
        else if (addOrCal == "cal")
        {
            std::ifstream inputFile(filename);
            std::vector<StudentData> students;

            if (inputFile)
            {
                std::string line;
                while (std::getline(inputFile, line))
                {
                    std::istringstream iss(line);
                    StudentData student;
                    std::string subjectStream;

                    std::getline(iss, student.studentName, ',');
                    std::getline(iss, student.className, ',');
                    std::getline(iss, subjectStream, ',');
                    std::getline(iss, student.subjectStream, ',');

                    if (subjectStream == "bio")
                    {
                        student.subjectStream = "bio"; // Update the subject stream in the struct
                        iss >> student.biologyMarks >> student.physicsMarks >> student.chemistryMarks;
                        student.totalMarks = student.biologyMarks + student.physicsMarks + student.chemistryMarks;
                    }
                    else if (subjectStream == "maths")
                    {
                        student.subjectStream = "maths"; // Update the subject stream in the struct
                        iss >> student.combinedMathsMarks >> student.physicsMarks >> student.chemistryMarks;
                        student.totalMarks = student.combinedMathsMarks + student.physicsMarks + student.chemistryMarks;
                    }

                    students.push_back(student);
                }

                // Calculate school rank and class rank
                std::sort(students.begin(), students.end(), [](const StudentData &a, const StudentData &b)
                          { return a.totalMarks > b.totalMarks; });

                int rank = 1;
                for (size_t i = 0; i < students.size(); ++i)
                {
                    students[i].schoolRank = rank;
                    if (i > 0 && students[i].totalMarks != students[i - 1].totalMarks)
                    {
                        rank = i + 1;
                    }
                }

                rank = 1;
                for (size_t i = 0; i < students.size(); ++i)
                {
                    if (students[i].className == students[0].className)
                    {
                        students[i].classRank = rank;
                        if (i > 0 && students[i].totalMarks != students[i - 1].totalMarks)
                        {
                            rank = i + 1;
                        }
                    }
                }

                // Print and write the student ranks to a separate file (result.txt)
                std::ofstream resultFile("result.txt", std::ios::trunc);
                if (resultFile)
                {
                    resultFile << "Student Name,Class Name,Subject Stream,Total Marks,School Rank,Class Rank\n";
                    for (const auto &student : students)
                    {
                        resultFile << student.studentName << "," << student.className << "," << student.subjectStream << ","
                                   << student.totalMarks << "," << student.schoolRank << "," << student.classRank << "\n";
                    }
                    std::cout << "Student ranks have been calculated and written to result.txt" << std::endl;
                }
                else
                {
                    std::cerr << "Error opening the file: result.txt" << std::endl;
                }
            }
            else
            {
                std::cerr << "Error opening the file: " << filename << std::endl;
            }
        }
        else
        {
            std::cout << "Enter valid word";
        }
    }
    else
    {
        std::cerr << "Error opening the file: " << filename << std::endl;
    }
}

//////////////////////////////////////////MainFun////////////////////////////////////////
int main()
{
    std::string filename = "student.txt"; // Replace with your desired file name.

    if (!fileExists(filename))
    {
        std::cout << "File does not exist. Creating a new file." << std::endl;
        std::ofstream newFile(filename);
        if (newFile)
        {
            std::cout << "File created: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error creating the file: " << filename << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "File already exists. Adding data to the " << filename << std::endl;
    }

    appendDataToFile(filename);

    return 0;
}
//////////////////////////////////////////MainFun////////////////////////////////////////
