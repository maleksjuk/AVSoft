#include "company.hpp"

Department::Department(string _name)
{
    name = _name;
    count_employee = 0;
    mean_salary = 0;
}

string Department::getName(){
    return name;
}

int Department::getCount(){
    return count_employee;
}

float Department::getMeanSalary(){
    return mean_salary;
}

void Department::setName(string _name){
    name = _name;
}

vector<Employee> Department::getEmployment(){
    return employments;
}

void Department::addEmployee(string _surname, string _name, string _middleName, string _function, int _salary)
{
    Employee employee(_surname, _name, _middleName, _function, _salary);
    employments.push_back(employee);
    count_employee++;
    mean_salary = (mean_salary + _salary) / count_employee;
}

void Department::delEmployee(string FIO)
{
    int i = 0;
    for (auto &employee : employments)
    {
        if (employee.getFIO() == FIO)
        {
            cout 
                << "УДАЛЕНИЕ СОТРУДНИКА: " 
                << employee.getSurname() << " " 
                << employee.getName() << " " 
                << employee.getMiddleName() << " (Должность: "
                << employee.getFunction() << ", ЗП: "
                << employee.getSalary() << ")" << endl;
            
            mean_salary = (mean_salary * count_employee - employee.getSalary()) / (count_employee - 1);
            count_employee--;

            employments.erase(employments.begin() + i);
            break;
        }
        i++;
    }
}

void Department::editEmployee(int id, char cmd, string new_value)
{
    Employee &employee = employments[id];

    switch (cmd)
    {
    case '1':
        employee.setSurname(new_value);
        break;
    case '2':
        employee.setName(new_value);
        break;
    case '3':
        employee.setMiddleName(new_value);
        break;
    case '4':
        employee.setFunction(new_value);
        break;
    case '5':
        employee.setSalary(std::stoi(new_value));
        break;
    default:
        break;
    }
}

void Department::printer()
{
    cout << CLR_CYAN << "Подразделение: " << name << CLR_RESET << endl;
    cout << INDENT_DEPARTMENT << "Количество сотрудников: " << count_employee << endl;
    cout << INDENT_DEPARTMENT << "Средняя зарплата: " << mean_salary << endl;

    for (auto &employee : employments)
        employee.printer();
}

void delete_department(vector<Department> &company, string name)
{
    int i = 0;
    for (auto &dep : company)
    {
        if (dep.getName() == name)
        {
            cout << "УДАЛЕНИЕ ПОДРАЗДЕЛЕНИЯ: " << dep.getName() << endl;
            company.erase(company.begin() + i);
            break;
        }
        i++;
    }
}

void edit_department(vector<Department> &company, string name_old, string name_new)
{
    for (auto &dep : company)
        if (dep.getName() == name_old)
        {
            cout << "ИЗМЕНЕНИЕ НАЗВАНИЯ ПОДРАЗДЕЛЕНИЯ: " 
                << dep.getName() << " --> " << name_new << endl;
            dep.setName(name_new);
            break;
        }
}

void add_department(vector<Department> &company, string _name)
{
    for (auto &dep : company)
        if (dep.getName() == _name)
        {
            cout << "Подразделение уже существует" << endl;
            return ;
        }
    company.push_back(Department(_name));
}
