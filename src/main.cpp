#include <Geode/Geode.hpp>
#include <Geode/modify/GJDifficultySprite.hpp>

using namespace geode::prelude;

class $modify(GFDifficultySprite, GJDifficultySprite) {
	struct Fields {
		int m_difficulty;
		GJDifficultyName m_difficultyName;
	};

	void specialTexturesCheck() {
		auto diff = m_fields->m_difficulty;
		auto name = diff > 5 ? m_fields->m_difficultyName : GJDifficultyName::Short;
		setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			m_featureState == GJFeatureState::Legendary || m_featureState == GJFeatureState::Mythic ?
				fmt::format("difficulty_{}_{}_{}_god.png"_spr, diff, (int)name, (int)m_featureState).c_str() :
				getDifficultyFrame(diff, name).c_str()
		));
	}

	void updateFeatureState(GJFeatureState state) {
		GJDifficultySprite::updateFeatureState(state);
		specialTexturesCheck();
		return;
	}

	static GJDifficultySprite* create(int diff, GJDifficultyName name) {
		auto self = static_cast<GFDifficultySprite*>(GJDifficultySprite::create(diff, name));
		self->m_fields->m_difficulty = diff;
		self->m_fields->m_difficultyName = diff > 5 ? name : GJDifficultyName::Short;
		return self;
	}

	void updateDifficultyFrame(int diff, GJDifficultyName name) {
		GJDifficultySprite::updateDifficultyFrame(diff, name);
		m_fields->m_difficulty = diff;
		m_fields->m_difficultyName = diff > 5 ? name : GJDifficultyName::Short;
		specialTexturesCheck();
		return;
	}
};
