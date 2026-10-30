// 题目：3018. 可处理的最大删除操作数 I（Maximum Number of Removal Queries That Can Be Processed I）
// 思路：每轮只能删除数组两端，所以已删部分永远是「前缀 + 后缀」，剩余部分始终是一段连续区间 [i, j]。用 f[i][j] 表示已删掉 nums[0..i-1] 与 nums[j+1..n-1] 时最多能处理多少个查询，按区间从大到小递推，最后枚举唯一剩下的那个元素收尾。
// 时间复杂度：O(n²)，共 n² 个区间状态、每个 O(1) 转移；空间复杂度：O(n²)，需要一张 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumProcessableQueries(vector<int>& nums, vector<int>& queries) {  // nums 是可删除的数组，queries 是按顺序到来的查询值，返回能处理的最多查询数
        int n = nums.size();  // n：数组长度
        int f[n][n];  // f[i][j]：已删掉前缀 nums[0..i-1] 与后缀 nums[j+1..n-1] 时，最多已处理多少个查询
        memset(f, 0, sizeof(f));  // 整张表清 0：一个元素都没删时处理数为 0，非法状态也保持 0 以便直接参与 max 比较
        int m = queries.size();  // m：查询总数，也是答案能达到的上限
        for (int i = 0; i < n; ++i) {  // 按左端点 i 从小到大枚举剩余区间（i 等于已删掉的前缀长度）
            for (int j = n - 1; j >= i; --j) {  // 右端点 j 从 n-1 递减到 i，只枚举 [i, j] 合法的非空区间
                if (i > 0) {  // i > 0 才存在「刚删掉 nums[i-1]」这条转移路径
                    f[i][j] = max(f[i][j], f[i - 1][j] + (nums[i - 1] >= queries[f[i - 1][j]] ? 1 : 0));  // 从状态 f[i-1][j] 转移：若被删掉的 nums[i-1] 不小于当前待处理查询 queries[k]，就能多处理一个查询
                }  // if (i > 0) 结束
                if (j + 1 < n) {  // j+1 < n 才存在「刚删掉 nums[j+1]」这条转移路径
                    f[i][j] = max(f[i][j], f[i][j + 1] + (nums[j + 1] >= queries[f[i][j + 1]] ? 1 : 0));  // 从状态 f[i][j+1] 转移：同理，nums[j+1] 不小于待处理查询时处理数 +1
                }  // if (j + 1 < n) 结束
                if (f[i][j] == m) {  // 已经处理完全部 m 个查询，不可能更优，直接返回
                    return m;  // 返回上限 m
                }  // if (f[i][j] == m) 结束
            }  // 内层 j 循环结束
        }  // 外层 i 循环结束
        int ans = 0;  // ans 记录所有收尾方式里的最大值
        for (int i = 0; i < n; ++i) {  // 枚举最后唯一剩下的元素 nums[i]，它会被最后一次删除操作处理
            ans = max(ans, f[i][i] + (nums[i] >= queries[f[i][i]] ? 1 : 0));  // 在 f[i][i] 的基础上再判断 nums[i] 能否满足下一个查询，够大就 +1，取最大值
        }  // for 结束
        return ans;  // 返回最多能处理的查询数
    }  // 方法结束
};  // 题解类结束