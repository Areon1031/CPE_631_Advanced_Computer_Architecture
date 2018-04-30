#!/bin/bash

kill $(ps aux | grep '[s]copeForever' | awk '{print $2}')
