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

template<typename _CharT, typename _Traits, typename _ToStringDescendant>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const auto_ptr<_ToStringDescendant> __s) {

    if (!__s.get()){
      __out.setstate(ios_base::badbit);

    } else {

      const _CharT* str = __s.get() -> toString().c_str();
      __ostream_insert(__out, str, static_cast<streamsize>(_Traits::length(str)));
    }
    return __out;
}


int main() {
  Appointment* appointment = meet("Joe");
  cout << appointment << endl;
  delete appointment;
  /*
  src/Main.cpp:78:10: warning: deleting object of polymorphic class type ‘Appointment’ which has non-virtual destructor might cause undefined behaviour [-Wdelete-non-virtual-dtor]
     delete appointment;
            ^
  */

  auto_ptr<Appointment> meeting( meet("Jack") );
  cout << meeting << endl;

  //auto_ptr<int> m( new int(1) );
  //cout << m << endl;
  /*
  src/Main.cpp: In instantiation of ‘std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>&, std::auto_ptr<_ToStringDescendant>) [with _CharT = char; _Traits = std::char_traits<char>; _ToStringDescendant = int]’:
  src/Main.cpp:89:11:   required from here
  src/Main.cpp:68:57: error: request for member ‘toString’ in ‘* __s.std::auto_ptr<_Tp>::get<int>()’, which is of non-class type ‘std::auto_ptr<int>::element_type {aka int}’
         const _CharT* str = __s.get() -> toString().c_str();
                                                           ^
  ninja: build stopped: subcommand failed.
  */

  return 0;
}