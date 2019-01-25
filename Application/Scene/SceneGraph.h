#pragma once
#include "Transforms.h"

#include <map>
#include <set>
#include <string>
#include <utility>

namespace Nome::Scene
{

using tc::TAutoPtr;

//Forward declaration
class CSceneNode;
class CEntity;

class CSceneTreeNode : public Flow::CFlowNode
{
	//The matrix that takes you from local coord to world
	DEFINE_OUTPUT_WITH_UPDATE(Matrix3x4, L2WTransform);

public:
	//Public APIs
	CSceneNode* GetOwner() const { return Owner; }
	bool IsValid() const { return Owner; }
	CEntity* GetInstanceEntity() const { return InstanceEntity; }

	//Note: linear time is prob too slow
	CSceneTreeNode* FindChildOfOwner(CSceneNode* owner) const;
	CSceneTreeNode* FindChild(const std::string& name) const;

    const std::set<CSceneTreeNode*>& GetChildren() const { return Children; }

private:
	//Only CSceneNode manages the tree nodes
	friend class CSceneNode;

	explicit CSceneTreeNode(CSceneNode* owner);

	static CSceneTreeNode* CreateTree(CSceneNode* dagNode);
	void RemoveTree();
	void MarkTreeL2WDirty();

	//Private fields, accessible to CSceneNode though
    CSceneNode* Owner;
    CSceneTreeNode* Parent = nullptr;
    std::set<CSceneTreeNode*> Children;

	//This is non-null if the entity is instantiable
	TAutoPtr<CEntity> InstanceEntity;
};

class CSceneNode : public Flow::CFlowNode
{
	DEFINE_INPUT(Matrix3x4, Transform);

public:
	explicit CSceneNode(std::string name, bool isRoot = false);
    ~CSceneNode() override;

    const std::string& GetName() const { return Name; }
    void SetName(std::string name) { Name = std::move(name); }

	//Hierarchy management
    void AddParent(CSceneNode* newParent);
    void RemoveParent(CSceneNode* parent);
	CSceneNode* CreateChildNode(const std::string& name);

	//Returns the number of associated tree nodes, i.e. the number of ways from the root to this graph node
    size_t CountTreeNodes() const;
    const std::set<TAutoPtr<CSceneTreeNode>>& GetTreeNodes() const;

	//Instance/Entity related
	CEntity* GetEntity() const;
	void SetEntity(CEntity* ent);

private:
    std::string Name;

	friend class CSceneTreeNode;
    //Parents and associated tree nodes organized by parent
    std::set<CSceneNode*> Parents;
    std::set<TAutoPtr<CSceneNode>> Children;
	std::set<TAutoPtr<CSceneTreeNode>> TreeNodes;

	//Associated entity, aka the generator instantiated
	TAutoPtr<CEntity> Entity;
};

}
