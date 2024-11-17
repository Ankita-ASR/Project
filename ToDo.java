import java.util.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;

class Task {
    private String name;
    private String description;
    private String dueDate;
    private boolean completed;

    // Task Constructor
    public Task(String name, String description, String dueDate) {
        this.name = name;
        this.description = description;
        this.dueDate = dueDate;
        this.completed = false;
    }

    public String getName() {
        return name;
    }

    public String getDueDate() {
        return dueDate;
    }

    public boolean isCompleted() {
        return completed;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setDueDate(String dueDate) {
        this.dueDate = dueDate;
    }

    public void markCompleted() {
        this.completed = true;
    }

    public void displayTask() {
        System.out.println("\t   Task Name: " + name);
        System.out.println("\t   Description: " + description);
        System.out.println("\t   Due Date: " + dueDate);
        System.out.println("\t   Status: " + (completed ? "Completed" : "Incomplete"));
        System.out.println("\t   ------------------------------");
    }
}

class ToDoListApp {
    private List<Task> taskList;

    public ToDoListApp() {
        taskList = new ArrayList<>();
    }

    private void sortTasksByDueDate() {
        taskList.sort(Comparator.comparing(Task::getDueDate));
    }

    public void addTask(String name, String description, String dueDate) {
        taskList.add(new Task(name, description, dueDate));
        System.out.println("\t   Task added successfully!");
    }

    public void displayTasks() {
        if (taskList.isEmpty()) {
            System.out.println("\t   Task list is empty.");
            return;
        }
        sortTasksByDueDate();
        for (Task task : taskList) {
            task.displayTask();
        }
    }

    public void markTaskCompleted(String taskName) {
        for (Task task : taskList) {
            if (task.getName().equalsIgnoreCase(taskName)) {
                task.markCompleted();
                System.out.println("\t   Task '" + taskName + "' marked as completed.");
                return;
            }
        }
        System.out.println("\t   Task '" + taskName + "' not found.");
    }

    public void deleteTask(String taskName) {
        Iterator<Task> iterator = taskList.iterator();
        while (iterator.hasNext()) {
            if (iterator.next().getName().equalsIgnoreCase(taskName)) {
                iterator.remove();
                System.out.println("\t   Task '" + taskName + "' deleted successfully!");
                return;
            }
        }
        System.out.println("\t   Task '" + taskName + "' not found.");
    }

    public void editTask(String taskName, String newDescription, String newDueDate) {
        for (Task task : taskList) {
            if (task.getName().equalsIgnoreCase(taskName)) {
                task.setDescription(newDescription);
                task.setDueDate(newDueDate);
                System.out.println("\t   Task updated successfully!");
                return;
            }
        }
        System.out.println("\t   Task '" + taskName + "' not found.");
    }

    private boolean isDueSoon(String currentDate, String dueDate) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        try {
            Date current = sdf.parse(currentDate);
            Date due = sdf.parse(dueDate);

            long diff = (due.getTime() - current.getTime()) / (1000 * 60 * 60 * 24);
            return diff == 0 || diff == 1; // Due today or tomorrow
        } catch (ParseException e) {
            System.out.println("\t   Error parsing dates.");
        }
        return false;
    }

    public void showReminders(String currentDate) {
        boolean found = false;
        System.out.println("\t   Upcoming tasks due soon:");
        for (Task task : taskList) {
            if (!task.isCompleted() && isDueSoon(currentDate, task.getDueDate())) {
                task.displayTask();
                found = true;
            }
        }
        if (!found) {
            System.out.println("\t   No tasks are due within the next day.");
        }
    }
}

public class ToDoListAppMain {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ToDoListApp toDoListApp = new ToDoListApp();
        int choice;

        do {
            System.out.println("=============================================");
            System.out.println("\t\t    To-Do List Application");
            System.out.println("=============================================");
            System.out.println("1. Add a new task");
            System.out.println("2. Display all tasks");
            System.out.println("3. Mark task as completed");
            System.out.println("4. Delete a task");
            System.out.println("5. Edit a task");
            System.out.println("6. Show reminders");
            System.out.println("7. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter task name: ");
                    String name = sc.nextLine();
                    System.out.print("Enter task description: ");
                    String description = sc.nextLine();
                    System.out.print("Enter due date (YYYY-MM-DD): ");
                    String dueDate = sc.nextLine();
                    toDoListApp.addTask(name, description, dueDate);
                    break;

                case 2:
                    toDoListApp.displayTasks();
                    break;

                case 3:
                    System.out.print("Enter the name of the task to mark as completed: ");
                    String completedTask = sc.nextLine();
                    toDoListApp.markTaskCompleted(completedTask);
                    break;

                case 4:
                    System.out.print("Enter the name of the task to delete: ");
                    String deleteTask = sc.nextLine();
                    toDoListApp.deleteTask(deleteTask);
                    break;

                case 5:
                    System.out.print("Enter the name of the task to edit: ");
                    String editTask = sc.nextLine();
                    System.out.print("Enter new description: ");
                    String newDescription = sc.nextLine();
                    System.out.print("Enter new due date (YYYY-MM-DD): ");
                    String newDueDate = sc.nextLine();
                    toDoListApp.editTask(editTask, newDescription, newDueDate);
                    break;

                case 6:
                    System.out.print("Enter the current date (YYYY-MM-DD): ");
                    String currentDate = sc.nextLine();
                    toDoListApp.showReminders(currentDate);
                    break;

                case 7:
                    System.out.println("Exiting application. Goodbye!");
                    break;

                default:
                    System.out.println("Invalid choice. Please try again.");
                    break;
            }
        } while (choice != 7);

        sc.close();
    }
}
