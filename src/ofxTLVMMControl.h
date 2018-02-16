/**
 * ofxTimeline
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#pragma once

#include "ofMain.h"
#include "ofxTLTrack.h"
#include "ofxOsc.h"
#include "ofxDatGui.h"

/*
enum ofxTLVMMControlType {
	OFXTLVMMCONTROL_TYPE_BUTTONS=0,
	OFXTLVMMCONTROL_TYPE_SLIDERS=1,
	OFXTLVMMCONTROL_TYPE_MIXED=2
};
*/
 
typedef struct {
	float value;
	unsigned long time;
} ClickPoint;


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

class ofxTLVMMControl : public ofxTLTrack {
  public:
    ofxTLVMMControl();
    
	virtual ~ofxTLVMMControl();

    int track;  //store the current track
    
    ofParameter<int> OSCsetMatCap;
    ofxDatGuiSlider* OSCsetMatCapSlider;
    
    ofParameter<int> OSCsetTrack;
    ofxDatGuiSlider* OSCsetTrackSlider;
        
    ofParameter<int> localSlices;
    ofxDatGuiSlider* localSlicesSlider;
    
    ofParameter<int> localCopies;
    ofxDatGuiSlider* localCopiesSlider;
    
    ofParameter<int> globalCopies;
    ofxDatGuiSlider* globalCopiesSlider;
 
    ofParameter<float> mirrorDistance;
    ofxDatGuiSlider* mirrorDistanceSlider;
    
    //playNoteOff
    bool playNoteOff;
    ofxDatGuiButton* playNoteOffToggle;
    
    bool playAll;
    ofxDatGuiToggle* playAllToggle;
    
    bool mirror;
    ofxDatGuiToggle* mirrorToggle;
    
    bool mirrorX;
    ofxDatGuiToggle* mirrorXToggle;
    
    bool mirrorY;
    ofxDatGuiToggle* mirrorYToggle;
    
    bool mirrorZ;
    ofxDatGuiToggle* mirrorZToggle;

    bool showGui;
    int compH = 24;
    int compW = 200;
    
    //test params for VMM
    bool test_still;
    int test_noteOnAndPlay;
    float test_localCopies;
    
    // ofxDatGui
    void setupTrack();
    
    void setButtonToggle(ofxDatGuiButton* _button, bool &val);
    
    ofxDatGuiToggle* tgl_still;
    ofxDatGuiButton* but_noteOnAndPlay;
    ofxDatGuiSlider* slider_localCopies;
    
    void trackGuiEvent(ofxDatGuiButtonEvent e);     //TODO: delete me
    
    void trackGuiButtonEvent(ofxDatGuiButtonEvent e);
    void trackGuiSliderEvent(ofxDatGuiSliderEvent e);
    
    void sendOSC(string name, float value);
    
    void setGuiValue(string param, int value);
    void setGuiValue(string param, bool value);
    
    void updateGuiToggle(string name, bool value);
    void updateGuiSlider(string name, float value);
    void updateGuiSlider(string name, int value);
    
    void trackGuiDelete();

	//enable and disable are always automatically called
	//in setup. Must call superclass's method as well as doing your own
	//enabling and disabling
	virtual void enable();
	virtual void disable();

	//update is called every frame.
	//if your track triggers events it's good to do it here
	//if timeline is set to thread this is called on the back thread so
	//be careful if loading images in herre
	virtual void update();

	//draw your track contents. use ofRectangle bounds to know where to draw
	//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
	virtual void draw();

	//called by the timeline, don't need to register events
	//is called even if the click is not in the track,
	//so check isActive() to see if the click is inside
	virtual bool mousePressed(ofMouseEventArgs& args, long millis);
	virtual void mouseMoved(ofMouseEventArgs& args, long millis);
	virtual void mouseDragged(ofMouseEventArgs& args, long millis);
	virtual void mouseReleased(ofMouseEventArgs& args, long millis);

	//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
	virtual void keyPressed(ofKeyEventArgs& args);
	virtual void nudgeBy(ofVec2f nudgePercent);

	//if your track has some selectable elements you can interface with snapping
	//and selection/unselection here
    virtual void getSnappingPoints(set<unsigned long>& points);

	//time range contains MIN and MAX time in milliseconds
	//valueRange is 0 at the bottom of the track, and 1 at the top
    virtual void regionSelected(ofLongRange timeRange, ofRange valueRange);
    virtual void unselectAll();
	virtual void selectAll();

	//return a unique name for your track
	virtual string getTrackType();

	//for copy+paste you can optionaly implement ways
	//of creating XML strings that represent your selected tracks
	virtual string copyRequest();
	virtual string cutRequest();
	//will return the same type of strings you provide in copy and paste
	//but may contain foreign data from other tracks so be careful
	virtual void pasteSent(string pasteboard);

	//for undo and redo you can implement a way of
	//reperesnt your whole track as XML
    virtual string getXMLRepresentation();
    virtual void loadFromXMLRepresentation(string rep);

	//serialize your track.
	//use ofxTLTrack's string xmlFileName
	virtual void save();
	virtual void load();
	virtual void clear();

  protected:
	ofVec2f clickPoint;
	bool createNewPoint;
	vector<ClickPoint> clickPoints;
};
