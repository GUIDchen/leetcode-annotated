// 3399. 字符相同的最短子字符串 II / Smallest Substring With Identical Characters II
// 核心思路：二分答案 m，判定能否用不超过 numOps 次操作把所有同字符段压到长度 ≤ m（m == 1 时与 01 交替串比较，取两种模板中较小的改动数）
// 复杂度：时间 O(n log n)，空间 O(1)
class Solution {  // 定义题目解答类
public:
    int minLength(string s, int numOps) {  // 方法入口：s 为 01 串，numOps 为最多可修改的字符数
        int n = s.size();  // 记录字符串长度，供判定函数与二分区间使用
        auto check = [&](int m) {  // 定义判定函数：所有同字符段长度都不超过 m 时是否可行
            int cnt = 0;  // 累计需要修改的字符数
            if (m == 1) {  // 上限为 1 时目标串只能是 01 交替串
                string t = "01";  // 交替模板，按下标奇偶取 "0" 或 "1"
                for (int i = 0; i < n; ++i) {  // 逐位与交替模板比较
                    if (s[i] == t[i & 1]) {  // 该位与模板相同
                        ++cnt;  // 相同位置个数加一
                    }
                }
                cnt = min(cnt, n - cnt);  // 改成 "01…" 需改 cnt 位，改成 "10…" 需改 n - cnt 位，取较小者
            } else {  // 上限大于 1 时按连续相同段分别计算
                int k = 0;  // 当前连续相同段的长度
                for (int i = 0; i < n; ++i) {  // 遍历整个字符串
                    ++k;  // 当前段长度加一
                    if (i == n - 1 || s[i] != s[i + 1]) {  // 到达末尾或与下一个字符不同，说明一段结束
                        cnt += k / (m + 1);  // 长度为 k 的段每 m + 1 个字符需改 1 个，共需 k / (m + 1) 次
                        k = 0;  // 清零，开始统计下一段
                    }
                }
            }
            return cnt <= numOps;  // 所需操作次数不超过 numOps 即可行
        };
        int l = 1, r = n;  // 可行长度落在 [1, n]，且可行性关于 m 单调
        while (l < r) {  // 二分查找最小的可行上限
            int mid = (l + r) >> 1;  // 取区间中点
            if (check(mid)) {  // mid 可行
                r = mid;  // 收缩右边界，保留更小的可行值
            } else {  // mid 不可行
                l = mid + 1;  // 左边界右移到 mid + 1
            }
        }
        return l;  // l == r 即最小的可行长度
    }
};
