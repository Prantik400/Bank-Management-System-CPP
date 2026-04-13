#!/bin/bash

echo "Checking environment variables..."

if [ -z "$DB_HOST" ] || [ -z "$DB_USER" ] || [ -z "$DB_PASS" ] || [ -z "$DB_NAME" ] || [ -z "$DB_PORT" ]; then
    echo "Environment variables not set!"
    echo "Use .env file or create"
    exit 1
fi

echo "Environment variables loaded"

echo "Compiling..."
g++ main.cpp core/*.cpp data/*.cpp models/*.cpp database/*.cpp ui/*.cpp auth/*.cpp utils/*.cpp -o bank -lmysqlclient

echo "Running..."
./bank