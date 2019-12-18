#!/bin/bash

count=0
time_prev=0
time_present=0

function no_ctrlc()
{
    echo -e "\nAre you sure to kill this programm? (yes/no)"
    read xx
    if [ $xx = 'yes' ]; then
	    echo -e '\n\n Have a nice day! Bye \n\n'
	    exit
    else
	echo "Programm is still running!"
	fi
}

function ignore_sigusr1()
{
echo "Ignoring SIGUSR1"
}

function time_usr2()
{
time_prev=$time_present
time_present=$(($(date +%s%N)/1000000))
let count++
if [[ count -gt 1 ]]; then
time=$(($time_present-$time_prev))
time_sec=$(($time/1000))
time_msec=$(($time % 1000))

echo -e "\n Różnica między kolejnymi SIGUSR2 wynosi $time_sec.$time_msec seconds"
fi
}

trap no_ctrlc SIGINT
trap ignore_sigusr1 USR1
trap time_usr2 USR2
while true
do
   true
done
