// 题目：3571. 最短超级串 II（Find the Shortest Superstring II）
// 思路：先保证 s1 是较短的串；若 s1 已是 s2 的子串，答案就是 s2；否则枚举重叠长度，分别检查 s1 的后缀与 s2 的前缀重叠、s1 的前缀与 s2 的后缀重叠，命中就省掉重叠部分拼接返回；都不成立则直接首尾相连。
// 时间复杂度：O(n^2)，枚举 O(n) 次、每次 find 最多 O(n)；空间复杂度：O(1)，只用常数个临时串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shortestSuperstring(string s1, string s2) {  // s1、s2：待合并的两个字符串；返回同时包含两者的最短超级串
        int m = s1.size(), n = s2.size();  // 两个字符串的长度
        if (m > n) {  // 保证 s1 是较短的串，可缩小后面的枚举范围
            return shortestSuperstring(s2, s1);  // 交换参数后递归求解，答案不变
        }  // 长短交换结束
        if (s2.find(s1) != string::npos) {  // s1 已经完整出现在 s2 中，无需再拼接
            return s2;  // 答案就是 s2
        }  // 包含判断结束
        for (int i = 0; i < m; ++i) {  // 枚举切分位置 i，重叠长度为 m - i
            if (s2.find(s1.substr(i)) == 0) {  // s1 的后缀 s1[i:] 恰好等于 s2 的前缀
                return s1.substr(0, i) + s2;  // 把 s1 未重叠的前缀拼在 s2 前面，重叠部分被省掉
            }  // 后缀匹配判断结束
            if (s2.rfind(s1.substr(0, m - i)) == s2.size() - (m - i)) {  // s1 的前缀 s1[0..m-i) 恰好等于 s2 的后缀
                return s2 + s1.substr(m - i);  // 把 s1 未重叠的后缀拼在 s2 后面
            }  // 前缀匹配判断结束
        }  // 所有重叠方案都试过
        return s1 + s2;  // 没有任何重叠，直接首尾相连
    }  // 方法结束
};  // 类定义结束
