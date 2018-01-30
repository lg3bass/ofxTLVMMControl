ofxTLVMMControl is an addon for ofxTimeline to add a pseudo-track ofxDatGui channel full of widgets meant send params to my application VMM.  

This addon is a customization of the ofxTLButtons addon by https://github.com/hvfrancesco/ofxTLButtons.

MyAddon uses ofxDatGui instead of ofxUI.  I will publish a ofxTLDatGuiTrack addon for general purpose.

To use it with ofxTimeline basically you have to:

Add in addons.make after ofxTimeline and its dependencies add:

	ofxTLVMMControl
	ofxDatGui

-- or -- 

Use the Project Generator to add ofxTLVMMControl

In you header file add (usually next to #include "ofxTimeline.h"):

	include "ofxTLVMMControl.h"

And the in your cpp file you can add buttons track with something like this:

	ofxTLVMMControl* buttonsTrack = new ofxTLVMMControl(string osc_target_ip ,int osc_target_port);
    string buttonsTrackName = _name;  //name of your track
    buttonsTrack->setXMLFileName(buttonsTrackName+".xml");	//make sure to set the xml so it will save.
    timeline->addTrack(_name, buttonsTrack);
        
while osc_target_ip and osc_target_port are the ip and port number of the target you want to manually send osc messages to.

TODO:
The OSC designation will be removed from the constructor
Multiple constructors will be removed.
All VMM settings will be added.
Extensive layout of all the VMM controls.
Send values on load to VMM