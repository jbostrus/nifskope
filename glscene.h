/***** BEGIN LICENSE BLOCK *****

BSD License

Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools projectmay not be
   used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***** END LICENCE BLOCK *****/

#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGL>
#include <QRegExp>

#include "nifmodel.h"

#include "glnode.h"
#include "glproperty.h"
#include "gltransform.h"
#include "gltex.h"

class Scene
{
public:
	Scene();
	~Scene();

	void clear( bool flushTextures = true );
	void make( NifModel * nif, bool flushTextures = false );
	void make( NifModel * nif, int blockNumber, QStack<int> & nodestack );
	
	void update( const NifModel * nif, const QModelIndex & index );
	
	void transform( const Transform & trans, float time = 0.0 );
	void draw();
	void drawShapes();
	void drawNodes();
	void drawHavok();
	
	GLTex * bindTexture( const QModelIndex & );
	void setupLights( Node * node );
	
	Node * getNode( const NifModel * nif, const QModelIndex & iNode );
	Property * getProperty( const NifModel * nif, const QModelIndex & iProperty );

	NodeList nodes;
	PropertyList properties;
	NodeList lights;

	NodeList roots;

	mutable QHash<int,Transform> worldTrans;
	mutable QHash<int,Transform> viewTrans;
	
	Transform view;
	
	bool animate;
	
	float time;

	bool texturing;
	QList<GLTex*> textures;
	
	bool blending;
	bool lighting;
	
	bool highlight;
	int currentNode;
	
	bool showHidden;
	bool showNodes;
	bool showHavok;
	
	QRegExp expCull;
	bool onlyTextured; // if true only textured meshes will be visible
	
	BoundSphere bounds() const;
	
	float	timeMin() const;
	float	timeMax() const;

protected:
	mutable bool sceneBoundsValid, timeBoundsValid;
	mutable BoundSphere bndSphere;
	mutable float tMin, tMax;

	void updateTimeBounds() const;
};

inline void glTranslate( const Vector3 & v )
{
	glTranslatef( v[0], v[1], v[2] );
}

inline void glVertex( const Vector3 & v )
{
	glVertex3fv( v.data() );
}

inline void glVertex( const Vector4 & v )
{
	glVertex3fv( v.data() );
}

inline void glNormal( const Vector3 & v )
{
	glNormal3fv( v.data() );
}

inline void glTexCoord( const Vector2 & v )
{
	glTexCoord2fv( v.data() );
}

inline void glColor( const Color3 & c )
{
	glColor3fv( c.data() );
}

inline void glColor( const Color4 & c )
{
	glColor4fv( c.data() );
}

inline void glMaterial( GLenum x, GLenum y, const Color4 & c )
{
	glMaterialfv( x, y, c.data() );
}


#endif
