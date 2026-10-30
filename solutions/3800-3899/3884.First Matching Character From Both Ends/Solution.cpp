// 3884. 双端字符匹配 / First Matching Character From Both Ends
// 核心思路：从左端枚举到中点，比较 s[i] 与对称位置 s[n-1-i]，第一个相等的位置即为答案。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有接口
    int firstMatchingIndex(string s) {  // 返回首尾对称位置字符相同的最小下标
        int n = s.size();  // 字符串长度
        for (int i = 0; i < n / 2 + 1; ++i) {  // 从左端向后枚举，最多到中点
            if (s[i] == s[n - i - 1]) {  // 与对称的最右端字符比较
                return i;  // 找到最小的匹配下标
            }  // if 分支结束
        }  // 枚举结束
        return -1;  // 不存在匹配则返回 -1
    }  // 方法结束
};  // 类定义结束
