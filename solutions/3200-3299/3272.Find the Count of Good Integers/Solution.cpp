// 题目：3272. 统计好整数的数目（Find the Count of Good Integers）
// 思路：只枚举回文数的前半部分拼出完整回文，先判断能否被 k 整除，再按「数字多重集」去重，用可重排列公式计数。
// 时间复杂度：O(10^(n/2) · n log n)，枚举前半部分并排序；空间复杂度：O(10^(n/2) · n)，存放已访问的数字串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countGoodIntegers(int n, int k) {  // n：位数；k：要求整除的除数
        vector<long long> fac(n + 1, 1);  // 阶乘表，fac[i] = i!，用于之后的可重排列计数
        for (int i = 1; i <= n; ++i) {  // 递推求出 1! 到 n!
            fac[i] = fac[i - 1] * i;  // 阶乘递推式：i! = (i-1)! * i
        }

        long long ans = 0;  // 累计答案：好整数的个数
        unordered_set<string> vis;  // 记录已统计过的「数字多重集」排序串，避免同一组数字被重复计数
        int base = pow(10, (n - 1) / 2);  // 回文前半部分的最小值，例如 n=4 时从 10 开始枚举两位前半段

        for (int i = base; i < base * 10; ++i) {  // 枚举回文前半部分的所有取值
            string s = to_string(i);  // 前半部分转成字符串
            string rev = s;  // 复制一份，准备翻转出后半部分
            reverse(rev.begin(), rev.end());  // 翻转得到镜像的后半部分
            s += rev.substr(n % 2);  // 拼接后半部分；n 为奇数时跳过翻转串首位，因为中间位与前半末尾共用
            if (stoll(s) % k) {  // 整个回文数不能被 k 整除，就不是好整数
                continue;  // 直接跳过这个回文数
            }
            string t = s;  // 复制回文串，用来生成它的数字多重集标识
            sort(t.begin(), t.end());  // 排序后作为该多重集的唯一标识
            if (vis.count(t)) {  // 这个数字组合已经统计过
                continue;  // 跳过，保证每个多重集只计算一次，避免重复枚举
            }
            vis.insert(t);  // 标记该数字组合已处理
            vector<int> cnt(10);  // cnt[d] 表示数字 d 在这个多重集中出现的次数
            for (char c : t) {  // 遍历多重集中的每个字符
                cnt[c - '0']++;  // 统计对应数字的出现次数
            }
            long long res = (n - cnt[0]) * fac[n - 1];  // 首位不能为 0：先选首位，再排列剩余 n-1 位
            for (int x : cnt) {  // 依次除以每个数字重复次数的阶乘
                res /= fac[x];  // 可重排列公式的分母部分，去掉相同数字造成的重复
            }
            ans += res;  // 把该多重集能组成的好整数个数累加进答案
        }
        return ans;  // 返回好整数的总数
    }
};
