// 题目：1340. 跳跃游戏 V（Jump Game V）
// 思路：记忆化 DFS（也可看作 DAG 上求最长路）。从每个下标出发，向左右各最多跳 d 步，遇到比自己高的柱子或超出距离就停止；f[i] 记忆「从 i 出发最多能访问多少个下标」，左右两侧取最大。
// 时间复杂度：O(n * d)，每个状态向两侧最多各看 d 步；空间复杂度：O(n)，记忆化数组加递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxJumps(vector<int>& arr, int d) {  // arr 是柱子高度数组，d 是单次跳跃的最大下标距离
        int n = arr.size();  // 下标个数
        int f[n];  // f[i] 记忆从 i 出发最多能访问的下标数量，0 表示还没算过
        memset(f, 0, sizeof(f));  // 记忆数组清零
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 记忆化 DFS；this auto&& 是显式对象参数写法，用于 lambda 自递归
            if (f[i]) {  // 已经算过就直接返回，避免重复搜索
                return f[i];  // 返回记忆的结果
            }  // 未计算分支结束
            int ans = 1;  // 至少能访问自己这一个下标
            for (int j = i - 1; j >= 0; --j) {  // 向左尝试跳跃
                if (i - j > d || arr[j] >= arr[i]) {  // 超出跳跃距离，或遇到不低于当前高度的柱子，再往左也走不了，直接跳出
                    break;  // 停止向左扩展
                }  // 判断结束
                ans = max(ans, 1 + dfs(j));  // 跳到 j 后还能继续走，取更长的路径
            }  // 向左枚举结束
            for (int j = i + 1; j < n; ++j) {  // 向右尝试跳跃
                if (j - i > d || arr[j] >= arr[i]) {  // 同样：超出 d 步或遇到不低于自己的柱子就停止
                    break;  // 停止向右扩展
                }  // 判断结束
                ans = max(ans, 1 + dfs(j));  // 从 j 继续走，取更长的路径
            }  // 向右枚举结束
            return f[i] = ans;  // 把结果写进记忆数组并返回
        };  // lambda 结束
        int ans = 1;  // 答案至少为 1
        for (int i = 0; i < n; ++i) {  // 枚举每个可能的起点
            ans = max(ans, dfs(i));  // 用从 i 出发的最长路径更新答案
        }  // 起点枚举结束
        return ans;  // 返回最多能访问的下标个数
    }  // 方法结束
};  // 类定义结束
