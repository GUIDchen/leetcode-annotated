// 题目：306. 累加数（Additive Number）
// 思路：枚举前两个数的切分位置，再用 DFS 逐位校验后续能否由前两项之和拼出。
// 时间复杂度：最坏 O(n^3)，n 为串长；空间复杂度：O(n)，递归栈与子串开销。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    bool isAdditiveNumber(string num) {  // num 是只含数字的字符串，判断它能否拆成累加序列
        int n = num.size();  // 串长
        for (int i = 1; i < min(n - 1, 19); ++i) {  // 枚举第一个数的结束位置 i：至少 1 位，最多 19 位以免 long long 溢出
            for (int j = i + 1; j < min(n, i + 19); ++j) {  // 枚举第二个数的结束位置 j，同样限制长度不超过 19 位
                if (i > 1 && num[0] == '0') break;  // 第一个数有前导 0 不合法，之后 i 只会更长，直接跳出外层循环
                if (j - i > 1 && num[i] == '0') continue;  // 第二个数有前导 0 不合法，换下一个 j
                auto a = stoll(num.substr(0, i));  // 取出第一个数并转成 long long
                auto b = stoll(num.substr(i, j - i));  // 取出第二个数
                if (dfs(a, b, num.substr(j, n - j))) return true;  // 用前两个数启动深度优先搜索，找到一条合法链路就返回 true
            }  // 内层循环结束
        }  // 外层循环结束
        return false;  // 所有拆分都尝试过，无法构成累加序列
    }  // isAdditiveNumber 结束

    bool dfs(long long a, long long b, string num) {  // 已知前两项 a、b，判断剩余串 num 能否继续构成累加序列
        if (num == "") return true;  // 剩余串为空，说明整个串已成功拆分
        if (a + b > 0 && num[0] == '0') return false;  // 下一项 a+b 若为正数，剩余串就不能以 '0' 开头，否则无法拼出合法数字，直接剪枝
        for (int i = 1; i < min((int) num.size() + 1, 19); ++i)  // 下一项最多 19 位，枚举它的长度 i
            if (a + b == stoll(num.substr(0, i)))  // 若剩余串前 i 位恰好等于 a+b
                if (dfs(b, a + b, num.substr(i, num.size() - i)))  // 继续搜索，把 b 与 a+b 作为新的前两项
                    return true;  // 找到完整序列，逐层向上返回 true
        return false;  // 这条分支失败
    }  // dfs 结束
};  // Solution 类结束