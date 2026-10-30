// 题目：2609. 最长平衡子字符串（Find the Longest Balanced Substring of a Binary String）
// 思路：枚举所有子串，校验「前半全为 0、后半全为 1 且两段长度相等」，取满足条件的最大长度。
// 时间复杂度：O(n^3)，枚举 O(n^2) 个子串、每个校验 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTheLongestBalancedSubstring(string s) {  // s：只含 0/1 的字符串；返回最长平衡子串长度
        int n = s.size();  // n：字符串长度
        int ans = 0;  // ans：目前找到的最长平衡子串长度
        auto check = [&](int i, int j) -> bool {  // lambda：判断子串 s[i..j] 是否「前半全 0、后半全 1 且等长」
            int cnt = 0;  // cnt：子串中字符 '1' 的个数
            for (int k = i; k <= j; ++k) {  // 从左到右扫描子串
                if (s[k] == '1') {  // 遇到字符 '1'
                    ++cnt;  // 计数加一
                } else if (cnt) {  // 已经出现过 '1' 之后又遇到 '0'
                    return false;  // 顺序被破坏，不是平衡子串
                }  // 分支结束
            }  // 扫描结束
            return cnt * 2 == j - i + 1;  // 1 的个数乘以 2 等于子串长度，说明 0 与 1 各占一半
        };  // lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 枚举子串左端点
            for (int j = i + 1; j < n; ++j) {  // 枚举右端点，长度至少为 2 才可能平衡
                if (check(i, j)) {  // 该子串是平衡子串
                    ans = max(ans, j - i + 1);  // 用它的长度更新答案
                }  // 分支结束
            }  // 右端点枚举结束
        }  // 左端点枚举结束
        return ans;  // 返回最长平衡子串长度
    }  // 方法结束
};  // 类定义结束