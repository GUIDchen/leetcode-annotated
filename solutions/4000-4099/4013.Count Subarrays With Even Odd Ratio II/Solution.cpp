// 题目：4013. 按奇偶比统计子数组 II（Count Subarrays With Even Odd Ratio II）
// 思路：把奇数记 +a、偶数记 -b 构造前缀和，则 x / y <= a / b 等价于 s[r] - s[l] >= 0；离散化前缀和后用树状数组统计「前面有多少个前缀和不大于当前值」，累加即得答案。
// 时间复杂度：O(n log n)，排序与树状数组；空间复杂度：O(n)，前缀和、离散化数组与树状数组。
class BinaryIndexedTree {  // 树状数组（Binary Indexed Tree），用于按前缀和计数
    int n;  // n 是树状数组下标的上界
    vector<int> c;  // c 是树状数组内部数组，下标从 1 开始

public:  // 对外接口
    BinaryIndexedTree(int n)  // 构造函数：n 为下标上界
        : n(n)  // 初始化上界
        , c(n + 1) {}  // 内部数组长度取 n + 1，便于 1 基编号

    void update(int x, int delta) {  // 单点更新：把下标 x 处的计数增加 delta
        while (x <= n) {  // 沿 lowbit 向上爬
            c[x] += delta;  // 累加到覆盖该位置的节点
            x += x & -x;  // x 加上自身最低位的 1
        }  // 结束上爬
    }  // 结束 update

    int query(int x) {  // 前缀查询：返回下标 1..x 的计数总和
        int s = 0;  // s 累计查询结果
        while (x > 0) {  // 沿 lowbit 向下跳
            s += c[x];  // 累加当前节点
            x -= x & -x;  // x 减去自身最低位的 1
        }  // 结束下跳
        return s;  // 返回前缀计数
    }  // 结束 query
};  // 结束树状数组类

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countRatioSubarrays(vector<int>& nums, int a, int b) {  // nums：待统计的数组；a、b：偶数个数与奇数个数比值的上界 a / b；返回满足条件的子数组个数
        int n = nums.size();  // n 为数组长度

        vector<long long> s(n + 1);  // 前缀和：奇数记 +a，偶数记 -b
        for (int i = 0; i < n; i++) {  // 递推计算前缀和
            s[i + 1] = s[i] + (nums[i] % 2 ? a : -b);  // 由 x / y <= a / b 推出 a * y - b * x >= 0，即对应区间和不小于 0
        }  // 结束前缀和计算

        vector<long long> st = s;  // 复制前缀和数组，用于离散化
        sort(st.begin(), st.end());  // 排序，便于把数值映射成下标
        st.erase(unique(st.begin(), st.end()), st.end());  // 去重，得到互不相同的数值序列 st

        BinaryIndexedTree bit(st.size() + 1);  // 树状数组规模取离散值个数 + 1（内部使用 1 基下标）

        long long ans = 0;  // ans 记录满足条件的子数组个数

        for (long long v : s) {  // 顺序遍历每个前缀和
            int x = lower_bound(st.begin(), st.end(), v) - st.begin() + 1;  // 把前缀和映射成从 1 开始的离散下标
            ans += bit.query(x);  // 前面已有多少个前缀和 <= 当前值，就有多少个满足条件的子数组
            bit.update(x, 1);  // 把当前前缀和也加入树状数组，供后续元素使用
        }  // 结束遍历

        return ans;  // 返回满足条件的子数组总数
    }  // 结束 countRatioSubarrays
};  // 结束 Solution 类