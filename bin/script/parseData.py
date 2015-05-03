import os
import re
import sys
from datetime import datetime

sysToString = {1: 'grab', 2: 'voice'}
taskToOccurenceMap = {1: 0, 2: 0, 3: 0, 4: 0}
modeToOccurenceMap = {}

def make(dirpath):
    full_file_paths = get_filepaths(dirpath)

    # Create output file:
    outputFilename = get_output_filename(dirpath) 
    if (None == outputFilename):
        return
    output = open(outputFilename, 'wb')

    # Write the header row to the file
    output.write("System, User, Task, Task Occurence, Mode, Mode Occurence, Time (ms)\n") 

    full_file_paths.sort() # Sort files in ascending order
    for filename in full_file_paths: # Go over all files in working directory 
        print ('Parsing %s') % (filename)
        file = open(filename, 'r')
        
        (user, system, task, month, date, year, hour, minute, second) = get_file_params(filename)
        system = sysToString(system)
        taskToOccurenceMap[task] += 1

        for line in file.readlines():
            #print line 
            [mode, startTime, endTime, timeInterval] = parse_line(line)
            modeToOccurenceMap[mode] = modeToOccurenceMap.get(mode, 0) + 1
            lineList = [system, user, task, taskToOccurenceMap[task], mode, modeToOccurenceMap[mode], timeInterval]
            lineStr = ', '.join(str(x) for x in lineList)
            output.write(lineStr + "\n")
    output.close()

def parse_line(line):
    # line = mode startTime endTime timeInterval (time in float milisecond)
    tokens = line.split()
    tokens[1:] = map(float, tokens[1:])
    return tokens # [mode, startTime, endTime, timeInterval]

def get_output_filename(directory):
    # timestamp = month_day_year_hour_minute_second
    timestamp = datetime.now().strftime("%m_%d_%Y_%H_%M_%S")
    return "stats-" + timestamp + ".csv"

def get_file_params(full_file_path):
    # timestamp = month_day_year_hour_minute_second (e.g. 05_03_2015_12_03_22)
    # system = 1 | 2 (1: grab, 2: voice)
    # task = 1 | 2 | 3 | 4 (1/2/3: practice tasks, 4: final task)
    # user = 1 | 2 | 3 | ....
    # filename = user_[user]-sys_[system]-task_[task]-timestamp_[timestamp].txt 
    # (e.g. user_1-sys_2-task_3-timestamp_05_03_2015_12_03_22.txt)
    m = re.match(".*user_\D*(\d+)-sys_\D*(\d+)-task_\D*(\d+)-timestamp_\D*(\d+)_\D*(\d+)_\D*(\d+)_\D*(\d+)_\D*(\d+)_\D*(\d+)\.txt", 
        full_file_path)
    params = None
    if m:
        # (user, system, task, month, date, year, hour, minute, second)
        for i in range(1, 10):
            params.append(int(m.group(i)))
    return params

def get_filepaths(dirpath):
    file_paths = []  # List which will store all of the full filepaths.

    # Walk the tree.
    for root, subdirs, files in os.walk(dirpath):
        for filename in files:
            # Join the two strings in order to form the full filepath.
            filepath = os.path.join(root, filename)
            file_paths.append(filepath)  # Add it to the list.

    return file_paths

# Run the above function and store its results in a variable.   
make(sys.argv[1])