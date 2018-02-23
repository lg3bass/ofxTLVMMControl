ofxTLVMMControl is an addon for ofxTimeline to add a pseudo-track ofxDatGui channel full of widgets meant send params to my application [VMM](https://github.com/lg3bass/VMM).  

This addon is a customization of the ofxTLButtons addon by [https://github.com/hvfrancesco/ofxTLButtons](https://github.com/hvfrancesco/ofxTLButtons).

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
      
To send events I created an event in the .h

	//CREATES A PREPACKAGED OSC MSG EVENT.
	class VMMOscMessageEvent : public ofEventArgs{
	public:
	    ofxOscMessage m;
	    string message;
	    int value;
	  
	    void composeOscMsg(int track, string msg, float val){
	        message = "/" + msg;
	        value = (int)floor(val);
	        
	        //compose an osc message
	        m.clear();
	        m.setAddress(message);
	        m.addIntArg(track);
	        m.addIntArg(value);
	    }
	    
	    static ofEvent <VMMOscMessageEvent> events;
	};
	  
And then in the .cpp file add the instance of the event.

	#include "ofxTLVMMControl.h"
	#include "ofxTimeline.h"
	
	// setup the events to pass back
	ofEvent <VMMOscMessageEvent> VMMOscMessageEvent::events; 


Another importan note:
If you want to disable the mouse events on ofxDatGui components the update() functions accepts a boolean param.  Setting to false disables mouse events.  This is needed if you have multiple timelines/tabs.

    playNoteOffToggle->setPosition(bounds.getX(), bounds.getY());
    playNoteOffToggle->setVisible(bounds.getBottom()-bounds.getTop() < playNoteOffToggle->getHeight() ? false : true);
    playNoteOffToggle->update(guiAcceptEvents);





* TODO:
* - default settings when you create a VMM track
* - color coded VMMTLControl sliders for easy identification
* - reduce the height of the params. adopt style of enclosing UI
* - color code clip matrix so you know which clip has data
* - *button to reset params.
* - test button.
* - clear button.
* - disable frame I-bar with VMM track.
* - setup undo on VMM
* - tab navigate through VMM controls
* - step increment on VMM params.
* - custom curve track with controls on the left and right.
* - Hide measure bars on VMM track only if VMM track is present.
* - alternate colors for bars in background
* - *render button
* - change params to float.
* - reload/revert track.
