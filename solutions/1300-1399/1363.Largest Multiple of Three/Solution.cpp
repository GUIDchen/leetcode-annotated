// 题目：1363. 形成三的最大倍数（Largest Multiple of Three）
// 思路：排序后做「数字和模 3」的长度 DP：f[i][j] 表示前 i 个数字能选出的、和模 3 余 j 的最大长度，再从后往前回溯出具体数字，最后去掉前导零。
// 时间复杂度：O(n)，一次 DP 加一次回溯；空间复杂度：O(n)，DP 数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestMultipleOfThree(vector<int>& digits) {  // digits：可使用的数字集合
        sort(digits.begin(), digits.end());  // 升序排序，便于 DP 以及回溯时先取到较大的数字
        int n = digits.size();  // n 是数字个数
        int f[n + 1][3];  // f[i][j]：从前 i 个数字中能选出的、数字和模 3 余 j 的最大长度
        memset(f, -0x3f, sizeof(f));  // 初始化为极小值，表示该余数暂时不可达
        f[0][0] = 0;  // 一个都不选时和为 0、余 0、长度 0
        for (int i = 1; i <= n; ++i) {  // 逐个考虑每个数字
            for (int j = 0; j < 3; ++j) {  // 枚举目标余数 j
                f[i][j] = max(f[i - 1][j], f[i - 1][(j - digits[i - 1] % 3 + 3) % 3] + 1);  // 不选第 i 个数字，或选它（余数由 k 变为 j），取长度更大的方案
            }  // 余数枚举结束
        }  // 数字枚举结束
        if (f[n][0] <= 0) {  // 没有任何非空子集能被 3 整除
            return "";  // 按题意返回空字符串
        }  // if 结束
        string ans;  // 保存回溯出的数字字符（先拼大数，结果天然最大）
        for (int i = n, j = 0; i; --i) {  // 从最后一位往前回溯；j 是当前状态需要满足的余数
            int k = (j - digits[i - 1] % 3 + 3) % 3;  // 若选第 i 个数字，则上一状态需要的余数 k
            if (f[i - 1][k] + 1 == f[i][j]) {  // 长度恰好差 1，说明第 i 个数字确实被选中
                ans += digits[i - 1] + '0';  // 把数字转成字符拼到答案末尾
                j = k;  // 更新需要的余数，继续往前回溯
            }  // if 结束
        }  // 回溯结束
        int i = 0;  // 从头开始找第一个非零数字
        while (i < ans.size() - 1 && ans[i] == '0') {  // 跳过前导零，但至少保留一位（避免把 0 变成空串）
            ++i;  // 继续后移
        }  // while 结束
        return ans.substr(i);  // 去掉前导零后返回答案
    }  // 方法结束
};  // 类定义结束