// 题目：2209. 用地毯覆盖后的最少白色砖块（Minimum White Tiles After Covering With Carpets）
// 核心思路：记忆化搜索。f(i, j) 表示从位置 i 起、还剩 j 块地毯时的最少剩余白砖；
//           每遇到一块白砖可选择「放弃它」或「用一块地毯覆盖 [i, i+carpetLen)」，两者取小；黑砖直接跳过。
// 时间复杂度：O(n * numCarpets)，每个状态只算一次；空间复杂度：O(n * numCarpets)，记忆化表加 O(n) 前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {  // floor 是地板串，numCarpets 是地毯数，carpetLen 是每块地毯的长度
        int n = floor.size();  // 地板的总长度
        vector<vector<int>> f(n, vector<int>(numCarpets + 1, -1));  // 记忆化表：-1 表示该状态尚未计算
        vector<int> s(n + 1);  // 前缀和数组：s[i] 表示 floor[0..i-1] 里白砖 '1' 的个数
        for (int i = 0; i < n; ++i) {  // 逐格扫描地板
            s[i + 1] = s[i] + (floor[i] == '1');  // 遇到白砖前缀和多加 1，黑砖加 0
        }
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // C++23 显式对象参数：把自身作为 dfs 传入，实现递归 lambda；i 是当前位置，j 是剩余地毯数
            if (i >= n) {  // 已经越界到地板末尾，后面没有砖块
                return 0;  // 剩余白砖数为 0
            }
            if (j == 0) {  // 地毯已经用完，没法再覆盖
                return s[n] - s[i];  // 区间 [i, n) 的白砖数由前缀和之差给出
            }
            if (f[i][j] != -1) {  // 该状态之前算过
                return f[i][j];  // 直接复用记忆化结果
            }
            if (s[i + 1] == s[i]) {  // 位置 i 是黑砖 '0'，覆盖它没有任何收益
                return dfs(i + 1, j);  // 直接右移一格，地毯数量不变
            }
            int ans = min(1 + dfs(i + 1, j), dfs(i + carpetLen, j - 1));  // 两种选择取小：放弃这块白砖（计数 +1 并右移），或用一块地毯覆盖 [i, i+carpetLen)
            f[i][j] = ans;  // 记录当前状态的最优值，避免重复搜索
            return ans;  // 返回当前状态的最优解
        };  // 递归 lambda 定义结束
        return dfs(0, numCarpets);  // 从位置 0 出发、手上有 numCarpets 块地毯，求解答案
    }
};
