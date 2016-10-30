#!/bin/sh
createdb `whoami`
psql -d `whoami` -f create_tables.sql
psql -d `whoami` -f insert_data.sql