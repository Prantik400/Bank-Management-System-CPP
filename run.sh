#!/bin/bash

echo "Loading environment variables..."

if [ -f .env ]; then
  export $(grep -v '^#' .env | xargs)
else
  echo ".env file not found!"
  exit 1
fi

echo "Compiling..."

g++ main.cpp core/*.cpp data/*.cpp models/*.cpp database/*.cpp ui/*.cpp auth/*.cpp utils/*.cpp -o bank -lmysqlclient

echo "Running..."

./bank