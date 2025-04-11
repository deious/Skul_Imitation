#pragma once
class BehaviorNode
{
public:
    BehaviorNode();
    virtual ~BehaviorNode();

public:
    virtual bool Run() = 0;
};

class ConditionNode : public BehaviorNode
{
public:
    ConditionNode(function<bool()> condition);
    bool Run() override;

private:
    function<bool()> condition;
};

class ActionNode : public BehaviorNode
{
public:
    ActionNode(function<void()> action);
    bool Run() override;

private:
    function<void()> action;
};

class SequenceNode : public BehaviorNode
{
public:
    void AddChild(BehaviorNode* child);
    bool Run() override;

private:
    vector<BehaviorNode*> children;
};

class SelectorNode : public BehaviorNode
{
public:
    void AddChild(BehaviorNode* child);
    bool Run() override;

private:
    vector<BehaviorNode*> children;
};