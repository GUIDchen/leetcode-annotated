// 题目：1172. 餐盘栈（Dinner Plate Stacks）
// 思路：用 vector<stack> 存每摞盘子，再用有序集合 notFull 记录所有未满栈的下标；push 放进最左未满栈，pop 从最右栈弹出并回收尾部空栈。
// 时间复杂度：push / pop / popAtStack 均为 O(log n)；空间复杂度：O(n)，即所有盘子的数量。
class DinnerPlates {  // 题目要求实现的餐盘栈类
public:  // 对外开放
    DinnerPlates(int capacity) {  // 构造函数：记录每个栈的容量上限
        this->capacity = capacity;  // 保存容量上限
    }  // 构造函数结束

    void push(int val) {  // 把 val 压入最左边（下标最小）的未满栈
        if (notFull.empty()) {  // 当前没有任何未满的栈
            stacks.emplace_back(stack<int>());  // 在最右边新开一个栈
            stacks.back().push(val);  // 把盘子放进新栈
            if (capacity > 1) {  // 新栈还有空位，记入「未满栈下标集合」
                notFull.insert(stacks.size() - 1);  // 把新栈的下标记入未满集合
            }  // if 结束
        } else {  // 否则存在未满的栈
            int index = *notFull.begin();  // 取下标最小的未满栈（set 自动升序，begin 即最左）
            stacks[index].push(val);  // 把盘子压入该栈
            if (stacks[index].size() == capacity) {  // 压入后这个栈刚好满了
                notFull.erase(index);  // 从「未满集合」中移除它
            }  // if 结束
        }  // else 结束
    }  // push 方法结束

    int pop() {  // 弹出最右边（下标最大）的栈顶
        return popAtStack(stacks.size() - 1);  // 直接复用 popAtStack
    }  // pop 方法结束

    int popAtStack(int index) {  // 弹出指定下标栈的栈顶
        if (index < 0 || index >= stacks.size() || stacks[index].empty()) {  // 下标越界或该栈为空时按题目要求返回 -1
            return -1;  // 返回 -1 表示无法弹出
        }  // if 结束
        int val = stacks[index].top();  // 记下栈顶元素
        stacks[index].pop();  // 弹出栈顶
        if (index == stacks.size() - 1 && stacks[index].empty()) {  // 弹出的是最右边的栈，并且它已经被弹空
            while (!stacks.empty() && stacks.back().empty()) {  // 从右往左把所有尾部空栈删掉
                notFull.erase(stacks.size() - 1);  // 同步从未满集合中移除该下标
                stacks.pop_back();  // 删除这个空栈
            }  // while 结束
        } else {  // 不是尾部空栈的情形：该栈还有盘子，或后面还有非空栈
            notFull.insert(index);  // 该栈现在未满，重新加入未满集合
        }  // else 结束
        return val;  // 返回弹出的值
    }  // 方法结束

private:  // 私有成员
    int capacity;  // 每个栈的容量上限
    vector<stack<int>> stacks;  // 所有栈，按从左到右的顺序保存
    set<int> notFull;  // 所有未满栈的下标，set 升序便于取最左
};  // 类定义结束

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */