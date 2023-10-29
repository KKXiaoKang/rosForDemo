# 如何手动安装ROS2
```
# 下载密钥
sudo apt install curl gnupg2 -y
curl -s https://gitee.com/ohhuo/rosdistro/raw/master/ros.asc | sudo apt-key add -

# 导出到系统
echo "deb [arch=$(dpkg --print-architecture)] https://repo.huaweicloud.com/ros2/ubuntu/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# 更新
sudo apt update    

# 安装ros2
sudo apt install ros-foxy-desktop

# 安装额外依赖
sudo apt install python3-argcomplete -y

# 配置环境变量
source /opt/ros/foxy/setup.bash

# 加入到终端中 每次打开终端都能链接
echo "source /opt/ros/foxy/setup.bash" >> ~/.bashrc

# ！！如果安装失败那就一键卸载吧
sudo apt remove ros-foxy-* && sudo apt autoremove
```