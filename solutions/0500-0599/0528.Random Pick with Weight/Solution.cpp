// 题目：528. 按权重随机选择（Random Pick with Weight）
// 思路：前缀和 + 二分。把下标 i 扩张成一段长度为 w[i] 的区间，随机落点 x 落在哪个前缀和区间里就返回哪个下标。
// 时间复杂度：构造函数 O(n)，pickIndex 每次 O(log n)；空间复杂度：O(n)，存放前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    vector<int> s;  // 前缀和数组：s[i] 表示前 i 个权重之和，多留一位 s[0] = 0 让递推式统一

    Solution(vector<int>& w) {  // 构造函数：w 是权重数组，先做前缀和预处理
        int n = w.size();  // 权重个数
        s.resize(n + 1);  // 长度取 n+1，多出来的第 0 位固定为 0
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + w[i];  // 递推前缀和：区间 (s[i], s[i+1]] 的长度恰好是 w[i]
    }

    int pickIndex() {  // 按权重随机返回一个下标
        int n = s.size();  // 前缀和数组长度，即权重个数加一
        int x = 1 + rand() % s[n - 1];  // 在 [1, 权重总和] 内均匀取一个整数，作为随机落点
        int left = 1, right = n - 1;  // 在原数组下标范围 [1, n-1] 上二分，找第一个满足 s[mid] >= x 的位置
        while (left < right) {  // 左右指针相遇即收敛
            int mid = left + right >> 1;  // 取中点；加法优先级高于 >>，等价于 (left + right) / 2
            if (s[mid] >= x)  // 落点没有超过 mid 的前缀和
                right = mid;  // 答案在左半段，且可能就是 mid，所以保留 mid
            else  // 落点大于 mid 的前缀和
                left = mid + 1;  // 答案严格在右半段，丢弃 mid
        }
        return left - 1;  // 前缀和下标 1 对应原数组下标 0，故整体减一
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */