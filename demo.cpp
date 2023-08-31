#include <any>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <json/core.hpp>

// DEF_DATA_CLASS(fk, (int)a, (long)fuck_rust,
//                (DEF_DATA_CLASS(mama, (float)c, (double)d))kfc);
using namespace std;
using namespace json;
using namespace reflect;

DEF_DATA_CLASS(Person, (unsigned short) age, (std::string) name,
               (std::vector<int>) socres);
int main() {
  std::vector<Person> ls1{{24, R"(dont say "hello world")", {3, 4, 89}},
                          {17, R"(alice)", {42}},
                          {18, R"(B/o\b)", {37, 107, 109, 10007}}};
  Json j{std::move(ls1)};
  // stl, JSON_DATA_CLASS serialized to Json

  string s{j.to_json_text()};
  cout << s << endl;
  // Json to serialized json-formatted string
  // output:[{"age":24,"name":"dont say \"hello
  // world\"","socres":[3,4,89]},{"age":17,"name":"alice","socres":[42]},{"age":18,"name":"B\/o\\b","socres":[37,107,109,10007]}]

  auto ls2 =
      Json::from_json_text(s).value().to_type<std::vector<Person>>().value();
  for (auto &p : ls2) {
    cout <<  p.name << ":" << endl;
    cout << " - age=" << p.age << endl;
    cout << " - scores=";
    std::copy(p.socres.begin(), p.socres.end(),
              std::ostream_iterator<int>(cout, ", "));
    cout << endl;
  }
  //  Json text deserialized to stl/JSON_DATA_CLASS
  // ouput:
  // dont say "hello world":
  // - age=24
  // - scores=3, 4, 89,
  // alice:
  // - age=17
  // - scores=42,
  // B/o\b:
  // - age=18
  // - scores=37, 107, 109, 10007,
  auto &as_arr = j.as_type<Array>()->get();
  (as_arr[1].as_type<Object>()->get())["age"] = 18;
  // json node modification

  auto new_alice = as_arr[1].to_type<Person>().value();
  //  Json convert to stl/JSON_DATA_CLASS

  cout << endl << "new alice:" << endl;
  cout << "age=" << new_alice.age << endl;
  cout << "name=" << new_alice.name << endl;
  cout << "scores=";
  std::copy(new_alice.socres.begin(), new_alice.socres.end(),
            std::ostream_iterator<int>(cout, ", "));
}
