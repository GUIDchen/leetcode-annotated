// 题目：902. 最大为 N 的数字组合（Numbers At Most N Given Digit Set）
// 核心思路：数位 DP，从高位到低位枚举可填数字，lead 标记是否仍为前导零，limit 标记是否仍贴上界。
// 时间复杂度：O(len(N) * 10 * 2 * 2)，即状态数乘转移；空间复杂度：O(len(N)) 记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int atMostNGivenDigitSet(vector<string>& digits, int n) {  // digits：允许使用的数字字符；n：上界
        string s = to_string(n);  // 把上界转成字符串，便于逐位比较
        unordered_set<int> nums;  // 允许使用的数字集合（整数形式）
        for (auto& x : digits) {  // 把字符串形式的数字转成整数
            nums.insert(stoi(x));  // 存入集合，供 O(1) 查询
        }
        int m = s.size();  // 上界 N 的位数，也是 DP 的层数
        int f[m];  // 记忆化数组：f[i] 记录不贴界且无前导零时，从第 i 位起的方案数
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示尚未计算
        auto dfs = [&](this auto&& dfs, int i, bool lead, bool limit) -> int {  // 递归函数：处理第 i 位；lead 为是否仍全是前导零；limit 为是否受上界约束
            if (i >= m) {  // 已经填满所有位
                return lead ? 0 : 1;  // 全是前导零说明数字为空，不计入；否则这是一个合法方案
            }
            if (!lead && !limit && f[i] != -1) {  // 状态可以缓存且已经算过
                return f[i];  // 直接返回记忆化结果
            }
            int up = limit ? s[i] - '0' : 9;  // 当前位的上限：贴界只能取到 N 的这一位，否则可以取 9
            int ans = 0;  // 当前状态的方案数
            for (int j = 0; j <= up; ++j) {  // 枚举当前位填入的数字
                if (j == 0 && lead) {  // 仍然保持前导零，相当于这一位不填数字
                    ans += dfs(i + 1, true, limit && j == up);  // 前导零状态延续；只有贴界且取到上界时才继续贴界
                } else if (nums.count(j)) {  // 填一个允许使用的数字
                    ans += dfs(i + 1, false, limit && j == up);  // 离开前导零状态；同样只在贴界且取到上界时才继续贴界
                }
            }
            if (!lead && !limit) {  // 与上界无关且无前导零的状态才能安全缓存
                f[i] = ans;  // 记录记忆化结果
            }
            return ans;  // 返回当前状态的方案数
        };
        return dfs(0, true, true);  // 从最高位开始，初始有前导零且贴上界
    }
};
