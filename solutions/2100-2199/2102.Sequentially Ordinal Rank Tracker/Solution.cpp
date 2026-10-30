// 题目：2102. 序列顺序查询（Sequentially Ordinal Rank Tracker）
// 思路：用 pb_ds 的 order statistics tree 按 (-score, name) 维护有序集合，get 时按调用次序取第 ++i 小的元素。
// 时间复杂度：单次 add / get 均为 O(log n)；空间复杂度：O(n)，保存全部记录。
#include <ext/pb_ds/assoc_container.hpp>  // 引入 pb_ds 容器定义，里面提供平衡树 tree
#include <ext/pb_ds/hash_policy.hpp>  // 引入 pb_ds 的策略定义（哈希等节点更新策略）
using namespace __gnu_pbds;  // 使用 pb_ds 命名空间，tree 才能直接写

template <class T>  // 模板参数 T 表示集合中元素的类型
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;  // 别名：带名次统计的红黑树，额外支持 find_by_order 按名次取元素

class SORTracker {  // 题目要求实现的类
public:  // 对外接口
    SORTracker() {  // 构造函数：成员容器在这里已完成默认初始化
    }

    void add(string name, int score) {  // add：往榜单里加入一条 name、score 记录
        st.insert({-score, name});  // 分数取负让高分排前面；同分时按名字字典序升序
    }

    string get() {  // get：按调用顺序返回第 1、2、3... 好的景点名
        return st.find_by_order(++i)->second;  // i 从 -1 起，先自增再取第 i 小（0 基）元素的名字，即本次要返回的答案
    }

private:  // 内部数据成员
    ordered_set<pair<int, string>> st;  // 有序集合，元素是 (-score, name)
    int i = -1;  // get 的调用次数减一，用作下一次查询的名次下标
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */