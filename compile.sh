#!/bin/bash

mkdir -p out
gcc -o out/exec.out producer.c consumers/consumer_input.c consumers/consumer_processing.c consumers/consumer_output.c utils/queue.c utils/semaphore.c utils/pids.c utils/signals.c
