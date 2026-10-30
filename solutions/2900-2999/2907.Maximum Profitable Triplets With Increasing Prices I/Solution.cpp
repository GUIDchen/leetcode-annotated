// 题目：2907. 价格递增的最大利润三元组 I（Maximum Profitable Triplets With Increasing Prices I）
// 核心思路：枚举中间下标 j 作为三元组的「峰」，分别向左找价格更小者中的最大利润、向右找价格更大者中的最大利润，两侧都存在时用 left + profits[j] + right 更新答案。
// 时间复杂度：O(n^2)，每个 j 都要扫一遍左右两边；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProfit(vector<int>& prices, vector<int>& profits) {  // prices 是价格数组，profits 是对应利润数组，返回最大利润和
        int n = prices.size();  // 数组长度
        int ans = -1;  // 初始化为 -1，表示暂时还没有找到合法三元组
        for (int j = 0; j < n; ++j) {  // 枚举中间那个下标 j，把它当作三元组的“山峰”
            int left = 0, right = 0;  // left 存左侧合法元素的最大利润，right 存右侧的最大利润，0 表示该侧还没找到
            for (int i = 0; i < j; ++i) {  // 在 j 左边找一个价格更小且利润最大的元素
                if (prices[i] < prices[j]) {  // 价格必须严格小于 prices[j] 才满足递增条件
                    left = max(left, profits[i]);  // 记录左侧能拿到的最大利润
                }  // if 结束
            }  // 左侧扫描结束
            for (int k = j + 1; k < n; ++k) {  // 在 j 右边找价格更大且利润最大的元素
                if (prices[j] < prices[k]) {  // 价格必须严格大于 prices[j] 才满足递增条件
                    right = max(right, profits[k]);  // 记录右侧能拿到的最大利润
                }  // if 结束
            }  // 右侧扫描结束
            if (left && right) {  // 0 代表对应侧没找到，两侧都非 0 才构成合法三元组
                ans = max(ans, left + profits[j] + right);  // 用两侧最大利润加上中间元素的利润更新答案
            }  // if 结束
        }  // 枚举结束
        return ans;  // 返回最大利润，找不到时仍是 -1
    }  // 方法结束
};  // 类定义结束