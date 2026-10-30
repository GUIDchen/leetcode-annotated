// 3675. Minimum Operations to Transform String（转换字符串的最小操作次数）
// 核心思路：把非 'a' 字符改成 'a' 需要 26 - (c - 'a') 次操作，答案取这些值中的最大值，全为 'a' 时为 0。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义 Solution 类
public:
    int minOperations(string s) {  // 求把字符串所有字符变成 'a' 的最小操作次数
        int ans = 0;  // 记录所需的最小操作次数，初始为 0
        for (char c : s) {  // 遍历字符串中的每个字符
            if (c != 'a') {  // 只处理非 'a' 的字符
                ans = max(ans, 26 - (c - 'a'));  // 把 c 变成 'a' 需要 26 - (c - 'a') 次操作，取最大值
            }
        }
        return ans;  // 返回让所有字符统一为 'a' 的最小操作次数
    }
};
