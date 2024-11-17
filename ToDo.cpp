#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// Task class to represent each task
class Task
{
public:
    string name;
    string description;
    string dueDate;
    bool completed;

    // Task Constructor
    Task(string name, string description, string dueDate)
    {
        this->name = name;
        this->description = description;
        this->dueDate = dueDate;
        this->completed = false;
    }

    // Display task details
    void displayTask()
    {
        cout << "\t\t\t\t\t   Task Name: " << name << "\n";
        cout << "\t\t\t\t\t   Description: " << description << "\n";
        cout << "\t\t\t\t\t   Due Date: " << dueDate << "\n";
        cout << "\t\t\t\t\t   Status: " << (completed ? "Completed" : "Incomplete") << "\n";
        cout << "\t\t\t\t\t   ------------------------------\n";
    }
};

// Main class to manage tasks
class ToDoListApp
{
public:
    vector<Task> taskList;

    void sortTasksByDueDate()
    {
        sort(taskList.begin(), taskList.end(), [](const Task &a, const Task &b)
             { return a.dueDate < b.dueDate; });
    }

    // Method to add a new task
    void addTask(string name, string description, string dueDate)
    {
        Task newTask(name, description, dueDate);
        taskList.push_back(newTask);
        cout << "\t\t\t\t\t   Task added successfully!\n";
    }

    // Display all tasks sorted by due date
    void displayTasks()
    {
        if (taskList.empty())
        {
            cout << "\t\t\t\t\t   Task list is empty.\n";
            return;
        }
        sortTasksByDueDate();
        for (auto &task : taskList)
        {
            task.displayTask();
        }
    }

    // Mark a task as completed
    void markTaskCompleted(const string &taskName)
    {
        for (auto &task : taskList)
        {
            if (task.name == taskName)
            {
                task.completed = true;
                cout << "\t\t\t\t\t   Task '" << taskName << "' marked as completed.\n";
                return;
            }
        }
        cout << "\t\t\t\t\t   Task '" << taskName << "' not found.\n";
    }

    // Delete a task
    void deleteTask(string taskName)
    {
        auto it = remove_if(taskList.begin(), taskList.end(), [&taskName](const Task &task)
                            { return task.name == taskName; });

        if (it != taskList.end())
        {
            taskList.erase(it, taskList.end());
            cout << "\t\t\t\t\t   Task '" << taskName << "' deleted successfully!\n";
        }
        else
        {
            cout << "\t\t\t\t\t   Task '" << taskName << "' not found.\n";
        }
    }

    // Edit task if needed
    void editTask(string taskName)
    {
        for (auto &task : taskList)
        {
            if (task.name == taskName)
            {
                cout << "\t\t\t\t\t   Editing Task: " << taskName << "\n";
                cout << "\t\t\t\t\t   Enter new description: ";
                getline(cin, task.description);
                cout << "\t\t\t\t\t   Enter new due date(yyyy-mm-dd): ";
                getline(cin, task.dueDate);
                cout << "\t\t\t\t\t   Task updated successfully!\n";
                return;
            }
        }
        cout << "\t\t\t\t\t   Task '" << taskName << "' not found.\n";
    }

    // Helper function to check if a task is due soon
    bool isDueSoon(string currentDate, string dueDate)
    {
        // Parse the current date
        int cYear, cMonth, cDay;
        sscanf(currentDate.c_str(), "%d-%d-%d", &cYear, &cMonth, &cDay);

        // Parse the due date
        int dYear, dMonth, dDay;
        sscanf(dueDate.c_str(), "%d-%d-%d", &dYear, &dMonth, &dDay);

        // Check if the due date is today or tomorrow
        if (cYear == dYear && cMonth == dMonth)
        {
            int daysLeft = dDay - cDay;
            return (daysLeft == 0 || daysLeft == 1); // Due today or tomorrow
        }

        return false;
    }

    // Function to display reminders for upcoming tasks
    void showReminders()
    {
        bool found = false;
        cout << "\t\t\t\t\t   Enter the current date (YYYY-MM-DD):";
        string currentDate;
        getline(cin, currentDate);

        cout << "\t\t\t\t\t   Upcoming tasks due soon:\n";
        for (auto &task : taskList)
        {
            if (!task.completed && isDueSoon(currentDate, task.dueDate))
            {
                task.displayTask();
                found = true;
            }
        }
        if (!found)
        {
            cout << "\t\t\t\t\t   No tasks are due within the next day.\n";
        }
    }
};

int main()
{
    ToDoListApp toDoListApp;
    int choice;
    string name, description, dueDate;

    while (choice != 7)
    {
        cout << "\t\t\t\t\t=============================================\n\t\t\t\t\t\t    To-Do List Application\n\t\t\t\t\t=============================================\n"
             << endl;
        cout << "\t\t\t\t\t   Add a new task___1" << endl;
        cout << "\t\t\t\t\t   Display all tasks__2" << endl;
        cout << "\t\t\t\t\t   Mark task as completed___3" << endl;
        cout << "\t\t\t\t\t   Delete a task__4" << endl;
        cout << "\t\t\t\t\t   Edit a task__5" << endl;
        cout << "\t\t\t\t\t   Show reminders___6" << endl;
        cout << "\t\t\t\t\t   For Exit___7" << endl;
        cout << "\t\t\t\t\t   Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the input buffer

        switch (choice)
        {
        case 1:
            system("cls");
            cout << "\t\t\t\t\t   Enter task name: ";
            getline(cin, name);
            cout << "\t\t\t\t\t   Enter task description: ";
            getline(cin, description);
            cout << "\t\t\t\t\t   Enter due date (YYYY-MM-DD): ";
            getline(cin, dueDate);

            toDoListApp.addTask(name, description, dueDate);
            getch();
            system("cls");
            break;

        case 2:
            system("cls");
            toDoListApp.displayTasks();
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            cout << "\t\t\t\t\t   Enter the name of the task to mark as completed: ";
            getline(cin, name);
            toDoListApp.markTaskCompleted(name);
            getch();
            system("cls");
            break;

        case 4:
            system("cls");
            cout << "\t\t\t\t\t   Enter the name of the task to delete: ";
            getline(cin, name);
            toDoListApp.deleteTask(name);
            getch();
            system("cls");
            break;

        case 5:
            system("cls");
            cout << "\t\t\t\t\t   Enter the name of the task to edit: ";
            getline(cin, name);
            toDoListApp.editTask(name);
            getch();
            system("cls");
            break;

        case 6:
            system("cls");
            toDoListApp.showReminders();
            getch();
            system("cls");
            break;

        case 7:
            system("cls");
            cout << "\t\t\t\t\t   Exiting application. Goodbye!\n";
            getch();
            system("cls");
            break;

        default:

            cout << "\t\t\t\t\t   Invalid choice. Please try again.\n";
            getch();
            system("cls");
            break;
        }
    }
    return 0;
}
