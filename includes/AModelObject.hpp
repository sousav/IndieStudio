//
// IModelObject.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_github/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 00:30:11 2017 Sousa Victor
// Last update Thu May 18 19:28:00 2017 Sousa Victor
//

#ifndef IMODELOBJECT_HPP_
#define IMODELOBJECT_HPP_

#include <string>
#include "AGameObject.hpp"

namespace indie {

    class AModelObject : public AGameObject {

    public:
        AModelObject();
        AModelObject(irr::scene::ISceneManager *sceneManager, std::string const &path,
                 irr::scene::ISceneNode *parent = 0, irr::s32 id = -1,
                 const irr::core::vector3df &position = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &rotation = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
         AModelObject(const AModelObject &obj);
         AModelObject &operator=(const AModelObject &obj);
         virtual ~AModelObject();

        virtual void OnFrame() = 0;

    protected:
        std::string _path;
        irr::scene::IMesh* _mesh;
        irr::scene::IMeshSceneNode *_node;

    public:
        virtual const irr::c8* getName() const {
			return this->_node->getName();
		}
		virtual void setName(const irr::c8* name) {
			this->_node->setName(name);
		}
		virtual void setName(const irr::core::stringc& name) {
			this->_node->setName(name);
		}
		virtual const irr::core::aabbox3d<irr::f32> getTransformedBoundingBox() const {
            return this->_node->getTransformedBoundingBox();
		}
        virtual const irr::core::matrix4& getAbsoluteTransformation() const {
			return this->_node->getAbsoluteTransformation();
		}
		virtual irr::core::matrix4 getRelativeTransformation() const {
            return this->_node->getRelativeTransformation();
		}
		virtual bool isVisible() const {
            return this->_node->isVisible();
		}
		virtual bool isTrulyVisible() const {
            return this->_node->isTrulyVisible();
		}
		virtual void setVisible(bool isVisible) {
            this->_node->setVisible(isVisible);
		}
        virtual irr::s32 getID() const {
			return this->_node->getID();
		}
		virtual void setID(irr::s32 id) {
            this->_node->setID(id);
		}
		virtual void addChild(irr::scene::ISceneNode* child) {
            this->_node->addChild(child);
		}
		virtual bool removeChild(irr::scene::ISceneNode* child) {
            return this->_node->removeChild(child);
		}
		virtual void removeAll() {
            this->_node->removeAll();
		}
		virtual void remove() {
            this->_node->remove();
		}
		virtual void addAnimator(irr::scene::ISceneNodeAnimator* animator) {
            this->_node->addAnimator(animator);
		}
		const irr::core::list<irr::scene::ISceneNodeAnimator*>& getAnimators() const {
			return this->_node->getAnimators();
		}
		virtual void removeAnimator(irr::scene::ISceneNodeAnimator* animator) {
            this->_node->removeAnimator(animator);
		}
		virtual void removeAnimators() {
            this->_node->removeAnimators();
		}
		virtual irr::video::SMaterial& getMaterial(irr::u32 num) {
			return this->_node->getMaterial(num);
		}
		virtual irr::u32 getMaterialCount() const {
			return this->_node->getMaterialCount();
		}
		void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue) {
            this->_node->setMaterialFlag(flag, newvalue);
		}
		void setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture* texture) {
            this->_node->setMaterialTexture(textureLayer, texture);
		}
		void setMaterialType(irr::video::E_MATERIAL_TYPE newType) {
            this->_node->setMaterialType(newType);
		}
		virtual const irr::core::vector3df& getScale() const {
			return this->_node->getScale();
		}
		virtual void setScale(const irr::core::vector3df& scale) {
            this->_node->setScale(scale);
		}
		virtual const irr::core::vector3df& getRotation() const {
			return this->_node->getRotation();
		}
		virtual void setRotation(const irr::core::vector3df& rotation) {
			this->_node->setRotation(rotation);
		}
		virtual const irr::core::vector3df& getPosition() const {
			return this->_node->getPosition();
		}
		virtual void setPosition(const irr::core::vector3df& newpos) {
			this->_node->setPosition(newpos);
		}
		virtual irr::core::vector3df getAbsolutePosition() const {
			return this->_node->getAbsolutePosition();
		}
		void setAutomaticCulling( irr::u32 state) {
			this->_node->setAutomaticCulling(state);
		}
		irr::u32 getAutomaticCulling() const {
			return this->_node->getAutomaticCulling();
		}
		virtual void setDebugDataVisible(irr::u32 state) {
			this->_node->setDebugDataVisible(state);
		}
		irr::u32 isDebugDataVisible() const {
			return this->_node->isDebugDataVisible();
		}
		void setIsDebugObject(bool debugObject) {
			this->_node->setIsDebugObject(debugObject);
		}
		bool isDebugObject() const {
            return this->_node->isDebugObject();
		}
		const irr::core::list<irr::scene::ISceneNode*>& getChildren() const {
			return this->_node->getChildren();
		}
		virtual void setParent(irr::scene::ISceneNode* newParent) {
            this->_node->setParent(newParent);
		}
		virtual irr::scene::ITriangleSelector* getTriangleSelector() const {
			return this->_node->getTriangleSelector();
		}
		virtual void setTriangleSelector(irr::scene::ITriangleSelector* selector) {
			this->_node->setTriangleSelector(selector);
		}
		virtual void updateAbsolutePosition() {
			this->_node->updateAbsolutePosition();
		}
		irr::scene::ISceneNode* getParent() const {
			return this->_node->getParent();
		}
		virtual irr::scene::ESCENE_NODE_TYPE getType() const {
			return this->_node->getType();
		}
		virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const {
			this->_node->serializeAttributes(out, options);
		}
		virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) {
			this->_node->deserializeAttributes(in, options);
		}
		virtual irr::scene::ISceneNode* clone(irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0) {
			return this->_node->clone();
		}
		virtual irr::scene::ISceneManager* getSceneManager(void) const {
            return this->_node->getSceneManager();
        }

    };

}

#endif /*IMODELOBJECT_HPP_*/
