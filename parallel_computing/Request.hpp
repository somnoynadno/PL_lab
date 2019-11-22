#ifndef Request_hpp
#define Request_hpp

#include <stdio.h>

using namespace std;

class Request{
public:
    Request();
    Request(int class_number, int priority);
    virtual ~Request();

    int get_class_number() const;
    int get_priority() const;

    friend bool operator < (const Request& lhs, const Request& rhs);
    friend bool operator > (const Request& lhs, const Request& rhs);

private:
    int class_number;
    int priority;
};

#endif /* Request_hpp */