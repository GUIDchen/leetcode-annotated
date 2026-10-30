// 题目：2875. 无限数组的最短子数组（Minimum Size Subarray in Infinite Array）
// 思路：先按整轮拆分 target，再用前缀和哈希表在「一轮内区间」及其补区间中取最短长度。
// 时间复杂度：O(n)，一轮只遍历一次；空间复杂度：O(n)，哈希表最多保存 n 个前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSizeSubarray(vector<int>& nums, int target) {  // nums 是循环数组，target 是目标和
        long long s = accumulate(nums.begin(), nums.end(), 0LL);  // 一轮元素和，用 long long 防溢出
        int n = nums.size();  // 一轮的长度
        int a = 0;  // a：完整轮贡献的长度
        if (target > s) {  // 目标超过一轮总和，可以整轮地取
            a = n * (target / s);  // 先拿走 target / s 个完整轮
            target -= target / s * s;  // 余数留在 target 里继续处理
        }
        if (target == s) {  // 剩余目标正好等于一轮总和
            return n;  // 一轮就是最短长度
        }
        unordered_map<long long, int> pos{{0, -1}};  // 前缀和 → 最近下标，0 的虚拟下标取 -1
        long long pre = 0;  // 当前前缀和
        int b = 1 << 30;  // b：不足一轮部分的最短长度，先用足够大的值当作无穷
        for (int i = 0; i < n; ++i) {  // 遍历一轮内的每个位置
            pre += nums[i];  // 累加到当前位置的前缀和
            if (pos.count(pre - target)) {  // 情况一：存在一段连续区间自身和等于 target
                b = min(b, i - pos[pre - target]);  // 区间长度是 i 减去起点下标，取更短者
            }
            if (pos.count(pre - (s - target))) {  // 情况二：中间段和等于 s - target，答案取它的补段
                b = min(b, n - (i - pos[pre - (s - target)]));  // 补段长度等于一轮长度减去中间段长度
            }
            pos[pre] = i;  // 记录当前前缀和最近一次出现的位置
        }
        return b == 1 << 30 ? -1 : a + b;  // 从未更新过 b 说明凑不出，否则整轮长度加剩余长度
    }
};