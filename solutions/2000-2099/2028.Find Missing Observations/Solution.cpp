// 题目：2028. 找出缺失的观测数据（Find Missing Observations）
// 思路：用「总个数 × 平均值」减去已知观测值之和，得到缺失部分必须凑出的和 s；再用 s 是否落在 [n, 6n] 判断可行性，然后把 s 尽量平均分成 n 份、余数逐个补给前面若干份。
// 时间复杂度：O(m + n)，m 为已知观测值个数；空间复杂度：O(n)，用于存放答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {  // rolls：已知的观测值；mean：全部数据的平均值；n：缺失的观测次数；返回任意一组合法缺失数据
        int m = rolls.size();  // 已知观测值的个数 m
        int s = (n + m) * mean - accumulate(rolls.begin(), rolls.end(), 0);  // 缺失部分的总和 = 全体总和 - 已知部分之和
        if (s > n * 6 || s < n) {  // 每个骰子点数只能取 1~6，因此缺失和必须落在 [n, 6n] 内
            return {};  // 无解，按题目要求返回空数组
        }  // 可行性判断结束
        vector<int> ans(n, s / n);  // 先给每个缺失位置分配「平均值向下取整」的份额
        for (int i = 0; i < s % n; ++i) {  // 余数有 s % n 个，逐个补给开头的若干位置
            ++ans[i];  // 每个位置补 1；因为 s/n < 6 时补完也不会超过 6
        }  // 余数分配完毕
        return ans;  // 返回构造好的缺失观测数据
    }  // 方法结束
};  // 类定义结束