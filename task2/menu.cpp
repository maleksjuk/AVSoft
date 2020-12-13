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
        << CLR_MAGENTA << getTitle() << CLR_RESET << std::endl;
    for (auto &action : actions)
        std::cout << action.first << " --> " << action.second << std::endl;
    std::cout
        << "^^^^^^^^^^^^^^^^^^^^\n" << std::endl;
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
    bool    right;
    char    cmd;
    string  name;
    int     i;

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
            break;
        
        case 'a':
            std::cout << "СОЗДАНИЕ НОВОГО ПОДРАЗДЕЛЕНИЯ\n" << "Введите название: ";
            std::getline(std::cin, name);
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
    bool    right;
    char    cmd;
    int     i;
    string  name;
    string  surname;
    string  middleName;
    string  function;
    int     salary;

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
            std::getline(std::cin, name);
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
            break;
        
        case 'a':
            std::cout << "ДОБАВЛЕНИЕ НОВОГО СОТРУДНИКА\n";
            std::cout << "Фамилия: ";
            std::getline(std::cin, surname);
            std::cout << "Имя: ";
            std::getline(std::cin, name);
            std::cout << "Отчество: ";
            std::getline(std::cin, middleName);
            std::cout << "Должность: ";
            std::getline(std::cin, function);
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

string get_new_value(string field, string old_value)
{
    string name;

    std::cout << "[РЕДАКТИРОВАНИЕ] " << field << std::endl;
    std::cout << "Старое значение: " << old_value << std::endl;
    std::cout << "Введите новое значение: ";
    std::getline(std::cin, name);
    return name;
}

void menu_employee(Department &department, vector<Menu> &menu_list, int id)
{
    bool    right;
    char    cmd;
    string  name;
    int     salary;

    Employee employee = department.getEmployment()[id];

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
            name = get_new_value("Фамилия", employee.getSurname());
            break;
        case '2':
            name = get_new_value("Имя", employee.getName());
            break;
        case '3':
            name = get_new_value("Отчество", employee.getMiddleName());
            break;
        case '4':
            name = get_new_value("Должность", employee.getFunction());
            break;
        case '5':
            name = get_new_value("Заработная плата", std::to_string(employee.getSalary()));
            break;
        default:
            right = false;
            break;
        }
        if (term_set())
            term_reset();
        if (right)
        {
            department.editEmployee(id, cmd, name);
            employee = department.getEmployment()[id];
            usleep(SLEEP_WAIT);
            menu_list[2].printer();
        }
    }
    term_reset();
}
