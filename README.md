# Operating Systems project

Producer creates three child processes and pauses. First process (consumer_input) reads data from the selected source and forwards it to consumer_processing via queue. Second consumer (consumer_processing) reads data and convert it to hexadecimal form. Then send it to consumer_output via file. Third consumer (consumer_output) prints data on diagnostic output stream.

## Requirements
Unix system e.g Ubuntu

## Compiling (gcc required)
```bash
./compile.sh
```

## Executable files
All executable files can be found in out directory.

## Signals sent to children
SIGINT - pause program
SIGCONT - resume program
SIGQUIT - close program

Those signals can be changed in utils/variables.h file
