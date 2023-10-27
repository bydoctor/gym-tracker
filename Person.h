#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

void create_person();
void view_person_list();
void delete_person();
void update_person();

class Person
{

private:
    std::string fullname;
    size_t age{};
    size_t thisId;
    double height{};
    double weight{};

public:
    void set_fullname(std::string s) { fullname = s; }
    std::string get_fullname() { return fullname; }

    void set_age(size_t s_age) { age = s_age; }
    size_t get_age() { return age; }

    void set_height(double s_height) { height = s_height; }
    double get_height() { return height; }

    void set_weight(double s_weight) { weight = s_weight; }
    double get_weight() { return weight; }

    void set_id(size_t s_id) { thisId = s_id; }
    size_t get_id() { return thisId; }
};

#endif