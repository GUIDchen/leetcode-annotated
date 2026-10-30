// 题目：1406. 石子游戏 III（Stone Game III）
// 思路：记忆化搜索，f[i] 表示从下标 i 开始行动的人能获得的最大「分差」；枚举本轮取 1~3 堆，转移为 sum - dfs(j+1)，最后按分差正负判定胜负。
// 时间复杂度：O(n)，每个状态只算一次且转移常数次；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string stoneGameIII(vector<int>& stoneValue) {  // stoneValue 为每堆石子的数量
        int n = stoneValue.size();  // 堆数
        vector<int> f(n, INT_MIN);  // 记忆化数组，INT_MIN 表示该状态尚未计算

        auto dfs = [&](auto&& dfs, int i) -> int {  // 泛型递归 lambda：第一个参数传自身以便递归调用
            if (i >= n) {  // 石子已取完，无法再得分
                return 0;  // 边界状态的分差为 0
            }  // 边界判断结束

            if (f[i] != INT_MIN) {  // 命中记忆化结果
                return f[i];  // 直接返回，避免重复计算
            }  // 记忆化命中结束

            int ans = INT_MIN;  // 当前状态下能取得的最大分差
            int s = 0;  // 本轮已取石子的累计数量

            for (int j = i; j < i + 3 && j < n; j++) {  // 本轮最多取 3 堆，且不能越界
                s += stoneValue[j];  // 累加本轮拿到的石子
                ans = max(ans, s - dfs(dfs, j + 1));  // 本轮得分减去对手后续最优分差
            }  // 枚举结束

            return f[i] = ans;  // 写入记忆化数组并返回
        };  // dfs 定义结束

        int res = dfs(dfs, 0);  // 先手（Alice）从 0 开始的最优分差

        if (res == 0) {  // 分差为 0 表示双方得分相同
            return "Tie";  // 平局
        }  // 平局分支结束
        return res > 0 ? "Alice" : "Bob";  // 分差为正 Alice 胜，否则 Bob 胜
    }  // stoneGameIII 方法结束
};  // Solution 类结束
