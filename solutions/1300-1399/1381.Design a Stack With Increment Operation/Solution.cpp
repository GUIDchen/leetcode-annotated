// 题目：1381. 设计一个支持增量操作的栈（Design a Stack With Increment Operation）
// 思路：栈体数组 stk 配合等长的延迟增量数组 add；increment 只在第 min(k,i)-1 个位置打标记，pop 时把标记向下传递。
// 时间复杂度：push/pop/increment 都是 O(1)；空间复杂度：O(maxSize)，两个与容量等长的数组。
class CustomStack {  // 题目要求实现的类
public:  // 构造函数与三个操作对外可见
    CustomStack(int maxSize) {  // maxSize：栈的容量上限
        stk.resize(maxSize);  // 栈体数组，预先分配 maxSize 个位置
        add.resize(maxSize);  // 延迟增量数组，与栈体下标一一对应
        i = 0;  // i 表示当前元素个数，同时也是下一个可写入的位置
    }  // 构造函数结束

    void push(int x) {  // x：要压入栈的元素
        if (i < stk.size()) {  // 栈未满时才允许写入，满了则静默丢弃
            stk[i++] = x;  // 写入当前位置，然后把栈顶指针后移一位
        }  // 容量判断结束
    }  // push 结束

    int pop() {  // 弹出栈顶并返回其真实值，栈空时返回 -1
        if (i <= 0) {  // 栈内没有元素
            return -1;  // 按题目约定返回 -1
        }  // 空栈判断结束
        int ans = stk[--i] + add[i];  // 先把下标回退到栈顶，再叠加该位置累积的增量
        if (i > 0) {  // 栈里还有更下层元素
            add[i - 1] += add[i];  // 把当前增量下传给下一个元素，这就是延迟标记的核心
        }  // 下传判断结束
        add[i] = 0;  // 该位置的标记已被消费，清零以免影响之后重新压入的元素
        return ans;  // 返回叠加增量后的栈顶值
    }  // pop 结束

    void increment(int k, int val) {  // 把栈底 k 个元素各自加上 val
        if (i > 0) {  // 栈非空时增量才有意义
            add[min(k, i) - 1] += val;  // 只在「实际被覆盖的最后一个元素」处打标记，避免逐个修改
        }  // 非空判断结束
    }  // increment 结束

private:  // 以下为内部状态
    vector<int> stk;  // 栈体数组
    vector<int> add;  // 每个位置待下传的增量
    int i;  // 当前元素个数 / 栈顶下标
};  // CustomStack 类结束

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */