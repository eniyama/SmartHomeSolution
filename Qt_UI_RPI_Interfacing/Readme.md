Qt_UI_Interfacing – SmartHomeDashboard Setup Guide

Overview

This document describes the steps required to set up and run the SmartHomeDashboard Qt application on a
Raspberry Pi using a prebuilt Qt 6 runtime. It also documents a common QML runtime error and its rectification.

Prerequisites

1 Raspberry Pi with Raspberry Pi OS (64-bit recommended)

2 Network connectivity between host PC and Raspberry Pi

3 Qt runtime archive: jan19_qt6.5.3.tar.gz

4 Application archive: UIapplication_jan19.tar.gz

1. Copy Files to Raspberry Pi

Use rsync to copy the Qt runtime and application from the host system to the Raspberry Pi:

rsync -avz --progress UIapplication_jan19.tar.gz user@192.168.0.46:/home/user/

rsync -avz --progress jan19_qt6.5.3.tar.gz user@192.168.0.46:/home/user/

2. Verify Files on Raspberry Pi

Log in to the Raspberry Pi and verify the copied files:

ls -lh ~/

3. Create Required Directories

Create directories for Qt runtime and applications:

mkdir -p ~/qt

mkdir -p ~/apps

4. Extract Archives

Extract the Qt runtime and application archives:

tar -xvzf jan19_qt6.5.3.tar.gz -C ~/qt

tar -xvzf UIapplication_jan19.tar.gz -C ~/apps

5. Verify Extraction

Confirm the contents of the extracted directories:

ls ~/qt

ls ~/apps

6. Make Application Executable
Navigate to the application directory and make the binary executable:

cd ~/apps/UIapplication

chmod +x SmartHomeDashboard

7. Set Qt Environment Variables

Set the required Qt environment variables:
export QT_ROOT=/home/user/qt/qt6-rpi/qt6.5.3
export PATH=$QT_ROOT/bin:$PATH
export LD_LIBRARY_PATH=$QT_ROOT/lib:$QT_ROOT/plugins:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM=eglfs

8. Persist Environment Variables
To make the environment variables persistent, add them to ~/.bashrc:

vi ~/.bashrc

# Add the export commands at the end

source ~/.bashrc

9. Run the Application

Run the application from the application directory:

cd ~/apps/UIapplication
./SmartHomeDashboard

Common Error: QML Module Not Loading

QQmlApplicationEngine failed to load component
Module "SmartHome" contains no type named "Main"

Cause

This error occurs when the QML engine cannot locate the Main type inside the SmartHome QML module. This is
usually caused by an incorrect qmldir file, improper directory structure, or missing QML import path.

Rectification

Ensure the following QML structure exists inside the application directory:

qml/SmartHome/Main.qml
qml/SmartHome/qmldir

The qmldir file must contain:

module SmartHome
Main 1.0 Main.qml

Before running the application, export the QML import path:

export QML_IMPORT_PATH=$PWD/qml

In some cases, the application may run but fail to display the UI
then follow this step

10. Raspberry Pi Boot Configuration
For proper display using eglfs, configure the Raspberry Pi to boot into console mode:

sudo raspi-config
System Options → Boot / Auto Login → B1 Console (Text console)

sudo reboot

11. Run Application After Reboot

After rebooting, log in to the console and run:

cd ~/apps/UIapplication

./SmartHomeDashboard

Notes

1 Ensure all environment variable paths match the extracted directories.
2 eglfs requires exclusive access to the framebuffer; console boot mode is recommended.
3 Verify Qt runtime and application compatibility with the Raspberry Pi OS version.
