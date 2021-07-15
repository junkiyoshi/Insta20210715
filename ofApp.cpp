#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "ABCDEFGHEJKLMNOPQRSTUVWXYZ!";
	int sample_count = 180;
	auto noise_param = ofRandom(1000);
	
	for (int i = 0; i < word.size(); i++) {

		ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
				auto rotation_y = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				auto noise_value = ofNoise(location.x * 0.002, ofGetFrameNum() * 0.005);
				float param = 0.5;
				if (noise_value < 0.3) { param = ofMap(noise_value, 0, 0.3, 0, 0.5); }
				if (noise_value > 0.7) { param = ofMap(noise_value, 0.7, 1, 0.5, 1); }

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(param, 0, 1, -PI * 1, PI * 1), glm::vec3(1, 0, 0));
				location = glm::vec4(location, 0) * rotation_x;


				ofVertex(location);
			}
		}
		ofEndShape();

		ofNoFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
				auto rotation_y = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				ofVertex(location);
			}
		}
		ofEndShape();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}