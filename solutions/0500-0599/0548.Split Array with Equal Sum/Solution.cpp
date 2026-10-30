// 题目：548. 将数组分割成和相等的子数组（Split Array with Equal Sum）🔒
// 思路：先用前缀和 O(1) 求区间和，枚举第二段的右端点 j；用哈希集合记下「能与 j 凑出相等前两段」的段和，再从右侧枚举 k 检查后两段是否相等且该和在集合中。
// 时间复杂度：O(n^2)，外层枚举 j、内层分别枚举 i 与 k；空间复杂度：O(n)，前缀和数组与哈希集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool splitArray(vector<int>& nums) {  // 判断能否把数组切成四段非空子数组，且四段之和彼此相等
        int n = nums.size();  // 数组长度 n
        vector<int> s(n + 1);  // 前缀和数组：s[i] 表示前 i 个元素之和，区间和可由 s[r]-s[l] 得到
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + nums[i];  // 递推计算前缀和，内联写法让预处理更紧凑
        for (int j = 3; j < n - 3; ++j) {  // 枚举第二段的右端点 j：左边、右边各至少留 3 个元素才放得下四段
            unordered_set<int> seen;  // 记录「能和 j 组成相等前两段」的段和，供后两段匹配
            for (int i = 1; i < j - 1; ++i)  // 枚举前两段的切点 i（第一段是 [0, i-1]，第二段是 [i+1, j]）
                if (s[i] == s[j] - s[i + 1])  // 第一段和 s[i] 与第二段和 s[j]-s[i+1] 相等
                    seen.insert(s[i]);  // 这个段和是可行的，记进集合
            for (int k = j + 2; k < n - 1; ++k)  // 枚举后两段的切点 k（第三段是 [j+1, k-1]，第四段是 [k+1, n-1]）
                if (s[n] - s[k + 1] == s[k] - s[j + 1] && seen.count(s[n] - s[k + 1]))  // 后两段之和相等，且这个和也出现在集合中（四段全等）
                    return true;  // 找到一种合法切法，立即返回
        }  // 结束枚举 k 的 for
        return false;  // 所有切法都试过仍不满足
    }  // 结束 splitArray
};  // 类定义结束