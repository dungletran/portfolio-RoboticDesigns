# TARA1
Tara1 was developed by my group consisting of six members during MP4006 Robotic Course, designed by Mechanical & Aerospace Engineering, Nayang Technological University, Singapore. Tara1 is a three-legged robot that can climb stairs. The project involved detailed studies of the current robotics mechanism to climb stairs, structural design and fabrication, software programming, and demo show by the end of the course.

The motion of the robot is programmed into the microcontroller. Then, the microcontroller will send out signals to the servo motors and receive signals from the sensor.

At first, BASIC Stamps was used as the microcontroller for our robotics project. However, various problems arose when BASIC Stamps was used. The problems are:
- Programming in BASIC Stamp has limited capability
- Servo motors draw too much current when connected to BASIC Stamp
- Constant jerking of the servo motor at a certain angle

As a result, we decided to use Arduino to replace BASIC Stamp as the microcontroller for our robot. This robot requires 2 Arduino microcontrollers. Synchronization is crucial for a robotics motion. Therefore, a server and client are established between the 2 Arduino microcontrollers (as shown above) to allow data being sent to each microcontroller. A channel is set up afterward to allow data being sent and received by the microcontroller. The semaphore technique is used to ensure that there is no data lost sent/received by the Arduino microcontroller.
