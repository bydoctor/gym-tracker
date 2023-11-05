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
    double bmr{0};
    double bmi{0};
    double neck{0};
    double waist{0};
    double hip{0};
    double fat_percentage{0};

public:
    Person(std::string fullname_val = "", size_t gender_val = 0, size_t age_val = 0, double height_val = 0.0, double weight_val = 0.0, double neck_val = 0.0, double waist_val = 0.0, double hip_val = 0.0) : fullname{fullname_val}, gender{gender_val}, age{age_val}, height{height_val}, weight{weight_val}, neck{neck_val}, waist{waist_val}, hip{hip_val}
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

    void set_neck(double s_neck)
    {
        neck = s_neck;
        calculations();
    }

    double get_neck() { return neck; }

    void set_waist(double s_waist)
    {
        waist = s_waist;
        calculations();
    }

    double get_waist() { return waist; }

    void set_hip(double s_hip)
    {
        hip = s_hip;
        calculations();
    }

    double get_hip() { return hip; }

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

    const double fat_percentage_calculation(size_t, double, double, double, double);

    double get_fat_percentage() { return fat_percentage; }

    void calculations()
    {
        bmr = bmr_calculation(gender, age, height, weight);
        bmi = bmi_calculation(height, weight);
        fat_percentage = fat_percentage_calculation(gender, height, neck, waist, hip);
    }
};

#endif