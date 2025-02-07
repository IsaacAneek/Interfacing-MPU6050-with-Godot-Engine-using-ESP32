# Interfacing-MPU6050-with-Godot-Engine-using-ESP32
In this small project i have interfaced a MPU6050 gyro and accel sensor with Godot engine using ESP32. UDP is used as the protocol to send data from the ESP32 to the desired device.

A small backstory. I wanted to control the direction of the character in a FPS game with an IMU sensor. For this project i used MPU6050 interfaced with an ESP32. I used [ReefwingAHRS](https://github.com/Reefwing-Software/Reefwing-AHRS "ReefwingAHRS") and [ReefwingMPU6050](https://github.com/Reefwing-Software/Reefwing-MPU6050 "ReefwingMPU6050") library to get the angle values from the gyro and accel data. Next i created an JSON array and added the roll, pitch and yaw values. The JSON data was sent through UDP to the target device. 
In the Godot project i wrote an script that listens to incoming UDP packets. Captured the packets and extracted the angle values and changed the rotation vector of the character and the camera.

To run this project do as follow.

# Step 1
1) First clone this repository or download the whole repository as a .zip.
2) Open the mpu6050_esp32_devkitv1 from /src/mpu6050_esp32_devkitv1/ in the Arduino IDE (or whatever IDE you wish to use).
3) Change the wifi address, password and the IP address of the device you wish to send the angle data to. You can change the port too but you will need to change the godot script too.
4) To get local IP address of your PC, press "win + R", type "cmd", type "ipconfig"
5) Get the IPv4 address that start with "192.168 blah blah" and put it into arduino sketch.
6) Upload the sketch to your ESP32.
7) Observe the angle values. You might need to reset the ESP32 once to get the correct values
8) Step 1 Finished!

# Step 2
1) Download Godot Engine from here https://godotengine.org/
2) Open it and import the project. Click the import button and browse through the "/src/Godot/" or "/src/OpenFPS/" folder and select the corresponding "project.godot" file.
3) Open the "mpu6050.gd" file
4) Change the offset values and rotation vectors according to your need.
5) Run the game.

# To-Do
- Use quaternions instead of euler angles
- Use a sensor fusion algorithm
- Properly calibrate the IMU sensor
- Refactor the code

# LICENSING:
MIT License applicable to anything not already covered by another License

# Credits
The project [OpenFPS](https://github.com/IMYdev/OpenFPS "OpenFPS") is made by [IMYdev](https://github.com/IMYdev "IMYdev"). Code is licensed under MIT License. All assets are licensed under [Creative Commons (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/ "Creative Commons (CC BY 4.0)")
