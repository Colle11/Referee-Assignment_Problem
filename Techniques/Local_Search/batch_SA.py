#! /usr/bin/env python
import os
from datetime import date
import random
import math

# list of names of instances
instances = ["RA-1-8.txt", "RA-1-10.txt", "RA-2-16.txt", "RA-2-20.txt", "RA-3-24.txt", "RA-3-30.txt", "RA-4-32.txt", "RA-4-40.txt", "RA-5-40.txt", "RA-5-50.txt"]
# number of repetitions
repetitions = 1

# directory of the instances
instance_directory = "../../RefAssign-Instances/Instances"

# directory of the solutions
solution_directory = "Solutions"
solution_extension = "sol"

# total number of iterations
total_iterations = 4E08

# ALGORITHM PARAMETERS
# Simulated Annealing has 3 parameters: start temperature, temperature range and cooling rate
start_temp_array = [10.0, 100.0, 1000.0]  
range_temp_array = [10.0, 30.0, 100.0]
cooling_rate_array = [0.95, 0.99, 0.995, 0.999] 

today = date.today()
# The log file stores a summary of the results
log_file = "Log_" + today.isoformat() + ".log"
f = open(log_file,"a")
f.write("Trial Instance Cost Seed Time Start_temp Min_Temp Cooling_Rate\n")
f.close()

for i in range(repetitions):
  for instance in instances:
    in_file_path = instance_directory + "/" + instance
    if os.path.isfile(in_file_path): # Check if the file exists 
      for st in range(len(start_temp_array)):
        for tr in range(len(range_temp_array)):
          for cr in range(len(cooling_rate_array)):
             seed = random.randint(0,100000000)
             start_temp = start_temp_array[st]
             temp_range = range_temp_array[tr]
             min_temp = start_temp/temp_range
             cooling_rate = cooling_rate_array[cr]
             number_of_temperatures = -math.log(temp_range)/math.log(cooling_rate)              
             neighbors_sampled = int(round(total_iterations/number_of_temperatures))
             neighbors_accepted = int(neighbors_sampled * 0.1)
             
             if not os.path.isdir(solution_directory):
              os.mkdir(solution_directory) 
             
             # the solution file
             sol_file = solution_directory + "/sol-" + instance + \
                  "-" + str(st) + "-" + str(tr) + "-" + str(cr)  + "_" + \
                  str(i) + "." + solution_extension
              
             # command line
             command = "./TestRALocalSearch.exe" + \
             " --main::instance " +  in_file_path  + \
             " --main::method CAR_SA" + \
             " --ChangeAssignedReferees_SimulatedAnnealing::start_temperature " + str(start_temp) + \
             " --ChangeAssignedReferees_SimulatedAnnealing::min_temperature " + str(min_temp) + \
             " --ChangeAssignedReferees_SimulatedAnnealing::cooling_rate " + str(cooling_rate) + \
             " --ChangeAssignedReferees_SimulatedAnnealing::neighbors_sampled " + str(neighbors_sampled) + \
             " --ChangeAssignedReferees_SimulatedAnnealing::neighbors_accepted " + str(neighbors_accepted) + \
             " --main::output_file " + sol_file
             
             print command + "\n"
             os.system(command)

             f = open(sol_file,'r')
             f.readline() # first line is the solution (we discard it)
             cost_string = f.readline()
             f.readline()
             time_string = f.readline()

             cost = str.rstrip(cost_string.split(" ")[1],'\n') # take only the second part (index 1)
             time = str.rstrip(time_string.split(" ")[1],'\n')
             f = open(log_file,"a")
             f.write(str(i) + " " + instance + " " + \
                 str(cost) + " " + str(seed) + " " + str(time) + " " + \
                 str(start_temp) + " " + str(min_temp) + " " + str(cooling_rate) + "\n")
             f.close()

