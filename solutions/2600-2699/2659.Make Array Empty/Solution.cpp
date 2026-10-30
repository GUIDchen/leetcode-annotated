// 题目：2659. 将数组清空（Make Array Empty）
// 核心思路：按值从小到大的顺序删除元素，用树状数组维护已删除的下标，逐段累加「沿环前进一步」的真实步数，绕回开头时多走一整圈。
// 时间复杂度：O(n log n)，排序加树状数组；空间复杂度：O(n)，pos 哈希表与树状数组。
class BinaryIndexedTree {  // 手写树状数组：支持单点加、前缀和查询
public:  // 对外接口
    BinaryIndexedTree(int _n)  // 构造函数，n 为下标上限（有效下标 1..n）
        : n(_n)  // 初始化下标上限 n
        , c(_n + 1) {}  // 树状数组本体，多开一位使下标从 1 开始

    void update(int x, int delta) {  // 在位置 x 上加 delta
        while (x <= n) {  // 沿 lowbit 向树根方向爬
            c[x] += delta;  // 更新当前节点覆盖的区间和
            x += x & -x;  // x 加上最低位的 1，跳到下一个负责该点的节点
        }
    }

    int query(int x) {  // 求前缀和（下标 1..x）
        int s = 0;  // 累加结果
        while (x) {  // x 变为 0 时结束
            s += c[x];  // 累加当前节点
            x -= x & -x;  // x 减去最低位的 1，跳到上一个节点
        }
        return s;  // 返回前缀和
    }

private:  // 以下为内部数据
    int n;  // 下标上限
    vector<int> c;  // 树状数组存储
};

class Solution {  // 题解类
public:  // 方法对外可见
    long long countOperationsToEmptyArray(vector<int>& nums) {  // 返回把数组清空所需的最少操作次数
        unordered_map<int, int> pos;  // 记录「值 → 原始下标」，题目保证元素互不相同
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n; ++i) {  // 遍历原始数组
            pos[nums[i]] = i;  // 保存每个值的初始位置
        }
        sort(nums.begin(), nums.end());  // 排序后 nums 按「被删除的先后顺序」排列
        BinaryIndexedTree tree(n);  // 用树状数组记录哪些下标已经被删除
        long long ans = pos[nums[0]] + 1;  // 先转圈走到最小值处并删除它：pos+1 次操作
        for (int k = 0; k < n - 1; ++k) {  // 依次处理排序后相邻的两个待删除值
            int i = pos[nums[k]], j = pos[nums[k + 1]];  // 两者在原数组中的下标
            long long d = j - i - (tree.query(j + 1) - tree.query(i + 1));  // 减去中间已被删除的元素个数，得到实际需要前进的步数
            ans += d + (n - k) * int(i > j);  // 若 i > j 说明要绕回开头，多走一整圈（此时还剩 n-k 个元素）
            tree.update(i + 1, 1);  // 把下标 i 标记为已删除（树状数组下标从 1 开始，故 +1）
        }
        return ans;  // 返回总操作次数
    }
};  // class Solution 结束