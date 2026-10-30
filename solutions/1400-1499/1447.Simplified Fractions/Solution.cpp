// 题目：1447. 最简分数（Simplified Fractions）
// 核心思路：枚举所有满足 1 ≤ i < j ≤ n 的分数 i/j，用最大公约数判断是否互质，互质的就是最简分数。
// 时间复杂度：O(n^2 log n)，共 O(n^2) 对分数、每对做一次 gcd；空间复杂度：O(1) 额外空间（不计答案数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> simplifiedFractions(int n) {  // 返回 0 到 1 之间（不含 0 和 1）、分母不超过 n 的所有最简分数
        vector<string> ans;  // 存放结果的字符串数组
        for (int i = 1; i < n; ++i) {  // 枚举分子 i，取值范围 1 到 n-1
            for (int j = i + 1; j < n + 1; ++j) {  // 枚举分母 j，保证 j > i（分数小于 1）且 j ≤ n
                if (__gcd(i, j) == 1) {  // __gcd 求最大公约数，等于 1 说明 i/j 已经互质，就是最简形式
                    ans.push_back(to_string(i) + "/" + to_string(j));  // 把分子分母拼成 "i/j" 后加入答案
                }  // if 分支结束
            }  // 内层循环（分母）结束
        }  // 外层循环（分子）结束
        return ans;  // 返回全部最简分数
    }  // simplifiedFractions 方法结束
};  // 类定义结束（源文件此处无结尾换行，保持原样）