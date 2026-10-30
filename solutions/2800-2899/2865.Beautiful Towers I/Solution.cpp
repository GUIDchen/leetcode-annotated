// 题目：2865. 美丽塔 I（Beautiful Towers I）
// 思路：枚举山顶下标 i，高度取 maxHeights[i]；向左、向右各扫一遍，相邻高度取「不超过 maxHeights 的递减」即 y = min(y, maxHeights[j])，求和后取最大。
// 时间复杂度：O(n^2)，每个山顶都要向两边各扫一遍；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumSumOfHeights(vector<int>& maxHeights) {  // maxHeights：每个位置的高度上限，返回最大高度和
        long long ans = 0;  // 记录目前枚举到的最大高度和，可能超过 int
        int n = maxHeights.size();  // 塔的数量
        for (int i = 0; i < n; ++i) {  // 枚举每一座塔作为山顶
            long long t = maxHeights[i];  // 山顶取到上限，先把它计入高度和
            int y = t;  // y 记录向左推进时允许的当前高度，初始等于山顶高度
            for (int j = i - 1; ~j; --j) {  // 从山顶向左扫；~j 等价于 j >= 0
                y = min(y, maxHeights[j]);  // 左侧塔不能比右边高，取 min 保证严格非递增
                t += y;  // 把这座塔的高度累加进总和
            }
            y = maxHeights[i];  // 右侧重新从山顶高度出发
            for (int j = i + 1; j < n; ++j) {  // 从山顶向右扫
                y = min(y, maxHeights[j]);  // 右侧塔不能比左边高，取 min 保证非递增
                t += y;  // 把这座塔的高度累加进总和
            }
            ans = max(ans, t);  // 用当前山顶方案的高度和刷新答案
        }
        return ans;  // 返回所有山顶方案中的最大高度和
    }
};