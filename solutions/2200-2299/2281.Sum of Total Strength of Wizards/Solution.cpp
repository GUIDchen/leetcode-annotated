// 题目：2281. 巫师的总力量和（Sum of Total Strength of Wizards）
// 核心思路：单调栈求出每个元素作为最小值时的左右边界，再用前缀和及其前缀和 O(1) 算出以它为中心的所有子数组贡献。
// 时间复杂度：O(n)，两趟单调栈与两次前缀和都是线性；空间复杂度：O(n)，栈、边界数组与两份前缀和都随 n 增长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int totalStrength(vector<int>& strength) {  // strength：每位巫师的力量值数组
        int n = strength.size();  // 数组长度，后续所有循环的上界
        vector<int> left(n, -1);  // left[i]：i 左边第一个严格更小元素的下标，-1 表示不存在
        vector<int> right(n, n);  // right[i]：i 右边第一个不大于当前元素的下标，n 表示不存在
        stack<int> stk;  // 单调递增栈，存放还没确定左边界的下标
        for (int i = 0; i < n; ++i) {  // 从左往右扫，确定每个位置的左边界
            while (!stk.empty() && strength[stk.top()] >= strength[i]) stk.pop();  // 栈顶力量不小于当前值就不能再当左边界，弹掉；用 >= 保证相等时取更靠左的边界
            if (!stk.empty()) left[i] = stk.top();  // 弹完后栈顶就是左边第一个更小的元素
            stk.push(i);  // 当前下标入栈，等待成为后面元素的左边界
        }  // 第一趟扫描结束
        stk = stack<int>();  // 清空并复用同一个栈，做从右往左的扫描
        for (int i = n - 1; i >= 0; --i) {  // 从右往左扫，确定每个位置的右边界
            while (!stk.empty() && strength[stk.top()] > strength[i]) stk.pop();  // 用严格大于弹栈，与左边界配合避免同一区间被重复统计
            if (!stk.empty()) right[i] = stk.top();  // 栈顶就是右边第一个不大于当前值的元素
            stk.push(i);  // 入栈，等待成为左边元素的右边界
        }  // 第二趟扫描结束
        int mod = 1e9 + 7;  // 结果要对 1e9+7 取模
        vector<int> s(n + 1);  // s[i]：strength 前 i 项之和
        for (int i = 0; i < n; ++i) s[i + 1] = (s[i] + strength[i]) % mod;  // 递推前缀和，边加边取模防止溢出
        vector<int> ss(n + 2);  // ss[i]：前缀和数组 s 的前 i 项之和，即「前缀和的前缀和」
        for (int i = 0; i < n + 1; ++i) ss[i + 1] = (ss[i] + s[i]) % mod;  // 再叠一层前缀和，之后可在 O(1) 时间内查出任意区间的加权和
        int ans = 0;  // 累计所有子数组的「最小值 × 元素和」之和
        for (int i = 0; i < n; ++i) {  // 枚举每个元素，让它作为所在子数组的最小值来统计贡献
            int v = strength[i];  // 当前元素，也就是这段子数组的最小值
            int l = left[i] + 1, r = right[i] - 1;  // 合法子数组必须同时包含 i，端点落在 [l, r] 内
            long a = (long) (i - l + 1) * (ss[r + 2] - ss[i + 1]);  // 左端点取 [l, i] 时，右半部分区间和的加权结果
            long b = (long) (r - i + 1) * (ss[i + 1] - ss[l]);  // 右端点取 [i, r] 时，左半部分区间和的加权结果
            ans = (ans + v * ((a - b) % mod)) % mod;  // 乘上最小值 v 累加；a-b 可能为负，先取模再由末尾统一修正
        }  // 枚举结束
        return (int) (ans + mod) % mod;  // 加上 mod 再取模，把可能的负数结果拉回非负区间
    }  // 方法结束
};  // 类定义结束