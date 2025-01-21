cmake_minimum_required(VERSION 3.20)
project(ultra)

set(SOURCES 
  src/main.cpp
  src/tokenizer.cpp
)

set(HEADERS
  include/tokenizer.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
