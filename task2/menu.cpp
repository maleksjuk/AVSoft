#include "company.hpp"

Menu::Menu(string _title){
    title = _title;
}

string Menu::getTitle(){
    return title;
}

void Menu::addAction(char c, string action)
{
    if (!actions.count(c))
        actions.insert({c, action});
    else
        actions[c] = action;
}

void Menu::printer()
{
    std::cout
        << "____________________\n"
        << getTitle() << std::endl;
    for (auto &action : actions)
        std::cout << action.first << " --> " << action.second << std::endl;
    std::cout
        << "^^^^^^^^^^^^^^^^^^^^" << std::endl;
}

Menu create_menu_main()
{
    Menu menu("ГЛАВНОЕ МЕНЮ");
    menu.addAction('x', "выйти");
    menu.addAction('p', "распечатать всё предприятие");
    menu.addAction('c', "выбрать подразделение");
    menu.addAction('a', "добавить подразделение");
    menu.addAction('r', "удалить подразделение");
    return menu;
}

Menu create_menu_department()
{
    Menu menu("МЕНЮ ПОДРАЗДЕЛЕНИЯ");
    menu.addAction('x', "вернуться в главное меню");
    menu.addAction('p', "распечатать подразделение");
    menu.addAction('n', "переименовать подразделение");
    menu.addAction('c', "выбрать сотрудника");
    menu.addAction('a', "добавить сотрудника");
    menu.addAction('r', "удалить сотрудника");
    return menu;
}

Menu create_menu_employee()
{
    Menu menu("МЕНЮ СОТРУДНИКА");
    menu.addAction('x', "вернуться в меню подразделения");
    menu.addAction('p', "распечатать данные о сотруднике");
    menu.addAction('1', "изменить фамилию");
    menu.addAction('2', "изменить имя");
    menu.addAction('3', "изменить отчество");
    menu.addAction('4', "изменить должность");
    menu.addAction('5', "изменить зарплату");
    return menu;
}

void main_menu(vector<Department> &company, vector<Menu> &menu_list)
{
    bool right;
    char cmd;
    string name;
    int i;

    if (term_set())
        term_reset();
    menu_list[0].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        switch (cmd)
        {
        case 'x':
            return ;
        
        case 'p':
            print_company(company);
            break;
        
        case 'c':
            std::cout << "[ВЫБОР] ВЫБЕРИТЕ ПОДРАЗДЕЛЕНИЕ" << std::endl;
            i = 1;
            for (auto &dep : company)
                std::cout << i++ << " - " << dep.getName() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= company.size())
                menu_department(company, menu_list, i - 1);
            else
                error_msg("Главное меню", "Неверный номер");
                // std::cout << "Неверный номер" << std::endl;
            break;
        
        case 'a':
            std::cout << "СОЗДАНИЕ НОВОГО ПОДРАЗДЕЛЕНИЯ\n" << "Введите название: ";
            std::cin >> name;
            add_department(company, name);
            break;
        
        case 'r':
            std::cout << "[УДАЛЕНИЕ] ВЫБЕРИТЕ ПОДРАЗДЕЛЕНИЕ" << std::endl;
            i = 1;
            for (auto &dep : company)
                std::cout << i++ << " - " << dep.getName() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= company.size())
                company.erase(company.begin() + i - 1);
            else
                error_msg("Главное меню", "Неверный номер");
                // std::cout << "Неверный номер" << std::endl;
            break;
        
        default:
            right = false;
            break;
        }
        if (term_set())
            term_reset();
        usleep(SLEEP_WAIT);
        if (right)
            menu_list[0].printer();
    }
    term_reset();
}

void menu_department(vector<Department> &company, vector<Menu> &menu_list, int id)
{
    bool right;
    char cmd;
    int i;
    string name;
    string surname;
    string middleName;
    string function;
    int salary;
    Department &department = company[id];

    if (term_set())
        term_reset();
    menu_list[1].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        switch (cmd)
        {
        case 'x':
            return ;
        
        case 'p':
            department.printer();
            break;
        
        case 'n':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новое название: ";
            std::cin >> name;
            department.setName(name);
            break;
        
        case 'c':
            std::cout << "[ВЫБОР] ВЫБЕРИТЕ СОТРУДНИКА" << std::endl;
            i = 1;
            for (auto &empl : department.getEmployment())
                std::cout << i++ << " - " << empl.getFIO() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= department.getEmployment().size())
                menu_employee(department, menu_list, i - 1);
            else
                error_msg("Меню подразделения", "Неверный номер");
                // std::cout << "Неверный номер" << std::endl;
            break;
        
        case 'a':
            std::cout << "ДОБАВЛЕНИЕ НОВОГО СОТРУДНИКА\n";
            std::cout << "Фамилия: ";
            std::cin >> surname;
            std::cout << "Имя: ";
            std::cin >> name;
            std::cout << "Отчество: ";
            std::cin >> middleName;
            std::cout << "Должность: ";
            std::cin >> function;
            std::cout << "Зарплата: ";
            std::cin >> salary;
            department.addEmployee(surname, name, middleName, function, salary);
            break;
        
        case 'r':
            std::cout << "[УДАЛЕНИЕ] ВЫБЕРИТЕ СОТРУДНИКА" << std::endl;
            i = 1;
            for (auto &empl : department.getEmployment())
                std::cout << i++ << " - " << empl.getFIO() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= department.getEmployment().size())
                department.delEmployee(department.getEmployment()[i - 1].getFIO());
            else
                error_msg("Меню подразделения", "Неверный номер");
                // std::cout << "Неверный номер" << std::endl;
            break;
        
        default:
            right = false;
            break;
        }
        if (term_set())
            term_reset();
        usleep(SLEEP_WAIT);
        if (right)
            menu_list[1].printer();
    }
    term_reset();
}

void menu_employee(Department &department, vector<Menu> &menu_list, int id)
{
    bool right;
    char cmd;
    string name;
    int salary;
    Employee &employee = department.getEmployment()[id];

    if (term_set())
        term_reset();
    menu_list[2].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        switch (cmd)
        {
        case 'x':
            return ;
        
        case 'p':
            employee.printer();
            break;
        
        case '1':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новую фамилию: ";
            std::cin >> name;
            employee.setSurname(name);
            break;

        case '2':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новое имя: ";
            std::cin >> name;
            employee.setName(name);
            break;

        case '3':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новое отчество: ";
            std::cin >> name;
            employee.setMiddleName(name);
            break;

        case '4':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новую должность: ";
            std::cin >> name;
            employee.setFunction(name);
            break;

        case '5':
            std::cout << "[РЕДАКТИРОВАНИЕ] Введите новую зарплату: ";
            std::cin >> salary;
            employee.setSalary(salary);
            break;
        
        default:
            right = false;
            break;
        }
        if (term_set())
            term_reset();
        usleep(SLEEP_WAIT);
        if (right)
            menu_list[2].printer();
    }
    term_reset();
}
