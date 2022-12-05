# ros2_astra_camera

A ROS2 driver for Orbbec 3D cameras.

**Only tested on Astra Pro**

## Install
This package tested on ROS2 Galactic.

1. Install [ROS](https://docs.ros.org/en/galactic/Installation.html)

2. Install dependences
    ```sh
    sudo apt install ros-$ROS_DISTRO-image-pipeline libuvc-dev
    ```

3. Create a ROS Workspace(if you don't have one)
    ```sh
    mkdir -p ~/ros2_ws/src
    ```

4. Pull the repository into your ROS workspace
    ```sh
    cd ~/ros2_ws/src
    git clone https://github.com/KavenYau/ros2_astra_camera.git
    ```

5. Create astra udev rule
    ```sh
    cd ros2_astra_camera
    sudo cp ./56-orbbec-usb.rules /etc/udev/rules.d/
    sudo systemctl reload systemd-udevd
    sudo systemctl restart systemd-udevd
    ```

6. Compile
    ```sh
    cd ../..
    colcon build --symlink-install
    ```

## Run


#### Disable color cloud(By default)
```sh
ros2 launch ros2_astra_camera astra_pro_launch.py
```

#### Enable color cloud
```sh
ros2 launch ros2_astra_camera astra_pro_launch.py enable_color_cloud:=True
```

#### Rviz2
```sh
ros2 launch ros2_astra_camera astra_rviz.py                                
```

## Known Issues
- Pointcloud messages are not published smoothly when running as component.

- DeviceOpen using default: no devices found
   ```log
   No matching device found.... waiting for devices
   ```
  setting LD_LIBRARY_PATH environment variable to the right path of libOpenNI2.so. e.g. 
   ```sh
  export LD_LIBRARY_PATH=~/ros2_ws/src/ros2_astra_camera/ros2_astra_camera/lib/openni2_redist/arm64:$LD_LIBRARY_PATH
  ```

## References
https://github.com/orbbec/ros_astra_camera
