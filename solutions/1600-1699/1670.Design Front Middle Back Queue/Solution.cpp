// 题目：1670. 设计前中后队列（Design Front Middle Back Queue）
// 思路：用两个双端队列把整个队列切成前后两半，始终保持 q1 长度 <= q2 长度 <= q1 长度 + 1，中位元素自然落在两半交界处。
// 时间复杂度：每次操作 O(1)；空间复杂度：O(n)，两个 deque 合计存 n 个元素。
class FrontMiddleBackQueue {  // 用两个双端队列维护前后两半：q1 是前半，q2 是后半
public:  // 对外提供的接口
    FrontMiddleBackQueue() {  // 构造函数：成员 deque 默认为空，无需额外初始化
    }  // 构造函数结束

    void pushFront(int val) {  // 在队首插入 val
        q1.push_front(val);  // 队首元素归入前半 q1
        rebalance();  // 调整两半长度，恢复平衡约束
    }  // pushFront 结束

    void pushMiddle(int val) {  // 在队列正中间插入 val
        q1.push_back(val);  // 先放到前半末尾，再由 rebalance 决定是否挪到后半
        rebalance();  // 调整两半长度，让 val 落在中位
    }  // pushMiddle 结束

    void pushBack(int val) {  // 在队尾插入 val
        q2.push_back(val);  // 队尾元素归入后半 q2
        rebalance();  // 调整两半长度，恢复平衡约束
    }  // pushBack 结束

    int popFront() {  // 弹出并返回队首元素，队空时返回 -1
        if (q1.empty() && q2.empty()) return -1;  // 两个队列都空说明整个队列为空
        int val = 0;  // 保存弹出的值
        if (q1.size()) {  // 前半非空时，队首一定在 q1
            val = q1.front();  // 取 q1 的队首元素
            q1.pop_front();  // 从 q1 队首删除
        } else {  // 前半为空，队首落在 q2 的头部
            val = q2.front();  // 取 q2 的队首元素
            q2.pop_front();  // 从 q2 队首删除
        }  // 分支结束
        rebalance();  // 删除后重新平衡两半长度
        return val;  // 返回弹出的值
    }  // popFront 结束

    int popMiddle() {  // 弹出并返回正中间元素，队空时返回 -1
        if (q1.empty() && q2.empty()) return -1;  // 整体为空，按题意返回 -1
        int val = 0;  // 保存弹出的值
        if (q1.size() == q2.size()) {  // 两半等长时，中位是前半的最后一个元素
            val = q1.back();  // 取 q1 的尾元素
            q1.pop_back();  // 从 q1 尾部删除
        } else {  // 否则 q2 比 q1 多一个，中位是 q2 的队首
            val = q2.front();  // 取 q2 的队首元素
            q2.pop_front();  // 从 q2 队首删除
        }  // 分支结束
        rebalance();  // 删除后重新平衡
        return val;  // 返回弹出的值
    }  // popMiddle 结束

    int popBack() {  // 弹出并返回队尾元素，队空时返回 -1
        if (q2.empty()) return -1;  // 队尾一定在 q2，q2 为空即整体为空
        int val = q2.back();  // 取 q2 的尾元素
        q2.pop_back();  // 从 q2 尾部删除
        rebalance();  // 删除后重新平衡
        return val;  // 返回弹出的值
    }  // popBack 结束

private:  // 内部数据结构与辅助函数
    deque<int> q1;  // 前半部分，队首即整个队列的队首
    deque<int> q2;  // 后半部分，队尾即整个队列的队尾

    void rebalance() {  // 维持 q1 长度 <= q2 长度 <= q1 长度 + 1
        if (q1.size() > q2.size()) {  // 前半过长，把它的尾元素挪到后半的头部
            q2.push_front(q1.back());  // q1 尾元素移到 q2 队首
            q1.pop_back();  // 从 q1 删除该元素
        }  // 第一个平衡分支结束
        if (q2.size() > q1.size() + 1) {  // 后半比前半多一个以上，把它的头元素挪到前半的尾部
            q1.push_back(q2.front());  // q2 首元素移到 q1 队尾
            q2.pop_front();  // 从 q2 删除该元素
        }  // 第二个平衡分支结束
    }  // rebalance 结束
};  // 类定义结束

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */