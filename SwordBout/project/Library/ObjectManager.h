#pragma once
/// <summary>
/// すべてのオブジェクトを管理します
/// ここからすべてのGameObjectのUpdate()/Draw()を呼び出します
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
	/// クラス名でオブジェクトを探す
	/// </summary>
	/// <typeparam name="C">クラス</typeparam>
	/// <returns>オブジェクトの実態（存在しなければnullptr）</returns>
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
	/// クラスのオブジェクトをすべて探す
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	/// <returns>オブジェクトの実態list</returns>
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
	/// クラス名とタグからオブジェクトを探す
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	/// <param name="tag">タグ</param>
	/// <returns>オブジェクトの実態（存在しなければnullptr）</returns>
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
	/// クラス名とタグからオブジェクトをすべて探す
	/// </summary>
	/// <typeparam name="C">クラス名</typeparam>
	/// <param name="tag">タグ</param>
	/// <returns>オブジェクトの実態list</returns>
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
	/// 描画のプライオリティを設定する
	/// 数値が少ない順に描画されるので、２Ｄでは奥に表示される
	/// ２Ｄで手前に表示したい時、３Ｄで後に描画したい時は、値を高くする
	/// プライオリティが同じものの順番は保証されない
	/// プライオリティのデフォルトは100です
	/// </summary>
	/// <param name="obj">プライオリティを設定するオブジェクト</param>
	/// <param name="order">描画プライオリティ</param>
	void SetDrawOrder(GameObject* _obj, int _order);

	/// <summary>
	/// Updateの優先順位を付ける
	/// </summary>
	/// <param name="_obj"></param>
	/// <param name="_priority"></param>
	void SetPriority(GameObject* _obj, int _priority);

	/// <summary>
	/// GameObjectを削除する
	/// </summary>
	/// <param name="obj">GameObjectのインスタンス</param>
	void DeleteGameObject(GameObject* obj);

	/// <summary>
	/// 全てのGameObjectを削除する
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