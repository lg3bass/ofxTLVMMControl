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
    
    
    //setup all my params
    OSCsetMatCap.set("OSCsetMatCap",1,1,20);
    OSCsetTrack.set("OSCsetTrack",1,1,20);
    localSlices.set("localSlices",2,1,4);
    localCopies.set("localCopies",8,1,12);
    globalCopies.set("globalCopies",1,1,12);
    mirrorDistance.set("mirrorDistance",0.0,-50.0,50.0);
    
    playNoteOff = false;
    playAll = false;
    mirror = false;
    mirrorX = false;
    mirrorY = false;
    mirrorZ = false;
    
    //test variables
    test_still = false;
    test_noteOnAndPlay = 0;
    test_localCopies = 5.0;
    
    setupTrack();

}

ofxTLVMMControl::~ofxTLVMMControl(){

    
    trackGuiDelete();
    
}


//ofxDatGui
//================================================================================
void ofxTLVMMControl::setupTrack(){
    
    //Col 1
    OSCsetMatCapSlider = new ofxDatGuiSlider(OSCsetMatCap);
    OSCsetMatCapSlider->setLabelMargin(10.0);
    OSCsetMatCapSlider->setWidth(200.0, 80.0);
    OSCsetMatCapSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    OSCsetTrackSlider = new ofxDatGuiSlider(OSCsetTrack);
    OSCsetMatCapSlider->setLabelMargin(10.0);
    OSCsetTrackSlider->setWidth(200.0, 80.0);
    OSCsetTrackSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    localSlicesSlider = new ofxDatGuiSlider(localSlices);
    localSlicesSlider->setLabelMargin(10.0);
    localSlicesSlider->setWidth(200.0, 80.0);
    localSlicesSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    localCopiesSlider = new ofxDatGuiSlider(localCopies);
    localCopiesSlider->setLabelMargin(10.0);
    localCopiesSlider->setWidth(200.0, 80.0);
    localCopiesSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    globalCopiesSlider = new ofxDatGuiSlider(globalCopies);
    globalCopiesSlider->setLabelMargin(10.0);
    globalCopiesSlider->setWidth(200.0, 80.0);
    globalCopiesSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    mirrorDistanceSlider = new ofxDatGuiSlider(mirrorDistance);
    mirrorDistanceSlider->setLabelMargin(10.0);
    mirrorDistanceSlider->setWidth(200.0, 80.0);
    mirrorDistanceSlider->onSliderEvent(this, &ofxTLVMMControl::trackGuiSliderEvent);
    
    //Col 2
    playNoteOffToggle = new ofxDatGuiButton("playNoteOff");
    playNoteOffToggle->setWidth(compW);
    playNoteOffToggle->onButtonEvent(this, &ofxTLVMMControl::trackGuiButtonEvent);
    
    //playNoteOffToggle->buttonEventCallback
    
    
    
}

//--------------------------------------------------------------
void ofxTLVMMControl::setButtonToggle(ofxDatGuiButton *_button, bool &val){
    
    val = !val;
    
    if(val){
        _button->setBackgroundColor(ofColor(255,0,0));
        cout << "drive on" << endl;
    } else {
        _button->setBackgroundColor(ofColor(0,0,0));
        cout << "drive off" << endl;
        
    }
    
}


//BUTTON AND TOGGLE EVENTS
//TODO: delete me.
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

//BUTTON EVENTS
void ofxTLVMMControl::trackGuiButtonEvent(ofxDatGuiButtonEvent e){
    if(e.target->is("playNoteOff")){
        
        setButtonToggle(e.target, playNoteOff);
        sendOSC("playNoteOff", playNoteOff);
        
        //bool tglStatus = e.target->getEnabled();
        //playNoteOff = tglStatus;
        
        
    } else if (e.target->is("playAll")){
        
        
    }
    
    
}

//SLIDER EVENTS
void ofxTLVMMControl::trackGuiSliderEvent(ofxDatGuiSliderEvent e){

    sendOSC(e.target->getName(), e.target->getValue());
    
    /*
    if(e.target->is("localCopies")){
        
        //set the local var.
        test_localCopies = e.target->getValue();
        
        //get the slidername and value
        string labelString = e.target->getName();
        float value = e.target->getValue();
        
        //4. class VMMOscMessageEvent
        static VMMOscMessageEvent vmmOscEvent;
        vmmOscEvent.composeOscMsg(track+1, labelString, test_localCopies);
        ofNotifyEvent(VMMOscMessageEvent::events, vmmOscEvent);
        
    } else {

    }
    */
}


void ofxTLVMMControl::sendOSC(string name, float value) {
    static VMMOscMessageEvent vmmOscEvent;
    vmmOscEvent.composeOscMsg(track+1, name, value);
    ofNotifyEvent(VMMOscMessageEvent::events, vmmOscEvent);
}

void ofxTLVMMControl::setGuiValue(string param, int value){
    
}
void ofxTLVMMControl::setGuiValue(string param, bool value){
    
}

void ofxTLVMMControl::updateGuiToggle(string name, bool value){
    
}
void ofxTLVMMControl::updateGuiSlider(string name, float value){
    if(name == "localCopies"){
        //gui->getSlider(name)->setValue(value);
    }
}
void ofxTLVMMControl::updateGuiSlider(string name, int value){
    
}

 
 
//enable and disable are always automatically called
//in setup. Must call superclass's method as well as doing your own
//enabling and disabling
void ofxTLVMMControl::enable(){
    ofxTLTrack::enable();
    
    cout << "Called from TimelinePanel - ofxTLVMMControl::enable()" << endl;
    
	//other enabling
    OSCsetMatCapSlider->setEnabled(true);
    OSCsetTrackSlider->setEnabled(true);
    localSlicesSlider->setEnabled(true);
    localCopiesSlider->setEnabled(true);
    globalCopiesSlider->setEnabled(true);
    mirrorDistanceSlider->setEnabled(true);
    
    playNoteOffToggle->setEnabled(true);
    //playNoteOffToggle->setEnabled(true);
    
    //showGui = true;
    
    cout << "enable() - showGui " << showGui << endl;
    
}

void ofxTLVMMControl::disable(){
    ofxTLTrack::disable();

    cout << "Called from TimelinePanel - ofxTLVMMControl::disable()" << endl;
    
	//other disabling
    OSCsetMatCapSlider->setEnabled(false);
    OSCsetTrackSlider->setEnabled(false);
    localSlicesSlider->setEnabled(false);
    localCopiesSlider->setEnabled(false);
    globalCopiesSlider->setEnabled(false);
    mirrorDistanceSlider->setEnabled(false);
    
    playNoteOffToggle->setEnabled(false);
    //playNoteOffToggle->setVisible(false);
    
    //showGui = false;
    
    cout << "disable() - showGui " << showGui << endl;
}

void ofxTLVMMControl::trackGuiDelete(){
    
    delete OSCsetMatCapSlider;
    delete OSCsetTrackSlider;
    delete localSlicesSlider;
    delete localCopiesSlider;
    delete globalCopiesSlider;
    delete mirrorDistanceSlider;
    delete playNoteOffToggle;
    delete playAllToggle;
    delete mirrorToggle;
    delete mirrorXToggle;
    delete mirrorYToggle;
    delete mirrorZToggle;
    
    //  REMOVE LISTENERS
    //ofRemoveListener(trackGui->newGUIEvent, this, &ofxTLVMMControl::trackGuiEvent);
    //ofRemoveListener(, this, &ofxTLVMMControl::trackGuiSliderEvent);
    //ofRemoveListener(OSCsetTrackSlider, this, &ofxTLVMMControl::trackGuiSliderEvent);
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
    
    //FINAL PLACEMENT CODE
    //column 1
    OSCsetMatCapSlider->setPosition(bounds.getX(), bounds.getY());
    OSCsetMatCapSlider->setVisible(bounds.getBottom()-bounds.getTop() < OSCsetMatCapSlider->getHeight() ? false : true);
    OSCsetMatCapSlider->update();
    
    OSCsetTrackSlider->setPosition(bounds.getX(), bounds.getY()+compH);
    OSCsetTrackSlider->setVisible(bounds.getBottom()-bounds.getTop() < (OSCsetTrackSlider->getHeight()+compH) ? false : true);
    OSCsetTrackSlider->update();
    
    localSlicesSlider->setPosition(bounds.getX(), bounds.getY()+(compH*2));
    localSlicesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (localSlicesSlider->getHeight()+(compH*2)) ? false : true);
    localSlicesSlider->update();
    
    localCopiesSlider->setPosition(bounds.getX(), bounds.getY()+(compH*3));
    localCopiesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (localCopiesSlider->getHeight()+(compH*3)) ? false : true);
    localCopiesSlider->update();
    
    globalCopiesSlider->setPosition(bounds.getX(), bounds.getY()+(compH*4));
    globalCopiesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (globalCopiesSlider->getHeight()+(compH*4)) ? false : true);
    globalCopiesSlider->update();
    
    mirrorDistanceSlider->setPosition(bounds.getX(), bounds.getY()+(compH*5));
    mirrorDistanceSlider->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorDistanceSlider->getHeight()+(compH*5)) ? false : true);
    mirrorDistanceSlider->update();
    
    //column 2
    playNoteOffToggle->setPosition(bounds.getX()+compW, bounds.getY());
    playNoteOffToggle->setVisible(bounds.getBottom()-bounds.getTop() < playNoteOffToggle->getHeight() ? false : true);
    playNoteOffToggle->update();
 
}

//draw your track contents. use ofRectangle bounds to know where to draw
//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
void ofxTLVMMControl::draw(){
    
   
    OSCsetMatCapSlider->draw();
    OSCsetTrackSlider->draw();
    localSlicesSlider->draw();
    localCopiesSlider->draw();
    globalCopiesSlider->draw();
    mirrorDistanceSlider->draw();
    
    
    playNoteOffToggle->draw();
    
    
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
    savedButtonsTrack.addValue(OSCsetMatCap.getName(), OSCsetMatCap.get());
    savedButtonsTrack.addValue(OSCsetTrack.getName(), OSCsetTrack.get());
    savedButtonsTrack.addValue(localSlices.getName(), localSlices.get());
    savedButtonsTrack.addValue(localCopies.getName(), localCopies.get());
    savedButtonsTrack.addValue(globalCopies.getName(), globalCopies.get());
    savedButtonsTrack.addValue(mirrorDistance.getName(), mirrorDistance.get());
    savedButtonsTrack.addValue("playNoteOff", playNoteOff);
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
        int VMM_OSCsetMatCap = savedVMMSettings.getValue("VMM:OSCsetMatCap", 0);
        sendOSC("OSCsetMatCap", VMM_OSCsetMatCap);
        OSCsetMatCap.set(VMM_OSCsetMatCap);
        
        int VMM_OSCsetTrack = savedVMMSettings.getValue("VMM:OSCsetTrack", 0);
        //sendOSC("OSCsetTrack", VMM_OSCsetTrack);
        OSCsetTrack.set(VMM_OSCsetTrack);
        
        int VMM_localSlices = savedVMMSettings.getValue("VMM:localSlices", 0);
        sendOSC("localSlices", VMM_localSlices);
        localSlices.set(VMM_localSlices);
        
        int VMM_localCopies = savedVMMSettings.getValue("VMM:localCopies", 0);
        sendOSC("localCopies", VMM_localCopies);
        localCopies.set(VMM_localCopies);
        
        int VMM_globalCopies = savedVMMSettings.getValue("VMM:globalCopies", 0);
        sendOSC("globalCopies", VMM_globalCopies);
        globalCopies.set(VMM_globalCopies);
        
        int VMM_mirrorDistance = savedVMMSettings.getValue("VMM:mirrorDistance", 0);
        sendOSC("mirrorDistance", VMM_mirrorDistance);
        mirrorDistance.set(VMM_mirrorDistance);
        
        bool VMM_playNoteOff = savedVMMSettings.getValue("VMM:playNoteOff", 0);
        sendOSC("playNoteOff", VMM_playNoteOff);
        playNoteOff = VMM_playNoteOff;
        
    }else{
        ofLogError("LOAD") <<  "ofxTLVMMControl::load() - unable to load: " << savedClipSettingsPath ;
        return;
    }
}

void ofxTLVMMControl::clear(){

}
