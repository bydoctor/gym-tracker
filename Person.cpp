#include <iostream>
#include "Person.h"
#include "VariadicTable.h"
#include <vector>
std::vector<Person> records;
static size_t ID{0};

void increase_ID()
{
    ID++;
}
void decrease_ID()
{
    ID--;
}
// prototypes
int update_selection_handler();

template <typename T>

void input_check(std::istream &stream, T &variable)
{
    while (!(stream))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\nWrong type please reenter : " << std::endl;
        std::cin >> variable;
    }
}

void create_person()
{

    std::string fullname{};
    size_t age{};
    double height{};
    double weight{};

    std::cin.get();

    std::cout << "Please enter the Fullname : " << std::endl;
    std::getline(std::cin, fullname);

    std::cout << "Please enter the age : " << std::endl;
    input_check(std::cin >> age, age);

    std::cout << "Please enter the height (cm): " << std::endl;
    input_check(std::cin >> height, height);

    std::cout << "Please enter the weight (kg): " << std::endl;
    input_check(std::cin >> weight, weight);

    // Person create
    Person newPerson{fullname, age, height, weight};

    newPerson.set_id(ID);
    increase_ID();
    records.push_back(newPerson);

    std::cout << "\nPerson created" << std::endl;
    std::cout << "\n---------Person Info----------" << std::endl;
    std::cout << "Fullname : " << newPerson.get_fullname() << std::endl;
    std::cout << "Age      : " << newPerson.get_age() << std::endl;
    std::cout << "Height   : " << newPerson.get_height() << std::endl;
    std::cout << "Weight   : " << newPerson.get_weight() << std::endl;
    std::cout << "\n";
}

void view_person(Person &p)
{
    VariadicTable<size_t, std::string, int, double, double> vt({"ID", "Name", "Age", "Height", "Weight"}, 10);

    vt.addRow(p.get_id(), p.get_fullname(), p.get_age(), p.get_height(), p.get_weight());

    vt.print(std::cout);
    std::cout << "\n";
}

void view_person_list()
{

    VariadicTable<size_t, std::string, int, double, double> vt({"ID", "Name", "Age", "Height", "Weight"}, 10);

    if (records.size())
    {
        for (auto p : records)
        {
            vt.addRow(p.get_id(), p.get_fullname(), p.get_age(), p.get_height(), p.get_weight());
        }
        vt.print(std::cout);
        std::cout << "\n";
    }
    else
    {
        std::cout << "\n--- List is empty ---\n"
                  << std::endl;
    }
}

Person *findPersonById(int id)
{
    bool is_find{false};
    size_t index{};

    for (auto it = records.begin(); it != records.end(); ++it)
    {
        if (it->get_id() == id)
        {

            index = it - records.begin(); // it-records.begin() gives us a index of that element.
            is_find = true;
        }
    }
    if (!is_find)
    {
        std::cout << "\nPerson with ID " << id << " not found.\n"
                  << std::endl;
        Person *emptyPerson = new Person(); // Boş bir Person nesnesi oluşturulur

        return emptyPerson;
    }
    else
    {

        return &(records.at(index));
    }
}

void update_field(Person &thisPerson, int selection)
{

    switch (selection)
    {
    case 1:
    {
        std::string fullname{};
        std::cout << "\nEnter the new value of fullname :" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::getline(std::cin, fullname);
        thisPerson.set_fullname(fullname);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 2:
    {
        size_t age{};
        std::cout << "\nEnter the new value of age :" << std::endl;
        input_check(std::cin >> age, age);
        thisPerson.set_age(age);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 3:
    {
        double height{};
        std::cout << "\nEnter the new value of height :" << std::endl;
        input_check(std::cin >> height, height);
        thisPerson.set_height(height);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 4:
    {
        double weight{};
        std::cout << "\nEnter the new value of weight :" << std::endl;
        input_check(std::cin >> weight, weight);
        thisPerson.set_weight(weight);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 5:
    {
        break;
    }

    default:
        std::cout << "\nSorry. Wrong selection. Try again !\n"
                  << std::endl;
    }
}

int update_selection_handler()
{
    int selection{};
    std::cout << "\n1 - Edit Fullname " << std::endl;
    std::cout << "2 - Edit Age " << std::endl;
    std::cout << "3 - Edit Height " << std::endl;
    std::cout << "4 - Edit Weight " << std::endl;
    std::cout << "5- Exit Update Menu " << std::endl;
    std::cout << "\nPlease select the field you want to change : " << std::endl;
    input_check(std::cin >> selection, selection);
    return selection;
}

void update_person()
{
    view_person_list();
    if (records.size() > 0)
    {
        size_t id{};
        std::cout << "\nPlease Enter the id number of the person you want to update : " << std::endl;
        input_check(std::cin >> id, id);
        Person *thisPerson = findPersonById(id);
        thisPerson->set_age(14);
        if (!thisPerson->get_fullname().empty())
        {
            view_person(*thisPerson);
        }
        else
        {
            delete thisPerson;
        }

        int selection = update_selection_handler();
        update_field(*thisPerson, selection);
    }
}

bool deletePersonByID(size_t &id)
{
    for (auto it = records.begin(); it != records.end(); ++it)
    {
        if (it->get_id() == id)
        {
            std::cout << "\n ---> "
                      << it->get_fullname() << " <--- deleted.\n"
                      << std::endl;
            records.erase(it);
            return true;
        }
    }
    std::cout << "\nPerson with ID " << id << " not found. Nothing removed.\n"
              << std::endl;
    return false;
}

void delete_person()
{
    view_person_list();
    if (records.size() > 0)
    {
        size_t id{};
        std::cout << "\nPlease Enter the id number of the person you want to delete : " << std::endl;
        input_check(std::cin >> id, id);
        deletePersonByID(id);
    }
}
