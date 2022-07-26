# Application-for-setting-daily-tasks
You can simpely manage your works with this Window's apllication that create by cpp.
In the input first you should enter the times that you are busy in them (in this form  hh:mm ) . 
after that you should type # , then you should enter the times that you need in the day(by form of minutes) . you should write an id near each time(it starts from 1)
this id show priority of the works . 
form of input :
<event_time>
<event_time>
...
#
<task_duration> <empty_range_id>
<task_duration> <empty_range_id>
...
example of input : 
13:00-15:00
16:00-17:00
19:00-20:00
#
60 1
30 2
20 2
120 3

the out put will show you the the free times of your day that you can do your works on them.
form of output:
<task_id> <task_scheduled_time>
<task_id> <task_scheduled_time>
….

example of output :
1 12:00-13:00
2 15:00-15:30
3 15:30-15:50
4 17:00-19:00

 the persian description is here :
 [APS01-A1-Description.pdf](https://github.com/Aliparviz/Application-for-setting-daily-tasks/files/9187072/APS01-A1-Description.pdf)
