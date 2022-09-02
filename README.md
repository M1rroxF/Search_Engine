# Search Server

### Description
This is a simple search engine 
for adding it to larger projects.

### How to install
You have to fulfill several conditions
* cxx 11 +
* gcc compiler

You should download project and in the 
place where the exe file will be created, 
you have to create json files
* config.json - to configure the search
* requests.json - for making requests
* answers.json - to output search data

### Examples json files

config.json
```json
{
  "config": {
    "name": "Searcher",
    "version": "1",
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

### Tests
This project uses Google tests

### Libraries
* nlohmann json | https://github.com/nlohmann/json