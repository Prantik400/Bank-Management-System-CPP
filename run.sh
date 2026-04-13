#!/bin/bash

echo "Loading environment variables..."

if [ -f .env ]; then
  set -o allexport
  source .env
  set +o allexport
else
  echo ".env file not found!"
  echo "Please create .env file (see .env.example)"
  exit 1
fi

echo "Compiling..."
g++ main.cpp core/*.cpp data/*.cpp models/*.cpp database/*.cpp ui/*.cpp auth/*.cpp utils/*.cpp -o bank -lmysqlclient

echo "Running..."
./bank