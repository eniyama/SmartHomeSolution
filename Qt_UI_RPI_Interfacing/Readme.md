SmartHomeDashboard Setup on Raspberry Pi

This README describes the steps to set up and run the SmartHomeDashboard application on a Raspberry
Pi. The instructions assume you have two files on your host system:

jan19_qt6.5.3.tar.gz (Qt Runtime)
UIapplication_jan19.tar.gz (Application UI)

1. Copy Files to Raspberry Pi
Use 
rsync to copy the files from the host system to the Raspberry Pi:

rsync-avz--progress UIapplication_jan19.tar.gz user@192.168.0.46:/home/user/
rsync-avz--progress jan19_qt6.5.3.tar.gz user@192.168.0.46:/home/user/

Options used: - --progress → Shows copy progress- -a → Keeps file permissions- -z → Compresses files during transfer 

2. Verify Files on Raspberry Pi
After copying, log in to the Raspberry Pi and verify the files:
ls-lh ~/
You should see: 
UIapplication_jan19.tar.gz
jan19_qt6.5.3.tar.gz

3. Create Directories
Create directories for Qt runtime and applications:
mkdir-p ~/qt
mkdir-p ~/apps

4. Extract Files
Extract the Qt runtime and the application:
tar-xvzf jan19_qt6.5.3.tar.gz-C ~/qt
tar-xvzf UIapplication_jan19.tar.gz-C ~/apps

5. Verify the contents:
ls ~/qt
ls ~/apps

6. Make the Application Executable
Navigate to the application folder and set executable permissions:
cd ~/apps/UIapplication
chmod +x SmartHomeDashboard

7. Set Qt Environment
Set the environment variables for Qt:
export QT_ROOT=/home/user/qt/qt6-rpi/qt6.5.3
export PATH=$QT_ROOT/bin:$PATH
export LD_LIBRARY_PATH=$QT_ROOT/lib:$QT_ROOT/plugins:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM=eglfs

8. If needed, add these to 
~/.bashrc to persist them:
vi ~/.bashrc

# Add the above export commands at the end
source ~/.bashrc

9. cd ~/apps/UIapplication
./SmartHomeDashboard

when you are facing issue with displaying but app is running then follow this and run app

10. Configure Raspberry Pi Boot
To display the UI correctly, the Raspberry Pi must boot to the console:
sudo raspi-config
Navigate: 
System Options → Boot / Auto Login → B1 Console (Text console)
Reboot the Raspberry Pi:
sudo reboot

After reboot, log in to the console and run the application:

11. cd ~/apps/UIapplication
./SmartHomeDashboard
If you select 
B2 Desktop (GUI) instead, the UI may not display correctly with Qt 
eglfs .

Notes
1)Ensure all paths in the environment variables match your extracted folders. 
2)eglfs requires exclusive access to the framebuffer, hence booting to console mode is
recommended. 
3)Verify Qt runtime and application are compatible with the Raspberry Pi OS version.

