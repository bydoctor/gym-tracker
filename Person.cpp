#include <iostream>
#include <cmath>
#include "Person.h"
#include "VariadicTable.h"
#include <vector>
std::vector<Person> records;
static size_t ID{0};

// prototypes
Person *findPersonById(int);
//
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

size_t gender_check(size_t &variable)
{
    std::cin >> variable;
    while (variable != 1 && variable != 2)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Wrong choice , please enter 1 or 2 : ";
        std::cin >> variable;
    }
    return variable;
}

void create_person()
{

    std::string fullname{};
    size_t age{};
    size_t gender{};
    double height{};
    double weight{};
    double neck{};
    double waist{};
    double hip{};

    std::cin.get();

    std::cout << "Please enter the Fullname : " << std::endl;
    std::getline(std::cin, fullname);

    std::cout << "Please enter your gender (Male=1,Female=2): " << std::endl;
    gender = gender_check(gender);

    std::cout << "Please enter the age : " << std::endl;
    input_check(std::cin >> age, age);

    std::cout << "Please enter the height (cm): " << std::endl;
    input_check(std::cin >> height, height);

    std::cout << "Please enter the weight (kg): " << std::endl;
    input_check(std::cin >> weight, weight);

    std::cout << "Please enter the neck circumference ( Widest - cm ) : " << std::endl;
    input_check(std::cin >> neck, neck);

    std::cout << "Please enter the waist circumference (Thinnest - cm ): " << std::endl;
    input_check(std::cin >> waist, waist);

    std::cout << "Please enter the hip circumference ( Widest - cm ): " << std::endl;
    input_check(std::cin >> hip, hip);

    // Person create
    Person newPerson{fullname, gender, age, height, weight, neck, waist, hip};

    newPerson.set_id(ID);
    increase_ID();
    records.push_back(newPerson);

    std::cout << "\nPerson created" << std::endl;
    std::cout << "\n---------Person Info----------" << std::endl;
    std::cout << "Fullname : " << newPerson.get_fullname() << std::endl;
    std::cout << "Gender : " << newPerson.get_gender() << std::endl;
    std::cout << "Age      : " << newPerson.get_age() << std::endl;
    std::cout << "Height   : " << newPerson.get_height() << std::endl;
    std::cout << "Weight   : " << newPerson.get_weight() << std::endl;
    std::cout << "Neck     : " << newPerson.get_neck() << std::endl;
    std::cout << "Waist    : " << newPerson.get_waist() << std::endl;
    std::cout << "Hip      : " << newPerson.get_hip() << std::endl;
    std::cout << "\n";
}

void view_person(Person &p)
{
    VariadicTable<size_t, std::string, std::string, int, double, double, double, double, double> vt({"ID", "Name", "Gender",
                                                                                                     "Age",
                                                                                                     "Height", "Weight", "Neck", "Waist", "Hip"},
                                                                                                    10);

    vt.addRow(p.get_id(), p.get_fullname(), p.get_gender(), p.get_age(), p.get_height(), p.get_weight(), p.get_neck(), p.get_waist(), p.get_hip());

    vt.print(std::cout);
    std::cout << "\n";
}

void display_calorie_need(double bmr)
{
    std::cout << "-- Daily Calorie (kcal) Need by Activity Level -- \n";

    // Daily Calorie Need by Activity Level
    VariadicTable<double, double, double, double, double> daily_calorie({"Sedentary", "Lightly (1-3 Days/Week)", "Moderately (3-5 Days/ Week)", "Very Active (6-7 Days/Week)", "Extra Active (Hard Exercise & Job)"}, 10);

    daily_calorie.addRow((bmr * 1.2), (bmr * 1.1375), (bmr * 1.55), (bmr * 1.725), (bmr * 1.9));

    daily_calorie.print(std::cout);
    std::cout << "\n";
}

void view_calculations_for_person(Person &p)
{
    std::cout << "\n"
              << std::endl;

    double bmr{p.get_bmr()};

    VariadicTable<size_t, std::string, double, double, double>
        vt({"ID", "Name", "BMR (Basal Metabolic Rate)", "BMI (Body Mass Index)", "Fat Percentage %"}, 10);

    vt.addRow(p.get_id(), p.get_fullname(), bmr, p.get_bmi(), p.get_fat_percentage());

    vt.print(std::cout);
    std::cout << "\n\n";

    display_calorie_need(bmr);
}

void view_person_list()
{

    VariadicTable<size_t, std::string, std::string, int, double, double, double, double, double> vt({"ID", "Name", "Gender", "Age", "Height", "Weight", "Neck", "Waist", "Hip"}, 10);

    if (records.size())
    {
        for (auto p : records)
        {
            vt.addRow(p.get_id(), p.get_fullname(), p.get_gender(), p.get_age(), p.get_height(), p.get_weight(), p.get_neck(), p.get_waist(), p.get_hip());
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

void view_calculations()
{
    view_person_list();

    if (records.size() > 0)
    {
        size_t id{};
        std::cout << "\nPlease Enter the id number of the person you want to see calculations : " << std::endl;
        input_check(std::cin >> id, id);
        Person *thisPerson = findPersonById(id);
        if (!thisPerson->get_fullname().empty())
        {

            view_calculations_for_person(*thisPerson);
        }
        else
        {
            delete thisPerson;
        }
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
        size_t gender{};
        std::cout << "\nEnter the new value of gender (Male=1, Female=2) :" << std::endl;
        thisPerson.set_gender(gender_check(gender));
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 3:
    {
        size_t age{};
        std::cout << "\nEnter the new value of age :" << std::endl;
        input_check(std::cin >> age, age);
        thisPerson.set_age(age);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 4:
    {
        double height{};
        std::cout << "\nEnter the new value of height :" << std::endl;
        input_check(std::cin >> height, height);
        thisPerson.set_height(height);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 5:
    {
        double weight{};
        std::cout << "\nEnter the new value of weight :" << std::endl;
        input_check(std::cin >> weight, weight);
        thisPerson.set_weight(weight);
        update_field(thisPerson, update_selection_handler());
        break;
    }

    case 6:
    {
        double neck{};
        std::cout << "\nEnter the new value of neck :" << std::endl;
        input_check(std::cin >> neck, neck);
        thisPerson.set_neck(neck);
        update_field(thisPerson, update_selection_handler());
        break;
    }

    case 7:
    {
        double waist{};
        std::cout << "\nEnter the new value of waist :" << std::endl;
        input_check(std::cin >> waist, waist);
        thisPerson.set_waist(waist);
        update_field(thisPerson, update_selection_handler());
        break;
    }

    case 8:
    {
        double hip{};
        std::cout << "\nEnter the new value of hip :" << std::endl;
        input_check(std::cin >> hip, hip);
        thisPerson.set_hip(hip);
        update_field(thisPerson, update_selection_handler());
        break;
    }
    case 9:
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
    std::cout << "2 - Edit Gender " << std::endl;
    std::cout << "3 - Edit Age " << std::endl;
    std::cout << "4 - Edit Height " << std::endl;
    std::cout << "5 - Edit Weight " << std::endl;
    std::cout << "6 - Edit Neck " << std::endl;
    std::cout << "7 - Edit Waist " << std::endl;
    std::cout << "8 - Edit Hip " << std::endl;
    std::cout << "9- Exit Update Menu " << std::endl;
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
        if (!thisPerson->get_fullname().empty())
        {
            view_person(*thisPerson);
            int selection = update_selection_handler();
            update_field(*thisPerson, selection);
        }
        else
        {
            delete thisPerson;
        }
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

const double Person::bmr_calculation(size_t gender, size_t age, size_t height, size_t weight)
{
    if (gender == 1)
    {
        return 66.5 + (13.75 * weight) + (5.003 * height) - (6.75 * age);
    }
    else if (gender == 2)
    {
        return 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age);
    }
    else
    {
        return 0.0;
    }
}
double set_digits_after_decimal_point(double value)
{
    double multiplier = 100.0;
    // multiplier and static_cast operation for set the value as a 2 digits after decimal point
    return static_cast<double>(static_cast<int>(value * multiplier)) / multiplier;
}

const double Person::bmi_calculation(double height, double weight)
{
    double value = (weight / ((height / 100) * (height / 100)));
    return set_digits_after_decimal_point(value);
}

const double Person::fat_percentage_calculation(size_t gender, double height, double neck, double waist, double hip)
{
    double value{0.0};
    // us navy fat percentage method

    if (gender == 1) // if male
    {
        value = 495 / (1.0324 - 0.19077 * log10(waist - neck) + 0.15456 * log10(height)) - 450;
        return set_digits_after_decimal_point(value);
    }
    else if (gender == 2) // if female
    {
        value = 495 / (1.29579 - 0.35004 * log10(waist + hip - neck) + 0.22100 * log10(height)) - 450;
        return set_digits_after_decimal_point(value);
    }
    else
    {
        return 0.0;
    }
}
