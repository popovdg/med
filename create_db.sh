#!/bin/sh
createdb `whoami`
psql -d `whoami` -f db.sql
psql -d `whoami` -f insert.sql