
#include <iostream>

struct my_class_t {
    int a = 0;
};

void init(my_class_t& t, std::ostream& out, size_t position) {
  std::cout << "my_class_t" << std::endl;
  t.a = 21;
}

void execute(my_class_t& t, std::ostream& out, size_t position) {
  std::cout << "my_class_t execute " << t.a << std::endl;

}
