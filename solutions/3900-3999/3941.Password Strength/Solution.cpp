// 3941. 密码强度 / Password Strength
// 核心思路：先用集合去重，再按小写 1 分、大写 2 分、数字 3 分、其他字符 5 分对每种不同字符累加。
// 复杂度：时间 O(n)，空间 O(1)（字符集大小固定）。
class Solution {  // 题解类定义
public:  // 公开接口
    int passwordStrength(string password) {  // 主函数：计算密码强度
        unordered_set<char> st(password.begin(), password.end());  // 构造字符集合，自动去重

        int ans = 0;  // 强度总分

        for (char ch : st) {  // 遍历每一种不同字符
            if (islower(ch)) {  // 小写字母
                ans += 1;  // 加 1 分
            } else if (isupper(ch)) {  // 大写字母
                ans += 2;  // 加 2 分
            } else if (isdigit(ch)) {  // 数字字符
                ans += 3;  // 加 3 分
            } else {  // 其余符号字符
                ans += 5;  // 加 5 分
            }  // if-else 链结束
        }  // 字符遍历结束

        return ans;  // 返回总强度
    }  // passwordStrength 函数结束
};  // 类定义结束