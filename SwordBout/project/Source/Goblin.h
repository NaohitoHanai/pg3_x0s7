#pragma once
#include "../Library/GameObject.h"
#include <unordered_map>
class Goblin : public GameObject
{
public:
	Goblin();
	~Goblin();
	void Start() override;
	void Update() override;
	void Draw() override;

	bool AttackLine(VECTOR p1, VECTOR p2, VECTOR pPos);

	void SetPositionAngle(VECTOR pos, float yrot);

	VECTOR Position() {
		return position;
	}
private:
	class ActionBase {
	public:
		ActionBase(Goblin* parent) { pParent = parent; }
		virtual ~ActionBase() {}
		virtual void Start() {}
		virtual void Update() {}
	protected:
		Goblin* pParent;
	};
	class ActionIdle : public ActionBase {
	public:
		ActionIdle(Goblin* parent) : ActionBase(parent) {}
		~ActionIdle() {}
		void Start() override {}
		void Update() override;
	};
	class ActionApproach : public ActionBase {
	public:
		ActionApproach(Goblin* parent) : ActionBase(parent) {}
		~ActionApproach() {}
		void Start() override {}
		void Update() override;
	};
	class ActionAttack : public ActionBase {
	public:
		ActionAttack(Goblin* parent) : ActionBase(parent) {}
		~ActionAttack() {}
		void Start() override;
		void Update() override;
	private:
		float timer;
	};
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	enum State {
		eIdle,
		eApproach,
		eAttack,
		eMax,
	};
private:
	State state;
	std::unordered_map<State, ActionBase*> action;
	void ChangeState(State st);
};