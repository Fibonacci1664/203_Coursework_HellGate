#include "SpellEffect.h"


SpellEffect::SpellEffect()
{
	initSpellEffect();
}

SpellEffect::~SpellEffect()
{
	delete spell;
	spell = nullptr;
}

void SpellEffect::render()
{
	spell->render();
}

void SpellEffect::initSpellEffect()
{
	spell = new Disc(20.0f, 0.5f, m_spellTexPath, false, 0);
}
