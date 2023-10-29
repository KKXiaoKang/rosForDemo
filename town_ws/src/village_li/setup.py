from setuptools import setup

# launch文件添加
from glob import glob
import os

package_name = 'village_li'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),glob('launch/*.launch.py')) # 将launch文件下的所有launch复制到install/功能包/share下
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='orangepi',
    maintainer_email='orangepi@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "li4_node=village_li.li4:main", # 重点新添加 搭配 source install/setup.bash 使用 这样子系统才能找到village_li这个包
            "li3_node=village_li.li3:main"
        ],
    },
)
