#include <iostream>
#include <memory>
using namespace std;

struct ToString {
  virtual string toString() const = 0;
};

class Person : public ToString {
public:
    Person(const string& name) : name(name) {
    }

    string toString() const {
        return string("People with name: ") + name;
    }

    const string& getName() const {
        return name;
    }

private:
    string name;
};

class Appointment : public ToString {
public:
    Appointment(const string& name) : people(name){
    }

    string toString() const {
        return string("Appointment with ") + people.getName();
    }

private:
    Person people;
};

Appointment* meet(const string& name){
  return new Appointment(name);
}


template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const ToString* __s) {

    if (!__s){
      __out.setstate(ios_base::badbit);

    } else {

      const _CharT* str = __s -> toString().c_str();
      __ostream_insert(__out, str, static_cast<streamsize>(_Traits::length(str)));
    }
    return __out;
}


int main() {
  Appointment* appointment = meet("Joe");
  cout << appointment << endl;
  delete appointment;

  auto_ptr<Appointment> meeting( meet("Jack") );
  cout << meeting.get() << endl;

  return 0;
}