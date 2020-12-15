/*
 * About this class
 *		- Spell object is a procedurally generated Disc object.
 *		- Disc takes care of loading textures etc.
 *		- Call the Disc render function.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <stdio.h>
#include "Disc.h"

///////////////////////////////////////////////////////////////////////////////////////////

class SpellEffect
{
public:
	SpellEffect();
	~SpellEffect();

	void render();

private:
	void initSpellEffect();

	GLuint m_texture;
	char* m_spellTexPath = "gfx/textures/magic.png";

	Disc* spell;
};

///////////////////////////////////////////////////////////////////////////////////////////