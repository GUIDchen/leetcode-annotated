// 题目：2969. 购买水果需要的最少金币数 II（Minimum Number of Coins for Fruits II）
// 思路：从后往前 DP，f[i] = prices[i] + min(f[i+1..2i+1])；用单调递增双端队列维护滑动窗口最小值，把转移降到 O(1)。
// 时间复杂度：O(n)，每个下标最多入队、出队一次；空间复杂度：O(n)（队列）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCoins(vector<int>& prices) {  // prices：每个水果的价格，返回从头买起的最少金币数
        int n = prices.size();  // n 为水果个数
        deque<int> q;  // 单调队列：存放下标，队首对应窗口内最小的 f 值
        for (int i = n; i; --i) {  // 从后往前推：i 是 1 基下标，i 从 n 递减到 1
            while (q.size() && q.front() > i * 2 + 1) {  // 买下 i 之后可免费拿到 i+1..2i 的水果，所以窗口是 [i+1, 2i+1]，越界的下标要弹掉
                q.pop_front();  // 从队首丢弃已经滑出窗口的下标
            }  // 循环体结束
            if (i <= (n - 1) / 2) {  // 只有当 2i < n（即 i 之后还有买不到的水果）时才需要额外付钱
                prices[i - 1] += prices[q.front() - 1];  // 累加后续窗口里的最小 f 值（队首即最小）；prices 被就地复用为 f 数组
            }  // 分支结束
            while (q.size() && prices[q.back() - 1] >= prices[i - 1]) {  // 维护单调性：比当前 f 值更大（或相等）的尾部下标以后都不会被选中
                q.pop_back();  // 从队尾弹出无用下标
            }  // 循环体结束
            q.push_back(i);  // 当前下标入队，供更靠前的 i 使用
        }  // 循环体结束
        return prices[0];  // f[1] 就是从第 1 个水果买起的最少金币数
    }  // 方法结束
};  // 类结束