// 题目：2179. 统计数组中好三元组数目（Count Good Triplets in an Array）
// 思路：以元素在 nums2 中的下标作为位置，按 nums1 的顺序插入树状数组；每个元素可配出的好三元组数等于「左侧已出现个数 × 右侧尚未出现个数」。
// 时间复杂度：O(n log n)，每个元素两次查询加一次更新；空间复杂度：O(n)，位置数组与树状数组。
class BinaryIndexedTree {  // 树状数组（Fenwick 树）：支持单点加值与前缀和查询
public:  // 类的对外接口
    int n;  // 下标范围是 1 ~ n
    vector<int> c;  // 树状数组本体，c[i] 管辖 lowbit(i) 个元素的和

    BinaryIndexedTree(int _n)  // 构造函数：大小为 _n 的树状数组
        : n(_n)  // 记录下标上界
        , c(_n + 1) {}  // 多开一位，让下标从 1 开始

    void update(int x, int delta) {  // 单点更新：把位置 x 增加 delta
        while (x <= n) {  // 沿 lowbit 向上更新所有管辖 x 的节点
            c[x] += delta;  // 该节点维护的区间和增加 delta
            x += lowbit(x);  // 跳到下一个管辖当前区间的节点
        }
    }

    int query(int x) {  // 前缀和查询：返回位置 1 ~ x 的元素之和
        int s = 0;  // 累加答案
        while (x > 0) {  // 沿 lowbit 向下累加各段区间
            s += c[x];  // 累加当前节点维护的区间和
            x -= lowbit(x);  // 跳到前面的区间
        }
        return s;  // 返回 1 ~ x 的前缀和
    }

    int lowbit(int x) {  // 取 x 二进制最低位的 1 所代表的值
        return x & -x;  // 位运算实现：x 与 -x 相与
    }
};  // 树状数组定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个长度为 n 的 0 ~ n-1 的排列
        int n = nums1.size();  // 排列长度，也是树状数组的大小
        vector<int> pos(n);  // pos[v]：值 v 在 nums2 中的位置（1 基）
        for (int i = 0; i < n; ++i) pos[nums2[i]] = i + 1;  // 记录 nums2 中每个值的下标，转成 1 基便于树状数组
        BinaryIndexedTree* tree = new BinaryIndexedTree(n);  // 树状数组统计已经出现过的位置
        long long ans = 0;  // 好三元组的个数
        for (int& num : nums1) {  // 按 nums1 的顺序依次插入元素
            int p = pos[num];  // 当前元素在 nums2 中的位置
            int left = tree->query(p);  // 已遍历过且位置比 p 靠前的元素个数，可作为三元组的左端点
            int right = n - p - (tree->query(n) - tree->query(p));  // 位置比 p 靠后且尚未被遍历到的元素个数，可作为三元组的右端点
            ans += 1ll * left * right;  // 以当前元素为中点，左右各选一个即构成好三元组
            tree->update(p, 1);  // 把当前元素的位置标记为已出现
        }
        return ans;  // 返回好三元组的总数
    }
};  // 类定义结束