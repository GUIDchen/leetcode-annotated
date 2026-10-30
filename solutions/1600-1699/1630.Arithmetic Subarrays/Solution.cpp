// 题目：1630. 等差子数组（Arithmetic Subarrays）
// 思路：对每个查询区间取最小/最大值算出公差，再用哈希集合验证等差数列的每一项是否都存在。
// 时间复杂度：O(q·k)，q 为查询个数、k 为区间长度；空间复杂度：O(k)，每个查询用哈希集合存区间元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {  // nums 是原数组，l/r 分别是各查询区间的左右端点（闭区间）
        vector<bool> ans;  // 保存每个查询区间的判定结果，true 表示该区间可以重排成等差数列
        auto check = [](vector<int>& nums, int l, int r) {  // 定义局部 lambda：单独判断 nums[l..r] 这一段是否等差
            unordered_set<int> s;  // 哈希集合，用于 O(1) 判断某个值是否出现在区间内
            int n = r - l + 1;  // 区间元素个数
            int a1 = 1 << 30, an = -a1;  // a1/an 记录区间最小值与最大值；1<<30 当足够大的哨兵，-a1 当足够小的哨兵
            for (int i = l; i <= r; ++i) {  // 遍历区间内每个元素，同时求出集合、最小值、最大值
                s.insert(nums[i]);  // 把当前元素放入集合
                a1 = min(a1, nums[i]);  // 维护区间最小值
                an = max(an, nums[i]);  // 维护区间最大值
            }  // 区间扫描结束
            if ((an - a1) % (n - 1)) {  // 首末差必须能被间隔数 n-1 整除，否则不可能构成连续等差数列
                return false;  // 除不尽，直接判定该区间不是等差子数组
            }  // if 结束
            int d = (an - a1) / (n - 1);  // 公差 d：等差数列相邻两项之差
            for (int i = 1; i < n; ++i) {  // 依次检查 a1, a1+d, ..., a1+(n-2)d 这 n 个项是否齐全
                if (!s.count(a1 + (i - 1) * d)) {  // 集合中缺少第 i 项，说明数值出现断层
                    return false;  // 缺少项即不连续，返回 false
                }  // if 结束
            }  // 循环结束
            return true;  // 所有项都命中集合，说明该区间是等差子数组
        };  // lambda 定义结束（分号表示这是一条 lambda 表达式语句）
        for (int i = 0; i < l.size(); ++i) {  // 遍历每一个查询区间 [l[i], r[i]]
            ans.push_back(check(nums, l[i], r[i]));  // 把该区间的判定结果追加到答案数组
        }  // 查询循环结束
        return ans;  // 按查询顺序返回全部判定结果
    }  // checkArithmeticSubarrays 方法结束
};  // 题解类定义结束