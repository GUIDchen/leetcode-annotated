// 题目：3149. 找出分数最低的排列（Find the Minimum Cost Array Permutation）
// 思路：状压 DP，f[mask][pre] 表示「已选集合为 mask、排列末尾为 pre」时补全排列的最小代价；再沿最优边回溯出具体排列。
// 时间复杂度：O(2^n * n^2)，共 2^n * n 个状态、每个状态枚举 n 个后继；空间复杂度：O(2^n * n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findPermutation(vector<int>& nums) {  // nums：输入数组；返回分数最低的排列
        int n = nums.size();  // 排列长度
        vector<int> ans;  // 保存最终答案排列
        int f[1 << n][n];  // 记忆化数组：f[mask][pre] 表示状态 (mask, pre) 的最小剩余代价
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该状态尚未计算过
        function<int(int, int)> dfs = [&](int mask, int pre) {  // 返回从状态 (mask, pre) 补全排列所需的最小代价
            if (mask == (1 << n) - 1) {  // 所有位置都已选完
                return abs(pre - nums[0]);  // 收尾：末尾元素要与 nums[0] 相邻，代价为两者之差的绝对值
            }
            int* res = &f[mask][pre];  // 取该状态在记忆化数组中的地址，后面读写都走这个指针
            if (*res != -1) {  // 该状态已经算过，直接复用结果
                return *res;  // 返回缓存的最小代价
            }
            *res = INT_MAX;  // 先置为无穷大，便于后面取 min
            for (int cur = 1; cur < n; ++cur) {  // 枚举下一个可选的元素；0 固定排首位，所以从 1 开始
                if (mask >> cur & 1 ^ 1) {  // 第 cur 位为 0 表示 cur 还没被使用（^ 1 即把最低位取反）
                    *res = min(*res, abs(pre - nums[cur]) + dfs(mask | 1 << cur, cur));  // 选 cur：累加相邻代价并递归求解剩余部分，取更小者
                }
            }
            return *res;  // 返回该状态的最小代价
        };  // dfs 记忆化搜索结束
        function<void(int, int)> g = [&](int mask, int pre) {  // 依据 dfs 的最优值回溯，构造出具体排列
            ans.push_back(pre);  // 当前元素确定放在这一位，写入答案
            if (mask == (1 << n) - 1) {  // 所有元素都已摆放完毕
                return;  // 构造完成，结束递归
            }
            int res = dfs(mask, pre);  // 取当前状态的最优值，用于判断哪个后继是最优的
            for (int cur = 1; cur < n; ++cur) {  // 按从小到大枚举候选后继，保证得到的排列字典序最小
                if (mask >> cur & 1 ^ 1) {  // cur 尚未被使用
                    if (abs(pre - nums[cur]) + dfs(mask | 1 << cur, cur) == res) {  // 该后继正好能取到最优值，说明它位于某条最优路径上
                        g(mask | 1 << cur, cur);  // 沿这条最优边继续向下构造
                        break;  // 只需要一条最优路径，找到即可退出枚举
                    }
                }
            }
        };  // 构造器结束
        g(1, 0);  // 0 已固定在首位：mask=1、pre=0，开始构造
        return ans;  // 返回最小代价对应的排列
    }
};