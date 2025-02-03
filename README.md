# Interfacing-MPU6050-with-Godot-Engine-using-ESP32
In this small project i have interfaced a MPU6050 gyro and accel sensor with Godot engine using ESP32. UDP is used as the protocol to send data from the ESP32 to the desired device.
To run this project do as follow.

# Step 1
1) First clone this repository or download the whole repository as a .zip.
2) Open the mpu6050_esp32_devkitv1 from /src/mpu6050_esp32_devkitv1/ in the Arduino IDE (or whatever IDE you wish to use).
3) Change the wifi address, password and the IP address of the device you wish to send the angle data to. You can change the port too but you will need to change the godot script too.
4) To get local IP address of your PC, press "win + R", type "cmd", type "ipconfig"
5) Get the IPv4 address that start with "192.168 blah blah" and put it into arduino sketch.
6) Step 1 Finished!

# Step 2
1) Download Godot Engine from here https://godotengine.org/
2) Open it and import the project. Click the import button and browse through the "/src/Godot/" folder and select the corresponding "project.godot" file.
3) Change the offset values according to your need.
4) Run the game.
