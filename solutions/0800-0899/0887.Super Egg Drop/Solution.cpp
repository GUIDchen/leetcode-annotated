// 题目：887. 鸡蛋掉落（Super Egg Drop）
// 思路：f[i][j] 表示 j 个鸡蛋、i 层楼时确定答案所需的最少操作次数；在第一次扔的楼层上二分，取两侧代价最大值再加 1，并记忆化复用子问题。
// 时间复杂度：O(k * n * log n)，每个状态做一次二分；空间复杂度：O(k * n)，记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int superEggDrop(int k, int n) {  // k 个鸡蛋，n 层楼
        int f[n + 1][k + 1];  // 记忆化表：f[i][j] 为 j 个鸡蛋、i 层楼的最少操作次数
        memset(f, 0, sizeof(f));  // 全部清零，0 表示该状态还没算过
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 递归 lambda，C++23 的 this auto&& 让它能调用自身
            if (i < 1) {  // 0 层楼不需要操作
                return 0;  // 直接返回 0
            }  // 边界判断结束
            if (j == 1) {  // 只剩一个鸡蛋时只能从下往上逐层试
                return i;  // 最坏情况要试 i 次
            }  // 单蛋情形处理完毕
            if (f[i][j]) {  // 该状态已经算过，直接复用
                return f[i][j];  // 返回记忆化结果
            }  // 命中缓存的分支结束
            int l = 1, r = i;  // 在 1..i 层之间二分「第一次扔的楼层」
            while (l < r) {  // 二分查找最优的第一次扔的层次
                int mid = (l + r + 1) >> 1;  // 取上中点，避免死循环
                int a = dfs(mid - 1, j - 1);  // 碎了：用 j-1 个蛋去试下面 mid-1 层
                int b = dfs(i - mid, j);  // 没碎：仍用 j 个蛋去试上面 i-mid 层
                if (a <= b) {  // 碎了的代价不大于没碎的代价，说明还可以往更高层扔
                    l = mid;  // 把下界抬到 mid
                } else {  // 否则最优楼层在更低的区间
                    r = mid - 1;  // 把上界降到 mid-1
                }  // else 分支结束
            }  // 二分结束，l 就是最优楼层
            return f[i][j] = max(dfs(l - 1, j - 1), dfs(i - l, j)) + 1;  // 最坏情况取两侧最大值，再加本次这一扔，并写入缓存
        };  // 递归 lambda 定义结束
        return dfs(n, k);  // 从「k 个蛋、n 层楼」这个初始状态开始求解
    }  // 方法结束
};  // 类定义结束
