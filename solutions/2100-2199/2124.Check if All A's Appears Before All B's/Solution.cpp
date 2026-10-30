// 题目：2124. 检查是否所有 A 都在 B 之前（Check if All A's Appears Before All B's）
// 核心思路：所有 A 都在 B 之前，等价于字符串里不存在子串 "ba"，一次查找即可判定。
// 时间复杂度：O(n)，contains 内部线性扫描；空间复杂度：O(1)，只查一个长度 2 的模式。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkString(string s) {  // s：只含 'a' 与 'b' 的字符串
        return !s.contains("ba");  // 出现 "ba" 说明某个 A 排到了 B 后面，取反即为答案
    }
};
