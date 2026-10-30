// 3398. 字符相同的最短子字符串 I / Smallest Substring With Identical Characters I
// 核心思路：二分答案 m，判断能否用不超过 numOps 次修改让所有相同字符连续段长度不超过 m：m=1 时只能是 0101... 或 1010... 两种交替串；m>1 时长度为 k 的连续段需要 k/(m+1) 次拆分修改
// 复杂度：时间 O(n log n)（二分 log n 次、每次 check O(n)）、空间 O(1)
class Solution {  // 定义 Solution 类
public:  // 公有方法
    int minLength(string s, int numOps) {  // 求至多修改 numOps 个字符后，最长相同字符子串的最小可能长度
        int n = s.size();  // 记下字符串长度
        auto check = [&](int m) {  // 判断最大连续长度不超过 m 时所需的最少修改次数是否不超过 numOps
            int cnt = 0;  // 记录需要的修改次数
            if (m == 1) {  // 当 m 等于 1 时，结果串只能是 0101... 或 1010... 两种交替形式
                string t = "01";  // 交替串模板
                for (int i = 0; i < n; ++i) {  // 逐位检查与模板的匹配情况
                    if (s[i] == t[i & 1]) {  // 若该字符与模板对应位置相同
                        ++cnt;  // 统计与模板相同的字符数（即保留不动的字符数）
                    }  // 判断结束
                }  // 循环结束
                cnt = min(cnt, n - cnt);  // 两种交替模板取修改次数较少者
            } else {  // 当 m 大于 1 时，按连续相同字符段分段处理
                int k = 0;  // 当前连续相同字符段的长度
                for (int i = 0; i < n; ++i) {  // 逐位遍历字符串
                    ++k;  // 当前段长度加一
                    if (i == n - 1 || s[i] != s[i + 1]) {  // 到达末尾或与下一个字符不同，说明一段结束
                        cnt += k / (m + 1);  // 长度为 k 的段每 m+1 个字符需要改一次，共需 k/(m+1) 次修改
                        k = 0;  // 段长度清零
                    }  // 判断结束
                }  // 循环结束
            }  // 分支结束
            return cnt <= numOps;  // 修改次数不超过 numOps 说明 m 可行
        };  // lambda 定义结束
        int l = 1, r = n;  // 答案下界为 1，上界为字符串长度 n
        while (l < r) {  // 二分查找最小的可行长度
            int mid = (l + r) >> 1;  // 取中点
            if (check(mid)) {  // 若 mid 可行
                r = mid;  // 缩小上界
            } else {  // 否则 mid 不可行
                l = mid + 1;  // 下界右移到 mid+1
            }  // 判断结束
        }  // 循环结束
        return l;  // 返回最小可行长度
    }  // 方法结束
};  // 类定义结束
