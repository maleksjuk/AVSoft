#include "company.hpp"

vector<Department> parser_company()
{
    vector<Department> company;
    string department_name;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(XML_FILE);

    if (!result)
    {
        std::cout << "XML [" << XML_FILE << "] parsed with errors" << endl;
        return company;
    }

    for (pugi::xml_node department_iter : doc.child("departments").children("department"))
    {
        department_name = department_iter.attribute("name").as_string();
        Department department(department_name);

        for (pugi::xml_node node : department_iter.child("employments").children("employment"))
            department.addEmployee(
                node.child("surname").child_value(),
                node.child("name").child_value(),
                node.child("middleName").child_value(),
                node.child("function").child_value(),
                node.child("salary").text().as_int()
            );
        company.push_back(department);
    }

    return company;
}
