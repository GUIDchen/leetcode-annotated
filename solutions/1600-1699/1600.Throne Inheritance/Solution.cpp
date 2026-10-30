// 题目：1600. 王位继承顺序（Throne Inheritance）
// 思路：把继承关系建成多叉树，用邻接表存孩子、用集合标记死亡，查询时从国王做一次前序遍历。
// 时间复杂度：birth/death O(1)，getInheritanceOrder O(n)；空间复杂度：O(n)，存下整棵树与结果。
class ThroneInheritance {  // 题目要求的王位继承类，需要支持出生、死亡与查询继承顺序
public:  // 对外接口，判题器按这些方法调用
    ThroneInheritance(string kingName) {  // 构造函数：记录国王姓名
        king = kingName;  // 保存根节点，后续 DFS 从国王开始
    }  // 构造函数结束

    // 记录一次出生：childName 的父亲是 parentName
    void birth(string parentName, string childName) {  // 出生事件
        g[parentName].emplace_back(childName);  // 追加到父亲的孩子列表末尾，从而保持出生顺序
    }  // birth 结束

    // 记录一次死亡：只做标记不删节点，保证其他成员在树中的位置不变
    void death(string name) {  // 死亡事件
        dead.insert(name);  // 把姓名放入死亡集合，DFS 输出时跳过
    }  // death 结束

    // 返回当前所有在世者的继承顺序（多叉树的前序遍历）
    vector<string> getInheritanceOrder() {  // 查询继承顺序
        ans.resize(0);  // 清空上一次查询的结果，复用成员变量避免重复分配
        dfs(king);  // 从国王开始做前序遍历
        return ans;  // 返回收集到的顺序
    }  // getInheritanceOrder 结束

    // 下面是内部状态与辅助函数
private:  // 私有成员，外部不可见
    string king;  // 国王（树的根）
    unordered_set<string> dead;  // 已死亡成员的集合，查询时跳过
    unordered_map<string, vector<string>> g;  // 邻接表：父亲 → 孩子列表
    vector<string> ans;  // 保存本次查询的遍历结果

    // 前序遍历：先访问自己，再按出生顺序访问每个孩子
    void dfs(string& x) {  // x 为当前访问的成员
        if (!dead.contains(x)) {  // 只有在世者才进入继承顺序
            ans.emplace_back(x);  // 记录当前成员
        }  // 在世判断结束
        for (auto& y : g[x]) {  // 按出生顺序遍历所有孩子
            dfs(y);  // 递归处理孩子及其后代
        }  // 孩子遍历结束
    }  // dfs 结束
};  // 类结束

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
