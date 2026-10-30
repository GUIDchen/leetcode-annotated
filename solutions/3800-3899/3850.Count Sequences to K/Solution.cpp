// 3850. 统计结果等于 K 的序列数目 / Count Sequences to K（困难）
// 核心思路：把元素逐个放进分子或分母（也可都不放），全程保持最简分数并记忆化搜索，最终约分为整数 k 即为一种方案。
// 复杂度：时间 O(n·S)，空间 O(S)，S 为不同 (下标, 分子, 分母) 状态数。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口与搜索所需的状态
    int n;  // 数组长度
    long long k;  // 目标值 k
    vector<int>* nums;  // 指向输入数组，供 dfs 递归使用
    map<tuple<int, long long, long long>, int> f;  // 记忆化表：状态 (下标, 分子, 分母) 到方案数的映射

    int countSequences(vector<int>& nums, long long k) {  // 返回按规则计算后结果恰好等于 k 的序列数目
        this->nums = &nums;  // 保存数组地址供 dfs 使用
        this->n = nums.size();  // 记录数组长度
        this->k = k;  // 记录目标值
        f.clear();  // 每次调用前清空记忆化表
        return dfs(0, 1LL, 1LL);  // 从下标 0、分子分母均为 1 开始搜索
    }  // countSequences 方法结束

    int dfs(int i, long long p, long long q) {  // 处理到下标 i 时，当前结果为最简分数 p / q
        if (i == n) {  // 所有元素处理完毕
            return (p == k && q == 1LL) ? 1 : 0;  // 结果恰为整数 k 时计 1 种方案
        }  // 递归出口结束

        auto key = make_tuple(i, p, q);  // 组合当前状态作为记忆化键
        if (f.count(key)) return f[key];  // 命中缓存直接返回

        int res = dfs(i + 1, p, q);  // 选择一：不把 nums[i] 计入分子或分母

        long long x = (*nums)[i];  // 取出当前元素

        long long g1 = gcd(p * x, q);  // 把 x 乘到分子后与分母的最大公约数
        res += dfs(i + 1, (p * x) / g1, q / g1);  // 选择二：把 x 计入分子，并按最大公约数约分

        long long g2 = gcd(p, q * x);  // 把 x 乘到分母后与分子的最大公约数
        res += dfs(i + 1, p / g2, (q * x) / g2);  // 选择三：把 x 计入分母，并按最大公约数约分

        f[key] = res;  // 记录当前状态的方案数
        return res;  // 返回该状态的方案数
    }  // dfs 方法结束
};  // 解题类定义结束
