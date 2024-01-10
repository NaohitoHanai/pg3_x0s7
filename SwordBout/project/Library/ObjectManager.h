#pragma once
/// <summary>
/// ���ׂẴI�u�W�F�N�g���Ǘ����܂�
/// �������炷�ׂĂ�GameObject��Update()/Draw()���Ăяo���܂�
/// </summary>
/// <author>N.Hanai</author>

#include <list>
#include <string>
class GameObject;

namespace ObjectManager {
	void Start();
	void Update();
	void Draw();
	void Release();

	void ChangeScene();

	void Push(GameObject* obj);

	void Destroy(GameObject* obj);

	struct ObjectUpdate {
		GameObject* object;
		bool initialized;
		bool destroyMe;
		bool dontDestroy;
		int priority;
		ObjectUpdate() : object(nullptr), initialized(false), destroyMe(false), dontDestroy(false), priority(0) {}
	};

	struct ObjectDraw {
		GameObject* object;
		int order;
		ObjectDraw() : object(nullptr), order(0) {}
	};

	const std::list<ObjectUpdate>& GetAllObject();

	/// <summary>
	/// �N���X���ŃI�u�W�F�N�g��T��
	/// </summary>
	/// <typeparam name="C">�N���X</typeparam>
	/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
	template<class C> C* FindGameObject()
	{
		const std::list<ObjectUpdate>& objs = GetAllObject();

		for (const ObjectUpdate& node : objs) {
			C* obj = dynamic_cast<C*>(node.object);
			if (obj != nullptr)
				return obj;
		}
		return nullptr;
	}

	/// <summary>
	/// �N���X�̃I�u�W�F�N�g�����ׂĒT��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <returns>�I�u�W�F�N�g�̎���list</returns>
	template<class C> std::list<C*> FindGameObjects()
	{
		std::list<C*> out;
		out.clear();

		const std::list<ObjectUpdate>& objs = GetAllObject();

		for (const ObjectUpdate& node : objs) {
			C* obj = dynamic_cast<C*>(node.object);
			if (obj != nullptr)
				out.emplace_back(obj);
		}
		return out;
	}

	/// <summary>
	/// �N���X���ƃ^�O����I�u�W�F�N�g��T��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <param name="tag">�^�O</param>
	/// <returns>�I�u�W�F�N�g�̎��ԁi���݂��Ȃ����nullptr�j</returns>
	template<class C> C* FindGameObjectWithTag(std::string tag)
	{
		const std::list<ObjectUpdate>& objs = GetAllObject();

		for (const ObjectUpdate& node : objs) {
			C* obj = dynamic_cast<C*>(node.object);
			if (obj != nullptr) {
				if (obj->IsTag(tag))
					return obj;
			}
		}
		return nullptr;
	}

	/// <summary>
	/// �N���X���ƃ^�O����I�u�W�F�N�g�����ׂĒT��
	/// </summary>
	/// <typeparam name="C">�N���X��</typeparam>
	/// <param name="tag">�^�O</param>
	/// <returns>�I�u�W�F�N�g�̎���list</returns>
	template<class C> std::list<C*> FindGameObjectsWithTag(std::string tag)
	{
		std::list<C*> out;
		out.clear();

		const std::list<ObjectUpdate>& objs = GetAllObject();

		for (const ObjectUpdate& node : objs) {
			C* obj = dynamic_cast<C*>(node.object);
			if (obj != nullptr) {
				if (obj->IsTag(tag))
					out.emplace_back(obj);
			}
		}
		return out;
	}


	/// <summary>
	/// �`��̃v���C�I���e�B��ݒ肷��
	/// ���l�����Ȃ����ɕ`�悳���̂ŁA�Q�c�ł͉��ɕ\�������
	/// �Q�c�Ŏ�O�ɕ\�����������A�R�c�Ō�ɕ`�悵�������́A�l����������
	/// �v���C�I���e�B���������̂̏��Ԃ͕ۏ؂���Ȃ�
	/// �v���C�I���e�B�̃f�t�H���g��100�ł�
	/// </summary>
	/// <param name="obj">�v���C�I���e�B��ݒ肷��I�u�W�F�N�g</param>
	/// <param name="order">�`��v���C�I���e�B</param>
	void SetDrawOrder(GameObject* _obj, int _order);

	/// <summary>
	/// Update�̗D�揇�ʂ�t����
	/// </summary>
	/// <param name="_obj"></param>
	/// <param name="_priority"></param>
	void SetPriority(GameObject* _obj, int _priority);

	/// <summary>
	/// GameObject���폜����
	/// </summary>
	/// <param name="obj">GameObject�̃C���X�^���X</param>
	void DeleteGameObject(GameObject* obj);

	/// <summary>
	/// �S�Ă�GameObject���폜����
	/// </summary>
	void DeleteAllGameObject();

	void DontDestroy(GameObject* obj, bool dont = true);
};

template <class C> C* Instantiate()
{
	C* obj = new C;
	return obj;
};

template <class C> C* SingleInstantiate()
{
	C* obj = ObjectManager::FindGameObject<C>();
	if (obj == nullptr) {
		obj = Instantiate<C>();
	}
	return obj;
}