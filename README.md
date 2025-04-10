# Embedded-Real-time-Operating-System-on-System-on-Chip_project

car.ino是Arduino的code、Object_Detection_Files是放樹梅派用的code、opencv-env是虛擬環境，燒入完Arduino之後執行以下動作。

**Raspberry pi 4 樹梅派**
-
python3 -m venv opencv-env

source opencv-env/bin/activate  #虛擬環境

cd Object_Detection_Files

bash opencv_pi_requirements.sh  #opencv 一定要4.4.0,我是用4.4.0.40 pip3 install opencv-python==4.4.0.40，環境安裝

pip3 install smbus 

pip3 install pyserial 

...

**Run**
-
cd Object_Detection_Files

python3 Final_project.py
