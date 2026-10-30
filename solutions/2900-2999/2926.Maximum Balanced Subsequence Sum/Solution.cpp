// 题目：2926. 平衡子序列的最大和（Maximum Balanced Subsequence Sum）
// 思路：把平衡条件 nums[j] - j >= nums[i] - i 记作关键值 key，问题变成「在 key 非降的前提下求最大子序列和」；把 key 离散化后用树状数组维护前缀最大值做 O(n log n) 的 DP。
// 时间复杂度：O(n log n)，排序加 n 次树状数组操作；空间复杂度：O(n)，存放离散化数组与树状数组。
class BinaryIndexedTree {  // 树状数组，这里用来维护前缀最大值
private:  // 内部实现
    int n;  // 下标范围是 1..n
    vector<long long> c;  // c[x] 保存区间 (x-lowbit(x), x] 上的最大值
    const long long inf = 1e18;  // 极大值，作为「该位置还没有候选值」的哨兵

public:  // 对外接口
    BinaryIndexedTree(int n) {  // 构造函数，n 为离散化后的值域大小
        this->n = n;  // 保存下标上界
        c.resize(n + 1, -inf);  // 全部初始化为 -inf，表示暂时没有候选值
    }

    void update(int x, long long v) {  // 单点更新：把位置 x 的候选值与 v 取最大值
        while (x <= n) {  // 沿着树状数组的父链向上
            c[x] = max(c[x], v);  // 每个覆盖 x 的区间都更新最大值
            x += x & -x;  // 跳到下一个覆盖 x 的下标
        }
    }

    long long query(int x) {  // 查询前缀最大值 max(c[1..x])
        long long mx = -inf;  // 初始为极小值，空查询也安全
        while (x > 0) {  // 把前缀拆成若干段
            mx = max(mx, c[x]);  // 合并当前段的最大值
            x -= x & -x;  // 去掉最低位的 1，跳到前一段
        }
        return mx;  // 返回 [1, x] 的最大值
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxBalancedSubsequenceSum(vector<int>& nums) {  // nums 为输入数组
        int n = nums.size();  // 数组长度
        vector<int> arr(n);  // 存放所有 nums[i] - i，用于离散化
        for (int i = 0; i < n; ++i) {  // 逐个计算关键值
            arr[i] = nums[i] - i;  // 平衡条件两边同减下标，等价于 nums[j]-j >= nums[i]-i
        }
        sort(arr.begin(), arr.end());  // 排序，为去重和二分做准备
        arr.erase(unique(arr.begin(), arr.end()), arr.end());  // 去重，得到互不相同的值域
        int m = arr.size();  // 不同关键值的个数，也就是树状数组大小
        BinaryIndexedTree tree(m);  // 建一棵大小为 m 的树状数组
        for (int i = 0; i < n; ++i) {  // 按原数组顺序做 DP
            int j = lower_bound(arr.begin(), arr.end(), nums[i] - i) - arr.begin() + 1;  // 关键值的排名，转成 1 起点下标
            long long v = max(tree.query(j), 0LL) + nums[i];  // 前面 key 不大于当前 key 的最大和；与 0 取大表示可以只取自己
            tree.update(j, v);  // 把以 i 结尾的最大平衡子序列和写入树状数组
        }
        return tree.query(m);  // 所有位置的前缀最大值就是全局答案
    }
};