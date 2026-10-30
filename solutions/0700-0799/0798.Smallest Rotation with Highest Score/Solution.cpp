// 题目：798. 得分最高的最小轮调（Smallest Rotation with Highest Score）
// 思路：元素 i 在轮调 k 次后落到 (i-k+n)%n，只有该位置 >= nums[i] 才得分，因此它只在环形区间 [i+1, n+i+1-nums[i]) 内贡献 1 分。用差分数组累加每个 k 的得分变化，再做前缀和取最大，即得最小 k。
// 时间复杂度：O(n)，一次差分构建加一次前缀和；空间复杂度：O(n)，差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int bestRotation(vector<int>& nums) {  // nums：原始数组，返回得分最高的最小轮调次数
        int n = nums.size();  // 数组长度
        int mx = -1, ans = n;  // mx 为当前最高得分；ans 记录对应的最小 k，严格大于才更新所以天然最小
        vector<int> d(n);  // 差分数组：d[k] 是第 k 次轮调相对 k-1 次的得分变化
        for (int i = 0; i < n; ++i) {  // 逐个元素计算它能得分的轮调次数区间
            int l = (i + 1) % n;  // 区间左端点：轮调 i+1 次后该元素换到末尾，开始进入得分段
            int r = (n + i + 1 - nums[i]) % n;  // 区间右端点（开）：再往后位置会小于 nums[i]，得分中断
            ++d[l];  // 区间起点处得分 +1
            --d[r];  // 区间终点（开）处得分 -1
        }  // 元素枚举结束
        int s = 0;  // 前缀和即当前轮调的得分
        for (int k = 0; k < n; ++k) {  // 按 k 从小到大还原差分
            s += d[k];  // 累加差分，得到第 k 次轮调的总得分
            if (s > mx) {  // 严格大于才更新，保证记录的是最小的 k
                mx = s;  // 更新最高得分
                ans = k;  // 记录当前最优轮调次数
            }  // 更新分支结束
        }  // 轮调枚举结束
        return ans;  // 返回得分最高且最小的轮调次数
    }  // bestRotation 结束
};  // 类定义结束