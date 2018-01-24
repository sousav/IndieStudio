//
// GroundMaterial.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/sources/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May 16 12:19:46 2017 Sousa Victor
// Last update Tue May 16 12:20:37 2017 Sousa Victor
//

#ifndef GROUNDMATERIAL_HPP_
#define GROUNDMATERIAL_HPP_

namespace indie {

    class GroundMaterial {

    public: enum SurfaceType {
            Hard,
            Soft
        };

    public:
        GroundMaterial();
        ~GroundMaterial();

        float getGrip() const;
        void setGrip(float grip);

        float getDrag() const;
        void setDrag(float drag);

    private:
        //PhysicMaterial physicMaterial;
        float _grip;
        float _drag;
        SurfaceType _surfaceType;

        // TireMarksRenderer marksRenderer;
        // TireParticleEmitter particleEmitter;
	};

}

#endif /*GROUNDMATERIAL_HPP_*/
