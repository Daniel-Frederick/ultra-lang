cmake_minimum_required(VERSION 3.20)
project(ultra)

set(HEADERS
  include/tokenizer.hpp
  include/parser.hpp
)

set(SOURCES 
  src/main.cpp
  src/tokenizer.cpp
  src/parser.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
