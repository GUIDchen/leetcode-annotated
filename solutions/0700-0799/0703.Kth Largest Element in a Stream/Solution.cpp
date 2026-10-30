// 题目：703. 数据流中的第 K 大元素（Kth Largest Element in a Stream）
// 思路：用小顶堆只保留最大的 k 个元素，堆顶就是这 k 个里最小的，即第 k 大；每次插入后若堆超过 k 个就弹出最小值。
// 时间复杂度：单次 add 为 O(log k)，构造函数为 O(n log k)；空间复杂度：O(k)，堆中最多保存 k 个元素。
class KthLargest {  // LeetCode 约定的题解类（构造时传入 k 与初始数据流）
public:  // 对外接口：构造函数与 add 方法都暴露给判题器
    KthLargest(int k, vector<int>& nums) {  // 构造函数：k 是要求的第 k 大，nums 是初始的数据流
        this->k = k;  // 把 k 记到成员变量，add 里要靠它维持堆的大小
        for (int x : nums) {  // 逐个把初始元素喂进堆
            add(x);  // 复用 add 的插入与收缩逻辑，保证初始化后也是「最大的 k 个」
        }  // for 循环结束
    }

    int add(int val) {  // 加入一个新值，返回当前数据流中的第 k 大元素
        minQ.push(val);  // 先把新值压入小顶堆
        if (minQ.size() > k) {  // 堆内元素个数超过 k 个
            minQ.pop();  // 弹出堆顶的最小值，保证堆里始终只有最大的 k 个
        }
        return minQ.top();  // 堆顶是这 k 个元素中最小的那个，也就是第 k 大
    }

private:  // 私有成员区：内部实现细节
    int k;  // 需要保留的「最大的 k 个」的个数
    priority_queue<int, vector<int>, greater<int>> minQ;  // 小顶堆：greater 让堆顶是最小值，方便弹出超额的较小元素
};  // 类定义结束

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */