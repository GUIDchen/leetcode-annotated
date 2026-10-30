// 题目：307. 区域和检索 - 数组可修改（Range Sum Query - Mutable）
// 思路：树状数组维护前缀和，单点修改与前缀查询都是 O(log n)，区间和由两个前缀和相减。
// 时间复杂度：构造 O(n log n)、更新 O(log n)、查询 O(log n)；空间复杂度：O(n)，树状数组本体。
class BinaryIndexedTree {  // 树状数组（Binary Indexed Tree）：支持单点加与前缀和查询
public:  // 对外接口
    int n;  // 数组长度
    vector<int> c;  // c 是树状数组本体，1 基下标，长度 n+1

    BinaryIndexedTree(int _n)  // 构造函数
        : n(_n)  // 初始化长度 n
        , c(_n + 1) {}  // c 分配 n+1 个位置，c[0] 不用

    void update(int x, int delta) {  // 在下标 x 处加上 delta（x 为 1 基下标）
        while (x <= n) {  // 沿 lowbit 链向上，更新所有覆盖 x 的节点
            c[x] += delta;  // 当前节点累加增量
            x += x & -x;  // x += x & -x 跳到下一个覆盖该点的节点
        }  // 更新结束
    }  // update 结束

    int query(int x) {  // 查询前缀和 [1, x]
        int s = 0;  // 累加器
        while (x > 0) {  // 沿 lowbit 链向下跳，把各段拼成完整前缀
            s += c[x];  // 累加当前节点的区间和
            x -= x & -x;  // x -= x & -x 去掉最低位的 1，跳到前一段
        }  // 前缀查询结束
        return s;  // 返回前缀和
    }  // query 结束
};  // BinaryIndexedTree 类结束

class NumArray {  // LeetCode 约定的题解类
public:  // 对外接口
    BinaryIndexedTree* tree;  // 指向树状数组的指针，在构造函数里按数据规模创建

    NumArray(vector<int>& nums) {  // 构造函数：nums 是初始数组
        int n = nums.size();  // 元素个数
        tree = new BinaryIndexedTree(n);  // 建一棵长度为 n 的树状数组
        for (int i = 0; i < n; ++i) tree->update(i + 1, nums[i]);  // 逐个元素插入：树状数组用 1 基下标，所以传 i+1
    }  // 构造函数结束

    void update(int index, int val) {  // 把下标 index 处的值改成 val
        int prev = sumRange(index, index);  // 先取出原来的值（单点查询 = 两个前缀和相减）
        tree->update(index + 1, val - prev);  // 只需把差值加进去，树状数组天然支持单点增量更新
    }  // update 结束

    int sumRange(int left, int right) {  // 查询闭区间 [left, right] 的和
        return tree->query(right + 1) - tree->query(left);  // 前缀和相减：query(right+1) 含前 right+1 项，再减去前 left 项
    }  // sumRange 结束
};  // NumArray 类结束

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */