###  MyJson:利用静态反射的C++对象自动序列化库

[![Static Badge](https://img.shields.io/badge/license-MIT-blue?logo=git&logoColor=%20)]() [![Static Badge](https://img.shields.io/badge/C%2B%2B-17-green?logo=cplusplus&logoColor=blue)]() [![Static Badge](https://img.shields.io/badge/cmake-3.22%2B-green?logo=cmake&logoColor=deepskyblue)]() [![Static Badge](https://img.shields.io/badge/compiler-x86%20gcc%2011.3+-green?logo=compilerexplorer)]()[![Static Badge](https://img.shields.io/badge/compiler-x86%20MSVC%2019.29%2B-green?logo=compilerexplorer)]() 

---

这是一个面向现代`C++`的轻量级，可读性强的对象序列化方案，核心代码仅`700+`行

本序列化库使用的协议为`json`，通过宏实现了聚合体类型的简单静态反射（侵入式）`json::Json`对象和`DEF_DATA_CLASS`宏定义的类类型、所有`c++17 stl`容器（不包括`std::array`， 因为定长）（可嵌套）、所有基本数值类型之间的转换代码，都使用模板自动生成，并支持容器间的移动语义

使用上，使用`DEF_DATA_CLASS`，仅需几行代码就能实现对象到`json`文本的序列化/反序列化

#### Blog

代码设计：

.todo

【C++】Json序列化库(1)：  类型设计

【C++】Json序列化库(2) :序列化

【C++】Json序列化库(3) :反序列化

【C++】Json序列化库(4): 支持stl容器： 模板简化代码

【C++】Json序列化库(5): 聚合体自动序列化： 静态反射

#### Build 

修改`CMakeLists.txt`

仅保留

```cmake
set(CMAKE_CXX_STANDARD 17)
add_library(json_lib STATIC Json.cpp JsonParser.cpp)
target_include_directories(json_lib PUBLIC ./include)
```

即可使用`CMake`构建静态库:

```bash
mkdir build
cd build 
cmake .. 
make 
```

#### Features

.todo

#### Test

.todo

#### Usage

例子：一个自定义聚合类型`Person`的`vector`到`json`文本的序列化/反序列化

more: .todo

```c++
#include <json/core.hpp>
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
}
```



