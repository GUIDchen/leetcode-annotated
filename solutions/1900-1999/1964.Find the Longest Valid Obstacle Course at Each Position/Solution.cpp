// 题目：1964. 找出到每个位置为止最长的有效障碍赛跑路线（Find the Longest Valid Obstacle Course at Each Position）
// 思路：等价于求以每个位置结尾的最长非降子序列长度；把高度离散化成 1..m 的名次，用树状数组维护「名次 → 该名次及之前的最大长度」的前缀最大值。
// 时间复杂度：O(n log n)，排序一次加 n 次 BIT 查询/更新；空间复杂度：O(n)，拷贝数组与树状数组各占 O(n)。
class BinaryIndexedTree {  // 树状数组：支持单点「取最大」更新与前缀最大值查询
private:  // 内部状态不对外暴露
    int n;  // n 是下标有效范围的上界，有效下标为 1..n
    vector<int> c;  // c[i] 维护区间 (i - lowbit(i), i] 上的最大值

public:  // 对外接口
    BinaryIndexedTree(int n) {  // 构造函数，n 是最大下标
        this->n = n;  // 保存范围上界，供 update 循环判断
        c = vector<int>(n + 1);  // 开 n+1 个位置（下标从 1 开始），默认 0 即最大值的单位元
    }  // 构造函数结束

    void update(int x, int v) {  // 把位置 x 的值更新为 max(原值, v)，只增不减
        while (x <= n) {  // 沿 x += lowbit(x) 向上覆盖所有包含 x 的区间
            c[x] = max(c[x], v);  // 对每个覆盖区间取最大值
            x += x & -x;  // 跳到父区间（x 加上自己的最低位 1）
        }  // while 结束
    }  // update 结束

    int query(int x) {  // 查询前缀 [1, x] 上的最大值
        int s = 0;  // 0 是空区间最大值，也是本题答案的下界
        while (x > 0) {  // 沿 x -= lowbit(x) 把前缀拆成若干块
            s = max(s, c[x]);  // 并入当前块的最大值
            x -= x & -x;  // 移向下一块（去掉最低位的 1）
        }  // while 结束
        return s;  // 返回前缀最大值
    }  // query 结束
};  // 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {  // obstacles 是障碍高度序列，返回每个位置结尾的最长有效路线长度
        vector<int> nums = obstacles;  // 复制一份用于排序离散化，避免破坏原顺序
        sort(nums.begin(), nums.end());  // 升序排序，得到所有可能的名次
        int n = nums.size();  // 障碍总数，也是树状数组的规模
        vector<int> ans(n);  // ans[k] 存放以第 k 个障碍结尾的最长非降子序列长度
        BinaryIndexedTree tree(n);  // 下标 1..n 对应排序后数组的各个名次
        for (int k = 0; k < n; ++k) {  // 按下标顺序依次处理每个障碍
            int x = obstacles[k];  // 当前障碍的高度
            auto it = lower_bound(nums.begin(), nums.end(), x);  // 二分找到第一个 >= x 的位置，相同高度会映射到同一名次
            int i = distance(nums.begin(), it) + 1;  // 转成 1 基名次，因为树状数组下标从 1 开始
            ans[k] = tree.query(i) + 1;  // 所有高度 <= x 的前缀最大值再加 1，即为以当前位置结尾的最优长度
            tree.update(i, ans[k]);  // 把当前答案写入树状数组，供后面的障碍查询
        }  // for 结束
        return ans;  // 返回每个位置的最长有效路线长度
    }  // 方法结束
};  // 类定义结束