// 题目：1849. 将字符串拆分为递减的连续值（Splitting a String Into Descending Consecutive Values）
// 思路：DFS 枚举每段的切点，首段不限制取值、但从第二段起必须恰好比上一段小 1，且首段不能独占整串。
// 时间复杂度：O(n^2)，首段 O(n) 种切法、之后每步切点唯一；空间复杂度：O(n)，递归栈深度不超过段数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool splitString(string s) {  // s：待拆分的数字字符串
        auto dfs = [&](this auto&& dfs, int i, long long x) -> bool {  // 泛型递归 lambda：i 是当前切分起点，x 是上一段的值（-1 表示还没有上一段）
            if (i >= s.size()) {  // 已经切到串尾，说明这种拆分方式覆盖了所有字符
                return true;  // 找到一种合法拆分
            }  // 结束 if
            long long y = 0;  // 当前这一段累加出的数值，用 long long 避免溢出
            int r = x < 0 ? s.size() - 1 : s.size();  // 首段必须给后面留下数字，所以枚举上界要减一
            for (int j = i; j < r; ++j) {  // 逐位把 s[i..j] 拼成当前这一段的数值
                y = y * 10 + s[j] - '0';  // 十进制左移一位再累加新数字
                if (y > 1e10) {  // 数值超过 1e10 就不可能再和上一段相差 1，直接剪枝
                    break;  // 跳出内层枚举
                }  // 结束 if
                if ((x < 0 || x - y == 1) && dfs(j + 1, y)) {  // 首段无约束；否则要求上一段恰好比当前段大 1，然后递归切剩余部分
                    return true;  // 剩余部分也能切成功，整体即成功
                }  // 结束 if
            }  // 结束 for
            return false;  // 当前起点没有任何可行切法
        };  // 递归 lambda 定义结束
        return dfs(0, -1);  // 从下标 0 开始切，此时还没有上一段
    }  // 结束 splitString
};  // 结束 Solution 类
