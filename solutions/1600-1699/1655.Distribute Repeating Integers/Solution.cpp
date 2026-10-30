// 题目：1655. 分配重复整数（Distribute Repeating Integers）
// 思路：状压 DP：先预处理 quantity 每个子集的需求总和 s[mask]，再把 nums 按值聚合成每种数字的可用个数，f[i][j] 表示用前 i+1 种数字能否满足顾客集合 j，枚举 j 的子集做转移。
// 时间复杂度：O(n·3^m)，m 为顾客数（≤10）；空间复杂度：O(n·2^m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {  // nums 是可分配的数字，quantity 是每个顾客需要的个数
        int m = quantity.size();  // 顾客数量，决定状压位数
        int s[1 << m];  // s[mask]：需求集合 mask 中的需求量总和
        memset(s, 0, sizeof(s));  // 全部清零
        for (int i = 1; i < 1 << m; ++i) {  // 枚举除空集外的每个需求子集
            for (int j = 0; j < m; ++j) {  // 找 mask 中最低的一个置位
                if (i >> j & 1) {  // 该位存在，可以用去掉它的子集递推
                    s[i] = s[i ^ (1 << j)] + quantity[j];  // 去掉这一位后的需求总和，再加该顾客的需求
                    break;  // 只用最低位递推一次，避免重复累加
                }  // 判断结束
            }  // 内层枚举结束
        }  // 子集需求预处理结束
        unordered_map<int, int> cnt;  // 统计 nums 中每个值出现的次数
        for (int& x : nums) {  // 遍历所有数字
            ++cnt[x];  // 对应计数加一
        }  // 统计结束
        int n = cnt.size();  // 不同数字的种类数
        vector<int> arr;  // 把每种数字的可用个数压成数组
        for (auto& [_, x] : cnt) {  // 结构化绑定：_ 是键（数值本身，用不上），x 是出现次数
            arr.push_back(x);  // 收集可用个数
        }  // 收集结束
        bool f[n][1 << m];  // f[i][j]：用前 i+1 种数字能否满足顾客集合 j
        memset(f, 0, sizeof(f));  // 全部初始化为 false
        for (int i = 0; i < n; ++i) {  // 任意前 i 种数字都能满足空需求集合
            f[i][0] = true;  // 空集合恒为真
        }  // 初始化结束
        for (int i = 0; i < n; ++i) {  // 逐种数字做转移
            for (int j = 1; j < 1 << m; ++j) {  // 枚举非空的需求集合
                if (i && f[i - 1][j]) {  // 前一种数字已经能满足 j，直接继承，不必动用当前数字
                    f[i][j] = true;  // 继承成功状态
                    continue;  // 跳过当前数字
                }  // 判断结束
                for (int k = j; k; k = (k - 1) & j) {  // 枚举 j 的所有非空子集 k，(k-1)&j 是标准的降序子集枚举写法
                    bool ok1 = i == 0 ? j == k : f[i - 1][j ^ k];  // 剩余集合 j^k 要么为空（i==0 时只能一次满足），要么由前 i-1 种数字满足
                    bool ok2 = s[k] <= arr[i];  // 子集 k 的总需求量不能超过当前数字的可用个数
                    if (ok1 && ok2) {  // 两个条件同时成立，说明当前数字可以接下子集 k
                        f[i][j] = true;  // 记录可行状态
                        break;  // 找到一种拆法就够了
                    }  // 判断结束
                }  // 子集枚举结束
            }  // 集合枚举结束
        }  // 数字枚举结束
        return f[n - 1][(1 << m) - 1];  // 所有数字用完后能否满足全部顾客
    }  // 方法结束
};  // Solution 类定义结束