#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;
struct task
{
    string name;
    time_t start_time;
    time_t end_time;
    bool is_active = false;
};

void begin_task(task &s_task, vector<task> &v_task)
{
    string task_name;

    if (v_task.size() > 0 && v_task.back().is_active == true)
    {
        v_task.back().end_time = time(nullptr);
        v_task.back().is_active = false;
    }

    cout << "Enter task name: ";
    cin >> task_name;
    s_task.name = task_name;
    s_task.start_time = time(nullptr);
    s_task.is_active = true;

    v_task.push_back(s_task);
}

void end_task(vector<task> &v_task)
{
    if (v_task.empty())
    {
        cout << "No tasks to end" << endl;
    }
    else if (v_task.back().is_active == false)
    {
        cout << "Task is not active" << endl;
    }
    else if (v_task.size() > 0 && v_task.back().is_active == true)
    {
        v_task.back().end_time = time(nullptr);
        v_task.back().is_active = false;
    }
}

void check_task_status(vector<task> &v_task)
{
    for (int i = 0; i < v_task.size(); ++i)
    {
        cout << endl << v_task[i].name << endl;
        if(v_task[i].is_active == false)
        {
            double diff = difftime (v_task[i].end_time, v_task[i].start_time);
            time_t t_diff = (time_t)diff;
            tm* tm_diff = gmtime(&t_diff);
            cout << put_time(tm_diff, "%H:%M:%S") << endl;
        }
    }
}

int main()
{
    string user_command;
    //v_task
    vector<task> task_struct;

    cout << "Input command (begin, end, status, exit): ";
    cin >> user_command;

    while (user_command != "exit")
    {
        if (user_command == "begin")
        {
            //s_task
            task task_tmp;

            begin_task(task_tmp, task_struct);
            cout << endl << "Input command (begin, end, status, exit): ";
            cin >> user_command;
        }
        else if (user_command == "end")
        {
            end_task(task_struct);
            cout << endl << "Input command (begin, end, status, exit): ";
            cin >> user_command;
        }
        else if (user_command == "status")
        {
            check_task_status(task_struct);
            cout << endl << "Input command (begin, end, status, exit): ";
            cin >> user_command;
        }
        else
        {
            cerr << "Unknown command! Try again!";
            cin >> user_command;
        }
    }
}