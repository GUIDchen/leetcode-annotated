// 题目：2081. k 镜像数字的和（Sum of k-Mirror Numbers）
// 思路：按十进制回文数位数 l 递增枚举，用前半部分拼出每个十进制回文数，再检查它在 k 进制下是否也回文，凑满 n 个求和。
// 时间复杂度：约 O(10^(l/2) * log_k(10^l))，只需枚举到第 n 个答案出现；空间复杂度：O(log_k(x))，用于存放 k 进制各位。
class Solution {  // LeetCode 约定的题解类
public:  // kMirror 对外可见，check 在下方私有区
    long long kMirror(int k, int n) {  // k：进制；n：需要收集的 k 镜像数个数；返回它们的和
        long long ans = 0;  // 累加和，数值可能很大所以用 long long
        for (int l = 1;; ++l) {  // l 是十进制回文数的位数，逐个位数枚举下去
            int x = pow(10, (l - 1) / 2);  // l 位回文数前半部分的下界，如 l=5 时为 10^2
            int y = pow(10, (l + 1) / 2);  // l 位回文数前半部分的上界（开区间），如 l=5 时为 10^3
            for (int i = x; i < y; ++i) {  // 枚举该位数下所有可能的「前半部分」
                long long v = i;  // v 由前半部分 i 生成完整的十进制回文数
                int j = (l % 2 == 0) ? i : i / 10;  // 偶数位整体镜像；奇数位要丢掉末位后再镜像
                while (j > 0) {  // 把前半部分的低位逐位反序拼到末尾
                    v = v * 10 + j % 10;  // 追加 j 的最低位
                    j /= 10;  // 去掉已经用过的位
                }  // 结束镜像拼接
                if (check(v, k)) {  // 检查 v 在 k 进制下是否也是回文
                    ans += v;  // 是 k 镜像数，累加进答案
                    if (--n == 0) {  // 已收集个数减一，减到 0 说明凑满 n 个
                        return ans;  // 返回前 n 个 k 镜像数字之和
                    }  // 结束 if (--n == 0)
                }  // 结束 if (check(v, k))
            }  // 结束内层枚举
        }  // 结束按位数枚举的循环（外层无限循环由 return 退出）
    }  // kMirror 方法结束

private:  // 以下为私有辅助函数
    bool check(long long x, int k) {  // 判断 x 在 k 进制表示下是否回文
        vector<int> s;  // s 存放 x 的 k 进制各位，低位在前
        while (x > 0) {  // 不断取模转成 k 进制
            s.push_back(x % k);  // 保存当前最低位
            x /= k;  // 右移去掉最低位
        }  // 转换结束
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {  // 双指针从两端向中间比较
            if (s[i] != s[j]) {  // 两端数字不同，说明不是回文
                return false;  // 立刻返回 false
            }  // 结束 if
        }  // 结束 for
        return true;  // 全部对称，是回文
    }  // check 函数结束
};  // Solution 类结束
