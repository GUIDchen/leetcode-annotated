// 题目：93. 复原 IP 地址（Restore IP Addresses）
// 思路：回溯切分，每段长度 1~3 且数值不超过 255、不能有前导 0；恰好切满 4 段且用完全部字符时收集答案。
// 时间复杂度：O(3^4 · n)，每段最多 3 种长度、共 4 段，拼接字符串还需 O(n)；空间复杂度：O(4)，递归深度与临时段数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> restoreIpAddresses(string s) {  // s 是待切分的数字串，返回所有合法 IPv4 地址
        int n = s.size();  // 字符串长度，供递归出口判断
        vector<string> ans;  // 结果集：保存所有合法地址
        vector<string> t;  // 回溯路径：保存已经切出的各段
        function<void(int)> dfs = [&](int i) {  // 递归函数：i 是下一段开始的下标
            if (i >= n && t.size() == 4) {  // 字符用尽且恰好凑够 4 段，得到一个合法地址
                ans.push_back(t[0] + "." + t[1] + "." + t[2] + "." + t[3]);  // 用点号拼接成标准 IPv4 形式
                return;  // 递归出口：本分支已处理完
            }
            if (i >= n || t.size() >= 4) {  // 字符用完却不足 4 段，或已经有 4 段还有剩余字符，都不是合法地址
                return;  // 剪枝返回
            }
            int x = 0;  // 当前段的数值，边扩展长度边累加
            for (int j = i; j < min(n, i + 3); ++j) {  // 枚举这一段的结尾 j：每段最多 3 位
                x = x * 10 + s[j] - '0';  // 把字符转成数字并累加到当前段
                if (x > 255 || (j > i && s[i] == '0')) {  // 数值越界，或长度大于 1 却有前导 0，都不合法
                    break;  // 再变长只会更不合法，直接结束本层的枚举
                }
                t.push_back(s.substr(i, j - i + 1));  // 当前段合法，先放进路径
                dfs(j + 1);  // 从下一段起点继续递归切分
                t.pop_back();  // 撤销这一段，尝试更长的切分
            }
        };
        dfs(0);  // 从第 0 个字符开始切分
        return ans;  // 返回所有合法地址
    }
};
