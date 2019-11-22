#include "Request.hpp"

bool operator < (const Request& lhs, const Request& rhs){
    return lhs.get_priority() < rhs.get_priority();
}

bool operator > (const Request& lhs, const Request& rhs){
    return lhs.get_priority() > rhs.get_priority();
}

Request::Request(){
}

Request::Request(int class_number, int priority):class_number(class_number), priority(priority){
}

Request::~Request(){
}

int Request::get_class_number() const{
    return class_number;
}

int Request::get_priority() const{
    return priority;
}
