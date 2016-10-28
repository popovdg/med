#!/bin/sh
createdb `whoami`
psql -d `whoami` -f db.sql
