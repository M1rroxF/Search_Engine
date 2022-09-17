# Search Server V2

### Description
This is a simple search engine 
for adding it to larger projects.

### How to install
You have to fulfill several conditions
* cxx 17+
* gcc compiler

You should download project and compile them

Create build folder in project folder
```text
$ mkdir build
$ cd build
```

Build project with CMake
```text
$ cmake ..
$ cmake --build . --config Release --target SearchEngine
```

run once project 
```text
$ ./Release/SearchEngine
```

then enter the data in .json files
* config.json - to configure the search
* requests.json - for making requests

#### Examples json files
config.json
```json
{
  "config": {
    "name": "Searcher",
    "version": "2",
    "max_responses": 5
  },
  "files": [
    "../your folder/your file path001",
    "../your folder/your file path002",
    "../your folder/your file path003"
  ]
}
```

requests.json
```json
{
  "requests": [
    "your request1",
    "your request2"
  ]
}
```
After that run project, 
the answers will be written 
to the answers.json file

### Tests
This project uses Google tests.

to test the project, compile the executable: "tests"

for example
```text
$ mkdir test_search_engine
$ cd test_search_engine
$ cmake ..
$ cmake --build . --config Release --target tests
```

and run compiled file

### Libraries
* nlohmann json | https://github.com/nlohmann/json
* gtest | https://github.com/google/googletest