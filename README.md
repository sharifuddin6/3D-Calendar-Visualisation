# 3D Calendar Visualisation

A 3D visualisation toolkit for calendar data, powered by C++/OpenGL/GLUT. <p>Calendars and timetables are usually presented in the form of a two-dimensional grid. Although this representation is easy to display, it bears little relation to the actual structure of time and is not well-suited to indicating the relative importance and relationship between different events. The aim of this project is to explore other ways to present calendar information which might give a more vivid impression of time and events.

===============================================

Build instructions:
* A prerequisuite for compilation; the system should be running a Linux distro, with Make and GLUT installed
* Download and extract source code
* Enter directory with file Makefile, from the command line
* Enter the command "make" to compile source
* To run the application enter command "./3DCalendarVis" or double click on the runnable application

===============================================

User guide:
<p>The application initially opens into dialog box, which includes a file directory explorer. Compatible calendar data files of format ".cvs" and ".ics" can be opened into this application. Example files in the "/data" directory can be opened.
<p>The data file "ics_small.csv" should be used as an initial visualisation testing. The application should open a 3D graphics application rendering a radial/spiral visualisation.

<p>The application includes three exploratory 3D calendar visualisations selectable from menu:
* radial/spiral visualisation
* pathway visualisation
* grid-style visualisation

===============================================

Keyboard/Mouse control for application:
* Menu: Mouse right click
* Calendar controls: Arrow keys, Mouse left click
* Reset: R
* Camera: W, A, S, D
* Zoom: Mouse scroll
* Elevation: Q, E

===============================================

External libraries and source code:
* tiny file dialogs [by Guillaume Vareille]: Cross-platform dialogs in C C++ WINDOWS OSX GNOME KDE SOLARIS CONSOLE <p>http://sourceforge.net/projects/tinyfiledialogs/
* Drawing Text [by Bill Jacobs]: 3D text rendering using 3D model data format <p>http://www.videotutorialsrock.com/opengl_tutorial/draw_text/text.php
* OBJ model parser [by David Henry]: Parser for Wavefront object files <p>http://tfc.duke.free.fr/
