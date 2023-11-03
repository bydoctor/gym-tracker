#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

void create_person();
void view_person_list();
void view_calculations();
void delete_person();
void update_person();

class Person
{

private:
    std::string fullname;
    size_t gender{};
    size_t age{};
    size_t thisId;
    double height{};
    double weight{};
    double bmr{};
    double bmi{};

public:
    Person() : fullname{"None"}, gender{0}, age{0}, height{0}, weight{0} {}
    Person(std::string fullname_val, size_t gender_val, size_t age_val, double height_val, double weight_val) : fullname{fullname_val}, gender{gender_val}, age{age_val}, height{height_val}, weight{weight_val}
    {
        calculations();
    }
    void set_fullname(std::string s) { fullname = s; }
    std::string get_fullname() { return fullname; }

    void set_age(size_t s_age)
    {
        age = s_age;
        calculations();
    }
    size_t get_age() { return age; }

    void set_height(double s_height)
    {
        height = s_height;
        calculations();
    }
    double get_height() { return height; }

    void set_weight(double s_weight)
    {
        weight = s_weight;
        calculations();
    }
    double get_weight() { return weight; }

    void set_id(size_t s_id) { thisId = s_id; }
    size_t get_id() { return thisId; }

    void set_gender(size_t s_gender)
    {
        gender = s_gender;
        calculations();
    }
    std::string get_gender()
    {
        if (gender == 1)
        {
            return std::string("Male");
        }
        else if (gender == 2)
        {
            return std::string("Female");
        }
        else
        {
            return std::string("None");
        }
    }

    const double bmr_calculation(size_t, size_t, size_t, size_t);
    double get_bmr() { return bmr; }

    const double bmi_calculation(double, double);
    double get_bmi() { return bmi; }

    void calculations()
    {
        bmr = bmr_calculation(gender, age, height, weight);
        bmi = bmi_calculation(height, weight);
    }
};

#endif