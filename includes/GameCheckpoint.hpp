/*
** GameCheckpoint.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue May 16 12:41:22 2017 Lucas Gambini
** Last update Wed Jun 14 19:33:09 2017 Lucas Gambini
*/

#ifndef GAMECHECKPOINT_HPP
#define GAMECHECKPOINT_HPP

#include "AGameObject.hpp"

namespace indie {

    class GameCheckpoint : public AGameObject, public irr::scene::IMeshSceneNode {

    public: enum Type {
        GARAGE,
        CONCESSIONNAIRE,
        COURSE,
        IN_COURSE,
        MONEY,
        ONLINE
    };

    public:
        GameCheckpoint(irr::scene::ISceneManager *sceneManager,
                 irr::f32 size, irr::f32 mass, irr::scene::ISceneNode *parent, irr::s32 id, Type type,
                 const irr::f32 radius,
                 const irr::core::vector3df &position = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &rotation = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
         //GameCheckpoint &operator=(const GameCheckpoint &obj);
        ~GameCheckpoint();

        virtual void OnFrame();

        //CCubeSceneNode
        void render();
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
        Type getChType() const;
        bool isBusy() const;
        void setBusy(bool);
        void setLaserVisible(bool);
        bool isLaserVisible() const;
        float getRadius() const;
        irr::core::vector3df getChPosition() const;
        void setChVisible(bool);

        void reCreate();

        //IMeshSceneNode
        void setMesh(irr::scene::IMesh* mesh);
        irr::scene::IMesh* getMesh(void);
        irr::scene::IShadowVolumeSceneNode *addShadowVolumeSceneNode(const irr::scene::IMesh *shadowMesh = 0, irr::s32 id = -1, bool zfailmethod = true, irr::f32 infinity = 1000.0f);
        void setReadOnlyMaterials(bool readonly);
        bool isReadOnlyMaterials() const;

    private:
        irr::scene::IMeshSceneNode *_cylindre;
        Type _type;
        bool _isBusy;
        irr::f32 _radius;
        irr::core::vector3df _pos;
        irr::core::vector3df _rotation;
        irr::core::vector3df _scale;
        irr::video::SColor _color;
        irr::s32 _id;

    public: ///!\ do not ever think to touch this!   we are redirecting ISceneNode function with custom parameter
		virtual const irr::c8* getName() const {
			return this->_cylindre->getName();
		}
		virtual void setName(const irr::c8* name) {
			this->_cylindre->setName(name);
		}
		virtual void setName(const irr::core::stringc& name) {
			this->_cylindre->setName(name);
		}
		virtual const irr::core::aabbox3d<irr::f32> getTransformedBoundingBox() const {
            return this->_cylindre->getTransformedBoundingBox();
		}
        virtual const irr::core::matrix4& getAbsoluteTransformation() const {
			return this->_cylindre->getAbsoluteTransformation();
		}
		virtual irr::core::matrix4 getRelativeTransformation() const {
            return this->_cylindre->getRelativeTransformation();
		}
		virtual bool isVisible() const {
            return this->_cylindre->isVisible();
		}
		virtual bool isTrulyVisible() const {
            return this->_cylindre->isTrulyVisible();
		}
		virtual void setVisible(bool isVisible) {
            this->_cylindre->setVisible(isVisible);
		}
        virtual irr::s32 getID() const {
			return this->_cylindre->getID();
		}
		virtual void setID(irr::s32 id) {
            this->_cylindre->setID(id);
		}
		virtual void addChild(irr::scene::ISceneNode* child) {
            this->_cylindre->addChild(child);
		}
		virtual bool removeChild(irr::scene::ISceneNode* child) {
            return this->_cylindre->removeChild(child);
		}
		virtual void removeAll() {
            this->_cylindre->removeAll();
		}
		virtual void remove() {
            this->_cylindre->remove();
		}
		virtual void addAnimator(irr::scene::ISceneNodeAnimator* animator) {
            this->_cylindre->addAnimator(animator);
		}
		const irr::core::list<irr::scene::ISceneNodeAnimator*>& getAnimators() const {
			return this->_cylindre->getAnimators();
		}
		virtual void removeAnimator(irr::scene::ISceneNodeAnimator* animator) {
            this->_cylindre->removeAnimator(animator);
		}
		virtual void removeAnimators() {
            this->_cylindre->removeAnimators();
		}
		virtual irr::video::SMaterial& getMaterial(irr::u32 num) {
			return this->_cylindre->getMaterial(num);
		}
		virtual irr::u32 getMaterialCount() const {
			return this->_cylindre->getMaterialCount();
		}
		void setMaterialFlag(irr::video::E_MATERIAL_FLAG flag, bool newvalue) {
            this->_cylindre->setMaterialFlag(flag, newvalue);
		}
		void setMaterialTexture(irr::u32 textureLayer, irr::video::ITexture* texture) {
            this->_cylindre->setMaterialTexture(textureLayer, texture);
		}
		void setMaterialType(irr::video::E_MATERIAL_TYPE newType) {
            this->_cylindre->setMaterialType(newType);
		}
		virtual const irr::core::vector3df& getScale() const {
			return this->_cylindre->getScale();
		}
		virtual void setScale(const irr::core::vector3df& scale) {
            this->_cylindre->setScale(scale);
		}
		virtual const irr::core::vector3df& getRotation() const {
			return this->_cylindre->getRotation();
		}
		virtual void setRotation(const irr::core::vector3df& rotation) {
			this->_cylindre->setRotation(rotation);
		}
		virtual const irr::core::vector3df& getPosition() const {
			return this->_cylindre->getPosition();
		}
		virtual void setPosition(const irr::core::vector3df& newpos) {
			this->_cylindre->setPosition(newpos);
		}
		virtual irr::core::vector3df getAbsolutePosition() const {
			return this->_cylindre->getAbsolutePosition();
		}
		void setAutomaticCulling( irr::u32 state) {
			this->_cylindre->setAutomaticCulling(state);
		}
		irr::u32 getAutomaticCulling() const {
			return this->_cylindre->getAutomaticCulling();
		}
		virtual void setDebugDataVisible(irr::u32 state) {
			this->_cylindre->setDebugDataVisible(state);
		}
		irr::u32 isDebugDataVisible() const {
			return this->_cylindre->isDebugDataVisible();
		}
		void setIsDebugObject(bool debugObject) {
			this->_cylindre->setIsDebugObject(debugObject);
		}
		bool isDebugObject() const {
            return this->_cylindre->isDebugObject();
		}
		const irr::core::list<irr::scene::ISceneNode*>& getChildren() const {
			return this->_cylindre->getChildren();
		}
		virtual void setParent(irr::scene::ISceneNode* newParent) {
            this->_cylindre->setParent(newParent);
		}
		virtual irr::scene::ITriangleSelector* getTriangleSelector() const {
			return this->_cylindre->getTriangleSelector();
		}
		virtual void setTriangleSelector(irr::scene::ITriangleSelector* selector) {
			this->_cylindre->setTriangleSelector(selector);
		}
		virtual void updateAbsolutePosition() {
			this->_cylindre->updateAbsolutePosition();
		}
		irr::scene::ISceneNode* getParent() const {
			return this->_cylindre->getParent();
		}
		virtual irr::scene::ESCENE_NODE_TYPE getType() const {
			return this->_cylindre->getType();
		}
		virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const {
			this->_cylindre->serializeAttributes(out, options);
		}
		virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) {
			this->_cylindre->deserializeAttributes(in, options);
		}
		virtual irr::scene::ISceneNode* clone(irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0) {
			return this->_cylindre->clone();
		}
		virtual irr::scene::ISceneManager* getSceneManager(void) const {
            return this->_cylindre->getSceneManager();
        }

    };

}

#else

namespace indie {
    class GameCheckpoint;
}

#endif /* !GAMECHECKPOINT_HPP */
