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

#include "ofxTLVMMControl.h"
#include "ofxTimeline.h"

// setup the events to pass back
//ofEvent <OscMsgEvent> OscMsgEvent::events;
//ofEvent <anotherOscMsgEvent> anotherOscMsgEvent::events;
ofEvent <VMMOscMessageEvent> VMMOscMessageEvent::events;

//TODO: make single constructor without variables.
ofxTLVMMControl::ofxTLVMMControl(){
    
    //test variables
    test_still = false;
    test_noteOnAndPlay = 0;
    test_localCopies = 5.0;
    
    //VMM variables.
    
    
    setupTrack();

}

/*
ofxTLVMMControl::ofxTLVMMControl(string _oscTarget, int _oscPort = 12345){
    
    //osc data
    oscTarget = _oscTarget;
    oscPort = _oscPort;
    
    test_still = false;
    test_noteOnAndPlay = 0;
    test_localCopies = 5.0;
    
    //create the gui
    setupTrack();
    
}

ofxTLVMMControl::ofxTLVMMControl(int _rows, int _cols, string _oscTarget = "localhost", int _oscPort = 12345, ofxTLVMMControlType _type=OFXTLVMMCONTROL_TYPE_BUTTONS){

    rows = _rows;
    cols = _cols;
    oscTarget = _oscTarget;
    oscPort = _oscPort;
    type = _type;
    setupTrack();

}

ofxTLVMMControl::ofxTLVMMControl(int _b_rows, int _b_cols, int _s_rows, int _s_cols, string _oscTarget = "localhost", int _oscPort = 12345, ofxTLVMMControlType _type=OFXTLVMMCONTROL_TYPE_MIXED){

    button_rows = _b_rows;
    button_cols = _b_cols;
    slider_rows = _s_rows;
    slider_cols = _s_cols;
    oscTarget = _oscTarget;
    oscPort = _oscPort;
    type = _type;
    setupTrack();

}

*/
 
 
ofxTLVMMControl::~ofxTLVMMControl(){
    
    delete gui;
    
    
    delete tgl_still;
    delete but_noteOnAndPlay;
    delete slider_localCopies;
    
}


//ofxDatGui
//================================================================================
void ofxTLVMMControl::setupTrack(){
    
    //TODO: REMOVE
    // OSC setup
    //sender.setup(oscTarget, oscPort);
    
    //datGui combined panel
    gui = new ofxDatGui( 200, 200 );
    gui->setAutoDraw(false);
   
    gui->addHeader("   ::GUI::   ", false);
    gui->addToggle("still", false);
    gui->addButton("noteOnAndPlay");
    gui->addSlider("localCopies", 0, 12, 0);
    gui->setWidth(100);
    
    //add event listeners
    gui->onButtonEvent(this, &ofxTLVMMControl::trackGuiEvent);
    gui->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    //individual elements
    tgl_still = new ofxDatGuiToggle("still",false);
    tgl_still->setWidth(100.0);
    tgl_still->setPosition(300.0, 0.0);
    tgl_still->setLabelMargin(10.0);
    tgl_still->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    tgl_still->onButtonEvent(this, &ofxTLVMMControl::trackGuiEvent);
    
    but_noteOnAndPlay = new ofxDatGuiButton("noteOnAndPlay");
    but_noteOnAndPlay->setWidth(100.0);
    but_noteOnAndPlay->setPosition(300.0, tgl_still->getHeight());
    but_noteOnAndPlay->setLabelMargin(10.0);
    but_noteOnAndPlay->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    but_noteOnAndPlay->onButtonEvent(this, &ofxTLVMMControl::trackGuiEvent);
    
    slider_localCopies = new ofxDatGuiSlider("localCopies", 0, 12, 0);
    slider_localCopies->setWidth(200.0, 100.0);
    slider_localCopies->setPosition(300.0, 0.0);
    slider_localCopies->setLabelMargin(10.0);
    slider_localCopies->setLabelAlignment(ofxDatGuiAlignment::LEFT);
    slider_localCopies->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    
    //TODO: CREATE GUI USING COMPONENTS VECTOR ALA SONOSCOPIA
}

//BUTTON AND TOGGLE EVENTS
void ofxTLVMMControl::trackGuiEvent(ofxDatGuiButtonEvent e){
    
    if(e.target->is("still")){
        string labelString = e.target->getName();
        bool tglEnabled = e.target->getEnabled();
        test_still = tglEnabled;
        string isEnabled = tglEnabled ? "true" : "false";
        //sendOscMessage(labelString, test_still);
        //TODO: send osc via event
    } else if (e.target->is("noteOnAndPlay")){
        
        string labelString = e.target->getName();
        //sendOscNoteOnAndPlay(labelString);
        //TODO: send osc via event
    }
}

//SLIDER EVENTS
void ofxTLVMMControl::trackGuiSliderEvent(ofxDatGuiSliderEvent e){
    
    if(e.target->is("localCopies")){
        
        //set the local var.
        test_localCopies = e.target->getValue();
        
        //get the slidername and value
        string labelString = e.target->getName();
        float value = e.target->getValue();
        
        //ofxTLVMMControl::sendOscLocalCopies()
        //sendOscLocalCopies(labelString, value);

        //TESTS -  EVENT TESTS (NOT BEING USED)
        //1. class OscMsgEvent
        /*
        static OscMsgEvent newEvent;
        newEvent.msg = "My Custom Message Event!";
        ofNotifyEvent(OscMsgEvent::events, newEvent);
        */
        
        //2. ofMessage > ofApp::gotMessage(ofMessage msg);
        /*
        ofMessage testMsg("ofMessage Message Event!");
        ofSendMessage(testMsg);
        */
        
        //3. class anotherOscMsgEvent
        /*
        static anotherOscMsgEvent testMsg2;
        testMsg2.setArgs(100,222);
        ofNotifyEvent(anotherOscMsgEvent::events, testMsg2);
        */
        
        //cout << "ofxTLVMMControl::trackGuiSliderEvent > track: " << track << endl;
         
        //4. class VMMOscMessageEvent
        static VMMOscMessageEvent vmmOscEvent;
        vmmOscEvent.composeOscMsg(track+1, labelString, test_localCopies);
        ofNotifyEvent(VMMOscMessageEvent::events, vmmOscEvent);
        
    }
}


void ofxTLVMMControl::setGuiSliderValue(string param, float value){
    if(param == "localCopies"){
        //set the public var
        test_localCopies = value;
        
        //update the gui
        updateGuiSlider(param, value);
        
        //cout << "ofxTLVMMControl::setGuiSliderValue > track: " << track << endl;
        
        //send out the osc
        static VMMOscMessageEvent vmmOscEvent;
        vmmOscEvent.composeOscMsg(track+1, param, value);
        ofNotifyEvent(VMMOscMessageEvent::events, vmmOscEvent);
    
    }
}

void ofxTLVMMControl::setGuiValue(string param, int value){
    
}
void ofxTLVMMControl::setGuiValue(string param, bool value){
    
}

void ofxTLVMMControl::updateGuiToggle(string name, bool value){
    
}
void ofxTLVMMControl::updateGuiSlider(string name, float value){
    if(name == "localCopies"){
        gui->getSlider(name)->setValue(value);
    }
}
void ofxTLVMMControl::updateGuiSlider(string name, int value){
    
}


//TODO: remove all send osc function.
//moved to ofApp.
/*
void ofxTLVMMControl::sendOscMessage(string _message){

        string message = _message;
        ofxOscMessage m;
        m.setAddress(message);
        sender.sendMessage(m);
}

void ofxTLVMMControl::sendOscMessage(string _message, float _value){

        string message = _message;
        float argument = _value;
        ofxOscMessage m;
        m.setAddress(message);
        m.addFloatArg(argument);
        sender.sendMessage(m);
    
    cout << "/" << _message << " " << ofToString(_value) << endl;
}

void ofxTLVMMControl::sendOscMessage(string _message, string _value){
    
    string message = _message;
    string argument = _value;
    ofxOscMessage m;
    m.setAddress(message);
    m.addStringArg(argument);
    sender.sendMessage(m);
}

void ofxTLVMMControl::sendOscNoteOnAndPlay(string _message){
    
    string message = "/" + _message;
    
    ofxOscMessage m;
    m.setAddress(message);
    m.addIntArg(1);
    m.addIntArg(500);
    m.addIntArg(1);
    m.addIntArg(200);

    sender.sendMessage(m);
    
    cout << message << " " << ofToString(1) << " " << ofToString(m.getArgAsInt32(1)) << " " << ofToString(m.getArgAsInt32(2)) << " " << ofToString(m.getArgAsInt32(3))  << endl;
}

void ofxTLVMMControl::sendOscLocalCopies(string _message,float _value){
    
    string message = "/" + _message;
    int value = (int)floor(_value);
    ofxOscMessage m;
    m.setAddress(message);
    m.addIntArg(1);
    m.addIntArg(value);
    sender.sendMessage(m);
    
    cout << message << " " << ofToString(1) << " " << ofToString(value) << endl;
}
*/
 
 
//enable and disable are always automatically called
//in setup. Must call superclass's method as well as doing your own
//enabling and disabling
void ofxTLVMMControl::enable(){
	ofxTLTrack::enable();
    
    gui->setEnabled(true);
    
	//other enabling
}

void ofxTLVMMControl::disable(){
	ofxTLTrack::disable();

    gui->setEnabled(false);
	//other disabling
}

void ofxTLVMMControl::trackGuiDelete(){
//    trackGui->disable();
//    ofRemoveListener(trackGui->newGUIEvent, this, &ofxTLVMMControl::trackGuiEvent);
    
    gui->setEnabled(false);
//  DO I NEED TO REMOVE THE LISTENER?
}

//update is called every frame.
//if your track triggers events it's good to do it here
//if timeline is set to thread this is called on the back thread so
//be careful if loading images in herre
void ofxTLVMMControl::update(){
    
    //    //get the bounds of the track.  used to show or hide the GUI.
    //    cout << "gui height: " << gui->getHeight() <<
    //    " track minY: " << bounds.getMinY() <<
    //    " track maxY: " << bounds.getMaxY() <<
    //    " getBottom - getTop = " << bounds.getBottom()-bounds.getTop() <<
    //    endl;
    
    
    
    //ALL THIS BELOW SETS THE VISIBILITY OF THE GUI ELEMENTS WHEN YOU MINIMIZE THE TRACK
    //TODO: SET THIS UP TO WORK ON UNNAMED COMPONENTS (ALA SONSCOPIA)
    //TODO: HIDE(OR PREVENT TRIGGERING) THE GUI ELEMENTS WHEN TRACK IS NOT FOCUSED.
    
    //gui
    gui->update();
    gui->setPosition(bounds.getX(), bounds.getMinY());
    if(bounds.getBottom()-bounds.getTop() < gui->getHeight()){
        
        gui->setVisible(false);
        
    } else {
        
        gui->setVisible(true);
    }
    
    //individual buttons
    tgl_still->setPosition(bounds.getX()+400, bounds.getY());
    tgl_still->update();
    
    if(bounds.getBottom()-bounds.getTop() < tgl_still->getHeight()){
        tgl_still->setVisible(false);
        
    } else {
        tgl_still->setVisible(true);
    }
    
    but_noteOnAndPlay->setPosition(bounds.getX()+400, bounds.getY()+tgl_still->getHeight());
    but_noteOnAndPlay->update();
    
    if(bounds.getBottom()-bounds.getTop() < tgl_still->getHeight()+but_noteOnAndPlay->getHeight()){
        but_noteOnAndPlay->setVisible(false);
    } else {
        but_noteOnAndPlay->setVisible(true);
    }
    
    slider_localCopies->setPosition(bounds.getX()+400, bounds.getY()+tgl_still->getHeight()+but_noteOnAndPlay->getHeight());
    slider_localCopies->update();

    if(bounds.getBottom()-bounds.getTop() < tgl_still->getHeight()+but_noteOnAndPlay->getHeight()+slider_localCopies->getHeight()){
        slider_localCopies->setVisible(false);
    } else {
        slider_localCopies->setVisible(true);
    }
    
}

//draw your track contents. use ofRectangle bounds to know where to draw
//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
void ofxTLVMMControl::draw(){
    
    //gui
    gui->draw();
    
    //TODO: unneeded
    //draw a rect if the track is too short to display gui
    if(bounds.getBottom()-bounds.getTop() < gui->getHeight()){
        ofPushStyle();
        ofFill();
        ofSetColor(100);
        ofDrawRectangle(bounds.getX(), bounds.getMinY(), gui->getWidth(), bounds.getBottom()-bounds.getTop());
        ofPopStyle();
    }
    
    
    //draw individual Gui components.
    tgl_still->draw();
    but_noteOnAndPlay->draw();
    slider_localCopies->draw();
    
	//this is just a simple example (not working for me)
	/*
	ofPushStyle();
	ofFill();
	if(isHovering()){
		//ofSetColor(timeline->getColors().backgroundColor);
        ofSetColor(ofColor::indianRed);
        ofRectangle(bounds);

	}

	ofNoFill();
	ofSetColor(timeline->getColors().keyColor);
	for(int i = 0; i < clickPoints.size(); i++){
		float screenX = millisToScreenX(clickPoints[i].time);
		if(screenX > bounds.x && screenX < bounds.x+bounds.width){
			float screenY = ofMap(clickPoints[i].value, 0.0, 1.0, bounds.getMinY(), bounds.getMaxY());
            ofDrawCircle(screenX, screenY, 4);
		}
	}
    ofPopStyle();
    */
}

//caled by the timeline, don't need to register events
bool ofxTLVMMControl::mousePressed(ofMouseEventArgs& args, long millis){
	/*
	createNewPoint = isActive();
	clickPoint = ofVec2f(args.x,args.y);
	return createNewPoint; //signals that the click made a selection
	*/
}

void ofxTLVMMControl::mouseMoved(ofMouseEventArgs& args, long millis){

}
void ofxTLVMMControl::mouseDragged(ofMouseEventArgs& args, long millis){

}
void ofxTLVMMControl::mouseReleased(ofMouseEventArgs& args, long millis){

	/*
	//need to create clicks on mouse up if the mouse hasn't moved in order to work
	//well with the click-drag rectangle thing
	if(createNewPoint && clickPoint.distance(ofVec2f(args.x, args.y)) < 4){
		ClickPoint newpoint;
		newpoint.value = ofMap(args.y, bounds.getMinY(), bounds.getMaxY(), 0, 1.0);
		newpoint.time = millis;
		clickPoints.push_back(newpoint);
		//call this on mouseup or keypressed after a click
		//will trigger save and needed for undo
		timeline->flagTrackModified(this);
	}
	*/
}

//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
void ofxTLVMMControl::keyPressed(ofKeyEventArgs& args){

}
void ofxTLVMMControl::nudgeBy(ofVec2f nudgePercent){

}

//if your track has some selectable elements you can interface with snapping
//and selection/unselection here
void ofxTLVMMControl::getSnappingPoints(set<unsigned long>& points){

}
void ofxTLVMMControl::regionSelected(ofLongRange timeRange, ofRange valueRange){

}
void ofxTLVMMControl::unselectAll(){

}
void ofxTLVMMControl::selectAll(){

}

//return a unique name for your track
string ofxTLVMMControl::getTrackType(){
	return "Buttons";
}

//for copy+paste you can optionaly implement ways
//of creating XML strings that represent your selected tracks
string ofxTLVMMControl::copyRequest(){
	return "";
}

string ofxTLVMMControl::cutRequest(){
	return "";
}

//will return the same type of strings you provide in copy and paste
//but may contain foreign data from other tracks so be careful
void ofxTLVMMControl::pasteSent(string pasteboard){

}

//for undo and redo you can implement a way of
//reperesnt your whole track as XML
string ofxTLVMMControl::getXMLRepresentation(){
	return "";
}

void ofxTLVMMControl::loadFromXMLRepresentation(string rep){

}

//serialize your track.
//use ofxTLTrack's string xmlFileName
void ofxTLVMMControl::save(){
    cout << "ofxTLVMMControl::save()" << endl;
    
    //string xmlRep = getXMLStringForKeyframes(keyframes);
    ofxXmlSettings savedButtonsTrack;
    
    //write all the VMM settings.
    savedButtonsTrack.addTag("VMM");
    savedButtonsTrack.pushTag("VMM");
    savedButtonsTrack.addValue("still", test_still);
    savedButtonsTrack.addValue("noteOnAndPlay", test_noteOnAndPlay);
    savedButtonsTrack.addValue("localCopies", test_localCopies);
    savedButtonsTrack.popTag();
    
    //cout where and what to save.
    string outstring;
    savedButtonsTrack.copyXmlToString(outstring);
    cout << outstring << endl;
    cout << "XMLFilePath: " << getXMLFilePath() << endl;
    cout << "XMLFileName: " << getXMLFileName() << endl;
    
    savedButtonsTrack.saveFile(xmlFileName);
    
}

void ofxTLVMMControl::load(){
    
    string savedClipSettingsPath = getXMLFilePath();
    ofxXmlSettings savedVMMSettings;
    
    if( savedVMMSettings.loadFile(savedClipSettingsPath) ){
        ofLogVerbose("LOAD") << "ofxTLVMMControl::load() - Loading VMM.xml " << savedClipSettingsPath;
        
        //update the params
        //TODO: ceate a function with all the setting to set from xml.
        setGuiSliderValue("localCopies",savedVMMSettings.getValue("VMM:localCopies", 0));
                
    }else{
        ofLogError("LOAD") <<  "ofxTLVMMControl::load() - unable to load: " << savedClipSettingsPath ;
        return;
    }
}

void ofxTLVMMControl::clear(){

}
