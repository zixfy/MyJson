###  MyJson: C++对象序列化库

[![Static Badge](https://img.shields.io/badge/license-MIT-blue?logo=git&logoColor=%20)]() [![Static Badge](https://img.shields.io/badge/C%2B%2B-17-green?logo=cplusplus&logoColor=blue)]() [![Static Badge](https://img.shields.io/badge/cmake-3.22%2B-green?logo=cmake&logoColor=deepskyblue)]() [![Static Badge](https://img.shields.io/badge/compiler-x86%20gcc%2011.3+-green?logo=compilerexplorer)]() [![Static Badge](https://img.shields.io/badge/compiler-x86%20MSVC%2019.29%2B-green?logo=compilerexplorer)]() 

---

#### Features

一个面向现代`C++`的轻量级对象序列化方案

本序列化库使用的协议为`Json`，支持以下类型到`Json`的序列化（反序列化）

1. `C++`基本数值类型、`nullptr_t/nullopt_t`(`Json null`)
2. `c++17 stl`容器（不包括定长的`std::array`）
3. 通过静态反射宏`DEF_DATA_CLASS`定义的聚合体
4. 以上类型的嵌套
	使用上，使用`DEF_DATA_CLASS`，仅需单行代码就能实现对象到`MyJson`文本的序列化/反序列化

`Json`对象到其他类型的转换全部支持移动语义以提高性能

`Json`对象转换到所保存的原生类型(`Array`,  `Integer`, `Boolean`, `Object`等)使用`Json::as_type<T>`

`Json`对象反序列化到其他类型使用`Json::to_type<T>`

`Json`数据实际中往往动态获取，`Json`对象内部使用`std::variant`多态，使用`std::optional<T>`作为`as_type/to_type`返回值类型，不使用异常

#### Usage

**基本：**

使用静态反射宏定义数据类型

```c++
#include <my_json/core.hpp> 
using namespace std;
using namespace MyJson;

DEF_DATA_CLASS(Person, (unsigned short)age, (std::string)name,
               (std::vector<int>)scores);
```

`list<Person>`到`Json`的序列化

```c++
list<Person> container0{{24, R"(alice)", {3, 4, 89}},
                        {17, R"(bob)", {42}},
                        {18, R"(chaos)", {37, 107, 109, 10007}}};
Json json{std::move(container0)};
cout << json << endl;
//[{"age":24,"name":"alice","scores":[3,4,89]},{"age":17,"name":"bob","scores":[42]},{"age":18,"name":"chaos","scores":[37,107,109,10007]}]
```

`Json`到`vector<Person>`的反序列化

```c++
auto container1 = std::move(json).to_type<vector<Person>>().value();
```

**更多用法：**

`Json`对象结构修改

```c++
Json json{list<Person>{{24, R"(alice)", {3, 4, 89}},
                       {17, R"(bob)", {42}},
                       {18, R"(chaos)", {37, 107, 109, 10007}}}};
json.as_type<Array>()->get().emplace_back(
    Person{13, "danny", vector{1, 2, 3}});
cout << json << endl;
//[{"age":24,"name":"alice","scores":[3,4,89]},{"age":17,"name":"bob","scores":[42]},{"age":18,"name":"chaos","scores":[37,107,109,10007]},{"age":13,"name":"danny","scores":[1,2,3]}]
```

从文件读取`Json`，修改并保存

```c++
filesystem::path file_path = "test.json";
fstream file;
file.open(file_path, std::ios::in);
Json json2 = Json::from_istream(file).value();
file.close();

auto &json2_as_array = json2.as_type<Array>()->get();
for (auto &node : json2_as_array) {
    auto &obj = node.as_type<Object>()->get();
    auto &scores = obj.at("scores").as_type<Array>()->get();
    for (auto &s : scores)
        ++s.as_type<Integer>()->get();
}
cout << json2;
file.open(file_path, ios::out | ios::trunc);
file.close();
file.open(file_path, ios::out | ios::app); // Open in append mode
file << json2;
file.close();
```

`test.json`：

```json
//before
[{"age":19,"name":"issac","scores":[31,32,33]},{"age":20,"name":"faery","scores":[22,-83]}]
//after
[{"age":19,"name":"issac","scores":[32,33,34]},{"age":20,"name":"faery","scores":[23,-82]}]
```

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

