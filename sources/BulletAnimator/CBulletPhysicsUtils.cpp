/*
 *  Copyright (c) 2007-2009  zet.dp.ua
 *  Copyright (c) 2009 Colombian Developers - Team
 *
 *  This file is part of IrrBullet (Bullet Physics Wrapper for Irrlicht)
 *
 *  IrrBullet is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  IrrBullet is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */



#include "CBulletPhysicsUtils.h"

#include "btBulletDynamicsCommon.h"

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletTriangleArray
//! get mesh data. Bullet can use the meshbuffer data directly in btTriangleIndexVertexArray,
//! but Irrlicht indices are 16 bits wide which is not compatible with Bullet :(
//! So we are just using a btTriangleMesh instead, although it would probably
//! be faster to store the indices in int arrays and use these in a btTriangleIndexVertexArray
btTriangleIndexVertexArray* ConvertIrrMeshToBulletTriangleArray(
  irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling)
{
  btVector3 vertices[3];
  irr::u32 i, j, numVertices, numIndices;
  irr::u16* aIrrIndices;

  const int vertStride = sizeof(btVector3);
  const int indexStride = 3*sizeof(int);
  int totalTriangles;

  btTriangleIndexVertexArray* indexVertexArrays = new btTriangleIndexVertexArray();
  btIndexedMesh aIndexedMesh;

  for (i = 0; i < pMesh->getMeshBufferCount(); i++)
  {
    irr::scene::IMeshBuffer* mb = pMesh->getMeshBuffer(i);

    //extract vertex data
    //because the vertices are stored as structs with no common base class,
    // we need to handle each type separately
    if (mb->getVertexType()==irr::video::EVT_STANDARD)
    {
      irr::video::S3DVertex* aIrrVertices=(irr::video::S3DVertex*)mb->getVertices();
      aIrrIndices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      totalTriangles = numIndices/3;


      // TODO: don't forget delete []
      int* aBtIndexBuffer = new int[numIndices];
      btVector3* aBtVertBuffer = new btVector3[numVertices];

      // fill ind
      for (j = 0; j < numIndices; j++)
      {
        aBtIndexBuffer[j] = aIrrIndices[j];
      }
      // fill vert
      for (j = 0; j < numVertices; j++)
      {
        aBtVertBuffer[j].setValue(aIrrVertices[j].Pos.X, aIrrVertices[j].Pos.Y, aIrrVertices[j].Pos.Z);
      }

      aIndexedMesh.m_numTriangles = totalTriangles;
      aIndexedMesh.m_triangleIndexBase = (const unsigned char *)aBtIndexBuffer;
      aIndexedMesh.m_triangleIndexStride = indexStride;
      aIndexedMesh.m_numVertices = numVertices;
      aIndexedMesh.m_vertexBase = (const unsigned char *) &aBtVertBuffer[0].x();
      aIndexedMesh.m_vertexStride = vertStride;
      indexVertexArrays->addIndexedMesh(aIndexedMesh);
    }
    else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
    {
      //same but for S3DVertex2TCoords data
      irr::video::S3DVertex2TCoords* aIrrVertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
      aIrrIndices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      totalTriangles = numIndices/3;

      int* aBtIndexBuffer = new int[numIndices];
      btVector3* aBtVertBuffer = new btVector3[numVertices];

      // fill ind
      for (j = 0; j < numIndices; j++)
      {
        aBtIndexBuffer[j] = aIrrIndices[j];
      }
      // fill vert
      for (j = 0; j < numVertices; j++)
      {
        aBtVertBuffer[j].setValue(
          aIrrVertices[j].Pos.X*scaling.X,
          aIrrVertices[j].Pos.Y*scaling.Y,
          aIrrVertices[j].Pos.Z*scaling.Z);
      }

      aIndexedMesh.m_numTriangles = totalTriangles;
      aIndexedMesh.m_triangleIndexBase = (const unsigned char *)aBtIndexBuffer;
      aIndexedMesh.m_triangleIndexStride = indexStride;
      aIndexedMesh.m_numVertices = numVertices;
      aIndexedMesh.m_vertexBase = (const unsigned char *)&aBtVertBuffer[0].x();
      aIndexedMesh.m_vertexStride = vertStride;
      indexVertexArrays->addIndexedMesh(aIndexedMesh);
    }
    //not bothering with EVT_TANGENTS vertex type
  }

  return indexVertexArrays;
}

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletTriangleMesh
//! get mesh data. Bullet can use the meshbuffer data directly in btTriangleIndexVertexArray,
//! but Irrlicht indices are 16 bits wide which is not compatible with Bullet :(
//! So we are just using a btTriangleMesh instead, although it would probably
//! be faster to store the indices in int arrays and use these in a btTriangleIndexVertexArray
btTriangleMesh* ConvertIrrMeshToBulletTriangleMesh(
  irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling)
{
  btVector3 vertices[3];
  irr::u32 i,j,k,index,numVertices,numIndices;
  irr::u16* mb_indices;

  btTriangleMesh *pTriMesh = new btTriangleMesh();

  for (i=0; i<pMesh->getMeshBufferCount(); i++)
  {
    irr::scene::IMeshBuffer* mb=pMesh->getMeshBuffer(i);

    //extract vertex data
    //because the vertices are stored as structs with no common base class,
    // we need to handle each type separately
    if(mb->getVertexType()==irr::video::EVT_STANDARD)
    {
      irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
      mb_indices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      for(j=0;j<numIndices;j+=3)
      { //get index into vertex list
        for (k=0;k<3;k++)
        { //three verts per triangle
          index = mb_indices[j+k];
          //convert to btVector3
          // we apply scaling factor directly to verticies
          vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X,
                                  mb_vertices[index].Pos.Y*scaling.Y,
                                  mb_vertices[index].Pos.Z*scaling.Z);
        }
        pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
      }


      //FILE* aMeshFile = fopen("mesh.dat", "w");
      //if (aMeshFile)
      //{
      //  fprintf(aMeshFile, "const int NUM_TRIANGLES = %d;\n", mb->getIndexCount()/3);
      //  fprintf(aMeshFile, "const int NUM_INDICES = %d;\n", mb->getIndexCount());
      //  fprintf(aMeshFile, "const int NUM_VERTICES = %d;\n", numVertices);

      //  fprintf(aMeshFile, "REAL gVertices[NUM_VERTICES * 3] = {\n");
      //  for (k = 0; k < numVertices; k++)
      //  {
      //    fprintf(aMeshFile, "  REAL(%10.7f), REAL(%10.7f), REAL(%10.7f),\n",
      //      mb_vertices[k].Pos.X, mb_vertices[k].Pos.Y, mb_vertices[k].Pos.Z
      //    );
      //  }
      //  fprintf(aMeshFile, "};\n");

      //  fprintf(aMeshFile, "int gIndices[NUM_TRIANGLES][3] = {\n");
      //  for (k = 0; k < mb->getIndexCount(); k+=3)
      //  {
      //    fprintf(aMeshFile, "  {%4d, %4d, %4d},\n",
      //      mb_indices[k+0], mb_indices[k+1], mb_indices[k+2]
      //    );
      //  }
      //  fprintf(aMeshFile, "};\n");

      //  fclose(aMeshFile);
      //}

    }
    else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
    {
      //same but for S3DVertex2TCoords data
      irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
      mb_indices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      for(j=0;j<numIndices;j+=3)
      { //index into irrlicht data
        for (k=0;k<3;k++)
        {
          index = mb_indices[j+k];
          // we apply scaling factor directly to verticies
          vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X,
                                  mb_vertices[index].Pos.Y*scaling.Y,
                                  mb_vertices[index].Pos.Z*scaling.Z);
        }
        pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
      }
    }
    //not bothering with EVT_TANGENTS vertex type
  }

  return pTriMesh;
}

//------------------------------------------------------------------------------
//! ConvertIrrMeshToBulletConvexHullShape
//! ConvexHullShape implements an implicit (getSupportingVertex) Convex Hull of a Point Cloud (vertices)
//! No connectivity is needed.
btConvexHullShape* ConvertIrrMeshToBulletConvexHullShape(
  irr::scene::IMesh* pMesh,
  const irr::core::vector3df& scaling)
{
  btVector3 vertices[3];
  irr::u32 i,j,k,index,numVertices;
  irr::u16* mb_indices;

  irr::core::array<btVector3> aBtVertBuffer(512);

  for (i=0; i<pMesh->getMeshBufferCount(); i++)
  {
    irr::scene::IMeshBuffer* mb=pMesh->getMeshBuffer(i);

    //extract vertex data
    //because the vertices are stored as structs with no common base class,
    // we need to handle each type separately
    if(mb->getVertexType()==irr::video::EVT_STANDARD)
    {
      irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
      mb_indices = mb->getIndices();
      numVertices = mb->getVertexCount();
      for(j=0;j<mb->getIndexCount();j+=3)
      { //get index into vertex list
        for (k=0;k<3;k++)
        { //three verts per triangle
          index = mb_indices[j+k];
          //convert to btPoint3
          aBtVertBuffer.push_back(btVector3(
            mb_vertices[index].Pos.X*scaling.X,
            mb_vertices[index].Pos.Y*scaling.Y,
            mb_vertices[index].Pos.Z*scaling.Z));
        }
      }
    }
    else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
    {
      //same but for S3DVertex2TCoords data
      irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
      irr::u16* mb_indices = mb->getIndices();
      irr::s32 numVertices = mb->getVertexCount();
      for(j=0;j<mb->getIndexCount();j+=3)
      { //index into irrlicht data
        for (k=0;k<3;k++)
        {
          irr::s32 index = mb_indices[j+k];
          //convert to btPoint3
          aBtVertBuffer.push_back(btVector3(
            mb_vertices[index].Pos.X*scaling.X,
            mb_vertices[index].Pos.Y*scaling.Y,
            mb_vertices[index].Pos.Z*scaling.Z));
        }
      }
    }
    //not bothering with EVT_TANGENTS vertex type
  }

  btScalar ratio = aBtVertBuffer[0].length();
  for (i = 0; i < aBtVertBuffer.size(); i++)
    aBtVertBuffer[i].normalize();

  btConvexHullShape* aConvexHullShape = new btConvexHullShape((btScalar*)&aBtVertBuffer[0], aBtVertBuffer.size());
  aConvexHullShape->setLocalScaling(btVector3(ratio, ratio, ratio));
  aConvexHullShape->recalcLocalAabb();
  return aConvexHullShape;
}


btTriangleMesh * ConvertTerrainToBulletTriangleMesh(
    irr::scene::ITerrainSceneNode* terrain,
    const irr::core::vector3df& Scaling)
      {
         //mesh converting

            btVector3 vertices[3];
            irr::u32 j,k,index,numVertices,numIndices;
            irr::u16* mb_indices16;
			irr::u32* mb_indices32;
			video::E_INDEX_TYPE indicesType;
            btTriangleMesh *triangleMesh;

            irr::scene::ITerrainSceneNode *pTerrain = terrain;


			scene::CDynamicMeshBuffer* buffer = 0;

			numVertices = terrain->getMesh()->getMeshBuffer(0)->getVertexCount();
			if (numVertices <= 65536)
			{
				//small enough for 16bit buffers
				buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
			}
			else
			{
				//we need 32bit buffers
				buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_32BIT);
			}

            pTerrain->getMeshBufferForLOD(*buffer, 0);

            numVertices = buffer->getVertexCount();
            numIndices = buffer->getIndexCount();
			indicesType = buffer->getIndexType();

			if (indicesType == video::EIT_16BIT)
			{
				mb_indices16 = buffer->getIndices();

				irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)buffer->getVertices();
				btTriangleMesh *pTriMesh = new btTriangleMesh();
				irr::core::vector3df scaling = Scaling;

				for(j = 0; j < numIndices; j += 3)
				{ 
					//index into irrlicht data
					for (k = 0; k < 3; k++)
					{
						index = mb_indices16[j+k];

						// we apply scaling factor directly to verticies
						vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X,
						mb_vertices[index].Pos.Y*scaling.Y,
						mb_vertices[index].Pos.Z*scaling.Z);
					}

					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}

				triangleMesh = pTriMesh;
			}
			else if (indicesType == video::EIT_32BIT)
			{
				mb_indices32 = (u32*)buffer->getIndices();

				irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)buffer->getVertices();
				btTriangleMesh *pTriMesh = new btTriangleMesh();
				irr::core::vector3df scaling = Scaling;

				for(j = 0; j < numIndices; j += 3)
				{ 
					//index into irrlicht data
					for (k = 0; k < 3; k++)
					{
						index = mb_indices32[j+k];

						// we apply scaling factor directly to verticies
						vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X,
						mb_vertices[index].Pos.Y*scaling.Y,
						mb_vertices[index].Pos.Z*scaling.Z);
					}

					pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
				}

				triangleMesh = pTriMesh;
			}
			else
			{
				// bad indices type!
				buffer->drop();

				return NULL;
			}

			buffer->drop();

			return  triangleMesh;
      }


f32 GetMaxRadius(const core::aabbox3d<f32> &box,const core::vector3df &scale)
{
	core::vector3df ext = box.getExtent();

	f32 ret = ext.X * scale.X;
	if (ext.Y * scale.Y > ret) ret = ext.Y * scale.Y;
	if (ext.Z * scale.Z > ret) ret = ext.Z * scale.Z;

	return ret;
}



irr::scene::IAnimatedMeshSceneNode* RepairBoundingBox(irr::scene::IAnimatedMeshSceneNode* node)
{
   irr::scene::IAnimatedMesh * mesh = node->getMesh();

   core::aabbox3df box;
   for (u32 i = 0; i < mesh->getMeshBufferCount(); i++)
   {
      mesh->getMesh(1)->getMeshBuffer(i)->recalculateBoundingBox();
      box.addInternalBox(mesh->getMesh(1)->getMeshBuffer(i)->getBoundingBox());
   }
   mesh->setBoundingBox(box);
   node->setMesh(mesh);
   return node;
}


void BulletToIrr(const btVector3& in, core::vector3df& result)
{
    //result.set(in.getX(), in.getY(), -in.getZ());
	result.set(in.getX(), in.getY(), in.getZ());
} 