// 题目：2698. 求一个整数的惩罚数（Find the Punishment Number of an Integer）
// 核心思路：枚举 i = 1..n，把 i*i 的十进制串做 DFS 枚举所有切分方式；若存在一种切分使各段之和等于 i，则 i 是惩罚数，把 i*i 累加进答案。
// 时间复杂度：O(n * 2^k)，k 为平方数的位数（k <= 7），每位数之间都可能断开；空间复杂度：O(k)，递归深度等于位数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int punishmentNumber(int n) {  // n：上界；返回 1..n 中所有惩罚数的平方和
        int ans = 0;  // ans：累加所有满足条件的 i*i
        for (int i = 1; i <= n; ++i) {  // 逐个枚举候选数 i
            int x = i * i;  // 候选平方数，若它是惩罚数就要把它加进答案
            string s = to_string(x);  // 转成字符串，方便枚举切分位置
            if (check(s, 0, i)) {  // 判断这个平方数的十进制表示能否切成若干段、各段之和恰好等于 i
                ans += x;  // 是惩罚数，把平方累加进答案
            }
        }
        return ans;  // 返回所有惩罚数的平方和
    }

    // DFS 回溯：在串 s 上从下标 i 开始切，还需要凑出剩余和 x
    bool check(const string& s, int i, int x) {  // s：平方数的字符串；i：当前切分起点；x：剩余还需要凑出的和
        int m = s.size();  // 串长
        if (i >= m) {  // 已经切到字符串末尾，说明所有字符都分配完了
            return x == 0;  // 剩余和恰好为 0 才是合法切分
        }
        int y = 0;  // y：当前这一段的数值，从 0 开始累加
        for (int j = i; j < m; ++j) {  // 枚举这一段的结束下标 j，段内容就是 s[i..j]
            y = y * 10 + s[j] - '0';  // 逐位把 s[i..j] 变成一个整数
            if (y > x) {  // 这一段已经超过剩余和，再往后拼只会更大
                break;  // 剪枝：不必继续延长这一段
            }
            if (check(s, j + 1, x - y)) {  // 递归处理剩下的后缀，剩余和减去当前段
                return true;  // 只要找到一种成功切分即可提前结束
            }
        }
        return false;  // 所有切法都失败
    }
};