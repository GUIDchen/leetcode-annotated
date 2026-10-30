// 题目：1759. 统计同质子字符串的数目（Count Number of Homogenous Substrings）
// 思路：按连续相同字符分段，长度为 cnt 的段贡献 cnt*(cnt+1)/2 个子串，逐段累加并取模。
// 时间复杂度：O(n)，i 与 j 都只向右前进；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 题目要求的取模常数

    int countHomogenous(string s) {  // s：只含小写字母的字符串
        int n = s.size();  // 字符串长度
        long ans = 0;  // 累计答案，用 long 避免中间乘法溢出
        for (int i = 0, j = 0; i < n; i = j) {  // i 是每段起点，本轮结束时把 i 跳到 j（即下一段起点）
            j = i;  // 从段起点开始向右探测
            while (j < n && s[j] == s[i]) ++j;  // 只要字符与段首相同就继续右移，直到不同或越界
            int cnt = j - i;  // 这一段连续相同字符的长度
            ans += 1ll * (1 + cnt) * cnt / 2;  // 该段贡献 cnt*(cnt+1)/2 个同质子串，1ll 保证按 64 位计算
            ans %= mod;  // 每段累加后立即取模，防止数值膨胀
        }
        return ans;  // 返回总数目（已取模，自动转回 int）
    }
};