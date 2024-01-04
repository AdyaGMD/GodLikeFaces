#include <Geode/Geode.hpp>
#include <Geode/modify/GJDifficultySprite.hpp>
#include <Geode/modify/RateStarsLayer.hpp>

using namespace geode::prelude;

int _featureState;

int _difficulty;
int _demon;

GJDifficultySprite* _diffSprite;

void specialTexturesCheck(GJDifficultySprite* self) {
	if (_featureState == 4) {
		std::string difficultyString = "difficulty_"_spr + std::to_string(_difficulty) + "_" + std::to_string(_demon) + "_god.png";
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

class $modify(RateStarsLayer) {
	void onFeature(CCObject* obj) {
		RateStarsLayer::onFeature(obj);
		(_difficulty == 6) ? _demon = 1 : _demon = 0;
		return;
	}
	void selectRating(CCObject* obj) {
		RateStarsLayer::selectRating(obj);
		(_difficulty == 6) ? _demon = 1 : _demon = 0;
		specialTexturesCheck(_diffSprite);
		return;
	}
};