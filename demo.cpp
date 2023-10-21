#include <any>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <my_json/core.hpp>

using namespace std;
using namespace MyJson;
namespace Hehe {
    DEF_DATA_CLASS(Person, (unsigned short) age, (std::string) name,
                   (std::vector<int>) scores);
}
int main() {
using namespace Hehe;
    list<Person> container0{{24, R"(alice)", {3,  4,   89}},
                            {17, R"(bob)",   {42}},
                            {18, R"(chaos)", {37, 107, 109, 10007}}};
    Json json0{std::move(container0)};
    cout << json0 << endl;
    // [{"age":24,"name":"alice","scores":[3,4,89]},{"age":17,"name":"bob","scores":[42]},{"age":18,"name":"chaos","scores":[37,107,109,10007]}]
    // STL container, JSON_DATA_CLASS serialized to Json

    auto container1 = std::move(json0).to_type<vector<Person>>().value();


    container1.emplace_back(Person{13, "danny", vector{1, 2, 3}});
    cout << Json{container1} << endl;
    Json json{list<Person>{{24, R"(alice)", {3,  4,   89}},
                           {17, R"(bob)",   {42}},
                           {18, R"(chaos)", {37, 107, 109, 10007}}}};
    json.as_type<Array>()->get().emplace_back(
            Person{13, "danny", vector{1, 2, 3}});
    cout << json << endl;
    auto container2 = std::move(json).to_type<vector<Person>>().value();
    cout << json << endl;
    for (auto &p: container2) {
        cout << p.name << " aged " << p.age << " with scores ";
        std::copy(p.scores.begin(), p.scores.end(),
                  ostream_iterator<int>(cout, ", ")),
                cout << endl;
    }

    filesystem::path file_path = "test.json";
    fstream file;
    file.open(file_path, std::ios::in);
    Json json2 = Json::from_istream(file).value();
    file.close();

    auto &json2_as_array = json2.as_type<Array>()->get();
    for (auto &node: json2_as_array) {
        auto &obj = node.as_type<Object>()->get();
        auto &scores = obj.at("scores").as_type<Array>()->get();
        for (auto &s: scores)
            ++s.as_type<Integer>()->get();
    }
    cout << json2;
    file.open(file_path, ios::out | ios::trunc);
    file.close();
    file.open(file_path, ios::out | ios::app); // Open in append mode
    file << json2;
    file.close();
//    getchar();
}
