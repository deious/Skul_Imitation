#include "pch.h"
#include "BehaviorNode.h"

BehaviorNode::BehaviorNode()
{
}

BehaviorNode::~BehaviorNode()
{
}

ConditionNode::ConditionNode(function<bool()> condition) : condition(condition) {}
bool ConditionNode::Run() { return condition(); }

ActionNode::ActionNode(function<void()> act) : action(act) {}
bool ActionNode::Run() { action(); return true; }

void SequenceNode::AddChild(BehaviorNode* child) { children.push_back(child); }
bool SequenceNode::Run()
{
    for (auto* child : children)
    {
        if (!child->Run())
        {
            return false;
        }
    }

    return true;
}

void SelectorNode::AddChild(BehaviorNode* child) { children.push_back(child); }
bool SelectorNode::Run()
{
    for (auto* child : children)
    {
        if (child->Run())
        {
            return true;
        }
    }

    return false;
}