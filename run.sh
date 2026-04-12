#!/bin/bash

echo "Checking environment..."

if [ -z "$DB_HOST" ] || [ -z "$DB_USER" ] || [ -z "$DB_PASS" ]; then
  echo "Environment variables not set!"
  echo "Please set DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT"
  exit 1
fi

echo "Compiling..."

g++ main.cpp core/*.cpp data/*.cpp models/*.cpp database/*.cpp ui/*.cpp auth/*.cpp utils/*.cpp -o bank -lmysqlclient

echo "Running..."

./bank