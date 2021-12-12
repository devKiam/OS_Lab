no_of_jobs = int(input("Number of jobs: "))
arrival_time = list(map(int, input("Arrival times: ").split(" ")))
service_time = list(map(int, input("Service times: ").split(" ")))
job = {}
for i in range(no_of_jobs):
job[i] = (arrival_time[i], service_time[i])
sorted_job = {k : v for k, v in sorted(job.items(), key=lambda x :
x[1][0])}
# sorted_job = sorted(job.items(), key=lambda x : x[1][0])
# print(sorted_job)
time = 0
finish_waiting = {}
done = {}

while True:
temp_dict = {}
for key in sorted_job:
if time >= sorted_job[key][0] and done.get(key, False) == False:
temp_dict[key] = (sorted_job[key][0], sorted_job[key][1])
sorted_temp_dict = {k : v for k, v in sorted(temp_dict.items(),
key=lambda x : x[1][1])}
# print(sorted_temp_dict)
if len(sorted_temp_dict) > 0:
for key in sorted_temp_dict:
finish_time = sorted_temp_dict[key][1] + time
waiting_time = time - sorted_temp_dict[key][0]
finish_waiting[key] = (finish_time, waiting_time)
time = finish_time
done[key] = True
break
else:
time += 1
if len(finish_waiting) == no_of_jobs:
break
total_waiting_time = 0
total_turnaround_time = 0

print(f"Job \t Arrival Time \t Finish Time \t Waiting Time \t Turn Around
Time")
for i in range(no_of_jobs):
print(f"{i} \t\t {sorted_job[i][0]} \t\t {finish_waiting[i][0]} \t\t
{finish_waiting[i][1]} \t\t {finish_waiting[i][0] - sorted_job[i][0]}")
total_waiting_time += finish_waiting[i][1]
total_turnaround_time += (finish_waiting[i][0] - sorted_job[i][0])
print(f"Average Waiting Time : {total_waiting_time/no_of_jobs} unit time")
print(f"Average Turnaround TIme : {total_turnaround_time/no_of_jobs} unit
time")
# for key in finish_waiting:
# print(f"{key} \t\t {sorted_job[key][0]} \t\t {finish_waiting[key][0]}
\t\t {finish_waiting[key][1]} \t\t {finish_waiting[key][0] -
sorted_job[key][0]}")
      
      
      
# Number of jobs: 5
# Arrival times: 1 9 10 12 13
# Service times: 10 7 1 1 8
# Job Arrival Time Finish Time Waiting Time Turn Around Time
# 0 1 11 0 10
# 1 9 20 4 11
# 2 10 12 1 2
# 3 12 13 0 1
# 4 13 28 7 15
# Average Waiting Time : 2.4 unit time
# Average Turnaround TIme : 7.8 unit time
# Process finished with exit code 0
