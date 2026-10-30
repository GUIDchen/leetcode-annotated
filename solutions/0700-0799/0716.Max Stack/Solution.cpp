// 题目：716. 最大栈（Max Stack）
// 核心思路：数据结构双写。list 当栈本体（迭代器在别处增删后仍有效），multimap 以元素值为 key 保存到该元素节点的迭代器，于是 popMax 能 O(log n) 定位最大值并从两个结构中同步删除。
// 时间复杂度：push/pop/popMax 为 O(log n)，top/peekMax 为 O(1)；空间复杂度：O(n)，两个容器各存 n 个元素。
class MaxStack {  // 最大栈：既支持栈的常规操作，又要能快速取出并弹出当前最大值
public:  // 对外接口区
    MaxStack() {  // 构造函数，两个容器自带初始化，方法体为空
    }  // 结束构造函数

    void push(int x) {  // 入栈：把元素压到栈顶，同时在有序表中登记它的位置
        stk.push_back(x);  // 把元素追加到 list 尾部，list 尾部就是栈顶
        tm.insert({x, --stk.end()});  // 把 (元素值, 该元素在 stk 中的迭代器) 插入按值排序的 multimap，允许重复值
    }  // 结束 push 方法

    int pop() {  // 出栈：弹出栈顶元素
        auto it = --stk.end();  // 指向栈顶（list 的最后一个元素）的迭代器
        int ans = *it;  // 先保存栈顶的值，稍后作为返回值
        auto mit = --tm.upper_bound(ans);  // 在 multimap 中找 key 等于 ans 的最后一项（重复值中后插入的那个），即该栈顶元素对应的记录
        tm.erase(mit);  // 从有序表中删掉该记录，保持两个容器同步
        stk.erase(it);  // 再从栈中删除栈顶元素；list 的 erase 会使 it 失效，所以放在最后
        return ans;  // 返回被弹出的栈顶值
    }  // 结束 pop 方法

    int top() {  // 读取栈顶值但不出栈
        return stk.back();  // list::back 直接给出末尾元素，O(1)
    }  // 结束 top 方法

    int peekMax() {  // 读取当前最大值但不出栈
        return tm.rbegin()->first;  // multimap 按 key 升序排列，反向迭代器的第一个元素就是最大 key
    }  // 结束 peekMax 方法

    int popMax() {  // 弹出当前最大值（若存在多个相同最大值，弹出最后插入的那个）
        auto mit = --tm.end();  // 指向最大元素对应的那一条记录的迭代器
        auto it = mit->second;  // 取出这个最大值在 stk 中的位置
        int ans = *it;  // 先保存要返回的值
        tm.erase(mit);  // 从有序表中删除该记录
        stk.erase(it);  // 再按迭代器把它从栈中删除，两个容器保持同步
        return ans;  // 返回被弹出的最大值
    }  // 结束 popMax 方法

private:  // 内部数据结构区
    multimap<int, list<int>::iterator> tm;  // multimap：key 是元素值（自动升序），value 是元素在 stk 中的迭代器；用 multimap 是为了支持重复值
    list<int> stk;  // list：栈本体，选 list 是因为它的迭代器在其它位置插入/删除后仍然有效
};  // 结束 MaxStack 类定义

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */