#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <chrono>
#include <random>
#include <map>

using namespace std;

struct Question {
    string question;
    string options[4];
    char correctOption;
    int timeLimit;
    string hint;
    string explanation;
    string topic;
};

vector<Question> getQuestions() {
    return {
        // Basic Questions
        {"Which of the following is a correct identifier in C++?",
         {"1variable", "variable_1", "variable-1", "variable 1"}, '2',
         20, "Consider C++ variable naming rules",
         "In C++, identifiers can't start with numbers or contain spaces/hyphens",
         "Basic Syntax"},
         
        {"Which keyword is used to define a class in C++?",
         {"def", "function", "class", "object"}, '3',
         25, "It's the same as the concept it defines",
         "The 'class' keyword is used to define classes in C++",
         "OOP Concepts"},
         
        {"Which operator is used to allocate memory dynamically in C++?",
         {"malloc", "alloc", "new", "make"}, '3',
         30, "Think about C++ specific operators",
         "'new' is the C++ operator for dynamic memory allocation",
         "Memory Management"},
         
        {"Which of the following is not a C++ data type?",
         {"float", "bool", "real", "char"}, '3',
         15, "Which one doesn't appear in primitive type lists?",
         "'real' is not a C++ primitive data type (use float/double instead)",
         "Data Types"},
         
        {"What is the size of int in C++ (typically)?",
         {"2 bytes", "4 bytes", "8 bytes", "16 bytes"}, '2',
         20, "Think about common architectures",
         "On most modern systems, int is typically 4 bytes",
         "Data Types"},
         
        {"Which of the following is used to take input in C++?",
         {"cin", "cout", "input", "scanf"}, '1',
         15, "Which one is the input stream?",
         "'cin' is the standard input stream object",
         "Basic I/O"},
         
        {"Which is the correct syntax to define a function in C++?",
         {"function myFunc()", "void myFunc()", "myFunc void()", "def myFunc()"}, '2',
         25, "Consider return type placement",
         "C++ functions specify return type before the function name",
         "Functions"},
         
        {"Which header file is needed for input/output in C++?",
         {"iostream", "stdio.h", "conio.h", "fileio.h"}, '1',
         15, "Which is the standard C++ header?",
         "<iostream> is the standard C++ header for I/O operations",
         "Basic I/O"},
         
        {"What is the scope resolution operator?",
         {"::", "..", "--", "->"}, '1',
         20, "Think about namespace and class scope",
         "'::' is used to access global scope or class members",
         "Operators"},
         
        {"What is the output of: cout << 5 / 2;",
         {"2.5", "2", "2.0", "Error"}, '2',
         25, "Consider integer division",
         "Integer division truncates the decimal part",
         "Operators"},

        // Advanced Questions
        {"What is the purpose of a virtual destructor in C++?",
         {"To prevent memory leaks when deleting polymorphic objects",
          "To make a class abstract",
          "To enable multiple inheritance",
          "To improve performance"}, '1',
         25, "Think about polymorphism and object destruction",
         "Virtual destructors ensure proper cleanup when deleting objects through base class pointers",
         "OOP Concepts"},

        {"What does RAII stand for in C++?",
         {"Resource Allocation Is Initialization",
          "Runtime Allocation of Internal Instances",
          "Recursive Algorithm Implementation",
          "Random Access Iterator Interface"}, '1',
         20, "It's a fundamental C++ idiom",
         "RAII ties resource management to object lifetime",
         "Memory Management"},

        {"Which STL container provides O(1) average complexity for insertions and deletions?",
         {"std::vector",
          "std::list",
          "std::unordered_map",
          "std::set"}, '2',
         25, "Think about linked data structures",
         "std::list (doubly-linked list) provides O(1) insertions/deletions",
         "STL Containers"},

        {"What is the output of: std::cout << sizeof('a'); in C++?",
         {"1", "2", "4", "Depends on the compiler"}, '1',
         15, "Character literals in C++ vs C",
         "In C++, character literals are of type char (1 byte), unlike in C",
         "Data Types"},

        {"Which keyword is used to prevent method overriding in a derived class?",
         {"static", "const", "final", "sealed"}, '3',
         20, "Introduced in C++11",
         "The 'final' keyword prevents further overriding of virtual methods",
         "OOP Concepts"},

        {"What is the purpose of std::move?",
         {"To physically move an object in memory",
          "To transfer ownership of resources",
          "To copy an object efficiently",
          "To change an object's type"}, '2',
         25, "Part of move semantics",
         "std::move casts to rvalue reference, enabling resource transfer",
         "Move Semantics"},

        {"Which of these is not a C++ smart pointer?",
         {"std::unique_ptr",
          "std::shared_ptr",
          "std::auto_ptr",
          "std::raw_ptr"}, '4',
         20, "Deprecated pointers vs non-existent ones",
         "std::raw_ptr doesn't exist (though std::auto_ptr is deprecated)",
         "Memory Management"},

        {"Which C++17 feature allows accessing multiple return values more easily?",
         {"auto keyword",
          "structured bindings",
          "template deduction",
          "lambda captures"}, '2',
         25, "Works with tuples and structs",
         "Structured bindings allow auto [x,y] = func_returning_pair();",
         "Modern C++"}
    };
}

void displayQuestion(const Question& q, int number) {
    cout << "\nQ" << number << ". " << q.question << "\n";
    for (int i = 0; i < 4; i++) {
        cout << "  " << i+1 << ") " << q.options[i] << "\n";
    }
    cout << "Time limit: " << q.timeLimit << " seconds\n";
    cout << "Enter your answer (1-4) or 'h' for hint: ";
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<Question> questions = getQuestions();
    int score = 0, total = questions.size();
    map<string, pair<int, int>> topicPerformance;

    unsigned seed = static_cast<unsigned>(time(0));
    shuffle(questions.begin(), questions.end(), default_random_engine(seed));

    cout << "======== C++ CODE QUIZ APP ========\n";
    cout << "  Answer each question (1-4)\n";
    cout << "  Type 'h' for hint during question\n";
    cout << "===================================\n";

    for (int i = 0; i < total; ++i) {
        displayQuestion(questions[i], i + 1);
        
        auto questionStart = chrono::high_resolution_clock::now();
        char answer = ' ';
        bool timeExpired = false;
        
        // Non-threaded timer implementation
        while (true) {
            auto currentTime = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - questionStart).count();
            
            if (elapsed >= questions[i].timeLimit) {
                cout << "\n⏰ Time's up! The correct answer was: " << questions[i].correctOption << "\n";
                timeExpired = true;
                break;
            }
            
            if (cin.peek() != EOF) {
                cin >> answer;
                
                if (answer == 'h' || answer == 'H') {
                    cout << "💡 Hint: " << questions[i].hint << "\n";
                    cout << "Enter your answer (1-4): ";
                    cin >> answer;
                }
                
                if (answer >= '1' && answer <= '4') {
                    break;
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "❗ Invalid input. Please enter 1-4: ";
                }
            }
        }

        if (!timeExpired) {
            if (answer == questions[i].correctOption) {
                cout << "✅ Correct! " << questions[i].explanation << "\n";
                ++score;
            } else {
                cout << "❌ Wrong! Correct Answer: Option " << questions[i].correctOption 
                     << "\nExplanation: " << questions[i].explanation << "\n";
            }
        }
        
        string topic = questions[i].topic;
        topicPerformance[topic].first += (answer == questions[i].correctOption);
        topicPerformance[topic].second += 1;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    
    cout << "\n========== RESULTS ==========\n";
    cout << " Your Score: " << score << " / " << total << "\n";
    float percent = (score * 100.0f) / total;
    cout << " Percentage: " << percent << "%\n";
    cout << " Time Taken: " << duration.count() << " seconds\n";
    
    if (percent == 100)
        cout << "🌟 Excellent! Perfect score!\n";
    else if (percent >= 75)
        cout << "🎉 Great job!\n";
    else if (percent >= 50)
        cout << "👍 Good effort. Keep learning.\n";
    else
        cout << "📚 Needs improvement. Try again!\n";

    cout << "\n======== PERFORMANCE ANALYSIS ========\n";
    for (const auto& entry : topicPerformance) {
        double topicPercent = (entry.second.first * 100.0) / entry.second.second;
        cout << entry.first << ": " << entry.second.first << "/" << entry.second.second 
             << " (" << topicPercent << "%)" << endl;
        if (topicPercent < 50) {
            cout << "   ➡ Focus more on this topic!\n";
        }
    }

    return 0;
}