#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	//ofBackground(66,66,66);

	curEventID = 1;
	nEvents = 0;

	/*
	grabcam controls

	Left click drag = rotate
	Right click drag = zoom
	hold 'h' whilst left click drag = pan
	'r' key = reset
	's' key = save pose
	'l' key = load saved pose
	*/

	

	int pitchWidth	= 120;
	int pitchHeight = 90;

	displayScale = 3.0f;

	displayWidth	= floor(pitchWidth*displayScale);
	displayHeight	= floor(pitchHeight*displayScale);

	string a = "displayWidth "+ofToString(displayWidth)+" displayHeight:"+ofToString(displayHeight)+"\n";
	printf(a.c_str());

	drawMesh		= true;
	drawSpheres		= true;


	//add one vertex to the mesh for each pixel
	for (int y = 0; y < displayHeight; y++){
		for (int x = 0; x < displayWidth; x++){
			mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
			mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data
		}
	}
	
	for (int y = 0; y<displayHeight-1; y++){
		for (int x=0; x<displayWidth-1; x++){
			mainMesh.addIndex(x+y*displayWidth);				// 0
			mainMesh.addIndex((x+1)+y*displayWidth);			// 1
			mainMesh.addIndex(x+(y+1)*displayWidth);			// 10
			
			mainMesh.addIndex((x+1)+y*displayWidth);			// 1
			mainMesh.addIndex((x+1)+(y+1)*displayWidth);		// 11
			mainMesh.addIndex(x+(y+1)*displayWidth);			// 10
		}
	}
	
	// xml loading

	string message;
	string filename = "xml/699948.xml"; 
	
	if( xml.loadFile(filename) ){
		message = filename+" loaded!";
		processXML();
	}else{
		message = "unable to load "+filename+" check data/ folder";        
	}
	printf(message.c_str());

	
	//this determines how much we push the meshes out
	extrusionAmount = 400.0;


}

//--------------------------------------------------------------
void testApp::update(){
	

	if(ofGetFrameNum() % 15 ==0) {
		curEventID++;
		processXML();
	}

	/*
	//update the mesh if we have a new frame
	if (vidGrabber.isFrameNew()){
		//this determines how far we extrude the mesh
		for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){

			ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
									 vidGrabber.getPixels()[i*3+1]/255.f,			// g
									 vidGrabber.getPixels()[i*3+2]/255.f);			// b
			
			//now we get the vertex aat this position
			//we extrude the mesh based on it's brightness
			ofVec3f tmpVec = mainMesh.getVertex(i);
			tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
			mainMesh.setVertex(i, tmpVec);

			mainMesh.setColor(i, sampleColor);
		}
	}*/





}

//--------------------------------------------------------------
void testApp::draw(){

 
    ofBackgroundGradient( ofColor(66,66,66), ofColor(10, 10, 10), OF_GRADIENT_CIRCULAR);
	

	//we have to disable depth testing to draw the video frame
	//ofDisableDepthTest();
	//	vidGrabber.draw(20,20);
	
	//but we want to enable it to show the mesh
	//ofEnableDepthTest();
	//cam.begin();	
	grabCam.begin();


	//You can either draw the mesh or the wireframe
	ofSetColor(255, 255, 255);
	if(drawMesh) mainMesh.drawWireframe();
	if(drawSpheres){
		for(int i =0; i < points.size(); i++){
			ofDrawSphere(points[i], 1);
		}
	}

	// corners
	ofSetColor(255, 0, 0);
	ofDrawSphere(ofPoint(0.0,displayHeight, 0.0), 2);
	ofDrawSphere(ofPoint(displayWidth,displayHeight, 0.0), 2);
	ofDrawSphere(ofPoint(displayWidth,0.0, 0.0), 2);

	//mainMesh.drawFaces();
	//cam.end();
	grabCam.end();

	//draw framerate for fun
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate() , 2)+ " Event: "+ofToString(curEventID-1)+" of "+ofToString(nEvents);
	ofDrawBitmapString(msg, 10, 20);

}
//--------------------------------------------------------------
void testApp::processXML(){

	xml.pushTag("Games");
	xml.pushTag("Game");
	nEvents = xml.getNumTags("Event");
	points.resize(nEvents);

	if(nEvents > 0){
		for(int i = curEventID-1; i < curEventID; i++){

			if(i < nEvents){
			
			int min	= xml.getAttribute("Event","min", -1, i);
			int sec	= xml.getAttribute("Event","sec", -1, i);

			double x	= xml.getAttribute("Event","x", -1, i);
			double y	= xml.getAttribute("Event","y", -1, i);
			double z	= xml.getAttribute("Event","z", -1, i);

			int outcome		= xml.getAttribute("Event", "outcome", -1, 1);
			int assist		= xml.getAttribute("Event", "assist", -1, 1); // value = 1 means led to a goal
			int keypass		= xml.getAttribute("Event", "assist", -1, 1); // Will only appear on an event if this event led directly to a shot off target, blocked or saved. Positive Integer

			int vertexID	= (x*displayWidth) + (y*displayWidth);
			int mVertex		= displayWidth*displayHeight;

			ofVec3f tmpVec	= mainMesh.getVertex(vertexID);

			tmpVec.z = ofRandom(-20, 20);
			if(z != -1) tmpVec.z = z;
			tmpVec.x = (x/100)*displayWidth;
			tmpVec.y = (y/100)*displayHeight;

			if(tmpVec.x !=0 || tmpVec.y != 0) points[i] = tmpVec;
						
			//ofFloatColor sampleColor(1.0f,1.f, 1.f);
			//mainMesh.setVertex(i, tmpVec);
			//mainMesh.setColor(i, sampleColor);

			string msg = "outcome:"+ofToString(outcome)+" min;"+ofToString(min)+" sec:"+ofToString(sec)+" x;"+ofToString(x,4)+" y:"+ofToString(y,4)+" \n";
			//if(vertexID>mVertex)msg = "--"+msg;
			if(outcome != 1) printf(msg.c_str());

			}

		}

	}

	printf("nEvents %i \n", nEvents);
	/*
	if(xml.exists("Games")){
		xml.setTo("Games[0]");
		if(xml.exists("Game")){
			xml.setTo("Game[0]");

			if(xml.getName() == "Game" && xml.setTo("Event[0]")){
				do {
				
					string min = xml.getValue("[@min]"); // x attribute
					string sec = xml.getValue("[@sec]"); // y attribute


					string x = xml.getValue("[@x]"); // x attribute
					string y = xml.getValue("[@y]"); // y attribute

					string msg = "min "+min+" sec  "+sec+" x "+x+" y "+y+" \n";

					printf(msg.c_str());
				}
				while(xml.setToSibling());
			}
			
		}
	}*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key) {

		case 'f':
			ofToggleFullscreen();
		break;

		case 'm':
			drawMesh = !drawMesh;
		break;

		case 's':
			drawSpheres = !drawSpheres;
		break;
	}

	if (key=='c')
		grabCam.toggleCursorDraw();
	
	if (key=='u')
		grabCam.toggleFixUpwards();
	
	if (key=='s')
		savedPose = grabCam.getGlobalTransformMatrix();
	
	if (key=='l')
		grabCam.setTransformMatrix(savedPose);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}