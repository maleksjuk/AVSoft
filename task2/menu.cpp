#include "company.hpp"

Menu::Menu(std::string _title){
    title = _title;
}

std::string Menu::getTitle(){
    return title;
}

void Menu::addAction(char c, std::string action)
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
    // menu.addAction('b', "отменить последнее изменение");
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

void main_menu(std::vector<Department> *company, std::vector<Menu> &menu_list)
{
    bool    right;
    bool    change;
    char    cmd;
    int     i;
    std::string  name;

    if (term_set())
        term_reset();
    menu_list[0].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        change = false;

        switch (cmd)
        {
        case 'x':
            return ;
        
        case 'p':
            print_company(*company);
            break;
        
        case 'c':
            std::cout << "[ВЫБОР] ВЫБЕРИТЕ ПОДРАЗДЕЛЕНИЕ" << std::endl;
            i = 1;
            for (auto &dep : *company)
                std::cout << i++ << " - " << dep.getName() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= (*company).size())
                menu_department(company, menu_list, i - 1);
            else
                error_msg("Главное меню", "Неверный номер");
            break;
        
        case 'a':
            std::cout << "СОЗДАНИЕ НОВОГО ПОДРАЗДЕЛЕНИЯ\n" << "Введите название: ";
            std::getline(std::cin, name);
            add_department(*company, name);
            change = true;
            break;
        
        case 'r':
            std::cout << "[УДАЛЕНИЕ] ВЫБЕРИТЕ ПОДРАЗДЕЛЕНИЕ" << std::endl;
            i = 1;
            for (auto &dep : *company)
                std::cout << i++ << " - " << dep.getName() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= (*company).size())
                (*company).erase((*company).begin() + i - 1);
            else
                error_msg("Главное меню", "Неверный номер");
            change = true;
            break;

        // case 'b':
        //     if (history.size() > 0)
        //     {
        //         *company = history.back();
        //         history.pop_back();
        //     }
        //     break;
        
        default:
            right = false;
            break;
        }

        if (term_set())
            term_reset();
        // if (change)
        // {
        //     history.push_back(*company);
        //     if (history.size() > HISTORY_SIZE)
        //         history.pop_front();
        // }
        if (right)
        {
            usleep(SLEEP_WAIT);
            menu_list[0].printer();
        }
    }
    term_reset();
}

void menu_department(std::vector<Department> *company, std::vector<Menu> &menu_list, int id)
{
    bool    right;
    bool    change;
    char    cmd;
    int     i;
    std::string  name;
    std::string  surname;
    std::string  middleName;
    std::string  function;
    int     salary;

    Department &department = (*company)[id];

    if (term_set())
        term_reset();
    menu_list[1].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        change = false;
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
            change = true;
            break;
        
        case 'c':
            std::cout << "[ВЫБОР] ВЫБЕРИТЕ СОТРУДНИКА" << std::endl;
            i = 1;
            for (auto &empl : department.getEmployment())
                std::cout << i++ << " - " << empl.getFIO() << std::endl;
            std::cout << "Введите номер: ";
            std::cin >> i;
            if (i > 0 && i <= department.getEmployment().size())
                menu_employee(company, department, menu_list, i - 1);
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
            change = true;
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
        // if (change)
        // {
        //     history.push_back(*company);
        //     if (history.size() > HISTORY_SIZE)
        //         history.pop_front();
        // }
        if (right)
        {
            usleep(SLEEP_WAIT);
            menu_list[1].printer();
        }
    }
    term_reset();
}

std::string get_new_value(std::string field, std::string old_value)
{
    std::string name;

    std::cout << "[РЕДАКТИРОВАНИЕ] " << field << std::endl;
    std::cout << "Старое значение: " << old_value << std::endl;
    std::cout << "Введите новое значение: ";
    std::getline(std::cin, name);
    return name;
}

void menu_employee(std::vector<Department> *company, Department &department, std::vector<Menu> &menu_list, int id)
{
    bool    right;
    bool    change;
    char    cmd;
    int     salary;
    std::string  name;

    Employee employee = department.getEmployment()[id];

    if (term_set())
        term_reset();
    menu_list[2].printer();

    while (read(STDIN_FILENO, &cmd, 1))
    {
        term_reset();
        right = true;
        change = false;
        switch (cmd)
        {
        case 'x':
            return ;
        case 'p':
            employee.printer();
            break;
        case '1':
            name = get_new_value("Фамилия", employee.getSurname());
            change = true;
            break;
        case '2':
            name = get_new_value("Имя", employee.getName());
            change = true;
            break;
        case '3':
            name = get_new_value("Отчество", employee.getMiddleName());
            change = true;
            break;
        case '4':
            name = get_new_value("Должность", employee.getFunction());
            change = true;
            break;
        case '5':
            name = get_new_value("Заработная плата", std::to_string(employee.getSalary()));
            change = true;
            break;
        default:
            right = false;
            break;
        }
        if (term_set())
            term_reset();
        // if (change)
        // {
        //     history.push_back(*company);
        //     if (history.size() > HISTORY_SIZE)
        //         history.pop_front();
        // }
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
