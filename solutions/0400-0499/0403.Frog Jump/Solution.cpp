// 题目：403. 青蛙过河（Frog Jump）
// 思路：记忆化 DFS。状态是「站在第 i 块石头上、上一步跳了 k 步」，下一步只能跳 k-1、k、k+1 步；用值到下标映射 O(1) 判断落点是不是石头，用二维数组 f 记忆结果。
// 时间复杂度：O(n^2)，状态数 n*n、每个状态只枚举 3 种步长；空间复杂度：O(n^2)，记忆化表大小 n*n。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    bool canCross(vector<int>& stones) {  // 判断青蛙能否从第 0 块石头跳到最后一块石头
        int n = stones.size();  // n 是石头个数
        vector<vector<int>> f(n, vector<int>(n, -1));  // 记忆化表 f[i][k]：在第 i 块石头、上次跳了 k 步时的结果（-1 未算，0 不可达，1 可达）
        unordered_map<int, int> pos;  // 值 -> 下标 的映射，用来 O(1) 判断某个位置有没有石头
        for (int i = 0; i < n; ++i) {  // 遍历所有石头建立映射
            pos[stones[i]] = i;  // 记录石头位置对应的下标
        }
        function<bool(int, int)> dfs = [&](int i, int k) -> bool {  // 定义递归函数：当前在 i 号石头，上一步跳了 k 步
            if (i == n - 1) {  // 已经站到最后一块石头上，说明这条路径成功
                return true;  // 返回成功
            }
            if (f[i][k] != -1) {  // 该状态算过就直接复用，避免重复搜索
                return f[i][k];  // 返回历史结果
            }
            for (int j = k - 1; j <= k + 1; ++j) {  // 下一步只能跳 k-1、k、k+1 步
                if (j > 0 && pos.count(stones[i] + j) && dfs(pos[stones[i] + j], j)) {  // 步长必须为正、落点必须是石头、且从落点继续能到终点
                    return f[i][k] = true;  // 三条都满足就记为成功；赋值表达式的结果就是 true
                }
            }
            return f[i][k] = false;  // 三种步长都失败，记为不可达并返回
        };
        return dfs(0, 0);  // 从第 0 块石头、上一步步长 0 开始搜索
    }
};  // 题解类结束