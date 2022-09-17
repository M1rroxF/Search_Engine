# Search Server V2

### Description
This is a simple search engine 
for adding it to larger projects.

### How to install
You have to fulfill several conditions
* cxx 17+
* gcc compiler

You should download project and compile them

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
After that, the answers will be written 
to the answers.json file

### Tests
This project uses Google tests

### Libraries
* nlohmann json | https://github.com/nlohmann/json