#include <Geode/Geode.hpp>
#include <Geode/modify/GJDifficultySprite.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/RateStarsLayer.hpp>

using namespace geode::prelude;

int _featureState;

int _difficulty;
int _demon;

GJDifficultySprite* _diffSprite;

void specialTexturesCheck(GJDifficultySprite* self) {
	if (_featureState > 2) {
		std::string difficultyString = "difficulty_"_spr + std::to_string(_difficulty) + "_" + std::to_string(_demon) + "_" + std::to_string(_featureState) + "_god.png";
		//log::info("{}", difficultyString);
    	self->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(difficultyString.c_str()));
	}
}

class $modify(GJDifficultySprite) {
	void updateFeatureState(GJFeatureState state) {
		//state = static_cast<GJFeatureState>(4);
		GJDifficultySprite::updateFeatureState(state);
		_featureState = static_cast<int>(state);
		specialTexturesCheck(this);
		return;
	}
	static GJDifficultySprite* create(int diff, GJDifficultyName demon) {
		_difficulty = diff;
		_demon = static_cast<int>(demon);
		_featureState = 0;
		return GJDifficultySprite::create(diff, demon);
	}
	void updateDifficultyFrame(int diff, GJDifficultyName demon) {
		GJDifficultySprite::updateDifficultyFrame(diff, demon);
		_difficulty = diff;
		_demon = static_cast<int>(demon);
		_diffSprite = this;
		specialTexturesCheck(this);
		return;
	}
};

// class $modify(RateStarsLayer) {

// 	bool enable = true;

// 	bool init(int a, bool b, bool c) {
// 		auto result = RateStarsLayer::init(a, b, c);
// 		if (b == false && c == false) enable = false;
// 		return result;
// 	}

// 	void onFeature(CCObject* obj) {
// 		bool wasFaceModified = false;
// 		if (_featureState > 2) wasFaceModified = true;
// 		RateStarsLayer::onFeature(obj);
// 		if (wasFaceModified) {
// 			_diffSprite->updateDifficultyFrame(_difficulty, static_cast<GJDifficultyName>(_demon));
// 		}
// 		if (_difficulty == 6) {
// 			_demon = 1;
// 			(_featureState > 2) ? _diffSprite->setPositionY(20.950f) : _diffSprite->setPositionY(25.950f);
// 		} else {
// 			_demon = 0;
// 			_diffSprite->setPositionY(25.950f);
// 		}
// 		return;
// 	}
// 	void selectRating(CCObject* obj) {
// 		RateStarsLayer::selectRating(obj);
// 		if (!enable) return;
// 		if (_difficulty == 6) {
// 			_demon = 1;
// 			if (_featureState > 2)
// 			_diffSprite->setPositionY(20.950f);
// 		} else {
// 			_demon = 0;
// 			_diffSprite->setPositionY(25.950f);
// 		}
// 		if (_featureState > 2) {
// 			specialTexturesCheck(_diffSprite);
// 		}
// 		return;
// 	}
// };
