# Scanline Polygon Filling Algorithm

## Overview
This project implements a Scanline Polygon Filling Algorithm using the Digital Differential Analyzer (DDA) line drawing algorithm. The application allows users to draw a polygon by clicking points with the mouse and then fill the polygon with a chosen color using the Scanline Fill Algorithm.

## Features
- **DDA Line Drawing Algorithm:** Utilizes the Digital Differential Analyzer algorithm for drawing polygon edges.
- **Scanline Fill Algorithm:** Efficiently fills the drawn polygon using a scanline-based approach.
- **Color Selection:** Users can choose a color for filling the polygon using QColorDialog.
- **Interactive Drawing:** Polygon vertices can be added by clicking on the canvas, and the polygon is closed upon a right-click.

## Requirements
- **Qt Framework:** The code is designed for Qt-based applications.
- **C++ Compiler:** Ensure you have a C++ compiler for building the project.

## Getting Started
1. Clone the repository.
2. Open the project in a Qt-supported development environment.
3. Build and run the application.

## Usage
1. Click on the canvas to draw the vertices of the polygon.
2. Right-click to complete the polygon.
3. Click the "Choose Color" button to pick a color for the polygon fill.
4. Click the "Fill Polygon" button to apply the Scanline Fill Algorithm and fill the polygon.

## Code Structure
- `mainwindow.h` and `mainwindow.cpp`: Define the main application window and its functionality.
- `QMouseEvent`: Handle mouse events to capture points for polygon creation.
- `dda()`: Implement the Digital Differential Analyzer line drawing algorithm.
- `on_pushButton_clicked()`: Handle the color selection button click event.
- `on_pushButton_2_clicked()`: Handle the polygon fill button click event.

