// 题目：3388. 统计数组中的美丽分割（Count Beautiful Splits in an Array）
// 思路：先 DP 求出任意两个后缀的最长公共前缀 lcp[i][j]，再枚举两个切点 i、j，用 lcp 判断第一段或第二段是否为后一段的前缀。
// 时间复杂度：O(n^2)，两重循环填 lcp 与枚举切点；空间复杂度：O(n^2)，lcp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int beautifulSplits(vector<int>& nums) {  // nums：输入数组，返回美丽分割的方案数
        int n = nums.size();  // 数组长度
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));  // lcp[i][j]：从 i 开始与从 j 开始的后缀的最长公共前缀长度

        for (int i = n - 1; i >= 0; i--) {  // 从后往前填 lcp，这样用到的 lcp[i+1][j+1] 已经算好
            for (int j = n - 1; j > i; j--) {  // 只关心 j > i 的位置，保证两段不重叠
                if (nums[i] == nums[j]) {  // 当前字符相同才能延长公共前缀
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;  // 长度等于后一位的 lcp 再加一
                }  // 分支结束
            }  // 内层循环结束
        }  // 外层循环结束，lcp 表构建完成

        int ans = 0;  // ans：美丽分割的方案数
        for (int i = 1; i < n - 1; i++) {  // 枚举第一个切点 i，切成 nums[0..i) 与 nums[i..n) 两部分
            for (int j = i + 1; j < n; j++) {  // 枚举第二个切点 j，把后半段再切一刀
                bool a = (i <= j - i) && (lcp[0][i] >= i);  // 情况一：第一段是第二段的前缀（第一段长度不超过第二段且 lcp >= i）
                bool b = (j - i <= n - j) && (lcp[i][j] >= j - i);  // 情况二：第二段是第三段的前缀（第二段长度不超过第三段且 lcp >= j-i）
                if (a || b) {  // 任一情况成立就是一种美丽分割
                    ans++;  // 方案数加一
                }  // 分支结束
            }  // 内层循环结束
        }  // 外层循环结束

        return ans;  // 返回方案数
    }  // 题解方法结束
};  // 题解类定义结束
