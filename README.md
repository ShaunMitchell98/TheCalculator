# TheCalculator

A scientific calculator, written in C++ using Windows Presentation Foundation for the UI. The design is inspired by the default
calculator app that comes with Windows 10.

![Application picture](https://github.com/ShaunMitchell98/TheCalculator/blob/master/images/Application%20Picture.png)
![Windows application](https://github.com/ShaunMitchell98/TheCalculator/blob/master/images/Windows%20Calculator%20Picture.png)

I originally intended to attempt to clone this app, but in the process decided to make some changes. One such change is that I removed some buttons whose purpose was unclear or beyond the scope of the app such as the up arrow in the bottom left corner of the Windows app and the dms button.

In the Windows app many of the unary operators that look like they should be pressed first actually expect to be typed after their input. 
For example:

![Windows calculator logarithm](https://github.com/ShaunMitchell98/TheCalculator/blob/master/images/Windows%20log.gif)

I found this to be unnatural so in my implementation I chose to put the operator before its input:

![TheCalculator logarithm](https://github.com/ShaunMitchell98/TheCalculator/blob/master/images/TheCalculator%20log.gif)
