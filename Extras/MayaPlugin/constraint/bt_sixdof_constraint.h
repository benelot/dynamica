/*
Bullet Continuous Collision Detection and Physics Library Maya Plugin
Copyright (c) 2008 Herbert Law
 
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising
from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:
 
1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must
not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
 
Written by: Herbert Law <Herbert.Law@gmail.com>

Modified by Roman Ponomarev <rponom@gmail.com>
01/22/2010 : Constraints reworked
*/

//bt_sixdof_constraint.h

#ifndef DYN_BT_SIXDOF_CONSTRAINT_H
#define DYN_BT_SIXDOF_CONSTRAINT_H

#include "bt_rigid_body.h"
#include "bt_constraint.h"
#include "sixdof_constraint_impl.h"

class bt_sixdof_constraint_t: public bt_constraint_t, public sixdof_constraint_impl_t {
public:

    virtual void set_damping(float d) {
        //btGeneric6DofConstraint* p2pc = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
        //p2pc->m_setting.m_damping = d;
    }

	virtual float damping() const {
        //btGeneric6DofConstraint const* hc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
        //return hc->m_setting.m_damping;
		return 0;
    }

	virtual void set_breakThreshold(float d) {
        btGeneric6DofConstraint* p2pc = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
        p2pc->setBreakingImpulseThreshold(d);
    }

	virtual void set_enabled(bool e) {
		btGeneric6DofConstraint* p2pc = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
		p2pc->setEnabled(e);
	}

    virtual void set_LinLimit(vec3f& lower, vec3f& upper) {
		btGeneric6DofConstraint* sixdof = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
		btVector3 btlow(lower[0], lower[1], lower[2]);
		btVector3 btupp(upper[0], upper[1], upper[2]);
		sixdof->setLinearLowerLimit(btlow);
		sixdof->setLinearUpperLimit(btupp);
    }

	virtual void set_AngLimit(vec3f& lower, vec3f& upper) {
		btGeneric6DofConstraint* sixdof = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
		btVector3 btlow(lower[0], lower[1], lower[2]);
		btVector3 btupp(upper[0], upper[1], upper[2]);
		sixdof->setAngularLowerLimit(btlow);
		sixdof->setAngularUpperLimit(btupp);
    }

	virtual void get_local_frameA(vec3f& p, quatf& r)const
	{
		const btGeneric6DofConstraint* sc = static_cast<const btGeneric6DofConstraint*>(m_constraint.get());
		p[0] = sc->getFrameOffsetA().getOrigin().x();
		p[1] = sc->getFrameOffsetA().getOrigin().y();
		p[2] = sc->getFrameOffsetA().getOrigin().z();

		btQuaternion orn = sc->getFrameOffsetA().getRotation();
		r[0] = orn.getW();
		r[1] = orn.getX();
		r[2] = orn.getY();
		r[3] = orn.getZ();
	}

	virtual void get_local_frameB(vec3f& p, quatf& r) const
	{
		const btGeneric6DofConstraint* sc = static_cast<const btGeneric6DofConstraint*>(m_constraint.get());
		p[0] = sc->getFrameOffsetB().getOrigin().x();
		p[1] = sc->getFrameOffsetB().getOrigin().y();
		p[2] = sc->getFrameOffsetB().getOrigin().z();

		btQuaternion orn = sc->getFrameOffsetB().getRotation();
		r[0] = orn.getW();
		r[1] = orn.getX();
		r[2] = orn.getY();
		r[3] = orn.getZ();
	}
	
	virtual void get_frameA(vec3f& p, quatf& r) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform& btxform = sc->getFrameOffsetA();
        btQuaternion bq = btxform.getRotation();
        btVector3 bp = btxform.getOrigin();
        p = vec3f(bp.x(), bp.y(), bp.z());
        r = quatf(bq.w(), bq.x(), bq.y(), bq.z());
	}
	virtual void get_frameB(vec3f& p, quatf& r) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform& btxform = sc->getFrameOffsetB();
        btQuaternion bq = btxform.getRotation();
        btVector3 bp = btxform.getOrigin();
        p = vec3f(bp.x(), bp.y(), bp.z());
        r = quatf(bq.w(), bq.x(), bq.y(), bq.z());
	}
	virtual void get_invFrameA(vec3f& p, quatf& r) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform btxform = sc->getFrameOffsetA().inverse();
        btQuaternion bq = btxform.getRotation();
        btVector3 bp = btxform.getOrigin();
        p = vec3f(bp.x(), bp.y(), bp.z());
        r = quatf(bq.w(), bq.x(), bq.y(), bq.z());
	}
	virtual void get_invFrameB(vec3f& p, quatf& r) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform btxform = sc->getFrameOffsetB().inverse();
        btQuaternion bq = btxform.getRotation();
        btVector3 bp = btxform.getOrigin();
        p = vec3f(bp.x(), bp.y(), bp.z());
        r = quatf(bq.w(), bq.x(), bq.y(), bq.z());
	}
	virtual void worldToA(vec3f& w, vec3f& p) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform w2a = (sc->getRigidBodyA().getWorldTransform() * sc->getFrameOffsetA()).inverse();
		btVector3 bw(w[0], w[1], w[2]);
		btVector3 bp = w2a * bw;
		p = vec3f(bp[0], bp[1], bp[2]);
	}
	virtual void worldFromB(vec3f& p, vec3f& w) const
	{
		btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		const btTransform b2w = sc->getRigidBodyB().getWorldTransform() * sc->getFrameOffsetB();
		btVector3 bp(p[0], p[1], p[2]);
		btVector3 bw = b2w * bp;
		w = vec3f(bw[0], bw[1], bw[2]);
	}

	virtual void set_world(vec3f const &p, quatf const& r) {
        btGeneric6DofConstraint* sc = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
        btVector3 worldP(p[0], p[1], p[2]);
		btQuaternion worldR(r[1], r[2], r[3], r[0]);
		btTransform frameAinW(worldR, worldP);
		btTransform frameA = sc->getRigidBodyA().getWorldTransform().inverse() * frameAinW;
		btTransform frameB = sc->getRigidBodyB().getWorldTransform().inverse() * frameAinW;
		sc->getFrameOffsetA() = frameA;
		sc->getFrameOffsetB() = frameB;
    }

	virtual void get_world(vec3f &p, quatf& r) const {
        btGeneric6DofConstraint const* sc = static_cast<btGeneric6DofConstraint const*>(m_constraint.get());
		btTransform frameAinW = sc->getRigidBodyA().getWorldTransform() * sc->getFrameOffsetA();
        btQuaternion bq = frameAinW.getRotation();
        btVector3 bp = frameAinW.getOrigin();
        p = vec3f(bp.x(), bp.y(), bp.z());
        r = quatf(bq.w(), bq.x(), bq.y(), bq.z());
    }

	virtual void update_constraint(rigid_body_impl_t* rb)
	{
		btGeneric6DofConstraint* sc = static_cast<btGeneric6DofConstraint*>(m_constraint.get());
        btRigidBody* bt_body = static_cast<bt_rigid_body_t*>(rb)->body();
		btTransform frameW, frameL;
		if(bt_body == &sc->getRigidBodyA())
		{
			frameW = sc->getRigidBodyB().getWorldTransform() * sc->getFrameOffsetB();
			frameL = sc->getRigidBodyA().getWorldTransform().inverse() * frameW;
			sc->getFrameOffsetA() = frameL;
		}
		else if(bt_body == &sc->getRigidBodyB())
		{
			frameW = sc->getRigidBodyA().getWorldTransform() * sc->getFrameOffsetA();
			frameL = sc->getRigidBodyB().getWorldTransform().inverse() * frameW;
			sc->getFrameOffsetB() = frameL;
		}
		setPivotChanged(true);
	}



protected:
    friend class bt_solver_t;

    bt_sixdof_constraint_t(rigid_body_impl_t* rb, vec3f const& pivot, quatf const& rot): 
        sixdof_constraint_impl_t()
    {
        btRigidBody& bt_body = *static_cast<bt_rigid_body_t*>(rb)->body();
        btVector3 p(pivot[0], pivot[1], pivot[2]);
		btQuaternion q(rot[1], rot[2], rot[3], rot[0]);
		btTransform frameInA(q, p);
		btGeneric6DofConstraint* sixdof = new btGeneric6DofConstraint(bt_body, frameInA, false);
        m_constraint.reset(sixdof);
		rb->add_constraint(this);
    }
    bt_sixdof_constraint_t(rigid_body_impl_t* rbA, vec3f const& pivotA, quatf const& rotA, rigid_body_impl_t* rbB, vec3f const& pivotB, quatf const& rotB): 
        sixdof_constraint_impl_t()
    {
        btRigidBody& bt_bodyA = *static_cast<bt_rigid_body_t*>(rbA)->body();
        btRigidBody& bt_bodyB = *static_cast<bt_rigid_body_t*>(rbB)->body();
        btVector3 pA(pivotA[0], pivotA[1], pivotA[2]);
		btQuaternion qA(rotA[1], rotA[2], rotA[3], rotA[0]);
		btTransform frameInA(qA, pA);
        btVector3 pB(pivotB[0], pivotB[1], pivotB[2]);
		btQuaternion qB(rotB[1], rotB[2], rotB[3], rotB[0]);
		btTransform frameInB(qB, pB);
		btGeneric6DofConstraint* sixdof = new btGeneric6DofConstraint(bt_bodyA, bt_bodyB, frameInA, frameInB, false);
        m_constraint.reset(sixdof);
		rbA->add_constraint(this);
		rbB->add_constraint(this);
    }

	virtual void register_name(solver_impl_t* solver, const char* objectName) const
	{
		const btGeneric6DofConstraint* sc = static_cast<const btGeneric6DofConstraint*>(m_constraint.get());
		solver->register_name(sc,objectName);
	}

private:

};

#endif //DYN_BT_SIXDOF_CONSTRAINT_H
