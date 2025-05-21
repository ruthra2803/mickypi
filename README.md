# Micky - Face Tracking with OpenCV

Micky is a Python-based face tracking project that uses OpenCV to detect and track faces in real-time video streams from a webcam.

## Table of Contents
- Overview
- Features
- Hardware Requirements
- Circuit Connections
- Software Requirements
- Installation
- Usage
- Code Explanation
- Contributing

## Overview
Micky leverages OpenCV's Haar Cascade Classifier to detect faces in real-time video captured from a webcam. The project processes video frames, identifies faces, and draws bounding boxes around them, making it suitable for applications like surveillance, human-computer interaction, or educational purposes.

## Features
- Real-time face detection and tracking using OpenCV.
- Displays bounding boxes around detected faces.
- Lightweight and easy to set up.
- Configurable for different video input sources (e.g., webcam, video file).

## Hardware Requirements
- A computer with a webcam (built-in or external).
- Arduino nano or uno
- 2xservo motors sg90s
- oled display
- external power supply for servo (optional for this project )
- 
## Circuit Connections 

OLED Pin	Connect to Nano

VCC        3.3V or 5V
GND	       GND
SCL	       A5
SDA        A4
Left-Right Servo (x)	D2
Up-Down Servo (y)   	D3
servo power supply 5v 



## Software Requirements
- Python 3.8 or later
- OpenCV (`opencv-python`)
- NumPy (optional, for advanced image processing)
- A webcam or video input device
