//
// IGameCamera.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 04:15:45 2017 Sousa Victor
// Last update Sat Jun 17 22:54:45 2017 Sousa Victor
//

#ifndef AGAMECAMERA_HPP_
#define AGAMECAMERA_HPP_

#include "AGameObject.hpp"

namespace indie {

    class AGameCamera : public AGameObject, public irr::scene::ICameraSceneNode {

    public:
        AGameCamera(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode* parent, irr::s32 id,
                    const irr::core::rect<irr::s32>& viewPort,
			        const irr::core::vector3df& position = irr::core::vector3df(0,0,0),
			        const irr::core::vector3df& rotation = irr::core::vector3df(0,0,0),
                    const irr::core::vector3df& scale = irr::core::vector3df(1.0f,1.0f,1.0f));
        AGameCamera(const AGameCamera &cam);
        AGameCamera &operator=(const AGameCamera &cam);
        ~AGameCamera();

        virtual void render() {
            this->_camera->render();
        };
        virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const {
            return this->_camera->getBoundingBox();
        }
        virtual irr::core::rect<irr::s32> const &getViewPort() const {
            return this->_viewport;
        }
        virtual irr::scene::ICameraSceneNode* getCamera() const  {
            return this->_camera;
        }

        virtual void OnFrame() = 0;

    protected:
        irr::core::rect<irr::s32> _viewport;
        irr::scene::ICameraSceneNode* _camera;

    public: ///!\ do not ever think to touch this!   we are redirecting ICameraSceneNode function with custom parameter
		virtual void setProjectionMatrix(const irr::core::matrix4& projection, bool isOrthogonal=false) {
            this->_camera->setProjectionMatrix(projection, isOrthogonal);
        }
		virtual const irr::core::matrix4& getProjectionMatrix() const {
            return this->_camera->getProjectionMatrix();
        }
		virtual const irr::core::matrix4& getViewMatrix() const {
            return this->_camera->getViewMatrix();
        }
		virtual void setViewMatrixAffector(const irr::core::matrix4& affector) {
            this->_camera->setViewMatrixAffector(affector);
        }
		virtual const irr::core::matrix4& getViewMatrixAffector() const {
            return this->_camera->getViewMatrixAffector();
        }
		virtual bool OnEvent(const irr::SEvent& event) {
            return this->_camera->OnEvent(event);
        }
		virtual void setTarget(const irr::core::vector3df& pos) {
            this->_camera->setTarget(pos);
        }
		virtual void setRotation(const irr::core::vector3df& rotation) {
            this->_camera->setRotation(rotation);
        }
        virtual void setPosition(const irr::core::vector3df& position) {
            this->_camera->setPosition(position);
        }
		virtual const irr::core::vector3df& getTarget() const {
            return this->_camera->getTarget();
        }
		virtual void setUpVector(const irr::core::vector3df& pos) {
            this->_camera->setUpVector(pos);
        }
		virtual const irr::core::vector3df& getUpVector() const {
            return this->_camera->getUpVector();
        }
		virtual irr::f32 getNearValue() const {
            return this->_camera->getNearValue();
        }
		virtual irr::f32 getFarValue() const {
            return this->_camera->getFarValue();
        }
		virtual irr::f32 getAspectRatio() const {
            return this->_camera->getAspectRatio();
        }
		virtual irr::f32 getFOV() const {
            return this->_camera->getFOV();
        }
		virtual void setNearValue(irr::f32 zn) {
            this->_camera->setNearValue(zn);
        }
		virtual void setFarValue(irr::f32 zf) {
            this->_camera->setFarValue(zf);
        }
		virtual void setAspectRatio(irr::f32 aspect) {
            this->_camera->setAspectRatio(aspect);
        }
		virtual void setFOV(irr::f32 fovy) {
            this->_camera->setFOV(fovy);
        }
		virtual const irr::scene::SViewFrustum* getViewFrustum() const {
            return this->_camera->getViewFrustum();
        }
		virtual void setInputReceiverEnabled(bool enabled) {
            this->_camera->setInputReceiverEnabled(enabled);
        }
		virtual bool isInputReceiverEnabled() const {
            return this->_camera->isInputReceiverEnabled();
        }
		virtual bool isOrthogonal() const {
			return this->_camera->isOrthogonal();
		}
		virtual void bindTargetAndRotation(bool bound) {
            this->_camera->bindTargetAndRotation(bound);
        }
		virtual bool getTargetAndRotationBinding(void) const {
            return this->_camera->getTargetAndRotationBinding();
        }
		virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const {
			this->_camera->serializeAttributes(out, options);
		}
		virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) {
			this->_camera->deserializeAttributes(in, options);
		}

    };

}

#else

namespace indie {
    class AGameCamera;
}

#endif /*AGAMECAMERA_HPP_*/
