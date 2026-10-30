// 3496. Maximize Score After Pair Deletions / 3496. 最大化配对删除后的得分
// 核心思路：所有元素都会被删掉，总得分等于元素总和减去必须舍弃的部分；n 为奇数时必有一个元素无法配对，舍弃最小值，n 为偶数时舍弃的一定是某个相邻元素对，取最小相邻和。
// 复杂度：时间 O(n)，空间 O(1)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int maxScore(vector<int>& nums) {  // nums 为待配对的整数数组，返回可获得的最高得分
        const int inf = 1 << 30;  // 足够大的哨兵值，用于求最小值
        int n = nums.size();  // 数组长度
        int s = 0, mi = inf;  // s 为元素总和，mi 为最小元素值
        int t = inf;  // t 为所有相邻元素对中的最小和
        for (int i = 0; i < n; ++i) {  // 一次遍历同时求解总和、最小值与最小相邻和
            s += nums[i];  // 累加元素总和
            mi = min(mi, nums[i]);  // 更新最小元素值
            if (i + 1 < n) {  // 存在右邻居时才能形成相邻对
                t = min(t, nums[i] + nums[i + 1]);  // 更新最小相邻元素和
            }
        }
        if (n % 2 == 1) {  // 长度为奇数，必然剩下一个元素无法配对
            return s - mi;  // 舍弃最小的那个元素即可让得分最高
        }
        return s - t;  // 长度为偶数，舍弃一个相邻对（取和最小者）后其余元素可全部配对
    }
};
