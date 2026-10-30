// 题目：2167. 移除所有载有违禁货物车厢所需的最少时间（Minimum Time to Remove All Cars Containing Illegal Goods）
// 思路：pre[i] 是只清理前 i 节中违禁车厢的最少时间，suf[i] 是只清理第 i 节及之后违禁车厢的最少时间；枚举分界点取两侧之和的最小值。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，两个长度为 n+1 的前后缀数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTime(string s) {  // s：'0' 是正常车厢，'1' 是违禁车厢；返回清空所有违禁车厢的最少时间
        int n = s.size();  // n：车厢数量，也是下标上界
        vector<int> pre(n + 1);  // pre[i]：只处理下标 0..i-1 这些车厢中的违禁车厢所需的最少时间
        vector<int> suf(n + 1);  // suf[i]：只处理下标 i..n-1 这些车厢中的违禁车厢所需的最少时间
        for (int i = 0; i < n; ++i) pre[i + 1] = s[i] == '0' ? pre[i] : min(pre[i] + 2, i + 1);  // 从左往右预处理：正常车厢不花时间；违禁车厢二选一，要么从左侧逐个移除（花 i+1 秒），要么在中间单独移出（花 2 秒）再继承上一个前缀
        for (int i = n - 1; ~i; --i) suf[i] = s[i] == '0' ? suf[i + 1] : min(suf[i + 1] + 2, n - i);  // 从右往左对称预处理；~i 等价于 i != -1，下标减到 -1 时循环结束
        int ans = INT_MAX;  // ans 先置为无穷大，后面逐步取最小值
        for (int i = 1; i <= n; ++i) ans = min(ans, pre[i] + suf[i]);  // 枚举分界点 i：左侧用 pre[i]（从左边清理），右侧用 suf[i]（从右边清理），两者相加就是该切分方案的总时间
        return ans;  // 返回所有切分方案中的最小总时间
    }  // 方法结束
};  // 类定义结束