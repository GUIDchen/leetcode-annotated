// 题目：906. 超级回文数（Super Palindromes）
// 核心思路：超级回文数的平方根必须是回文数，于是先枚举回文根并镜像生成所有回文数，平方后判断是否落在区间内且仍是回文。
// 时间复杂度：O(M log R)，M≈2×10^5 个候选回文数，每个判回文 O(log R)；空间复杂度：O(M) 存储回文数。
using ll = unsigned long long;  // 用更短的名字表示无符号长整型，避免平方后溢出

ll ps[2 * 100000];  // 预处理数组：保存所有由回文根镜像生成的回文数，供多次查询复用

int init = [] {  // 全局 lambda：在程序启动时执行一次预处理
    for (int i = 1; i <= 100000; i++) {  // 枚举回文根 i，10^5 的上界足以覆盖 10^18 的平方范围
        string s = to_string(i);  // 回文根的字符串形式
        string t1 = s;  // t1 用来构造偶数长度的回文
        reverse(t1.begin(), t1.end());  // 反转得到镜像部分
        string t2 = s.substr(0, s.length() - 1);  // 去掉最后一位，用于构造奇数长度的回文
        reverse(t2.begin(), t2.end());  // 反转得到奇数长度回文的镜像部分
        ps[2 * i - 2] = stoll(s + t1);  // 存入偶数长度回文 s + reverse(s)
        ps[2 * i - 1] = stoll(s + t2);  // 存入奇数长度回文 s + reverse(s 去掉末位)
    }  // 结束预处理循环
    return 0;  // lambda 需要有返回值，这里只是占位
}();  // 立即调用，返回值赋给 init，从而在全局初始化阶段执行

class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int superpalindromesInRange(string left, string right) {  // left/right：闭区间边界（字符串形式，可能超出 int 范围）
        ll l = stoll(left), r = stoll(right);  // 转成 64 位整数，方便比较大小
        int ans = 0;  // 统计区间内超级回文数的个数
        for (ll p : ps) {  // 枚举所有预处理好的回文数 p
            ll x = p * p;  // 超级回文数要求平方根也是回文数，所以检查 p*p
            if (x >= l && x <= r && is_palindrome(x)) {  // 落在区间内，且 p*p 本身仍然是回文数
                ++ans;  // 计数加一
            }  // 结束条件判断
        }  // 结束枚举
        return ans;  // 返回区间内超级回文数的个数
    }  // 结束 superpalindromesInRange

    bool is_palindrome(ll x) {  // 判断 x 是否是回文数
        ll y = 0;  // y 保存 x 反转后的数字
        for (ll t = x; t; t /= 10) {  // 从低位到高位逐位取出
            y = y * 10 + t % 10;  // 把当前最低位接到 y 的末尾
        }  // 结束逐位反转
        return x == y;  // 反转后与原数相同即为回文数
    }  // 结束 is_palindrome
};  // 结束 Solution 类